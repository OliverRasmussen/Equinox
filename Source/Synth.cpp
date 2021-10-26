/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    Synth.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "Synth.h"

Synth::Synth(voiceType synthVoiceType)
{
    _voiceType = synthVoiceType;
}

Synth::~Synth()
{
    clearSounds();
    clearVoices();
}

void Synth::prepare(dsp::ProcessSpec& spec)
{
    notesHeldDown.clear();
    
    setCurrentPlaybackSampleRate(spec.sampleRate);
    
    for (auto* voice : voices)
    {
        if (auto v = dynamic_cast<OscSynthVoice*>(voice))
        {
            v->prepareVoice(spec);
        }
        else if (auto v = dynamic_cast<SampleSynthVoice*>(voice))
        {
            v->prepareVoice(spec);
        }
    }
}

void Synth::addVoices(int voicesToAdd)
{
    clearAllCurrentNotes();
    clearVoices();
    notesHeldDown.clear();
    
    bool monophonic = voicesToAdd == 1 ? true : false;
    
    if (_voiceType == voiceType::oscillator)
    {
        for (int i = 0; i < voicesToAdd; i++)
        {
            addVoice(new OscSynthVoice(monophonic));
        }
        clearSounds();
        addSound(new OscSynthSound());
    }
    else if (_voiceType == voiceType::sampler)
    {
        for (int i = 0; i < voicesToAdd; i++)
        {
            addVoice(new SampleSynthVoice(monophonic));
        }
    }
}

void Synth::clearAllCurrentNotes()
{
    for (auto* voice : voices)
    {
        if (auto v = dynamic_cast<OscSynthVoice*>(voice))
        {
            v->clearCurrentNote();
        }
        else if (auto v = dynamic_cast<SampleSynthVoice*>(voice))
        {
            v->clearCurrentNote();
        }
    }
}

void Synth::noteOn (const int midiChannel, const int midiNoteNumber, const float velocity)
{
    const ScopedLock sl (lock);

    for (auto* sound : sounds)
    {
        if (sound->appliesToNote (midiNoteNumber) && sound->appliesToChannel (midiChannel))
        {
            if(!monoEnabled())
            {
                for (auto* voice : voices)
                    if (voice->getCurrentlyPlayingNote() == midiNoteNumber && voice->isPlayingChannel (midiChannel))
                        stopVoice (voice, 1.0f, true);
                
            }
            startVoice (findFreeVoice (sound, midiChannel, midiNoteNumber, isNoteStealingEnabled()),
                        sound, midiChannel, midiNoteNumber, velocity);

        }
    }
}

void Synth::noteOff (const int midiChannel, const int midiNoteNumber, const float velocity, const bool allowTailOff)
{
    const ScopedLock sl (lock);

    for (auto* voice : voices)
    {
        if ((voice->getCurrentlyPlayingNote() == midiNoteNumber
              && voice->isPlayingChannel (midiChannel)))
        {
            if (auto sound = voice->getCurrentlyPlayingSound())
            {
                if (sound->appliesToNote (midiNoteNumber)
                     && sound->appliesToChannel (midiChannel))
                {

                    if (!monoEnabled() || notesHeldDown.size() == 0)
                    {
                        voice->setKeyDown (false);
                    }

                    if (! (voice->isSustainPedalDown() || voice->isSostenutoPedalDown()))
                    {
                        stopVoice (voice, velocity, allowTailOff);
                    }
                }
            }
        }
    }
}

SynthesiserVoice* Synth::findFreeVoice (SynthesiserSound* soundToPlay, int midiChannel, int midiNoteNumber, const bool stealIfNoneAvailable) const
{
    const ScopedLock sl (lock);

    for (auto* voice : voices)
        if (((!voice->isVoiceActive()) && voice->canPlaySound (soundToPlay)) || monoEnabled())
            return voice;

    if (stealIfNoneAvailable)
        return findVoiceToSteal (soundToPlay, midiChannel, midiNoteNumber);

    return nullptr;
}

void Synth::handleMidiEvent(const MidiMessage& m)
{
    const int channel = m.getChannel();
    
    if (m.isNoteOn())
    {
        if (monoEnabled())
        {
            notesHeldDown.add(m);
        }
        noteOn (channel, m.getNoteNumber(), m.getFloatVelocity());
    }
    else if (m.isNoteOff())
    {
        if (monoEnabled())
        {
            if (notesHeldDown.size() > 1)
            {
                const int noteNumberToRemove = m.getNoteNumber();
                
                    for (int i = 0; i < notesHeldDown.size(); ++i)
                    {
                        if (notesHeldDown[i].getNoteNumber() == noteNumberToRemove)
                        {
                            int lastInList = notesHeldDown.getLast().getNoteNumber();

                            if (noteNumberToRemove == lastInList)
                            {
                                notesHeldDown.removeLast(1);
                                const MidiMessage previousNote = notesHeldDown.getLast();
                                noteOn (previousNote.getChannel(), previousNote.getNoteNumber(), previousNote.getFloatVelocity());
                                return;
                            }
                            else
                            {
                                notesHeldDown.remove(i);
                            }
                        }
                    }
            }
            else
            {
                notesHeldDown.clear();
            }
        }
        noteOff (channel, m.getNoteNumber(), m.getFloatVelocity(), true);
    }
    else if (m.isAllNotesOff() || m.isAllSoundOff())
    {
        allNotesOff (channel, true);
    }
    else if (m.isPitchWheel())
    {
        const int wheelPos = m.getPitchWheelValue();
        lastPitchWheelValues [channel - 1] = wheelPos;
        handlePitchWheel (channel, wheelPos);
    }
    else if (m.isAftertouch())
    {
        handleAftertouch (channel, m.getNoteNumber(), m.getAfterTouchValue());
    }
    else if (m.isChannelPressure())
    {
        handleChannelPressure (channel, m.getChannelPressureValue());
    }
    else if (m.isController())
    {
        handleController (channel, m.getControllerNumber(), m.getControllerValue());
    }
    else if (m.isProgramChange())
    {
        handleProgramChange (channel, m.getProgramChangeNumber());
    }
}

bool Synth::monoEnabled() const
{
    return getNumVoices() == 1;
}

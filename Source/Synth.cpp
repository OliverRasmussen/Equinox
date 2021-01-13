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

Synth::Synth()
{
    
}

Synth::~Synth()
{
    
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
            const int noteNumberToRemove = m.getNoteNumber();
            
                for (int i = 0; i < notesHeldDown.size(); ++i)
                {
                    if (notesHeldDown[i].getNoteNumber() == noteNumberToRemove)
                    {
                        int lastInList = notesHeldDown.getLast().getNoteNumber();

                        if (noteNumberToRemove == lastInList)
                        {
                            notesHeldDown.removeLast(1);
                            if (notesHeldDown.size() > 0)
                            {
                                const MidiMessage previousNote = notesHeldDown.getLast();
                                noteOn (previousNote.getChannel(), previousNote.getNoteNumber(), previousNote.getFloatVelocity());
                            }
                        }
                        else
                        {
                            notesHeldDown.remove(i);
                        }
                    }
                }
            
            if (!notesHeldDown.isEmpty())
            {
                return;
            }
        }
        else
        {
            notesHeldDown.clear();
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

/*
  ==============================================================================

    Synth.cpp
    Created: 15 May 2020 8:12:53pm
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

void Synth::handleMidiEvent(const MidiMessage& m)
{
    if (getNumVoices() == 1)
    {
        const int channel = m.getChannel();
        
        if (m.isNoteOn())
        {
            notesHeldDown.add(m);
            noteOn(channel, m.getNoteNumber(), m.getFloatVelocity());
        }
        else if (m.isNoteOff())
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
            noteOff(channel, m.getNoteNumber(), m.getVelocity(), true);
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
    else
    {
        if (m.isNoteOff())
        {
            notesHeldDown.clear();
        }
        // Using Synthesisers implementation of handleMidiEvent if theres more than one voice
        Synthesiser::handleMidiEvent(m);
    }
}

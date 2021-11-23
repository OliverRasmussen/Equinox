/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    OscSynthVoice.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "OscSynthVoice.h"

OscSynthVoice::OscSynthVoice(bool isMonoVoice) : SynthVoice(isMonoVoice)
{
}

OscSynthVoice::~OscSynthVoice(){}

void OscSynthVoice::prepareVoice(dsp::ProcessSpec& spec)
{
    SynthVoice::prepareVoice(spec);
}

bool OscSynthVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<const OscSynthSound*>(sound) != nullptr;
}

void OscSynthVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    if (dynamic_cast<const OscSynthSound*> (sound))
    {
        if (!noteHasBeenTriggered)
        {
            oscillator1.setPhase(phase);
            oscillator2.setPhase(phase + (getRandomAnalogValue(true) / 100));
        }
        setFrequencyByMidiNote(midiNoteNumber);
        SynthVoice::startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    }

}

void OscSynthVoice::setPhase(float phase)
{
    this->phase = phase;
}

float OscSynthVoice::getPhase() const
{
    return phase;
}

void OscSynthVoice::setWaveform(float* selectedWaveform)
{
    oscillator1.setWaveform(static_cast<WavetableOscillator::Waveform>(*selectedWaveform));
    oscillator2.setWaveform(static_cast<WavetableOscillator::Waveform>(*selectedWaveform));
}

double OscSynthVoice::getNextOscillatorSample(int channel)
{
    double nextSample = 0;
    
    if (channel == 0)
    {
        nextSample = oscillator1.getNextSample(getFrequency());
    }
    else
    {
        nextSample = oscillator2.getNextSample(getDetune() ? getFrequency() * getDetune() : getFrequency());
    }
    return nextSample;
}


void OscSynthVoice::renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if (isVoiceActive())
    {
        voiceBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
        voiceBuffer.clear();
        
        for (int sample = 0; sample < voiceBuffer.getNumSamples(); ++sample)
        {
            for (int channel = 0; channel < voiceBuffer.getNumChannels(); ++channel)
            {
                voiceBuffer.addSample (channel, sample, getNextOscillatorSample(channel));
            }
        }
        addBufferToOutput (voiceBuffer, outputBuffer, startSample, numSamples);
    }
}

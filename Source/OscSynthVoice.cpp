/*
  ==============================================================================

    OscSynthVoice.cpp
    Created: 4 Apr 2020 5:13:23pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "OscSynthVoice.h"

OscSynthVoice::OscSynthVoice(bool isMonoVoice) : SynthVoice(isMonoVoice)
{
}

OscSynthVoice::~OscSynthVoice(){}


bool OscSynthVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<const OscSynthSound*>(sound) != nullptr;
}

void OscSynthVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    if (dynamic_cast<const OscSynthSound*> (sound))
    {
        // Resetting the two oscillators
        oscillator1.phaseReset(0);
        oscillator2.phaseReset(0);
        setFrequencyByMidiNote(midiNoteNumber);
        SynthVoice::startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    }
    else
    {
        jassertfalse;
    }

}

// used for setting the currentWaveform
void OscSynthVoice::setWaveform(float* selectedWaveform)
{
    currentWaveform = static_cast<int>(*selectedWaveform);
}


// Returns a oscillated waveform from the passed in oscillator and frequency
double OscSynthVoice::getWaveform(maxiOsc& oscillator, double frequency)
{
    double waveform;
    switch (currentWaveform)
    {
        case 0:
            waveform = oscillator.sinewave(frequency);
            break;
        case 1:
            waveform = oscillator.sawn(frequency);
            break;
        case 2:
            waveform = oscillator.square(frequency);
            break;
        case 3:
            waveform = oscillator.triangle(frequency);
            break;
        case 4:
            waveform = oscillator.noise();
            break;
        default:
            waveform = oscillator.sinewave(frequency);
            break;
    }
    return waveform;
}

double OscSynthVoice::getOscillator(int channel)
{
    return (channel == 0) ? getWaveform(oscillator1, getFrequency()) : (getDetune()) ? getWaveform(oscillator2, getFrequency() * getDetune()) : getWaveform(oscillator2, getFrequency());
}


void OscSynthVoice::renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    getAmpEnvelope().setParameters();
    getFilterEnvelope().setParameters();

    if (isVoiceActive())
    {
        voiceStoppedPlaying = false;
        jassert (numSamples <= voiceBuffer.getNumSamples());
        AudioBuffer<float> proxyBuffer (voiceBuffer.getArrayOfWritePointers(), voiceBuffer.getNumChannels(), startSample, numSamples);
        proxyBuffer.clear();
        
        for (int sample = 0; sample < proxyBuffer.getNumSamples(); ++sample)
        {
            for (int channel = 0; channel < proxyBuffer.getNumChannels(); ++channel)
            {
                proxyBuffer.addSample (channel, sample, getOscillator(channel));
            }
        }
        addBufferToOutput (proxyBuffer, outputBuffer, startSample, numSamples);
    }
    else
    {
        voiceStoppedPlaying = true;
    }
    
    if (noteHasBeenTriggered && !getAmpEnvelope().isActive())
    {
        stopNote(0.0f, false);
    }
}

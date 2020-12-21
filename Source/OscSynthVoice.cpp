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

void OscSynthVoice::prepareVoice(double sampleRate, int samplesPerBlock, int numChannels, dsp::ProcessSpec& spec)
{
    WavetableOscillator::prepare(sampleRate);
    SynthVoice::prepareVoice(sampleRate, samplesPerBlock, numChannels, spec);
}

bool OscSynthVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<const OscSynthSound*>(sound) != nullptr;
}

void OscSynthVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    if (dynamic_cast<const OscSynthSound*> (sound))
    {
        if (!isMonoEnabled())
        {
            oscillator1.setPhase(0);
            oscillator2.setPhase(0);            
        }
        setFrequencyByMidiNote(midiNoteNumber);
        SynthVoice::startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    }

}

// used for setting the currentWaveform
void OscSynthVoice::setWaveform(float* selectedWaveform)
{
    currentWaveform = static_cast<int>(*selectedWaveform);
}


// Returns a oscillated waveform from the passed in oscillator and frequency
double OscSynthVoice::getWaveform(WavetableOscillator& osc, double frequency)
{
    double waveform;
    switch (currentWaveform)
    {
        case 0:
            waveform = osc.sine(frequency);
            break;
        case 1:
            waveform = osc.saw(frequency);
            break;
        case 2:
            waveform = osc.triangle(frequency);
            break;
        case 3:
            waveform = osc.square(frequency);
            break;
        case 4:
            waveform = osc.noise();
            break;
        default:
            waveform = osc.sine(frequency);
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
    if (isVoiceActive())
    {
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
}

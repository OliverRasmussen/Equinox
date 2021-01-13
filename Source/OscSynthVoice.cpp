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

void OscSynthVoice::setWaveform(float* selectedWaveform)
{
    currentWaveform = static_cast<int>(*selectedWaveform);
}

double OscSynthVoice::getNextOscillatorSample(int channel)
{
    double nextSample = 0;
    double frequency;
    WavetableOscillator* oscPtr = nullptr;
    
    if (channel == 0)
    {
        oscPtr = &oscillator1;
        frequency = getFrequency();
    }
    else
    {
        oscPtr = &oscillator2;
        frequency = getDetune() ? getFrequency() * getDetune() : getFrequency();
    }
    
    if (oscPtr != nullptr)
    {
        switch (currentWaveform)
        {
            case 0:
                nextSample = oscPtr->sine(frequency);
                break;
            case 1:
                nextSample = oscPtr->saw(frequency);
                break;
            case 2:
                nextSample = oscPtr->triangle(frequency);
                break;
            case 3:
                nextSample = oscPtr->square(frequency);
                break;
            case 4:
                nextSample = oscPtr->noise();
                break;
            default:
                nextSample = oscPtr->sine(frequency);
                break;
        }
    }
    return nextSample;
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
                proxyBuffer.addSample (channel, sample, getNextOscillatorSample(channel));
            }
        }
        addBufferToOutput (proxyBuffer, outputBuffer, startSample, numSamples);
    }
}

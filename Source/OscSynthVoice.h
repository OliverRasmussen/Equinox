/*
  ==============================================================================

    OscSynthVoice.h
    Created: 4 Apr 2020 5:13:23pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "SynthVoice.h"
#include "OscSynthSound.h"
#include "WavetableOscillator.h"

class OscSynthVoice : public SynthVoice
{
public:
    
    OscSynthVoice(bool isMonoVoice);
    
    ~OscSynthVoice() override;
    
    void prepareVoice(double sampleRate, int samplesPerBlock, int numChannels, dsp::ProcessSpec&) override;
    
    bool canPlaySound (SynthesiserSound*) override;
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    void setWaveform(float* selectedWaveform);
    
private:
    
    double getWaveform(WavetableOscillator& osc, double frequency);
    
    double getOscillator(int channel);
    
    int currentWaveform;
    
    int dummy = 0;
    
    WavetableOscillator oscillator1, oscillator2;
};

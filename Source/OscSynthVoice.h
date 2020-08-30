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
#include "maximilian.h"

class OscSynthVoice : public SynthVoice
{
public:
    
    OscSynthVoice(bool isMonoVoice);
    
    ~OscSynthVoice() override;
    
    bool canPlaySound (SynthesiserSound*) override;
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    void setWaveform(float* selectedWaveform);
    
private:
    
    double getWaveform(maxiOsc& oscillator, double frequency);
    
    double getOscillator(int channel);
    
    int currentWaveform;
    
    maxiOsc oscillator1;
    maxiOsc oscillator2;
    
};

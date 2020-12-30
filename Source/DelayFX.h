/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    Delay.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#define MINUTE_IN_SECONDS 60
#define MAXIMUM_DELAY 480000

class DelayFX
{
public:
    DelayFX();
    ~DelayFX();
    
    void prepare(const dsp::ProcessSpec& spec);
    
    void reset();
    
    bool isActive();

    void setParameters(float time, float feedback, float mix);
    
    void process(AudioBuffer<float>& bufferToProcess, double& bpm);
    
private:
    float calculateDelayInSamples();
    
    dsp::DelayLine<float> delay;
    float feedback = 0;
    float time = 0;
    float mix = 0;
    float currentBPM = 120;
    
    dsp::DryWetMixer<float> delayMixer;
    
    float samplerate = 44100;
    
    AudioBuffer<float> delayBuffer;
};

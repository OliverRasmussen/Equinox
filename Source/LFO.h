/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    LFO.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
class LFO
{
public:
    
    LFO();
    ~LFO();
    
    enum waveform {sine, saw, square, triangle, random};
    
    void prepareToPlay(int samplerate);
    
    void setWaveform(waveform waveformToUse = sine);
    
    void valueToModulate(double &targetValue);

    void setRate(float rate);
    
    void setDepth(float depth);
    
    void setDelay(float delay);
    
    
private:
    waveform currentWaveform;
    
    double* targetValue = nullptr;
    
    float rate;
    float depth;
    float delay;
};

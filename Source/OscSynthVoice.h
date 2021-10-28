/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    OscSynthVoice.h
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
    
    /** Prepares the voices*/
    void prepareVoice(dsp::ProcessSpec&) override;
    
    /** Returns wether the sound is available*/
    bool canPlaySound (SynthesiserSound*) override;
    
    /** Starts a note*/
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    /** Renders the next block*/
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    /** Sets the waveform*/
    void setWaveform(float* selectedWaveform);
    
    /** Sets the phase to a value between 0 and 1*/
    void setPhase(float phase);
    
    /** Returns the phase value*/
    float getPhase() const;
    
private:
    
    /** Returns the next oscillator sample, based on the current set waveform*/
    double getNextOscillatorSample(int channel);
    
    float phase = 0;
    
    int currentWaveform = 0;
    
    WavetableOscillator oscillator1, oscillator2;
};

/*
  ==============================================================================

    WavetableOscillator.h
    Created: 26 Oct 2020 2:05:16pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include <map>
#include <array>
#include <math.h>

#define M_2PI 6.283185307179586476925286766559

class WavetableOscillator
{
public:
    
    /** Set samplerate and generates wavetables */
    static void prepare(int sampleRate);
    
    /** Get current phase value */
    float getPhase() const;
    
    /** Set the oscillators phase.
    phase value must be between 0 and 1 */
    void setPhase(float phaseValue);
    
    /** Generates a Sine wave */
    double sine(double frequency);
    
    /** Generates a Square wave */
    double square(double frequency);
    
    /** Generates a Saw wave */
    double saw(double frequency);
    
    /** Generates a triangle wave */
    double triangle(double frequency);
    
    /** Generates random noise */
    double noise() const;
    
    
private:
    enum waveform { sineWave, sawWave, squareWave, triangleWave };
    waveform currentWaveform;
    static int sampleRate;
    static int nyquistFrequency;
    static const int frequencyRange = 117;
    static const int waveTableSize = 2048;
    float phase = 0;
    double currentFrequency;
    float fractionFrequency;
    static std::map<double, std::array<double, waveTableSize>> sineTable, squareTable, sawTable, triangleTable;
    static double frequencies[frequencyRange];
    
    /** Calculates and returns the next sample from a wavetable */
    double nextOutputSample(std::map<double, std::array<double, waveTableSize>>& wavetable, double frequency);
    
    /** Generate wavetable */
    static void generateWavetable(waveform waveform);
    
};

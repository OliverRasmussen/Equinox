/*
  ==============================================================================

    Oscillator.h
    Created: 26 Oct 2020 2:05:16pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include <map>
#include <array>
#include <math.h>

#define M_2PI 6.283185307179586476925286766559

class Oscillator
{
public:
    static void prepare(int sampleRate);
    
    float getPhase() const;
    
    void setPhase(float phaseValue);
    
    double sine(double frequency);
    
    double square(double frequency);
    
    double saw(double frequency);
    
    double triangle(double frequency);
    
    double noise() const;
    
    
private:
    enum waveform { sineWave, sawWave, squareWave, triangleWave };
    waveform currentWaveform;
    static int sampleRate;
    static int nyquistFrequency;
    static const int frequencyRange = 117;
    static const int waveTableSize = 2048;
    float phase = 0;
    
    static std::map<double, std::array<double, waveTableSize>> sineTable, squareTable, sawTable, triangleTable;
    
    static double frequencies[frequencyRange];
    
    double nextOutputSample(double frequency);
    
    static void generateWavetable(waveform waveform);
    
};

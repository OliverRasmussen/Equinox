/*
  ==============================================================================

    Oscillator.cpp
    Created: 26 Oct 2020 2:05:16pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "Oscillator.h"

/* Static Variables*/
int Oscillator::sampleRate;
int Oscillator::nyquistFrequency;

std::map<double, std::array<double, Oscillator::waveTableSize>> Oscillator::sineTable;
std::map<double, std::array<double, Oscillator::waveTableSize>> Oscillator::sawTable;
std::map<double, std::array<double, Oscillator::waveTableSize>> Oscillator::squareTable;
std::map<double, std::array<double, Oscillator::waveTableSize>> Oscillator::triangleTable;

double Oscillator::frequencies[Oscillator::frequencyRange] = {16.351599, 17.323914, 18.354048, 19.445436, 20.601723, 21.826765, 23.124651, 24.5, 25.956543, 27.5, 29.135235, 30.867706, 32.703197, 34.647827, 36.708096, 38.890873, 41.203445, 43.65353, 46.249302, 49., 51.913086, 55., 58.27047, 61.735413, 65.406395, 69.295654, 73.416191, 77.781746, 82.406891, 87.30706, 92.498604, 97.998856, 103.826172, 110., 116.540939, 123.470825, 130.81279, 138.591309, 146.832382, 155.563492, 164.813782, 174.61412, 184.997208, 195.997711, 207.652344, 220., 233.081879, 246.94165, 261.62558, 277.182617,293.664764, 311.126984, 329.627563, 349.228241, 369.994415, 391.995422, 415.304688, 440., 466.163757, 493.883301, 523.25116, 554.365234, 587.329529, 622.253967, 659.255127, 698.456482, 739.988831, 783.990845, 830.609375, 880., 932.327515, 987.766602, 1046.502319, 1108.730469, 1174.659058, 1244.507935, 1318.510254, 1396.912964, 1479.977661, 1567.981689, 1661.21875, 1760., 1864.655029, 1975.533203, 2093.004639, 2217.460938, 2349.318115, 2489.015869, 2637.020508, 2793.825928, 2959.955322, 3135.963379, 3322.4375, 3520., 3729.31, 3951.066406, 4186.009277, 4434.921875, 4698.63623, 4978.031738, 5274.041016, 5587.651855, 5919.910645, 6271.926758, 6644.875, 7040., 7458.620117, 7902.132812, 8372.018555, 8869.84375, 9397.272461, 9956.063477, 10548.082031, 11175.303711, 11839.821289, 12543.853516, 13289.75};


void Oscillator::prepare(int sampleRate)
{
    // Makes sure we only generate the wavetables once (sampleRate is static)
    if (Oscillator::sampleRate == sampleRate) { return; }
    
    Oscillator::sampleRate = sampleRate;
    Oscillator::nyquistFrequency = Oscillator::sampleRate / 2;
    
    generateWavetable(sawWave);
    generateWavetable(sineWave);
    generateWavetable(squareWave);
    generateWavetable(triangleWave);
}

float Oscillator::getPhase() const
{
    return phase / waveTableSize;
}

void Oscillator::setPhase(float phaseValue)
{
    if (phaseValue > 1 || phaseValue < 0) { return; }
    phase = phaseValue * waveTableSize;
}

double Oscillator::sine(double frequency)
{
    return nextOutputSample(sineTable, frequency);
}

double Oscillator::square(double frequency)
{
    return nextOutputSample(squareTable, frequency);
}

double Oscillator::saw(double frequency)
{
    return nextOutputSample(sawTable, frequency);
}

double Oscillator::triangle(double frequency)
{
    return nextOutputSample(triangleTable, frequency);
}

double Oscillator::noise() const
{
    return (rand() / (float)RAND_MAX)*2-1;
}

double Oscillator::nextOutputSample(std::map<double, std::array<double, waveTableSize>>& wavetable, double frequency)
{
    // Sets currentFrequency and fractionFrequency when frequency changes
    if (currentFrequency != frequency)
    {
        // Return null if frequency is above the frequency range
        if (frequency > frequencies[frequencyRange-1]) { return NULL; }
        
        currentFrequency = frequency;
        fractionFrequency = frequency * ((float)waveTableSize / (float)sampleRate);
    }

    // Linear interpolation
    unsigned int index0 = phase;
    unsigned int index1 = index0 == (waveTableSize - 1) ? 0 : index0 + 1;

    float fraction = phase - (float)index0;
    
    auto value0 = wavetable.lower_bound(currentFrequency)->second[index0];
    auto value1 = wavetable.lower_bound(currentFrequency)->second[index1];

    double outputSample = value0 + fraction * (value1 - value0);

    // Increments phase and wraps value if it exceeds waveTableSize
    if ((phase += fractionFrequency) > (float)waveTableSize) { phase -= (float)waveTableSize; }
    
    return outputSample;
}

void Oscillator::generateWavetable(waveform waveform)
{
    // Creates tables for all frequencies
    for (int i = 0; i < frequencyRange; i++)
    {
        // The current frequency
        double frequency = frequencies[i];
        
        // Table to be filled with the wave at the current frequency
        std::array<double, waveTableSize> frequencyTable;
        frequencyTable.fill(0);
        
        int harmonic = 1;
        
        // Calculating the harmonics frequency
        float harmonicFrequency = (float)harmonic * frequency;
        
        // Only allow harmonics below the nyquist
        while (harmonicFrequency < nyquistFrequency)
            {
                // Delta of the angle
                double angleDelta = M_2PI / (waveTableSize - 1) * (float)harmonic;
                double currentAngle = 0.0f;
                
                // Fills frequencyTable with samples of the wave and its harmonics
                for (int i = 0; i < waveTableSize; ++i)
                {
                    // Generating the sample of the wave and adding it to the table
                    double sample = waveform == triangleWave ? cos(currentAngle) / (float)(harmonic * harmonic) : sin(currentAngle) / (float)harmonic;
                    
                    frequencyTable[i] += sample / 2; // Dividing with two for amplitude reduction
                    currentAngle += angleDelta;
                }
                
                // Break if waveform is sinewave: only one harmonic
                if(waveform == sineWave) { break; }
                
                // Increment harmonic based on the waveform
                harmonic += waveform == sawWave ? 1 : 2;
                
                harmonicFrequency = (float)harmonic * frequency;
            }
        
        // Adds the frequencyTable to the current frequency in the wavetable
        switch (waveform)
        {
            case sawWave:
                sawTable[frequency] = frequencyTable;
                break;
                
            case squareWave:
                squareTable[frequency] = frequencyTable;
                break;
                
            case triangleWave:
                triangleTable[frequency] = frequencyTable;
                break;
            
            case sineWave:
                sineTable[frequency] = frequencyTable;
                break;
        }
    }
}

/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    WavetableOscillator.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "WavetableOscillator.h"

bool WavetableOscillator::isPrepared = false;
int WavetableOscillator::sampleRate;
int WavetableOscillator::nyquistFrequency;

std::map<double, std::array<double, WavetableOscillator::waveTableSize>> WavetableOscillator::sineTable;
std::map<double, std::array<double, WavetableOscillator::waveTableSize>> WavetableOscillator::sawTable;
std::map<double, std::array<double, WavetableOscillator::waveTableSize>> WavetableOscillator::squareTable;
std::map<double, std::array<double, WavetableOscillator::waveTableSize>> WavetableOscillator::triangleTable;

const double WavetableOscillator::frequencies[WavetableOscillator::frequencyRange] = {16.351599, 17.323914, 18.354048, 19.445436, 20.601723, 21.826765, 23.124651, 24.5, 25.956543, 27.5, 29.135235, 30.867706, 32.703197, 34.647827, 36.708096, 38.890873, 41.203445, 43.65353, 46.249302, 49., 51.913086, 55., 58.27047, 61.735413, 65.406395, 69.295654, 73.416191, 77.781746, 82.406891, 87.30706, 92.498604, 97.998856, 103.826172, 110., 116.540939, 123.470825, 130.81279, 138.591309, 146.832382, 155.563492, 164.813782, 174.61412, 184.997208, 195.997711, 207.652344, 220., 233.081879, 246.94165, 261.62558, 277.182617,293.664764, 311.126984, 329.627563, 349.228241, 369.994415, 391.995422, 415.304688, 440., 466.163757, 493.883301, 523.25116, 554.365234, 587.329529, 622.253967, 659.255127, 698.456482, 739.988831, 783.990845, 830.609375, 880., 932.327515, 987.766602, 1046.502319, 1108.730469, 1174.659058, 1244.507935, 1318.510254, 1396.912964, 1479.977661, 1567.981689, 1661.21875, 1760., 1864.655029, 1975.533203, 2093.004639, 2217.460938, 2349.318115, 2489.015869, 2637.020508, 2793.825928, 2959.955322, 3135.963379, 3322.4375, 3520., 3729.31, 3951.066406, 4186.009277, 4434.921875, 4698.63623, 4978.031738, 5274.041016, 5587.651855, 5919.910645, 6271.926758, 6644.875, 7040., 7458.620117, 7902.132812, 8372.018555, 8869.84375, 9397.272461, 9956.063477, 10548.082031, 11175.303711, 11839.821289, 12543.853516, 13289.75};


WavetableOscillator::WavetableOscillator()
{
}

WavetableOscillator::~WavetableOscillator()
{
    currentTable = nullptr;
}

void WavetableOscillator::prepare(int sampleRate)
{
    if ((!isPrepared || WavetableOscillator::sampleRate != sampleRate) && sampleRate > 0)
    {
        WavetableOscillator::sampleRate = sampleRate;
        WavetableOscillator::nyquistFrequency = WavetableOscillator::sampleRate / 2;

        generateWavetable(Waveform::sawWave);
        generateWavetable(Waveform::sineWave);
        generateWavetable(Waveform::squareWave);
        generateWavetable(Waveform::triangleWave);

        isPrepared = true;
    }
}

void WavetableOscillator::setWaveform(Waveform waveform)
{
    M_ASSERT(isPrepared, "setWaveform called before oscillator has been prepared!");

    switch (waveform)
    {
    case Waveform::sineWave:
        currentTable = &sineTable;
        break;
    case Waveform::sawWave:
        currentTable = &sawTable;
        break;
    case Waveform::triangleWave:
        currentTable = &triangleTable;
        break;
    case Waveform::squareWave:
        currentTable = &squareTable;
        break;
    case Waveform::noise:
        currentTable = nullptr;
        break;
    default:
        currentTable = &sineTable;
        break;
    }

    waveform == Waveform::noise ? nextSampleFunction = [this] (double) { return nextNoiseSample(); } :
                                  nextSampleFunction = [this] (double frequency) { return nextWaveformSample(frequency); };

    setTableIterator();
}

float WavetableOscillator::getPhase()
{
    return phase / (waveTableSize - 1);
}

void WavetableOscillator::setPhase(float phaseValue)
{
    if (phaseValue > 1 || phaseValue < 0) { return; }
    phase = phaseValue * (waveTableSize - 1);
}

double WavetableOscillator::getNextSample(double frequency)
{
    M_ASSERT(isPrepared, "getNextSample called before oscillator has been prepared!");
    return nextSampleFunction(frequency);
}

double WavetableOscillator::nextWaveformSample(double frequency)
{
    if (currentFrequency != frequency)
    {
        currentFrequency = frequency;

        fractionFrequency = currentFrequency * ((float)waveTableSize / (float)sampleRate);

        setTableIterator();
    }

    // Linear interpolation
    unsigned int index0 = phase;
    unsigned int index1 = index0 == (waveTableSize - 1) ? 0 : index0 + 1;

    float fraction = phase - (float)index0;

    auto value0 = tableIterator->second[index0];
    auto value1 = tableIterator->second[index1];

    double outputSample = value0 + fraction * (value1 - value0);

    // Increments phase and wraps value if it exceeds the wavetables size
    phase += fractionFrequency;

    if (phase > waveTableSize - 1)
    {
        phase -= (float)waveTableSize;
    }

    return outputSample;
}

double WavetableOscillator::nextNoiseSample() const
{
    return (rand() / (float)RAND_MAX)*2-1;
}


void WavetableOscillator::setTableIterator()
{
    if (currentTable != nullptr)
    {
        // Find iterator to corresponding frequency or closest match
        // in the current table
        auto it = currentTable->lower_bound(currentFrequency);

        // Set tableIterator to refer the given frequency,
        // or last frequency if iterator is out of the tables range
        tableIterator = it == currentTable->end() ? --it : it;
    }
}

void WavetableOscillator::generateWavetable(Waveform waveform)
{
    // Creates tables for all frequencies
    for (int i = 0; i < frequencyRange - 1; i++)
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
                    double sample = waveform == Waveform::triangleWave ? cos(currentAngle) / (float)(harmonic * harmonic) : sin(currentAngle) / (float)harmonic;
                    
                    frequencyTable[i] += sample / 2; // Dividing with two for amplitude reduction
                    currentAngle += angleDelta;
                }
                
                // Break if waveform is sinewave: only one harmonic
                if(waveform == Waveform::sineWave) { break; }
                
                // Increment harmonic based on the waveform
                harmonic += waveform == Waveform::sawWave ? 1 : 2;
                
                harmonicFrequency = (float)harmonic * frequency;
            }
        
        // Adds the frequencyTable to the current frequency in the wavetable
        switch (waveform)
        {
            case Waveform::sawWave:
                sawTable[frequency] = frequencyTable;
                break;
                
            case Waveform::squareWave:
                squareTable[frequency] = frequencyTable;
                break;

            case Waveform::sineWave:
                sineTable[frequency] = frequencyTable;
                break;

            case Waveform::triangleWave:
                triangleTable[frequency] = frequencyTable;
                break;
        }
    }
}

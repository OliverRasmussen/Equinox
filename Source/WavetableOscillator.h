/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    WavetableOscillator.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include <map>
#include <array>
#include <math.h>
#include <functional>
#include <cassert>

#define M_ASSERT(expr, msg) assert(( (void)(msg), (expr) ))

#define M_2PI 6.283185307179586476925286766559

class WavetableOscillator
{

public:
    enum class Waveform { sineWave, sawWave, triangleWave, squareWave, noise };

    WavetableOscillator();

    ~WavetableOscillator();

    /** Set samplerate and generates wavetables */
    static void prepare(int samplerate);

    /** Set the waveform to be used */
    void setWaveform(Waveform waveform);

    /** Get current phase value */
    float getPhase();

    /** Set the oscillators phase.
        phase value must be between 0 and 1 */
    void setPhase(float phaseValue);

    /** Returns the next oscillator sample*/
    double getNextSample(double frequency);

private:

    static bool isPrepared;

    static int sampleRate;

    static int nyquistFrequency;

    static const int frequencyRange = 117;

    static const int waveTableSize = 2048;

    float phase = 0;

    double currentFrequency = 0;

    float fractionFrequency = 0;

    static std::map<double, std::array<double, waveTableSize>> sineTable, squareTable, sawTable, triangleTable;

    std::map<double, std::array<double, waveTableSize>>::const_iterator tableIterator;

    const std::map<double, std::array<double, waveTableSize>>* currentTable = nullptr;

    const static double frequencies[frequencyRange];

    std::function<double(double)> nextSampleFunction = [](double) { return 0; };

    /** Calculates and returns the next sample,
    based on the current waveform, frequency, and phase*/
    double nextWaveformSample(double frequency);

    /** Generates random noise */
    double nextNoiseSample() const;

    /** Set TableIterator to point to the current frequency in the current table */
    void setTableIterator();
    
    /** Set the frequency of the waveform*/
    void setFrequency(double frequency);

    /** Generate wavetable */
    static void generateWavetable(Waveform waveform);
};

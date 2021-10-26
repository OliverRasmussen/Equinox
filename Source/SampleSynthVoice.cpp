/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SampleSynthVoice.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "SampleSynthVoice.h"

SampleSynthVoice::SampleSynthVoice(bool isMonoVoice) : SynthVoice(isMonoVoice)
{
    
}

SampleSynthVoice::~SampleSynthVoice()
{
    
}

void SampleSynthVoice::prepareVoice(dsp::ProcessSpec& spec)
{
    SynthVoice::prepareVoice(spec);
}

bool SampleSynthVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<const SampleSynthSound*> (sound) != nullptr;
}

void SampleSynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    if (auto* sampleSound = dynamic_cast<const SampleSynthSound*> (sound))
    {
        if (sampleSound->data)
        {
            setFrequency(std::pow (2.0f, (midiNoteNumber - sampleSound->midiRootNote) / 12.0f)
                         * sampleSound->sourceSamplerate / getSampleRate());
            
            sampleLength = sampleSound->length;
            
            if (!noteHasBeenTriggered)
            {
                sourceSamplePositionLeft = getSampleStartTime();
                sourceSamplePositionRight = getSampleStartTime();
            }
            SynthVoice::startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
        }
    }
}

void SampleSynthVoice::setSampleStartTime(float startTime)
{
    if (startTime > 1 || startTime < 0) { return; }
    sampleStart = startTime;
}

float SampleSynthVoice::getSampleStartTime() const
{
    return sampleStart * sampleLength;
}

void SampleSynthVoice::stopNote(float velocity, bool allowTailOff)
{
    SynthVoice::stopNote(velocity, allowTailOff);
}

float SampleSynthVoice::getNextSamplerSample (int channel, const float* const inL, const float* const inR)
{
    float nextSample = 0;
    if (sourceSamplePositionLeft < sampleLength &&
        sourceSamplePositionRight < sampleLength &&
        inL != nullptr && inR != nullptr)
    {
        double* sourceSamplePos = (channel == 0) ? &sourceSamplePositionLeft : &sourceSamplePositionRight;
        auto* channelReadPtr = (channel == 0) ? inL : inR;
        
        auto pos = (int) *sourceSamplePos;
        auto alpha = (float) (*sourceSamplePos - pos);
        auto invAlpha = 1.0f - alpha;
        
        nextSample = (channelReadPtr[pos] * invAlpha + channelReadPtr[pos + 1] * alpha);
        
        *sourceSamplePos += (channel == 0) ? getFrequency() : (getDetune()) ? getFrequency() * (getDetune()) : getFrequency();
    }
    return nextSample;
}

void SampleSynthVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if (isVoiceActive() && sourceSamplePositionLeft < sampleLength && sourceSamplePositionRight < sampleLength)
    {
        if (auto* playingSound = dynamic_cast<SampleSynthSound*> (getCurrentlyPlayingSound().get()))
        {
            jassert (numSamples <= voiceBuffer.getNumSamples());
            AudioBuffer<float> proxyBuffer (voiceBuffer.getArrayOfWritePointers(), voiceBuffer.getNumChannels(), startSample, numSamples);
            proxyBuffer.clear();

            auto& sampleData = *playingSound->data;
            const float* const inL = sampleData.getReadPointer (0);
            const float* const inR = sampleData.getNumChannels() > 1 ? sampleData.getReadPointer (1) : nullptr;

            for (int sample = 0; sample < proxyBuffer.getNumSamples(); ++sample)
            {
                for (int channel = 0; channel < sampleData.getNumChannels(); ++channel)
                {
                    proxyBuffer.addSample (channel, sample, getNextSamplerSample(channel, inL, inR));
                }
            }
            addBufferToOutput(proxyBuffer, outputBuffer, startSample, numSamples);
        }
    }
}

/*
  ==============================================================================

    SampleSynthVoice.cpp
    Created: 1 May 2020 6:38:36pm
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

bool SampleSynthVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<const SampleSynthSound*> (sound) != nullptr;
}

void SampleSynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    if (auto* sampleSound = dynamic_cast<const SampleSynthSound*> (sound))
    {
        setFrequency(std::pow (2.0f, (midiNoteNumber - sampleSound->midiRootNote) / 12.0f)
                     * sampleSound->sourceSampleRate / getSampleRate());
        
        sourceSamplePositionLeft = 0.0;
        sourceSamplePositionRight = 0.0;
        gain = velocity;
        
        sampleLength = sampleSound->length;

        getAmpEnvelope().setSampleRate(sampleSound->sourceSampleRate);
        SynthVoice::startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    }
    else
    {
        jassertfalse;
    }
}

void SampleSynthVoice::stopNote(float velocity, bool allowTailOff)
{
    SynthVoice::stopNote(velocity, allowTailOff);
}

float SampleSynthVoice::getNextSamplerSample (int channel, const float* const inL, const float* const inR)
{
        
    double * sourceSamplePos = (channel == 0) ? &sourceSamplePositionLeft : &sourceSamplePositionRight;
    
    auto pos = (int) *sourceSamplePos;
    auto alpha = (float) (*sourceSamplePos - pos);
    auto invAlpha = 1.0f - alpha;
    
    float nextSample = ((channel == 0) ? (inL[pos] * invAlpha + inL[pos + 1] * alpha) : (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha)
    : 0) * gain;
    
    *sourceSamplePos += (channel == 0) ? getFrequency() : (getDetune()) ? getFrequency() * (getDetune()) : getFrequency();
    
    return nextSample;
    
}

void SampleSynthVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    
    if (auto* playingSound = static_cast<SampleSynthSound*> (getCurrentlyPlayingSound().get()))
    {
        voiceStoppedPlaying = false;
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
                
                if (sourceSamplePositionLeft > sampleLength || sourceSamplePositionRight > sampleLength)
                {
                    stopNote (0.0f, false);
                    break;
                }
            }
        }
        
        
//        voiceStoppedPlaying = false;
//        jassert (numSamples <= voiceBuffer.getNumSamples());
//        AudioBuffer<float> proxyBuffer (voiceBuffer.getArrayOfWritePointers(), voiceBuffer.getNumChannels(), startSample, numSamples);
//        proxyBuffer.clear();
//
//        auto& data = *playingSound->data;
//        const float* const inL = data.getReadPointer (0);
//        const float* const inR = data.getNumChannels() > 1 ? data.getReadPointer (1) : nullptr;
//
//        float* outL = proxyBuffer.getWritePointer(0, 0);
//        float* outR = proxyBuffer.getNumChannels() > 1 ? proxyBuffer.getWritePointer (1, 0) : nullptr;
//
//        for (int sample = 0; sample < proxyBuffer.getNumSamples(); ++sample)
//        {
//
//
//            auto pos = (int) sourceSamplePosition;
//            auto alpha = (float) (sourceSamplePosition - pos);
//            auto invAlpha = 1.0f - alpha;
//
//            // just using a very simple linear interpolation
//            float l = (inL[pos] * invAlpha + inL[pos + 1] * alpha);
//            float r = (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha)
//                                       : l;
//
//            l *= lgain;
//            r *= rgain;
//
//            if (outR != nullptr)
//            {
//                *outL++ += l;
//                *outR++ += r;
//            }
//            else
//            {
//                *outL++ += (l + r) * 0.5f;
//            }
//
//            sourceSamplePosition += getFrequency();
//
//            if (sourceSamplePosition > playingSound->length)
//            {
//                stopNote (0.0f, false);
//                break;
//            }
//        }
        
        addBufferToOutput(proxyBuffer, outputBuffer, startSample, numSamples);
        
    }
    else
    {
        voiceStoppedPlaying = true;
    }
    
    if (noteHasBeenTriggered && !getAmpEnvelope().isActive())
    {
        stopNote(0.0f, false);
    }
}

/*
  ==============================================================================

    AudioSampleValueTreeState.cpp
    Created: 8 Dec 2020 3:42:03pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "AudioSampleValueTreeState.h"

AudioSampleValueTreeState::AudioSampleValueTreeState(const Identifier &type)
{
    state = ValueTree(type);
    formatManager.registerBasicFormats();
}

AudioSampleValueTreeState::~AudioSampleValueTreeState()
{
}

// Used for adding an audiofile to the AudioSampleValueTreeState
void AudioSampleValueTreeState::addAudioSample(File audioFile, String sampleId)
{
    // Creating reader for sample file
    if (auto formatReader = std::unique_ptr<AudioFormatReader>(formatManager.createReaderFor(audioFile)))
    {
        String fileExtension = formatReader->getFormatName().dropLastCharacters(5);
        
        // Writing the files audio data to a memoryblock
        // so it can be added to a valuetree
        MemoryBlock sampleSourceBlock;
        {
            auto format = formatManager.findFormatForFileExtension(fileExtension);

            std::unique_ptr<AudioFormatWriter> writer (format->createWriterFor (new MemoryOutputStream (sampleSourceBlock, false), formatReader->sampleRate, formatReader->numChannels, formatReader->bitsPerSample, StringPairArray(), 0));
            
            int startSample = 0;
            
            writer->writeFromAudioReader(*formatReader, startSample, formatReader->lengthInSamples);
        }
        
        ValueTree audioSample(sampleId);
        
        audioSample.setProperty("samplename", var(audioFile.getFileName()), nullptr);
        audioSample.setProperty("sampleformat", var(fileExtension), nullptr);
        audioSample.setProperty("samplerate", var(formatReader->sampleRate), nullptr);
        audioSample.setProperty("bitspersample", var((int)formatReader->bitsPerSample), nullptr);
        audioSample.setProperty("numberofchannels", var((int)formatReader->numChannels), nullptr);
        audioSample.setProperty("lengthinsamples", var(formatReader->lengthInSamples), nullptr);
        audioSample.setProperty("samplesource", var(sampleSourceBlock), nullptr);
        
        state.addChild(audioSample, state.getNumChildren() + 1, nullptr);
    }
}

// Returns an AudioSample
std::unique_ptr<AudioSample> AudioSampleValueTreeState::getAudioSample(String sampleId)
{
    ValueTree audioSampleAsValueTree = state.getChildWithName(sampleId);
    
    if (audioSampleAsValueTree.isValid())
    {
        AudioBuffer<float> sampleSource = AudioBuffer<float>(int(audioSampleAsValueTree.getProperty("numberofchannels")), int(audioSampleAsValueTree.getProperty("lengthinsamples")));
        {
            MemoryBlock* sampleSourceBlock = audioSampleAsValueTree.getProperty("samplesource").getBinaryData();
            auto format = formatManager.findFormatForFileExtension(audioSampleAsValueTree.getProperty("sampleformat"));

            std::unique_ptr<AudioFormatReader> reader (format->createReaderFor(new MemoryInputStream (*sampleSourceBlock, false), true));
            
            int startSample = 0;
            
            reader->read(&sampleSource, startSample, int(audioSampleAsValueTree.getProperty("lengthinsamples")), 0, true, true);
        }

        std::unique_ptr<AudioSample> audioSample (new AudioSample(audioSampleAsValueTree.getProperty("samplename").toString(), audioSampleAsValueTree.getProperty("sampleformat").toString(), int(audioSampleAsValueTree.getProperty("samplerate")), int(audioSampleAsValueTree.getProperty("bitspersample")), int(audioSampleAsValueTree.getProperty("numberofchannels")), int(audioSampleAsValueTree.getProperty("lengthinsamples")), sampleSource));
        
        return audioSample;
    }
    
    return nullptr;
}

// Replaces the state with a new one
void AudioSampleValueTreeState::replaceState(ValueTree newState)
{
    ScopedLock lock(replacingState);
    
    state = newState;
}

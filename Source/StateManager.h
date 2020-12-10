/*
  ==============================================================================

    StateManager.h
    Created: 4 Dec 2020 2:04:12pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioSampleValueTreeState.h"

class StateManager
{
    
public:
    
    StateManager(AudioProcessorValueTreeState*, AudioSampleValueTreeState*);
    
    ~StateManager();
    
    ValueTree& getState();
    
    AudioProcessorValueTreeState& getAPVTS();
    
    std::atomic<float>* getAudioParameterValue(StringRef paramId) const;
    
    void addAudioSample(File audioFile, String synthInstanceNum);
    
    std::unique_ptr<AudioSample> getAudioSample(String sampleId);
    
    void saveStateToBinary(MemoryBlock& destinationData);
    
    void loadStateFromBinary(const void* data, int sizeInBytes);
    
    bool saveStateToFile(File& file);
    
    bool loadStateFromFile(File& file);
    
private:
    
    std::unique_ptr<XmlElement> getStateAsXml();
    
    bool setStateFromXml(std::unique_ptr<XmlElement> stateXml);
    
    ValueTree currentState;
    
    std::unique_ptr<AudioProcessorValueTreeState> parameterState = nullptr;
    
    std::unique_ptr<AudioSampleValueTreeState> audioSampleState = nullptr;
    
};

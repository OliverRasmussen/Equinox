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
    
    // StateManager should not be cloneable
    StateManager(StateManager &other) = delete;
    
    // StateManager should not be assignable
    void operator=(const StateManager &) = delete;
    
    static StateManager& GetInstance(AudioProcessorValueTreeState* = nullptr, AudioSampleValueTreeState* asvts = nullptr);
    
    static void ResetInstance();
    
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
    
    StateManager(AudioProcessorValueTreeState*, AudioSampleValueTreeState*);
    
    ~StateManager();
    
    std::unique_ptr<XmlElement> getStateAsXml();
    
    bool setStateFromXml(std::unique_ptr<XmlElement> stateXml);
    
    ValueTree currentState;
    
    AudioFormatManager formatManager;
    
    std::unique_ptr<AudioProcessorValueTreeState> parameterState = nullptr;
    
    std::unique_ptr<AudioSampleValueTreeState> audioSampleState = nullptr;
    
    static std::mutex mutex;
    
    static StateManager* instance;
    
};

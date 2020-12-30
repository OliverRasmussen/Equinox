/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    StateManager.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioSampleValueTreeState.h"
#include "PresetInfo.h"

class StateManager
{
    
public:
    
    StateManager(AudioProcessorValueTreeState*, AudioSampleValueTreeState*);
    
    ~StateManager();
    
    ValueTree& getState();
    
    AudioProcessorValueTreeState& getParameters();
    
    std::atomic<float>* getAudioParameterValue(StringRef paramId) const;
    
    void addAudioSample(File audioFile, String synthInstanceNum);
    
    std::unique_ptr<AudioSample> getAudioSample(String sampleId);
    
    void setPresetInfo(int index, String presetName);
    
    //std::unique_ptr<std::tuple<int, String>> getPresetInfo();
    std::unique_ptr<PresetInfo> getPresetInfo();
    
    void saveStateToBinary(MemoryBlock& destinationData);
    
    void loadStateFromBinary(const void* data, int sizeInBytes);
    
    bool saveStateToFile(File& file);
    
    bool loadStateFromFile(File& file);
    
    void resetStateToDefault();
    
private:
    
    std::unique_ptr<XmlElement> getStateAsXml();
    
    bool setStateFromXml(std::unique_ptr<XmlElement> stateXml);
    
    ValueTree currentState;
    
    ValueTree initialState;
    
    std::unique_ptr<AudioProcessorValueTreeState> parameterState = nullptr;
    
    std::unique_ptr<AudioSampleValueTreeState> audioSampleState = nullptr;
    
};

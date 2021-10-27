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

class StateManager
{
    
public:
    
    StateManager(AudioProcessorValueTreeState*, AudioSampleValueTreeState*);
    
    ~StateManager();
    
    /** Adds a listener to the internal ValueTree*/
    void addListener(ValueTree::Listener *listener);

    /**Removes a listenerr from the internal ValueTree*/
    void removeListener(ValueTree::Listener* listener);
    
    /** Returns a child ValueTree object*/
    ValueTree getChildWithName (const Identifier& type) const;
    
    /** Returns a reference to the AudioProcessorValueTreeState object*/
    AudioProcessorValueTreeState& getParameters();
    
    /** Returns the value of a specific audio parameter*/
    std::atomic<float>* getAudioParameterValue(StringRef paramId) const;
    
    /** Adds a file as an AudioSample with the synths instance number as id*/
    void addAudioSample(File audioFile, String synthInstanceNum);
    
    /** Returns a pointer to a specific AudioSample*/
    std::unique_ptr<AudioSample> getAudioSample(String sampleId);
    
    /** Sets the current states preset name*/
    void setPresetName(String presetName);
    
    /** Returns the current states preset name*/
    Value getPresetName();
    
    /** Saves the state to binary*/
    void saveStateToBinary(MemoryBlock& destinationData);
    
    /** Loads the state from binary*/
    void loadStateFromBinary(const void* data, int sizeInBytes);
    
    /** Saves the state to a specified file*/
    bool saveStateToFile(File& file);
    
    /** Loads the state from a specified file*/
    bool loadStateFromFile(File& file);
    
    /** Resets the state to default*/
    void resetStateToDefault();
    
private:
    
    /** Returns the state as a XmlElement*/
    std::unique_ptr<XmlElement> getStateAsXml();
    
    /** Sets the state from a XmlElement*/
    bool setStateFromXml(std::unique_ptr<XmlElement> stateXml);
    
    ValueTree currentState;
    
    ValueTree initialState;
    
    std::unique_ptr<AudioProcessorValueTreeState> parameterState = nullptr;
    
    std::unique_ptr<AudioSampleValueTreeState> audioSampleState = nullptr;
    
};

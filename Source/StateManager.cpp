/*
  ==============================================================================

    StateManager.cpp
    Created: 4 Dec 2020 2:04:12pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "StateManager.h"

StateManager::StateManager(AudioProcessorValueTreeState* apvts, AudioSampleValueTreeState* asvts)
{
    // Initializing currentState
    currentState = ValueTree("currentstate");
    
    this->parameterState = std::unique_ptr<AudioProcessorValueTreeState>(apvts);
    
    // Adding parameterStates valuetree as a child to the currentState
    currentState.addChild(this->parameterState->state, 0, nullptr);
    

    //audioSampleState = ValueTree("audiosamplestate");
    this->audioSampleState = std::unique_ptr<AudioSampleValueTreeState>(asvts);
    
    // Adding audioSampleStates valuetree as a child to the currentState
    currentState.addChild(this->audioSampleState->state, 1, nullptr);
}

StateManager::~StateManager()
{
}

ValueTree& StateManager::getState()
{
    return currentState;
}

AudioProcessorValueTreeState& StateManager::getAPVTS()
{
    return *parameterState;
}

std::atomic<float>* StateManager::getAudioParameterValue(StringRef paramId) const
{
    return parameterState->getRawParameterValue(paramId);
}

void StateManager::addAudioSample(File audioFile, String synthInstanceNum)
{
    audioSampleState->addAudioSample(audioFile, synthInstanceNum);
}

std::unique_ptr<AudioSample> StateManager::getAudioSample(String sampleId)
{
    return audioSampleState->getAudioSample(sampleId);
}

std::unique_ptr<XmlElement> StateManager::getStateAsXml()
{
    // Creates and returns a xml element that represents the currentState
    return std::unique_ptr<XmlElement>(new XmlElement(*currentState.createXml()));
}

bool StateManager::setStateFromXml(std::unique_ptr<XmlElement> stateXml)
{
    if (stateXml.get() != nullptr)
    {
        if (stateXml->hasTagName(currentState.getType()))
        {
            if (XmlElement* audioProcessorValueTreeState = stateXml->getChildByName(parameterState->state.getType()))
            {
                parameterState->replaceState(ValueTree::fromXml(*audioProcessorValueTreeState));
                
                if (XmlElement* audioSampleValueTreeStateXml = stateXml->getChildByName(audioSampleState->state.getType()))
                {
                    audioSampleState->replaceState(ValueTree::fromXml(*audioSampleValueTreeStateXml));
                    
                    currentState.addChild(this->parameterState->state, 0, nullptr);
                    currentState.addChild(this->audioSampleState->state, 1, nullptr);
                    return true;
                }
            }
        }
    }
    return false;
}

void StateManager::saveStateToBinary(MemoryBlock& destinationData)
{
    juce::AudioPluginInstance::copyXmlToBinary(*getStateAsXml(), destinationData);
}

void StateManager::loadStateFromBinary(const void* data, int sizeInBytes)
{
    setStateFromXml(juce::AudioPluginInstance::getXmlFromBinary (data, sizeInBytes));
}

bool StateManager::saveStateToFile(File& file)
{
    return getStateAsXml()->writeTo(file);
}

bool StateManager::loadStateFromFile(File& file)
{
    XmlDocument xmlDocument(file);
    return setStateFromXml(xmlDocument.getDocumentElement());
    
}

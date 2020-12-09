/*
  ==============================================================================

    SynthMenuGUI.h
    Created: 13 May 2020 6:53:02pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "TabMenu.h"
#include "OscillatorGUI.h"
#include "SamplerGUI.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class SynthMenuGUI    : public Component, private AudioProcessorValueTreeState::Listener
{
public:
    SynthMenuGUI(EquinoxSynthesizer&, std::string);
    ~SynthMenuGUI();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    void tabSwitched();
    
    void parameterChanged(const String &parameterID, float newValue) override;
    
    OscillatorGUI oscillatorGUI;
    
    SamplerGUI samplerGUI;
    
    TabMenu tabMenu;
    
    std::unique_ptr<AudioParameterFloat*> currentSynthModeState;

    std::string synthInstance;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthMenuGUI)
};

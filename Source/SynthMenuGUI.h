/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SynthMenuGUI.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "EquinoxComponent.h"
#include "TabMenu.h"
#include "OscillatorGUI.h"
#include "SamplerGUI.h"

//==============================================================================
/*
*/
class SynthMenuGUI    : public EquinoxComponent, private AudioProcessorValueTreeState::Listener
{
public:
    SynthMenuGUI(StateManager& stateManager, std::string);
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

    StateManager& stateManager;
    std::string synthInstance;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthMenuGUI)
};

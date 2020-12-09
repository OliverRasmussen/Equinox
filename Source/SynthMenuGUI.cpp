/*
  ==============================================================================

    SynthMenuGUI.cpp
    Created: 13 May 2020 6:53:02pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "SynthMenuGUI.h"

//==============================================================================
SynthMenuGUI::SynthMenuGUI(EquinoxSynthesizer& synth, std::string synthInstance) : oscillatorGUI(synth, synthInstance), samplerGUI(synth, synthInstance), tabMenu(TabbedButtonBar::Orientation::TabsAtTop), synthInstance(synthInstance)
{
    setSize (200, 200);
    tabMenu.addTab("Oscillator", Colours::transparentBlack, &oscillatorGUI, false);
    tabMenu.addTab("Sampler", Colours::transparentBlack, &samplerGUI, false);
    
    StateManager::GetInstance().getAPVTS().addParameterListener("synthMode" + synthInstance, this);
    currentSynthModeState = std::make_unique<AudioParameterFloat*>(dynamic_cast<AudioParameterFloat*>(StateManager::GetInstance().getAPVTS().getParameter("synthMode" + synthInstance)));
    
    tabMenu.setCurrentTabIndex(**currentSynthModeState);

    tabMenu.onTabChanged = [&](){ tabSwitched(); };
    addAndMakeVisible(&tabMenu);

}

SynthMenuGUI::~SynthMenuGUI()
{
}

// Called if the current tab gets switch to another tab
void SynthMenuGUI::tabSwitched()
{
    // Sets currentSynthModeState equal to the currentTabIndex if it isnt already equal
    if (StateManager::GetInstance().getAPVTS().getParameterAsValue("synthMode" + synthInstance) != tabMenu.getCurrentTabIndex())
    {
        **currentSynthModeState = tabMenu.getCurrentTabIndex();
    }
}

// Called if the synthmode parameter changes
void SynthMenuGUI::parameterChanged(const String &parameterID, float newValue)
{
    juce::String synthModeId = "synthMode" + synthInstance;
    if (parameterID == synthModeId)
    {
        // Sets the currentTabIndex equal to the parameters value if it isnt already equal
        if (tabMenu.getCurrentTabIndex() != newValue)
        {
            tabMenu.setCurrentTabIndex(newValue);
        }
    }
}

void SynthMenuGUI::paint (Graphics& g)
{

}

void SynthMenuGUI::resized()
{
    tabMenu.setBounds(0, 0, 200, 200);

}

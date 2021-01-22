/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SynthMenuGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "SynthMenuGUI.h"

//==============================================================================
SynthMenuGUI::SynthMenuGUI(StateManager& stateManager, std::string synthInstance) : oscillatorGUI(stateManager, synthInstance), samplerGUI(stateManager, synthInstance), tabMenu(TabbedButtonBar::Orientation::TabsAtTop), stateManager(stateManager), synthInstance(synthInstance)
{
    tabMenu.addTab("Oscillator", Colours::transparentBlack, &oscillatorGUI, false);
    tabMenu.addTab("Sampler", Colours::transparentBlack, &samplerGUI, false);
    
    stateManager.getParameters().addParameterListener("synthMode" + synthInstance, this);
    currentSynthModeState = std::make_unique<AudioParameterFloat*>(dynamic_cast<AudioParameterFloat*>(stateManager.getParameters().getParameter("synthMode" + synthInstance)));
    
    tabMenu.setCurrentTabIndex(**currentSynthModeState);

    tabMenu.onTabChanged = [&](){ tabSwitched(); };
    addAndMakeVisible(&tabMenu);

}

SynthMenuGUI::~SynthMenuGUI()
{
    stateManager.getParameters().removeParameterListener("synthMode" + synthInstance, this);
}

// Called if the current tab gets switch to another tab
void SynthMenuGUI::tabSwitched()
{
    // Sets currentSynthModeState equal to the currentTabIndex if it isnt already equal
    if (stateManager.getParameters().getParameterAsValue("synthMode" + synthInstance) != tabMenu.getCurrentTabIndex())
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
    tabMenu.setBounds(0, 0, getLocalBounds().getWidth(), getLocalBounds().getHeight() - 23);
    oscillatorGUI.setSize(200, 200);
    samplerGUI.setSize(200, 200);
}

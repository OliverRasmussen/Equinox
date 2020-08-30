/*
  ==============================================================================

    SynthMenuGUI.cpp
    Created: 13 May 2020 6:53:02pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "SynthMenuGUI.h"

//==============================================================================
SynthMenuGUI::SynthMenuGUI(EquinoxAudioProcessor& p, EquinoxSynthesizer& s) : oscillatorGUI(p, s), samplerGUI(p, s), tabMenu(TabbedButtonBar::Orientation::TabsAtTop), processor(p), synth(s)
{
    setSize (200, 200);
    tabMenu.addTab("Oscillator", Colours::transparentBlack, &oscillatorGUI, false);
    tabMenu.addTab("Sampler", Colours::transparentBlack, &samplerGUI, false);
    
    processor.treeState.addParameterListener("synthMode" + synth.instanceNumAsStr(), this);
    if (AudioParameterFloat* synthModeParameter = dynamic_cast<AudioParameterFloat*>(processor.treeState.getParameter("synthMode" + synth.instanceNumAsStr())))
    {
        currentSynthModeState = std::make_unique<AudioParameterFloat*>(synthModeParameter);
    }

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
    if (processor.treeState.getParameterAsValue("synthMode" + synth.instanceNumAsStr()) != tabMenu.getCurrentTabIndex())
    {
        **currentSynthModeState = tabMenu.getCurrentTabIndex();
    }
    synth.setSynthMode(tabMenu.getCurrentTabIndex());
}

// Called if the synthmode parameter changes
void SynthMenuGUI::parameterChanged(const String &parameterID, float newValue)
{
    juce::String synthModeId = "synthMode" + synth.instanceNumAsStr();
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

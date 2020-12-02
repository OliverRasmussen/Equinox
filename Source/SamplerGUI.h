/*
  ==============================================================================

    SamplerGUI.h
    Created: 13 May 2020 8:43:49pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "SynthGUI.h"

//==============================================================================
/*
*/
class SamplerGUI    : public SynthGUI
{
public:
    SamplerGUI(AudioProcessorValueTreeState& treeState, EquinoxSynthesizer& synth, std::string synthInstance);
    ~SamplerGUI();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    TextButton loadSampleButton { "Load Sample" };
    
    Label samplerLabel;
    
    void browseForSampleFile();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerGUI)
};

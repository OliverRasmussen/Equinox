/*
  ==============================================================================

    FilterEnvelopeGUI.h
    Created: 24 Apr 2020 12:12:22am
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class FilterEnvelopeGUI    : public Component
{
public:
    FilterEnvelopeGUI(AudioProcessorValueTreeState& treeState, std::string synthInstance);
    ~FilterEnvelopeGUI();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    AudioProcessorValueTreeState& treeState;
    std::string synthInstance;
    
    Slider attackSlider, decaySlider, sustainSlider, releaseSlider, cutoffLimitSlider;
    
    Label attackLabel, decayLabel, sustainLabel, releaseLabel, cutoffLimitLabel;
        
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> attackAttachment, decayAttachment, sustainAttachment, releaseAttachment, cutoffLimitAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterEnvelopeGUI)
};

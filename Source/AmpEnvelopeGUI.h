/*
  ==============================================================================

    AmpEnvelopeGUI.h
    Created: 7 Apr 2020 1:28:35am
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class AmpEnvelopeGUI    : public Component
{
public:
    AmpEnvelopeGUI(EquinoxAudioProcessor&, EquinoxSynthesizer&);
    ~AmpEnvelopeGUI();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    EquinoxAudioProcessor& processor;
    EquinoxSynthesizer& synth;
    
    Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
    
    Label attackLabel, decayLabel, sustainLabel, releaseLabel;
        
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> attackAttachment, decayAttachment, sustainAttachment, releaseAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpEnvelopeGUI)
};

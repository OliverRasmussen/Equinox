/*
  ==============================================================================

    SynthGUI.h
    Created: 13 May 2020 9:21:08pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class SynthGUI    : public Component
{
public:
    SynthGUI(StateManager& stateManager, std::string);
    ~SynthGUI();

    void paint (Graphics&) override;
    void resized() override;
    
protected:
    StateManager& stateManager;
    std::string synthInstance;
    
private:
    
    Slider ampSlider, analogSlider, finePitchSlider, pitchTransposeSlider, panningSlider, detuneSlider, portamentoSlider;
    
    Label ampLabel, analogLabel, finePitchLabel, pitchTransposeLabel, panningLabel, detuneLabel, portamentoLabel;
    
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> ampAttachment, analogAttachment, finePitchAttachment, pitchTransposeAttachment, panningAttachment, detuneAttachment, portamentoAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> monoAttachment;
    
    TextButton monoButton { "Mono" };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthGUI)
};

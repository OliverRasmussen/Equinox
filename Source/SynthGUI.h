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
#include "EquinoxSynthesizer.h"

//==============================================================================
/*
*/
class SynthGUI    : public Component, private AudioProcessorValueTreeState::Listener
{
public:
    SynthGUI(EquinoxAudioProcessor&, EquinoxSynthesizer&);
    ~SynthGUI();

    void paint (Graphics&) override;
    void resized() override;
    
protected:
    
    EquinoxAudioProcessor& processor;
    EquinoxSynthesizer& synth;
    
private:
    
    void monoSwitch();
    
    void parameterChanged(const String &parameterID, float newValue) override;
    
    Slider ampSlider, analogSlider, finePitchSlider, pitchTransposeSlider, panningSlider, detuneSlider, portamentoSlider;
    
    Label ampLabel, analogLabel, finePitchLabel, pitchTransposeLabel, panningLabel, detuneLabel, portamentoLabel;
    
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> ampAttachment, analogAttachment, finePitchAttachment, pitchTransposeAttachment, panningAttachment, detuneAttachment, portamentoAttachment;
    
    TextButton monoButton { "Mono" };
    
    std::unique_ptr<AudioParameterBool*> currentVoicingModeState;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthGUI)
};

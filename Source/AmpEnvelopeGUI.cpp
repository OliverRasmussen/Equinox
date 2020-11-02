/*
  ==============================================================================

    AmpEnvelopeGUI.cpp
    Created: 7 Apr 2020 1:28:35am
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "AmpEnvelopeGUI.h"

//==============================================================================
AmpEnvelopeGUI::AmpEnvelopeGUI(EquinoxAudioProcessor& p, EquinoxSynthesizer& s) : processor(p), synth(s)
{
    setSize(200, 200);
    
    // Attack Slider
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.0f, 5.0f);
    attackSlider.setValue(0.0f);
    attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&attackSlider);
    
    attackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "ampAttack" + synth.instanceNumAsString(), attackSlider);
    
    // Attack Label
    attackLabel.setText("A", NotificationType::dontSendNotification);
    attackLabel.setSize(46, 18);
    attackLabel.setMinimumHorizontalScale(0.1f);
    attackLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&attackLabel);
    
    // Decay Slider
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 5.0f);
    decaySlider.setValue(0.1f);
    decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&decaySlider);
    
    decayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "ampDecay" + synth.instanceNumAsString(), decaySlider);
    
    // Decay Label
    decayLabel.setText("D", NotificationType::dontSendNotification);
    decayLabel.setSize(46, 18);
    decayLabel.setMinimumHorizontalScale(0.1f);
    decayLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&decayLabel);
    
    // Sustain Slider
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&sustainSlider);
    
    sustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "ampSustain" + synth.instanceNumAsString(), sustainSlider);
    
    // Sustain Label
    sustainLabel.setText("S", NotificationType::dontSendNotification);
    sustainLabel.setSize(46, 18);
    sustainLabel.setMinimumHorizontalScale(0.1f);
    sustainLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&sustainLabel);
    
    // Release Slider
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5.0f);
    releaseSlider.setValue(0.5f);
    releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&releaseSlider);
    
    releaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "ampRelease" + synth.instanceNumAsString(), releaseSlider);
    
    // Release Label
    releaseLabel.setText("R", NotificationType::dontSendNotification);
    releaseLabel.setSize(46, 18);
    releaseLabel.setMinimumHorizontalScale(0.1f);
    releaseLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&releaseLabel);

}

AmpEnvelopeGUI::~AmpEnvelopeGUI()
{
}

void AmpEnvelopeGUI::paint (Graphics& g)
{
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.setColour(Colours::white);
    g.drawText("Amp Envelope", titleArea, Justification::centredTop);
    
    Rectangle<float> area (25, 25, 160, 150);
    
    g.setColour(Colours::antiquewhite);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void AmpEnvelopeGUI::resized()
{
    attackSlider.setBounds(30, 45, 40, 130);
    attackLabel.setBounds(27, 33, 40, 30);
    
    decaySlider.setBounds(66, 45, 40, 130);
    decayLabel.setBounds(63, 33, 40, 30);
    
    sustainSlider.setBounds(102, 45, 40, 130);
    sustainLabel.setBounds(99, 33, 40, 30);
    
    releaseSlider.setBounds(138, 45, 40, 130);
    releaseLabel.setBounds(135, 33, 40, 30);

}

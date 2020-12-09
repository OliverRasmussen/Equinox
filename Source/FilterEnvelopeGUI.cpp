/*
  ==============================================================================

    FilterEnvelopeGUI.cpp
    Created: 24 Apr 2020 12:12:22am
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "FilterEnvelopeGUI.h"

//==============================================================================
FilterEnvelopeGUI::FilterEnvelopeGUI(std::string synthInstance) : synthInstance(synthInstance)
{
    setSize(200, 200);
    
    // Attack Slider
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.0f, 99.0f);
    attackSlider.setValue(0.0f);
    attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&attackSlider);
    
    attackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(StateManager::GetInstance().getAPVTS(), "filterAttack" + synthInstance, attackSlider);
    
    // Attack Label
    attackLabel.setText("A", NotificationType::dontSendNotification);
    attackLabel.setSize(46, 18);
    attackLabel.setMinimumHorizontalScale(0.1f);
    attackLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&attackLabel);
    
    // Decay Slider
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.0f, 99.0f);
    decaySlider.setValue(0.0f);
    decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&decaySlider);
    
    decayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(StateManager::GetInstance().getAPVTS(), "filterDecay" + synthInstance, decaySlider);
    
    // Decay Label
    decayLabel.setText("D", NotificationType::dontSendNotification);
    decayLabel.setSize(46, 18);
    decayLabel.setMinimumHorizontalScale(0.1f);
    decayLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&decayLabel);
    
    // Sustain Slider
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 99.0f);
    sustainSlider.setValue(50.0f);
    sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&sustainSlider);
    
    sustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(StateManager::GetInstance().getAPVTS(), "filterSustain" + synthInstance, sustainSlider);
    
    // Sustain Label
    sustainLabel.setText("S", NotificationType::dontSendNotification);
    sustainLabel.setSize(46, 18);
    sustainLabel.setMinimumHorizontalScale(0.1f);
    sustainLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&sustainLabel);
    
    // Release Slider
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.0f, 200.0f);
    releaseSlider.setValue(0.0f);
    releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&releaseSlider);
    
    releaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(StateManager::GetInstance().getAPVTS(), "filterRelease" + synthInstance, releaseSlider);
    
    // Release Label
    releaseLabel.setText("R", NotificationType::dontSendNotification);
    releaseLabel.setSize(46, 18);
    releaseLabel.setMinimumHorizontalScale(0.1f);
    releaseLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&releaseLabel);
    
    // Cutoff Limit Slider
    cutoffLimitSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffLimitSlider.setRange(200.0f, 22050.0f);
    cutoffLimitSlider.setValue(10000.0f);
    cutoffLimitSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&cutoffLimitSlider);
    
    cutoffLimitAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(StateManager::GetInstance().getAPVTS(), "envelopeCutoffLimit" + synthInstance, cutoffLimitSlider);
    
    // Attack Label
    cutoffLimitLabel.setText("Cutoff Limit", NotificationType::dontSendNotification);
    cutoffLimitLabel.setSize(46, 18);
    cutoffLimitLabel.setMinimumHorizontalScale(0.1f);
    cutoffLimitLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&cutoffLimitLabel);
        
}

FilterEnvelopeGUI::~FilterEnvelopeGUI()
{
}

void FilterEnvelopeGUI::paint (Graphics& g)
{
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.setColour(Colours::white);
    g.drawText("Filter Envelope", titleArea, Justification::centredTop);
    
    Rectangle<float> area (10, 25, 190, 150);
    
    g.setColour(Colours::antiquewhite);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void FilterEnvelopeGUI::resized()
{
    attackSlider.setBounds(15, 45, 40, 130);
    attackLabel.setBounds(12, 33, 40, 30);
    
    decaySlider.setBounds(51, 45, 40, 130);
    decayLabel.setBounds(48, 33, 40, 30);
    
    sustainSlider.setBounds(87, 45, 40, 130);
    sustainLabel.setBounds(84, 33, 40, 30);
    
    releaseSlider.setBounds(123, 45, 40, 130);
    releaseLabel.setBounds(120, 33, 40, 30);
    
    cutoffLimitSlider.setBounds(150, 45, 45, 45);
    cutoffLimitLabel.setBounds(150, 33, 40, 30);

}

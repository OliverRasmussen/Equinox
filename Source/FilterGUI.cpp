/*
  ==============================================================================

    FilterGUI.cpp
    Created: 7 Apr 2020 2:23:45pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "FilterGUI.h"

//==============================================================================
FilterGUI::FilterGUI(std::string synthInstance) : synthInstance(synthInstance)
{
    setSize (200, 200);
    
    // Filter Menu
    filterMenu.addItem("LPF12", 1);
    filterMenu.addItem("HPF12", 2);
    filterMenu.addItem("LPF24", 3);
    filterMenu.addItem("HPF24", 4);
    filterMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&filterMenu);
    
    filterTypeAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(StateManager::GetInstance().getAPVTS(), "filterType" + synthInstance, filterMenu);
    
    // Cutoff Slider
    cutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffSlider.setRange(50.0f, 22050.0f);
    cutoffSlider.setValue (22050.0f);
    cutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&cutoffSlider);
    
    cutoffAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(StateManager::GetInstance().getAPVTS(), "cutoff" + synthInstance, cutoffSlider);
    
    // cutoff Label
    cutoffLabel.setText("Cutoff", NotificationType::dontSendNotification);
    cutoffLabel.setSize(46, 18);
    cutoffLabel.setMinimumHorizontalScale(0.1f);
    cutoffLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&cutoffLabel);
    
    // Resonance Slider
    resonanceSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    resonanceSlider.setRange(0.0f, 0.9f);
    resonanceSlider.setValue (0.0f);
    resonanceSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&resonanceSlider);
    
    resonanceAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(StateManager::GetInstance().getAPVTS(), "resonance" + synthInstance, resonanceSlider);
    
    // resonance Label
    resonanceLabel.setText("Reso", NotificationType::dontSendNotification);
    resonanceLabel.setSize(46, 18);
    resonanceLabel.setMinimumHorizontalScale(0.1f);
    resonanceLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&resonanceLabel);

    
    // Drive Slider
    driveSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    driveSlider.setRange(1.0f, 15.0f);
    driveSlider.setValue (1.0f);
    driveSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&driveSlider);
    
    driveAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(StateManager::GetInstance().getAPVTS(), "drive" + synthInstance, driveSlider);
    
    // drive Label
    driveLabel.setText("Drive", NotificationType::dontSendNotification);
    driveLabel.setSize(46, 18);
    driveLabel.setMinimumHorizontalScale(0.1f);
    driveLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&driveLabel);

}

FilterGUI::~FilterGUI()
{
}

void FilterGUI::paint (Graphics& g)
{
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    

    g.setColour(Colours::white);
    g.drawText("Filter", titleArea, Justification::centredTop);
    
    Rectangle<float> area (25, 25, 150, 150);
    
    g.setColour(Colours::antiquewhite);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void FilterGUI::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    
    filterMenu.setBounds(area.removeFromTop(20));
    
    cutoffSlider.setBounds(25, 110, 70, 70);
    cutoffLabel.setBounds(36, 98, 40, 30);
    
    resonanceSlider.setBounds(105, 110, 70, 70);
    resonanceLabel.setBounds(116, 98, 40, 30);
    
    driveSlider.setBounds(75, 78, 50, 50);
    driveLabel.setBounds(77, 66, 40, 30);
}

/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    EquinoxSlider.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LabelSlider.h"

//==============================================================================
LabelSlider::LabelSlider(Slider::SliderStyle sliderStyle, float minRangeValue, float maxRangeValue, float startValue, int sliderWidth, int sliderHeight, String parameterID, String labelText, StateManager& state) :
parameterID(parameterID)
{
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.setMinimumHorizontalScale(0.1f);
    label.setJustificationType(Justification::centredTop);
    label.setSize(label.getFont().getStringWidth(labelText), 30);
    addAndMakeVisible(&label);
    
    slider.setSliderStyle(sliderStyle);
    slider.setRange(minRangeValue, maxRangeValue);
    slider.setValue(startValue);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    slider.setSize(sliderWidth, sliderHeight);
    addAndMakeVisible(&slider);
    
    sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(state.getParameters(), parameterID, slider);
    
    slider.onValueChange = [&]() {slider.setTooltip((String)slider.getValue());};
}

LabelSlider::~LabelSlider()
{
}

void LabelSlider::setPosition(int x, int y)
{
    setBounds(x, y, getWidth(), getHeight());
}

void LabelSlider::setSliderComponentBounds(int x, int y, int width, int height)
{
    int sliderWidth = width == -1 ? slider.getWidth() : width;
    int sliderHeight = height == -1 ? slider.getHeight() : height;
    slider.setBounds(x, y, sliderWidth, sliderHeight);
}

Rectangle<int> LabelSlider::getSliderComponentBounds() const
{
    return slider.getBounds();
}

void LabelSlider::setLabelComponentBounds(int x, int y, int width, int height)
{
    int labelWidth = width == -1 ? label.getWidth() : width;
    int labelHeight = height == -1 ? label.getHeight() : height;
    label.setBounds(x, y, labelWidth, labelHeight);
}

Rectangle<int> LabelSlider::getLabelComponentBounds() const
{
    return label.getBounds();
}

String LabelSlider::getID() const
{
    return parameterID;
}

Slider& LabelSlider::getSliderComponent()
{
    return slider;
}

Label& LabelSlider::getLabelComponent()
{
    return label;
}

void LabelSlider::center()
{
    setSliderComponentBounds((getWidth() * 0.5f) - (slider.getWidth() * 0.5), slider.getY());
    
    setLabelComponentBounds(0, label.getY());
}

void LabelSlider::paint (juce::Graphics& g)
{

}

void LabelSlider::resized()
{

}

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
#include "EquinoxSlider.h"

//==============================================================================
EquinoxSlider::EquinoxSlider(Slider::SliderStyle sliderStyle, float minRangeValue, float maxRangeValue, float startValue, int sliderWidth, int sliderHeight, String parameterID, String labelText, StateManager& state) : parameterID(parameterID)
{
    slider.setSliderStyle(sliderStyle);
    slider.setRange(minRangeValue, maxRangeValue);
    slider.setValue(startValue);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    slider.setSize(sliderWidth, sliderHeight);
    addAndMakeVisible(&slider);
    
    sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(state.getParameters(), parameterID, slider);
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.setMinimumHorizontalScale(0.1f);
    label.setJustificationType(Justification::centredTop);
    addAndMakeVisible(&label);
}

EquinoxSlider::~EquinoxSlider()
{
}

void EquinoxSlider::setPosition(int x, int y)
{
    setBounds(x, y, getWidth(), getHeight());
}

String EquinoxSlider::getID() const
{
    return parameterID;
}

Slider& EquinoxSlider::getSliderComponent()
{
    return slider;
}

Label& EquinoxSlider::getLabelComponent()
{
    return label;
}

void EquinoxSlider::paint (juce::Graphics& g)
{
}

void EquinoxSlider::resized()
{
}

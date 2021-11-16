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
LabelSlider::LabelSlider(StateManager& state, Slider::SliderStyle sliderStyle, float minSliderValue, float maxSliderValue,
                         int sliderWidth, int sliderHeight, String paramID, String labelText, String valueSuffix, String valuePrefix, unsigned int valueMaxDecimals) :
                         parameterID(paramID), suffix(valueSuffix), prefix(valuePrefix), minValue(minSliderValue), maxValue(maxSliderValue) , maxDecimals(valueMaxDecimals)
{
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.setMinimumHorizontalScale(0.1f);
    label.setJustificationType(Justification::centredTop);
    label.setSize(label.getFont().getStringWidth(labelText), 30);
    addAndMakeVisible(&label);
    
    slider.setSliderStyle(sliderStyle);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    slider.setSize(sliderWidth, sliderHeight);
    addAndMakeVisible(&slider);

    slider.setPopupDisplayEnabled(true, false, nullptr, -1);
    
    sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(state.getParameters(), parameterID, slider);

    // Formatting the parameters value to match the corresponding value on the sliders valuerange,
    // and adding potential prefix and suffix, before returning the value as a string
    slider.textFromValueFunction = [&](double value)
    {
        auto sourceParamRange = state.getParameters().getParameterRange(parameterID);

        float scaledValue = jmap((float)value, sourceParamRange.start, sourceParamRange.end, minValue, maxValue);

        String scaledValueStr = String(scaledValue, maxDecimals, false);

        if (scaledValueStr.containsChar('.') && maxDecimals == 0)
        {
            scaledValue = round(scaledValue);
            scaledValueStr = String(scaledValue);
        }

        String textFromValue = prefix + scaledValueStr + suffix;

        return textFromValue;
    };

    
    // Removing potential prefix and suffix from the passed in text,
    // and formatting its numerical value to match the corresponding 
    // value on the parameters valuerange, before returning the string as a value
    slider.valueFromTextFunction = [&](const String text)
    {
        auto targetParamRange = state.getParameters().getParameterRange(parameterID);

        float value = text.substring(prefix.length()).dropLastCharacters(suffix.length()).trim().getFloatValue();

        if (value > maxValue)
        {
            value = maxValue;
        }
        else if (value < minValue)
        {
            value = minValue;
        }

        float valueFromText = jmap(value, minValue, maxValue, targetParamRange.start, targetParamRange.end);

        return valueFromText;
    };

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

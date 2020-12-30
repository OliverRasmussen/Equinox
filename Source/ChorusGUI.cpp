/*
  ==============================================================================

    Chorus.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChorusGUI.h"

//==============================================================================
ChorusGUI::ChorusGUI(StateManager& stateManager)
{
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "chorusMix", "Mix", stateManager));
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 5.0f, 1.0f, 40, 40, "chorusRate", "Rate", stateManager));
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 0.15f, 0.0f, 40, 40, "chorusDepth", "Depth", stateManager));
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 1.0f, 30.0f, 1.0f, 40, 40, "chorusDelay", "Delay", stateManager));
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, -1.0f, 1.0f, 0.0f, 40, 40, "chorusFeedback", "Feedback", stateManager));
}

ChorusGUI::~ChorusGUI()
{
}

void ChorusGUI::paint (juce::Graphics& g)
{
    drawTitle(g, Colours::white, "Chorus", 0, 5, getWidth(), 20);
    drawRectangle(g, Colours::darkgrey, 0, 0, getWidth(), getHeight(), 1.0f, 2.0f);
}

void ChorusGUI::resized()
{
    setHorizontalSliderLayout(25, 35);
}

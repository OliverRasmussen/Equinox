/*
  ==============================================================================

    DelayGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayGUI.h"

//==============================================================================
DelayGUI::DelayGUI(StateManager& stateManager)
{
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "delayMix", "Mix", stateManager));
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 1.0f, 8.0f, 1.0f, 40, 40, "delayTime", "Time", stateManager));
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 100.0f, 0.0f, 40, 40, "delayFeedback", "Feedback", stateManager));
}

DelayGUI::~DelayGUI()
{
}

void DelayGUI::paint (juce::Graphics& g)
{
    drawTitle(g, Colours::white, "Delay", 0, 5, getWidth(), 20);
    drawRectangle(g, Colours::darkgrey, 0, 0, getWidth(), getHeight());
}

void DelayGUI::resized()
{
    setHorizontalSliderLayout(25, 35);
}

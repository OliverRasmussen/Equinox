/*
  ==============================================================================

    ReverbGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbGUI.h"

//==============================================================================
ReverbGUI::ReverbGUI(StateManager& stateManager)
{
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "reverbMix", "Mix", stateManager));
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "reverbRoomsize", "Size", stateManager));
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "reverbDamping", "Damping", stateManager));
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "reverbWidth", "Width", stateManager));
}

ReverbGUI::~ReverbGUI()
{
}

void ReverbGUI::paint (juce::Graphics& g)
{
    drawTitle(g, Colours::white, "Reverb", 0, 5, getWidth(), 20);
    drawRectangle(g, Colours::darkgrey, 0, 0, getWidth(), getHeight(), 1.0f, 2.0f);
}

void ReverbGUI::resized()
{
    setHorizontalSliderLayout(25, 35);
}


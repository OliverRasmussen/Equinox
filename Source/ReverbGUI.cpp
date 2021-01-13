/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    ReverbGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbGUI.h"

//==============================================================================
ReverbGUI::ReverbGUI(StateManager& stateManager)
{
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "reverbMix", "Mix", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "reverbRoomsize", "Size", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "reverbDamping", "Damping", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "reverbWidth", "Width", stateManager));
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


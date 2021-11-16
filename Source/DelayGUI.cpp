/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    DelayGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayGUI.h"

//==============================================================================
DelayGUI::DelayGUI(StateManager& stateManager)
{
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 100.0f, 40, 40, "delayMix", "Mix", "%"));
    
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, 1.0f, 8.0f, 40, 40, "delayTime", "Time", "", "1/"));
    
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 100.0f, 40, 40, "delayFeedback", "Feedback"));
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

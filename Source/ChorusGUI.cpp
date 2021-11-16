/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    Chorus.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChorusGUI.h"

//==============================================================================
ChorusGUI::ChorusGUI(StateManager& stateManager)
{
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 100.0f, 40, 40, "chorusMix", "Mix", "%"));
    
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 5.0f, 40, 40, "chorusRate", "Rate", "Hz", "", 2));
    
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 100.0f, 40, 40, "chorusDepth", "Depth", "%"));
    
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 30.0f, 40, 40, "chorusDelay", "Delay", "ms"));
    
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, -100.0f, 100.0f, 40, 40, "chorusFeedback", "Feedback"));
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

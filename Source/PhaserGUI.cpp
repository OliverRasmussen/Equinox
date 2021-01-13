/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    PhaserGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PhaserGUI.h"

//==============================================================================
PhaserGUI::PhaserGUI(StateManager& stateManager)
{
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "phaserMix", "Mix", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "phaserRate", "Rate", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 1.0f, 0.0f, 40, 40, "phaserDepth", "Depth", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 100.0f, 22000.0f, 11000.0f, 40, 40, "phaserFrequency", "Freq", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, -0.9f, 0.9f, 0.0f, 40, 40, "phaserFeedback", "Feedback", stateManager));
}

PhaserGUI::~PhaserGUI()
{
}

void PhaserGUI::paint (juce::Graphics& g)
{
    drawTitle(g, Colours::white, "Phaser", 0, 5, getWidth(), 20);
    drawRectangle(g, Colours::darkgrey, 0, 0, getWidth(), getHeight(), 1.0f, 2.0f);
}

void PhaserGUI::resized()
{
    setHorizontalSliderLayout(25, 35);
}

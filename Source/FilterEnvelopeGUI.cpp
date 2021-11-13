/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    FilterEnvelopeGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "FilterEnvelopeGUI.h"

//==============================================================================
FilterEnvelopeGUI::FilterEnvelopeGUI(StateManager& stateManager, std::string synthInstance)
{
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.0f, 99.0f, 0.0f, 40, 155, "filterAttack" + synthInstance, "A", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.0f, 99.0f, 0.0f, 40, 155, "filterDecay" + synthInstance, "D", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.0f, 99.0f, 50.0f, 40, 155, "filterSustain" + synthInstance, "S", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.0f, 200.0f, 0.0f, 40, 155, "filterRelease" + synthInstance, "R", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 200.0f, 22050.0f, 10000.0f, 45, 45, "envelopeCutoffLimit" + synthInstance, "Limit", stateManager));
}

FilterEnvelopeGUI::~FilterEnvelopeGUI()
{
}

void FilterEnvelopeGUI::paint (Graphics& g)
{
    drawTitle(g, Colours::white, "Filter Envelope",0, 15, getWidth(), 20);
    
    int rectXPos = 5;
    int rectYPos = 30;
    drawRectangle(g, Colours::darkgrey, rectXPos, rectYPos, getWidth() - rectXPos, getLocalBounds().getHeight() - (rectYPos * 2), 20.0f, 2.0f);
}

void FilterEnvelopeGUI::resized()
{
    setHorizontalSliderLayout(35, 50, 20, 20);
}

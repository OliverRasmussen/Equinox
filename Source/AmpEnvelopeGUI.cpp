/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    AmpEnvelopeGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "AmpEnvelopeGUI.h"

//==============================================================================
AmpEnvelopeGUI::AmpEnvelopeGUI(StateManager& stateManager, std::string synthInstance)
{
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.001f, 5.0f, 0.1f, 40, 155, "ampAttack" + synthInstance, "A", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.01f, 5.0f, 0.1f, 40, 155, "ampDecay" + synthInstance, "D", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.0f, 1.0f, 0.8f, 40, 155, "ampSustain" + synthInstance, "S", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.001f, 5.0f, 0.5f, 40, 155, "ampRelease" + synthInstance, "R", stateManager));
}

AmpEnvelopeGUI::~AmpEnvelopeGUI()
{
}

void AmpEnvelopeGUI::paint (Graphics& g)
{
    
    drawTitle(g, Colours::white, "Amp Envelope",0, 15, getWidth(), 20);
    
    int rectXPos = 5;
    int rectYPos = 30;
    drawRectangle(g, Colours::darkgrey, rectXPos, rectYPos, getWidth() - rectXPos, getLocalBounds().getHeight() - (rectYPos * 2), 20.0f, 2.0f);
}

void AmpEnvelopeGUI::resized()
{
    setHorizontalSliderLayout(35, 50, 20, 20);
}

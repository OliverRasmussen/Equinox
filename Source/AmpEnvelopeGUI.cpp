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
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.001f, 5.0f, 0.1f, 40, 125, "ampAttack" + synthInstance, "A", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.01f, 5.0f, 0.1f, 40, 125, "ampDecay" + synthInstance, "D", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.0f, 1.0f, 0.8f, 40, 125, "ampSustain" + synthInstance, "S", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.001f, 5.0f, 0.5f, 40, 125, "ampRelease" + synthInstance, "R", stateManager));
}

AmpEnvelopeGUI::~AmpEnvelopeGUI()
{
}

void AmpEnvelopeGUI::paint (Graphics& g)
{
    drawTitle(g, Colours::white, "Amp Envelope",0, 15, getWidth(), 20);
    drawRectangle(g, Colours::darkgrey, 5, 30, getWidth() - 5, 145, 20.0f, 2.0f);
}

void AmpEnvelopeGUI::resized()
{
    setHorizontalSliderLayout(35, 50, 20, 20);
}

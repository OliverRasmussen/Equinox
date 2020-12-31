/*
  ==============================================================================

    AmpEnvelopeGUI.cpp
    Created: 7 Apr 2020 1:28:35am
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "AmpEnvelopeGUI.h"

//==============================================================================
AmpEnvelopeGUI::AmpEnvelopeGUI(StateManager& stateManager, std::string synthInstance)
{
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.01f, 5.0f, 0.1f, 40, 130, "ampAttack" + synthInstance, "A", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.01f, 5.0f, 0.1f, 40, 130, "ampDecay" + synthInstance, "D", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.0f, 1.0f, 0.8f, 40, 130, "ampSustain" + synthInstance, "S", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::LinearVertical, 0.1f, 5.0f, 0.5f, 40, 130, "ampRelease" + synthInstance, "R", stateManager));
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
    setHorizontalSliderLayout(35, 45, 20, 20);
}

/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    FilterGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "FilterGUI.h"

//==============================================================================
FilterGUI::FilterGUI(StateManager& stateManager, std::string synthInstance) : synthInstance(synthInstance)
{ 
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, 5.0f, 22050.0f, 70, 70, "cutoff" + synthInstance, "Cutoff", "Hz"));
    
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 100.0f, 50, 50, "drive" + synthInstance, "Drive"));
    
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 100.0f, 70, 70, "resonance" + synthInstance, "Resonance"));

    filterMenu.addItem("LPF12", 1);
    filterMenu.addItem("HPF12", 2);
    filterMenu.addItem("LPF24", 3);
    filterMenu.addItem("HPF24", 4);
    filterMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&filterMenu);

    filterTypeAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(stateManager.getParameters(), "filterType" + synthInstance, filterMenu);
    
}

FilterGUI::~FilterGUI()
{
}

void FilterGUI::paint (Graphics& g)
{
    drawTitle(g, Colours::white, "Filter",0, 15, getWidth(), 20);
    
    int rectXPos = 5;
    int rectYPos = 30;
    drawRectangle(g, Colours::darkgrey, rectXPos, rectYPos, getWidth() - rectXPos, getLocalBounds().getHeight() - (rectYPos * 2), 20.0f, 2.0f);
}

void FilterGUI::resized()
{
    filterMenu.setSize(100, 20);
    filterMenu.setBounds((getWidth() * 0.5f) - (filterMenu.getWidth() * 0.5f), 40, filterMenu.getWidth(), filterMenu.getHeight());
    
    setHorizontalSliderLayout(100, 110, 25, 25);
    
    LabelSlider& driveSlider = *getSlider("drive" + synthInstance);
    driveSlider.setPosition(driveSlider.getX(), -30);
}

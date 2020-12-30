/*
  ==============================================================================

    FilterGUI.cpp
    Created: 7 Apr 2020 2:23:45pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "FilterGUI.h"

//==============================================================================
FilterGUI::FilterGUI(StateManager& stateManager, std::string synthInstance) : synthInstance(synthInstance)
{
    filterMenu.addItem("LPF12", 1);
    filterMenu.addItem("HPF12", 2);
    filterMenu.addItem("LPF24", 3);
    filterMenu.addItem("HPF24", 4);
    filterMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&filterMenu);
    
    filterTypeAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(stateManager.getParameters(), "filterType" + synthInstance, filterMenu);
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 50.0f, 22050.0f, 22050.0f, 70, 70, "cutoff" + synthInstance, "Cutoff", stateManager));
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 1.0f, 15.0f, 1.0f, 50, 50, "drive" + synthInstance, "Drive", stateManager));
    
    addSliderWithLabel(std::make_shared<EquinoxSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 0.9f, 0.0f, 70, 70, "resonance" + synthInstance, "Resonance", stateManager));
    
}

FilterGUI::~FilterGUI()
{
}

void FilterGUI::paint (Graphics& g)
{
    drawTitle(g, Colours::white, "Filter",0, 15, getWidth(), 20);
    drawRectangle(g, Colours::darkgrey, 5, 30, getWidth() - 5, 145, 20.0f, 2.0f);
}

void FilterGUI::resized()
{
    filterMenu.setSize(100, 20);
    filterMenu.setBounds((getWidth() * 0.5f) - (filterMenu.getWidth() * 0.5f), 40, filterMenu.getWidth(), filterMenu.getHeight());
    
    setHorizontalSliderLayout(100, 110, 25, 25);
    
    EquinoxSlider& driveSlider = *getSlider("drive" + synthInstance);
    driveSlider.setPosition(driveSlider.getX(), -30);
}

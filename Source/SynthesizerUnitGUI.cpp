/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SynthesizerUnitGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "SynthesizerUnitGUI.h"

//==============================================================================

int SynthesizerUnitGUI::objCounter;

SynthesizerUnitGUI::SynthesizerUnitGUI(StateManager& stateManager, std::string instanceNum) : synthMenuGUI(stateManager, instanceNum), ampEnvelopeGUI(stateManager, instanceNum), filterEnvelopeGUI(stateManager, instanceNum), filterGUI(stateManager, instanceNum)

{
    instanceNum = ++objCounter;
    addAndMakeVisible(&synthMenuGUI);
    addAndMakeVisible(&ampEnvelopeGUI);
    addAndMakeVisible(&filterEnvelopeGUI);
    addAndMakeVisible(&filterGUI);
}

SynthesizerUnitGUI::~SynthesizerUnitGUI()
{
    --objCounter;
}

int SynthesizerUnitGUI::getNumInstances()
{
    return objCounter;
}

void SynthesizerUnitGUI::paint (Graphics& g)
{
}

void SynthesizerUnitGUI::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    const int componentCount = 4;
    
    const int componentWidth = area.getWidth() / componentCount;
    const int componentHeight = 200;
    
    synthMenuGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    ampEnvelopeGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    filterEnvelopeGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}

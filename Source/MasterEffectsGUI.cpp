/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    MasterEffectsGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MasterEffectsGUI.h"

//==============================================================================
MasterEffectsGUI::MasterEffectsGUI(StateManager& state) : chorusGUI(state), phaserGUI(state), reverbGUI(state), delayGUI(state)
{
    addAndMakeVisible(&chorusGUI);
    addAndMakeVisible(&phaserGUI);
    addAndMakeVisible(&reverbGUI);
    addAndMakeVisible(&delayGUI);
}

MasterEffectsGUI::~MasterEffectsGUI()
{
}

void MasterEffectsGUI::paint (juce::Graphics& g)
{
    Rectangle<int> titleArea (5, 5, 67, 22);

    g.setColour(Colours::white);
    g.drawText("Master FX", titleArea, Justification::topLeft);
    
    Rectangle<float> area (0, 0, titleArea.getWidth(), titleArea.getHeight());
    
    g.setColour(Colours::darkgrey);
    g.drawRoundedRectangle(area, 1.0f, 2.0f);
}

void MasterEffectsGUI::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    const int componentCount = 4;
    
    const int componentWidth = area.getWidth() / componentCount;
    const int componentHeight = 80;
    
    chorusGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));

    phaserGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));

    reverbGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));

    delayGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}

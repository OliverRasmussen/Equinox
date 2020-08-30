/*
  ==============================================================================

    SynthesizerUnitGUI.cpp
    Created: 19 May 2020 6:30:24pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "SynthesizerUnitGUI.h"

//==============================================================================

int SynthesizerUnitGUI::objCounter;

SynthesizerUnitGUI::SynthesizerUnitGUI(EquinoxAudioProcessor& p, EquinoxSynthesizer& s) : synthMenuGUI(p, s), ampEnvelopeGUI(p, s), filterEnvelopeGUI(p, s), filterGUI(p, s)
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
   //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void SynthesizerUnitGUI::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    synthMenuGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    ampEnvelopeGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    filterEnvelopeGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}

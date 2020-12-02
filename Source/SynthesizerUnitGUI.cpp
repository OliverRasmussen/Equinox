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

SynthesizerUnitGUI::SynthesizerUnitGUI(AudioProcessorValueTreeState& treeState, EquinoxSynthesizer& synth) : synthMenuGUI(treeState, synth, synth.instanceNumAsString()), ampEnvelopeGUI(treeState, synth.instanceNumAsString()), filterEnvelopeGUI(treeState, synth.instanceNumAsString()), filterGUI(treeState, synth.instanceNumAsString())
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

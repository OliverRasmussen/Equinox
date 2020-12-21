/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EquinoxAudioProcessorEditor::EquinoxAudioProcessorEditor (EquinoxAudioProcessor& p)
    : AudioProcessorEditor (&p), synthUnitGUI1(p.stateManager, p.synthLayer1.instanceNumAsString()), synthUnitGUI2(p.stateManager, p.synthLayer2.instanceNumAsString()), synthUnitGUI3(p.stateManager, p.synthLayer3.instanceNumAsString()), mainMenu(p.stateManager)
{
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colour(30.0f, 124.0f, 105.0f));
    
    
    //synthInstanceNum = SynthesizerUnitGUI::getNumInstances();
    int numberOfSynths = 3;
    setSize (800, 200 + (200 * numberOfSynths));
    
    
    addAndMakeVisible(&synthUnitGUI1);
    addAndMakeVisible(&synthUnitGUI2);
    addAndMakeVisible(&synthUnitGUI3);
    
    addAndMakeVisible(&mainMenu);
}

EquinoxAudioProcessorEditor::~EquinoxAudioProcessorEditor()
{
}

//==============================================================================
void EquinoxAudioProcessorEditor::paint (Graphics& g)
{
    Image background = ImageCache::getFromMemory(BinaryData::Background_png, BinaryData::Background_pngSize);
    g.drawImageAt(background, -125, 0);
    //mainMenu.paint(g);
}

void EquinoxAudioProcessorEditor::resized()
{
    mainMenu.setBounds(0, 0, 800, 170);
    synthUnitGUI1.setBounds(0, 170, 800, 200);
    synthUnitGUI2.setBounds(0, 380, 800, 200);
    synthUnitGUI3.setBounds(0, 590, 800, 200);
}

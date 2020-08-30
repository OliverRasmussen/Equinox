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
    : AudioProcessorEditor (&p), synthUnitGUI1(p, p.synthLayer1), synthUnitGUI2(p, p.synthLayer2), synthUnitGUI3(p, p.synthLayer3)
{
    
    synthInstanceNum = SynthesizerUnitGUI::getNumInstances();
    setSize (800, 100 + (200 * synthInstanceNum));
    

    addAndMakeVisible(&synthUnitGUI1);
    addAndMakeVisible(&synthUnitGUI2);
    addAndMakeVisible(&synthUnitGUI3);
}

EquinoxAudioProcessorEditor::~EquinoxAudioProcessorEditor()
{
}

//==============================================================================
void EquinoxAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    Image background = ImageCache::getFromMemory(BinaryData::testbackgroundsmall_png, BinaryData::testbackgroundsmall_pngSize);
    g.drawImageAt(background, 0, 0);
}

void EquinoxAudioProcessorEditor::resized()
{
    synthUnitGUI1.setBounds(0, 100, 800, 200);
    synthUnitGUI2.setBounds(0, 300, 800, 200);
    synthUnitGUI3.setBounds(0, 500, 800, 200);
}

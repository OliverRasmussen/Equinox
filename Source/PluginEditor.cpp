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
    : AudioProcessorEditor (&p), synthLayerTabMenu(TabbedButtonBar::Orientation::TabsAtTop), synthUnitGUI1(p.stateManager, p.synthLayer1.instanceNumAsString()), synthUnitGUI2(p.stateManager, p.synthLayer2.instanceNumAsString()), synthUnitGUI3(p.stateManager, p.synthLayer3.instanceNumAsString()), mainMenu(p.presetManager), masterEffects(p.stateManager), keyboardComponent(p.midiKeyboardState, MidiKeyboardComponent::Orientation::horizontalKeyboard)
{
    setLookAndFeel(&lookAndFeel);
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colour(30.0f, 124.0f, 105.0f));
    
    
    synthInstanceNum = 3;
    
    synthLayerTabMenu.addTab("A", Colours::transparentBlack, &synthUnitGUI1, false);
    synthLayerTabMenu.addTab("B", Colours::transparentBlack, &synthUnitGUI2, false);
    synthLayerTabMenu.addTab("C", Colours::transparentBlack, &synthUnitGUI3, false);
    
    synthLayerTabMenu.setCurrentTabIndex(0);
    
    addAndMakeVisible(&synthLayerTabMenu);
    
    int height = 330 + 200;// (200 * synthInstanceNum);
    int width = 1050;
    setSize (width, height);
    
    addAndMakeVisible(&mainMenu);
    
    addAndMakeVisible(&masterEffects);
    
    keyboardComponent.clearKeyMappings();
    keyboardComponent.setBounds(0, 850, getWidth(), 80);
    addAndMakeVisible(&keyboardComponent);
    
    setBufferedToImage(true);
    
}

EquinoxAudioProcessorEditor::~EquinoxAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void EquinoxAudioProcessorEditor::paint (Graphics& g)
{
    Image background = ImageCache::getFromMemory(BinaryData::Background_png, BinaryData::Background_pngSize);
    g.drawImageAt(background, 0, 0);
}

void EquinoxAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    mainMenu.setBounds(0, 0, getBounds().getWidth(), 170);
  
    synthLayerTabMenu.setBounds(0, 170, area.getWidth(), 280);
//    synthUnitGUI1.setBounds(0, 170, area.getWidth(), 200);
//    synthUnitGUI2.setBounds(0, 370, area.getWidth(), 200);
//    synthUnitGUI3.setBounds(0, 570, area.getWidth(), 200);
    
    masterEffects.setBounds(0, 450, area.getWidth(), 80);
}

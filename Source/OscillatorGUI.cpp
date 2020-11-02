/*
  ==============================================================================

    OscillatorGUI.cpp
    Created: 6 Apr 2020 11:26:08pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "OscillatorGUI.h"

//==============================================================================
OscillatorGUI::OscillatorGUI(EquinoxAudioProcessor& p, EquinoxSynthesizer& s) : SynthGUI(p, s)
{
    
    // Waveform menu
    waveformMenu.addItem("Sine", 1);
    waveformMenu.addItem("Saw", 2);
    waveformMenu.addItem("Triangle", 3);
    waveformMenu.addItem("Square", 4);
    waveformMenu.addItem("Noise", 5);
    waveformMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&waveformMenu);
    
    waveformMenuAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.treeState, "waveform" + synth.instanceNumAsString(), waveformMenu);
    
    // Waveform Label
    waveformLabel.setText("Oscillator", NotificationType::dontSendNotification);
    waveformLabel.setSize(48, 18);
    waveformLabel.setMinimumHorizontalScale(0.1f);
    waveformLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&waveformLabel);

}

OscillatorGUI::~OscillatorGUI()
{
}

void OscillatorGUI::paint (Graphics& g)
{
    
}

void OscillatorGUI::resized()
{

    waveformMenu.setBounds(5, 20, 100, 20);

}

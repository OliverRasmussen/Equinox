/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    OscillatorGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "OscillatorGUI.h"

//==============================================================================
OscillatorGUI::OscillatorGUI(StateManager& stateManager, std::string synthInstance) : SynthGUI(stateManager, synthInstance)
{
    // Waveform menu
    waveformMenu.addItem("Sine", 1);
    waveformMenu.addItem("Saw", 2);
    waveformMenu.addItem("Triangle", 3);
    waveformMenu.addItem("Square", 4);
    waveformMenu.addItem("Noise", 5);
    waveformMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&waveformMenu);
    
    waveformMenuAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(stateManager.getParameters(), "waveform" + synthInstance, waveformMenu);
    
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
    SynthGUI::resized();
}

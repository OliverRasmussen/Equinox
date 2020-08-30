/*
  ==============================================================================

    SamplerGUI.cpp
    Created: 13 May 2020 8:43:49pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "SamplerGUI.h"

//==============================================================================
SamplerGUI::SamplerGUI(EquinoxAudioProcessor& p, EquinoxSynthesizer& s) : SynthGUI(p, s)
{
    loadSampleButton.onClick = [&]() {synth.loadNewSample();};
    addAndMakeVisible(loadSampleButton);
    
    // Sampler Label
    samplerLabel.setText("Sampler", NotificationType::dontSendNotification);
    samplerLabel.setSize(46, 18);
    samplerLabel.setMinimumHorizontalScale(0.1f);
    samplerLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&samplerLabel);
}

SamplerGUI::~SamplerGUI()
{
}

void SamplerGUI::paint (Graphics& g)
{
   
}

void SamplerGUI::resized()
{

    loadSampleButton.setBounds(5, 20, 100, 20);
}

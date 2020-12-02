/*
  ==============================================================================

    SamplerGUI.cpp
    Created: 13 May 2020 8:43:49pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "SamplerGUI.h"

//==============================================================================
SamplerGUI::SamplerGUI(AudioProcessorValueTreeState& treeState, EquinoxSynthesizer& synth, std::string synthInstance) : SynthGUI(treeState, synth,  synthInstance)
{
    loadSampleButton.onClick = [&]() {browseForSampleFile();};
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

void SamplerGUI::browseForSampleFile()
{
    FileChooser fileChooser("Load audio sample", File(), "*.wav;*.mp3;*.flac", true, false, nullptr);
    
    if (fileChooser.browseForFileToOpen())
    {
        File sampleFile = fileChooser.getResult();
        String sampleName = sampleFile.getFileName();
        
        int fileExtensionStartIndex = sampleName.indexOfChar('.');
        sampleName = sampleName.substring(0, fileExtensionStartIndex);
        
        synth.loadSampleFromFile(sampleFile, sampleName);
    }
}

void SamplerGUI::paint (Graphics& g)
{
   
}

void SamplerGUI::resized()
{

    loadSampleButton.setBounds(5, 20, 100, 20);
}

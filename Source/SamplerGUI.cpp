/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SamplerGUI.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "SamplerGUI.h"

//==============================================================================
SamplerGUI::SamplerGUI(StateManager& stateManager, std::string synthInstance) : SynthGUI(stateManager, synthInstance)
{
    loadSampleButton.onClick = [&]() {browseForSampleFile();};
    addAndMakeVisible(loadSampleButton);
    
    // Sampler Label
    samplerLabel.setText("Sampler", NotificationType::dontSendNotification);
    samplerLabel.setSize(46, 18);
    samplerLabel.setMinimumHorizontalScale(0.1f);
    samplerLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&samplerLabel);
    
    // sample start time labelslider
    addLabelSlider(std::make_shared<LabelSlider>(stateManager, Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 100.0f, 40, 40, "sampleStartTime" + synthInstance, "Start time"));
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
        
        stateManager.addAudioSample(sampleFile, "audiosample" + synthInstance);
    }
}

void SamplerGUI::paint (Graphics& g)
{
   
}

void SamplerGUI::resized()
{
    loadSampleButton.setBounds(5, 20, 100, 20);
    
    LabelSlider& sampleStartSlider = *getSlider("sampleStartTime" + synthInstance);
    sampleStartSlider.setBounds(105, 46, 50, 70);
    sampleStartSlider.setSliderComponentBounds(sampleStartSlider.getSliderComponentBounds().getX(), 14);
    sampleStartSlider.setLabelComponentBounds(sampleStartSlider.getLabelComponentBounds().getX(), 2, sampleStartSlider.getWidth(), 30);
    sampleStartSlider.center();
    
    SynthGUI::resized();
}

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SynthesizerUnitGUI.h"

//==============================================================================
/**
*/
class EquinoxAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    EquinoxAudioProcessorEditor (EquinoxAudioProcessor&);
    ~EquinoxAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    int synthInstanceNum;
    SynthesizerUnitGUI synthUnitGUI1, synthUnitGUI2, synthUnitGUI3;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EquinoxAudioProcessorEditor)
};

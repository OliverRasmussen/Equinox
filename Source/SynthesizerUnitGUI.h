/*
  ==============================================================================

    SynthesizerUnitGUI.h
    Created: 19 May 2020 6:30:24pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SynthMenuGUI.h"
#include "AmpEnvelopeGUI.h"
#include "FilterEnvelopeGUI.h"
#include "FilterGUI.h"

//==============================================================================
/*
*/
class SynthesizerUnitGUI    : public Component
{
public:
    SynthesizerUnitGUI(EquinoxSynthesizer&);
    ~SynthesizerUnitGUI();
    
    static int getNumInstances();

    void paint (Graphics&) override;
    void resized() override;

private:

    static int objCounter;
    
    int instanceNum;
    
    SynthMenuGUI synthMenuGUI;
    
    AmpEnvelopeGUI ampEnvelopeGUI;
    
    FilterEnvelopeGUI filterEnvelopeGUI;
    
    FilterGUI filterGUI;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthesizerUnitGUI)
};

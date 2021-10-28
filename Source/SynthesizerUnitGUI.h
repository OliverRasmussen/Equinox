/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SynthesizerUnitGUI.h
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
    SynthesizerUnitGUI(StateManager&, std::string);
    ~SynthesizerUnitGUI();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    SynthMenuGUI synthMenuGUI;
    
    AmpEnvelopeGUI ampEnvelopeGUI;
    
    FilterEnvelopeGUI filterEnvelopeGUI;
    
    FilterGUI filterGUI;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthesizerUnitGUI)
};

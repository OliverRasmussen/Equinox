/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SamplerGUI.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "SynthGUI.h"

//==============================================================================
/*
*/
class SamplerGUI    : public SynthGUI
{
public:
    SamplerGUI(StateManager& stateManager, std::string);
    ~SamplerGUI();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    TextButton loadSampleButton { "Load Sample" };
    
    Label samplerLabel;
    
    void browseForSampleFile();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerGUI)
};

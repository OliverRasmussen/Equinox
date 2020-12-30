/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    MasterEffectsGUI.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StateManager.h"
#include "ChorusGUI.h"
#include "PhaserGUI.h"
#include "ReverbGUI.h"
#include "DelayGUI.h"

//==============================================================================
/*
*/
class MasterEffectsGUI  : public juce::Component
{
public:
    MasterEffectsGUI(StateManager& state);
    ~MasterEffectsGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ChorusGUI chorusGUI;
    PhaserGUI phaserGUI;
    ReverbGUI reverbGUI;
    DelayGUI delayGUI;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterEffectsGUI)
};

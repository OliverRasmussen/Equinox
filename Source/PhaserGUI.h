/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    PhaserGUI.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include "EquinoxComponent.h"
#include "StateManager.h"

//==============================================================================
/*
*/
class PhaserGUI  : public EquinoxComponent
{
public:
    PhaserGUI(StateManager& stateManager);
    ~PhaserGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserGUI)
};

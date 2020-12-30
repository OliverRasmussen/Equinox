/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    FilterGUI.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include "EquinoxComponent.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class FilterGUI    : public EquinoxComponent
{
public:
    FilterGUI(StateManager& stateManager, std::string);
    ~FilterGUI();

    void paint (Graphics&) override;
    void resized() override;

private:
    String synthInstance;
    ComboBox filterMenu;
    std::unique_ptr <AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGUI)
};

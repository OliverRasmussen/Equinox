/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    FilterEnvelopeGUI.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "EquinoxComponent.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class FilterEnvelopeGUI    : public EquinoxComponent
{
public:
    FilterEnvelopeGUI(StateManager& stateManager, std::string);
    ~FilterEnvelopeGUI();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterEnvelopeGUI)
};

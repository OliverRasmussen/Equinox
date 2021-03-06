/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SynthGUI.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "EquinoxComponent.h"

//==============================================================================
/*
*/
class SynthGUI    : public EquinoxComponent
{
public:
    SynthGUI(StateManager& stateManager, std::string);
    ~SynthGUI();

    void paint (Graphics&) override;
    void resized() override;
    
protected:
    StateManager& stateManager;
    std::string synthInstance;
    
private:
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> monoAttachment;
    
    TextButton monoButton { "Mono" };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthGUI)
};

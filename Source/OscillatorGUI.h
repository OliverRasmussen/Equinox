/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    OscillatorGUI.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "SynthGUI.h"

//==============================================================================
/*
*/
class OscillatorGUI    : public SynthGUI
{
public:
    OscillatorGUI(StateManager& stateManager, std::string);
    ~OscillatorGUI();

    void paint (Graphics&) override;
    void resized() override;
    

private:
    
    ComboBox waveformMenu;
    
    Label waveformLabel;
    
    std::unique_ptr <AudioProcessorValueTreeState::ComboBoxAttachment> waveformMenuAttachment;
    
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> detuneAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorGUI)
};

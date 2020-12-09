/*
  ==============================================================================

    FilterGUI.h
    Created: 7 Apr 2020 2:23:45pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class FilterGUI    : public Component
{
public:
    FilterGUI(std::string);
    ~FilterGUI();

    void paint (Graphics&) override;
    void resized() override;

private:
    std::string synthInstance;
    
    Slider cutoffSlider, resonanceSlider, driveSlider;
    
    Label cutoffLabel, resonanceLabel, driveLabel;
    
    ComboBox filterMenu;
    
    std::unique_ptr <AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment, resonanceAttachment, driveAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGUI)
};

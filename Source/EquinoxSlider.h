/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    EquinoxSlider.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StateManager.h"

//==============================================================================
/*
*/
class EquinoxSlider  : public juce::Component
{
public:
    EquinoxSlider();
    
    // Creates a slider with a label
    EquinoxSlider(Slider::SliderStyle sliderStyle, float minRangeValue, float maxRangeValue, float startValue, int sliderWidth, int sliderHeight, String parameterID, String labelText, StateManager& state);
    
    ~EquinoxSlider() override;
    
    void setPosition(int x, int y);
    
    String getID() const;
    
    Slider& getSliderComponent();
    
    Label& getLabelComponent();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    String parameterID;
    Slider slider;
    Label label;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EquinoxSlider)
};

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
class LabelSlider  : public juce::Component
{
public:
    LabelSlider();
    
    /** Creates a slider with a label */
    LabelSlider(Slider::SliderStyle sliderStyle, float minRangeValue, float maxRangeValue, float startValue, int sliderWidth, int sliderHeight, String parameterID, String labelText, StateManager& state);
    
    ~LabelSlider() override;
    
    void setPosition(int x, int y);
    
    void setSliderComponentBounds(int x, int y, int width = -1, int height = -1);
    
    Rectangle<int> getSliderComponentBounds() const;
    
    void setLabelComponentBounds(int x, int y, int width = -1, int height = -1);
    
    Rectangle<int> getLabelComponentBounds() const;
    
    String getID() const;
    
    Slider& getSliderComponent();
    
    Label& getLabelComponent();
    
    void center();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    String parameterID;
    Slider slider;
    Label label;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabelSlider)
};

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
    
    /** Sets the position of the LabelSlider*/
    void setPosition(int x, int y);
    
    /** Sets the bounds of the Slider component*/
    void setSliderComponentBounds(int x, int y, int width = -1, int height = -1);
    
    /** Returns the bounds of the Slider component*/
    Rectangle<int> getSliderComponentBounds() const;
    
    /** Sets the bounds of the Label component*/
    void setLabelComponentBounds(int x, int y, int width = -1, int height = -1);
    
    /** Returns the bounds of the Label component*/
    Rectangle<int> getLabelComponentBounds() const;
    
    /** Returns the LabelSliders ID*/
    String getID() const;
    
    /** Returns a reference to the Slider component*/
    Slider& getSliderComponent();
    
    /** Returns a reference to the Label component*/
    Label& getLabelComponent();
    
    /** Centers the LabelSliders components*/
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

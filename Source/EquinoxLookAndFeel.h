/*
  ==============================================================================

    EquinoxLookandFeel.h
    Created: 31 Jul 2021 12:03:51am
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class EquinoxLookAndFeel : public LookAndFeel_V4
{
    
public:
    EquinoxLookAndFeel();
    
    ~EquinoxLookAndFeel() override;
    
private:
    
    void drawButtonBackground (Graphics&, Button&, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
    void drawButtonText (Graphics& g, TextButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
    void drawLinearSlider (Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider&) override;
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;
    
    Image buttonUp;
    Image buttonDown;
    Image rotaryKnob;
    Image rotaryKnobShadow;
    Image sliderKnob;
    Image sliderLine;
    
};

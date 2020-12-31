/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    EquinoxComponent.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LabelSlider.h"

//==============================================================================
/*
*/
class EquinoxComponent  : public juce::Component
{
public:
    EquinoxComponent();
    ~EquinoxComponent() override;
    
    /** Adds a slider with a label to the component */
    void addLabelSlider(std::shared_ptr<LabelSlider> slider);
    
    /** Returns a shared pointer to one of the sliders */
    std::shared_ptr<LabelSlider> getSlider(String parameterID);
    
    /** Draws a title */
    void drawTitle(Graphics& g, Colour textColour, String titleText, int x, int y, int width, int height);
    
    /** Draws a rectangle */
    void drawRectangle(Graphics& g, Colour rectangleColour, float x, float y, float width, float height, float cornerSize = 1.0f, float lineThickness = 2.0f);
    
    /** Spreads the sliders evenly on a horizontal axis */
    void setHorizontalSliderLayout(int labelYPos, int sliderYPos, unsigned int leftPadding = 0, unsigned int rightPadding = 0);

private:
    std::vector<std::shared_ptr<LabelSlider>> labelSliders;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EquinoxComponent)
};

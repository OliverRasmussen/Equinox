/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    EquinoxComponent.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EquinoxComponent.h"

//==============================================================================
EquinoxComponent::EquinoxComponent()
{
}

EquinoxComponent::~EquinoxComponent()
{
}

void EquinoxComponent::addSliderWithLabel(std::shared_ptr<EquinoxSlider> slider)
{
    addAndMakeVisible(*slider);
    sliders.push_back(slider);
}

std::shared_ptr<EquinoxSlider> EquinoxComponent::getSlider(String parameterID)
{
    for (auto& slider : sliders)
    {
        if (slider->getID() == parameterID)
        {
            return slider;
        }
    }
    return nullptr;
}

void EquinoxComponent::drawTitle(Graphics& g, Colour textColour, String titleText, int x, int y, int width, int height)
{
    Rectangle<int> titleArea (x, y, width, height);
    g.setColour(textColour);
    g.drawText(titleText, titleArea, Justification::centredTop);
}

void EquinoxComponent::drawRectangle(Graphics& g, Colour rectangleColour, float x, float y, float width, float height, float cornerSize, float lineThickness)
{
    Rectangle<float> area (x, y, width, height);
    g.setColour(rectangleColour);
    g.drawRoundedRectangle(area, cornerSize, lineThickness);
}

void EquinoxComponent::setHorizontalSliderLayout(int labelYPos, int sliderYPos, unsigned int leftPadding, unsigned int rightPadding)
{
    Rectangle<int> localBounds = getLocalBounds();
    const int horizontalSpace = (localBounds.getWidth() - rightPadding - leftPadding) / sliders.size();
    const int verticalSpace = localBounds.getHeight();
    
    const int labelWidth = horizontalSpace;
    const int labelHeight = 30;
    
    int xOffsetMultiplier = 0;
    
    for (auto& slider : sliders)
    {
        
        slider->setBounds(leftPadding + (horizontalSpace * xOffsetMultiplier), 0, horizontalSpace, verticalSpace);
        
        int sliderWidth = slider->getSliderComponent().getWidth();
        int sliderHeight = slider->getSliderComponent().getHeight();
        
        slider->getSliderComponent().setBounds((horizontalSpace * 0.5f) - (sliderWidth * 0.5), sliderYPos, sliderWidth, sliderHeight);
        
        slider->getLabelComponent().setBounds(0, labelYPos, labelWidth, labelHeight);
        
        xOffsetMultiplier++;
    }
}

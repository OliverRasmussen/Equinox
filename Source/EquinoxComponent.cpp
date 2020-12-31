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

void EquinoxComponent::addLabelSlider(std::shared_ptr<LabelSlider> slider)
{
    addAndMakeVisible(*slider);
    labelSliders.push_back(slider);
}

std::shared_ptr<LabelSlider> EquinoxComponent::getSlider(String parameterID)
{
    for (auto& slider : labelSliders)
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
    const int horizontalSpace = (localBounds.getWidth() - rightPadding - leftPadding) / labelSliders.size();
    const int verticalSpace = localBounds.getHeight();
    
    const int labelWidth = horizontalSpace;
    const int labelHeight = 30;
    
    int xOffsetMultiplier = 0;
    
    for (auto& labelSlider : labelSliders)
    {
        labelSlider->setBounds(leftPadding + (horizontalSpace * xOffsetMultiplier), 0, horizontalSpace, verticalSpace);
        
        labelSlider->setSliderComponentBounds(labelSlider->getSliderComponentBounds().getX(), sliderYPos);
        
        labelSlider->setLabelComponentBounds(labelSlider->getLabelComponentBounds().getX(), labelYPos, labelWidth, labelHeight);
        
        labelSlider->center();
        
        xOffsetMultiplier++;
    }
}

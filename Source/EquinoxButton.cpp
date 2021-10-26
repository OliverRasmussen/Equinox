/*
  ==============================================================================

    EquinoxButton.cpp
    Created: 18 Sep 2021 10:35:11pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EquinoxButton.h"

//==============================================================================
EquinoxButton::EquinoxButton(String buttonName, bool isToggleButton) : juce::TextButton(buttonName), shadow(Colours::black, 3, {0, 1})
{
    setShadower();
    onStateChange = [&](){ changeShadow(); };
    
    this->isToggleButton = isToggleButton;
    
    setClickingTogglesState(isToggleButton);
    
}

EquinoxButton::~EquinoxButton()
{
}

void EquinoxButton::paintButton (Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    TextButton::paintButton(g, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
}

void EquinoxButton::setShadower()
{
    shadower = std::make_unique<DropShadower>(shadow);
    shadower->setOwner(this);
}

void EquinoxButton::changeShadow()
{
    /**Only change shadow on buttonDown or buttonNormal, or if button was released*/
    if (getState() != buttonOver || lastState == buttonDown)
    {
        if (getState() == buttonDown)
        {
            shadow.colour = Colours::transparentBlack;
        }
        else
        {
            shadow.colour = Colours::black;
            shadow.offset = {0, 1};
            shadow.radius = 3;
        }
        setShadower();
        lastState = getState();
    }
}

/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|

    EquinoxButton.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EquinoxButton  : public juce::TextButton
{
public:

    EquinoxButton(String buttonName, bool isToggleButton = false);
    ~EquinoxButton() override;
    
    void paintButton (Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
private:
    void setShadower();
    
    void changeShadow();
    
    ButtonState lastState;
    
    bool isToggleButton = false;
    
    DropShadow shadow;
    std::unique_ptr<DropShadower> shadower = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EquinoxButton)
};

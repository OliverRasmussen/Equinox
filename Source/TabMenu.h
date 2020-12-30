/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    TabMenu.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class TabMenu : public TabbedComponent
{
public:
    TabMenu(TabbedButtonBar::Orientation orientation) : TabbedComponent(orientation)
    {
        onTabChanged = []() {};
    }
    void currentTabChanged(int index, const String&) override
    {
        onTabChanged();
    }
    std::function<void()> onTabChanged;
};

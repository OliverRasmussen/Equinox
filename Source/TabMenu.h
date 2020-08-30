/*
  ==============================================================================

    TabMenu.h
    Created: 14 May 2020 12:50:46am
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

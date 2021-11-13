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

#include "TabMenu.h"

TabMenu::TabMenu(TabbedButtonBar::Orientation orientation) : TabbedComponent(orientation)
{
    onTabChanged = []() {};
}

void TabMenu::currentTabChanged(int currentTabIndex, const String &currentTabName)
{
    onTabChanged();
}

/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    MainMenu.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StateManager.h"
#include "PresetManager.h"

//==============================================================================
/*
*/
class MainMenu  : public juce::Component, Value::Listener
{
public:
    MainMenu(StateManager& state);
    ~MainMenu() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    void displayOverwritePopUp();
    
    void valueChanged(Value& value) override;
    
    Font menuFont;
    
    Label menuTitleLabel;
    
    Label presetNameLabel;
    Value presetName;
    
    ArrowButton backArrow;
    ArrowButton forwardArrow;
    
    TextButton initializeButton {"Initialize"};
    TextButton loadButton {"Load Preset"};
    TextButton overwriteButton {"Overwrite"};
    TextButton saveButton {"Save Preset"};
    
    PopupMenu overwritePopUp;
    
    Image menuScreen;
    Image screenReflection;
    
    PresetManager presetManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainMenu)
};

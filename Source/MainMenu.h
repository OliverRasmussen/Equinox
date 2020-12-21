/*
  ==============================================================================

    MainMenu.h
    Created: 14 Dec 2020 12:57:31am
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

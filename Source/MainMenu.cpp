/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    MainMenu.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainMenu.h"

//==============================================================================
MainMenu::MainMenu(PresetManager& presetManager) : backArrow("back", 0.5, Colours::black), forwardArrow("forward", 0.0, Colours::black), presetManager(presetManager)
{    
    presetName = Value(*presetManager.getCurrentPresetName());
    presetName.addListener(this);
    
    presetHasBeenEdited = Value(*presetManager.getCurrentPresetHasBeenEdited());
    presetHasBeenEdited.addListener(this);
    
    menuScreen = ImageCache::getFromMemory(BinaryData::MenuScreen_png, BinaryData::MenuScreen_pngSize);
    screenReflection = ImageCache::getFromMemory(BinaryData::MenuScreenReflection_png, BinaryData::MenuScreenReflection_pngSize);
    
    menuFont = Font (Typeface::createSystemTypefaceFor (BinaryData::_8bit_fortress_ttf, BinaryData::_8bit_fortress_ttfSize));
    menuFont.setSizeAndStyle(11, 1, 0.95f, 0);
    
    menuTitleLabel.setText("Preset", NotificationType::dontSendNotification);
    menuTitleLabel.setFont(menuFont);
    menuTitleLabel.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
    addAndMakeVisible(&menuTitleLabel);
    
    presetNameLabel.setText(presetName.toString(), NotificationType::dontSendNotification);
    presetNameLabel.setFont(menuFont);
    presetNameLabel.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
    addAndMakeVisible(&presetNameLabel);
    
    backArrow.onClick = [&]() { presetManager.getPreviousPreset(); };
    addAndMakeVisible(&backArrow);
    
    forwardArrow.onClick = [&]() { presetManager.getNextPreset(); };
    addAndMakeVisible(&forwardArrow);
    
    
    initializeButton.onClick = [&]() { presetManager.initializePreset(); };
    addAndMakeVisible(&initializeButton);
    
    loadButton.onClick = [&]() { presetManager.loadPreset(); };
    addAndMakeVisible(&loadButton);
    
    overwriteButton.onClick = [&]() { displayOverwritePopUp(); };
    addAndMakeVisible(&overwriteButton);
    
    saveButton.onClick = [&]() { presetManager.savePreset(); };
    addAndMakeVisible(&saveButton);
    
    overwritePopUp.addSectionHeader("Overwrite preset?");
    overwritePopUp.addItem(1, "Confirm");
    overwritePopUp.addItem(2, "Cancel");
}

MainMenu::~MainMenu()
{
    presetName.removeListener(this);
    presetHasBeenEdited.removeListener(this);
}

void MainMenu::displayOverwritePopUp()
{
    if (presetManager.currentPresetExistsAsFile() && (bool)presetHasBeenEdited.getValue())
    {
        int result = overwritePopUp.show();
        
        if (result == 1)
        {
            // User confirmed to overwrite preset
            presetManager.overwritePreset();
        }
    }
}

void MainMenu::valueChanged(Value& value)
{
    if (presetName == value)
    {
        // Changes the presetNamelabel text to match the preset name
        presetNameLabel.setText(presetName.toString(), NotificationType::dontSendNotification);
    }
    
    if (presetHasBeenEdited == value)
    {
        if ((bool)presetHasBeenEdited.getValue() == true)
        {
            String editedAffix = " *Edited*";
            presetNameLabel.setText(presetName.toString() + editedAffix, NotificationType::dontSendNotification);
        }
        else
        {
            presetNameLabel.setText(presetName.toString(), NotificationType::dontSendNotification);
        }
    }
}

void MainMenu::paint (juce::Graphics& g)
{
    g.drawImageAt(menuScreen, screenXPosition, 80);
    g.drawImageAt(screenReflection, screenXPosition, 80);
}

void MainMenu::resized()
{
    screenXPosition = (getLocalBounds().getWidth() - menuScreen.getWidth()) / 2;
    menuTitleLabel.setBounds(screenXPosition + 45, 100, 100, 12);
    presetNameLabel.setBounds(screenXPosition + 45, 120, 200, 14);
    backArrow.setBounds(635, 103, 12, 12);
    forwardArrow.setBounds(655, 103, 12, 12);
    initializeButton.setBounds(715, 80, 60, 16);
    overwriteButton.setBounds(715, 100, 60, 16);
    saveButton.setBounds(715, 120, 60, 16);
    loadButton.setBounds(715, 140, 60, 16);
}

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
}

void MainMenu::displayOverwritePopUp()
{
    if (presetManager.currentPresetExistsAsFile())
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
        presetNameLabel.setText(presetManager.getCurrentPresetName()->toString(), NotificationType::dontSendNotification);
    }
}

void MainMenu::paint (juce::Graphics& g)
{
    g.drawImageAt(menuScreen, (800 - menuScreen.getWidth()) / 2, 80);
    
    g.drawImageAt(screenReflection, (800 - screenReflection.getWidth()) / 2, 80);
}

void MainMenu::resized()
{
    menuTitleLabel.setBounds(((800 - menuScreen.getWidth()) / 2) + 45, 100, 100, 12);
    presetNameLabel.setBounds(((800 - menuScreen.getWidth()) / 2) + 45, 120, 200, 14);
    backArrow.setBounds(515, 103, 12, 12);
    forwardArrow.setBounds(535, 103, 12, 12);
    initializeButton.setBounds(595, 80, 60, 16);
    overwriteButton.setBounds(595, 100, 60, 16);
    saveButton.setBounds(595, 120, 60, 16);
    loadButton.setBounds(595, 140, 60, 16);
}

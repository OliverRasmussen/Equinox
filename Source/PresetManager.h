/*
  ==============================================================================

    PresetManager.h
    Created: 21 Dec 2020 12:07:57pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "StateManager.h"

class PresetManager : ChangeListener
{
public:
    
    PresetManager(StateManager& state);
    
    ~PresetManager();
    
    void loadDirectory(String directoryPath);
    
    void savePreset();
    
    void loadPreset();
    
    void getNextPreset();
    
    void getPreviousPreset();
    
    void overwritePreset();
    
    void initializePreset();
    
    Value* getCurrentPresetName();
    
    bool currentPresetFileExists() const;
    
private:
    
    void setCurrentPreset(File presetFile);
    
    int getPresetIndexFromFile(File& presetFile);
    
    bool directoryContainsFiles();
    
    void onDirectoryLoaded();
    
    void changeListenerCallback (ChangeBroadcaster* source);
    
    std::unique_ptr<DirectoryContentsList> directoryList;
    TimeSliceThread directoryScanThread;
    
    File defaultDirectory;
    String directoryPath;
    
    File currentPresetFile;
    Value currentPresetName;
    
    StateManager& state;
    
    bool directoryLoaded = false;
};

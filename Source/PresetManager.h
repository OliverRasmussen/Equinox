/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    PresetManager.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "StateManager.h"

class PresetManager
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
    
    bool currentPresetExistsAsFile();
    
private:
    int getPresetIndexFromName(String presetName);
    
    File getPresetFileFromName(String presetName);
    
    bool directoryContainsFiles();
    
    void waitForDirectoryToLoad();
    
    std::unique_ptr<DirectoryContentsList> directoryList;
    TimeSliceThread directoryScanThread;
    
    WildcardFileFilter fileFilter;
    
    File directory;
    String directoryPath;
    
    Value currentPresetName;
    int currentPresetIndex = 0;
    
    StateManager& state;
    
    bool directoryLoaded = false;
    
};

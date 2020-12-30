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
    
    void initializeFromLastUsedPreset();
    
    void changeListenerCallback (ChangeBroadcaster* source);
    
    std::unique_ptr<DirectoryContentsList> directoryList;
    TimeSliceThread directoryScanThread;
    
    WildcardFileFilter fileFilter;
    
    File defaultDirectory;
    String directoryPath;
    
    File currentPresetFile;
    Value currentPresetName;
    
    StateManager& state;
    
    bool directoryLoaded = false;
    
    bool scanningForFiles = false;
};

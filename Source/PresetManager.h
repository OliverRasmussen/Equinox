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
    
    /** Loads the directory from the specified path*/
    void loadDirectory(String directoryPath, bool createDirectoryIfNotExisting = false);
    
    /** Opens a dialog box that makes it possible to save the current preset to a file*/
    void savePreset();
    
    /** Opens a dialog box that makes it possible to load a preset file*/
    void loadPreset();
    
    /** Gets the next preset file found in the directory*/
    void getNextPreset();
    
    /** Gets the previous preset file found in the directory*/
    void getPreviousPreset();
    
    /** Overwrites the current preset file*/
    void overwritePreset();
    
    /** Initializes the preset*/
    void initializePreset();
    
    /** Returns the current presets name*/
    Value* getCurrentPresetName();
    
    /** Returns true if the current preset exists as an actual file*/
    bool currentPresetExistsAsFile();
    
private:
    /** Returns the index of a preset file by name*/
    int getPresetIndexFromName(String presetName);
    
    /** Returns a file matching the specified presetName*/
    File getPresetFileFromName(String presetName);
    
    /** Returns true if the directory contains any files*/
    bool directoryContainsFiles();
    
    /** Waits for the directory load before continuing*/
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

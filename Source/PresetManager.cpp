/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    PresetManager.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "PresetManager.h"

PresetManager::PresetManager(StateManager& state) : directoryScanThread("directoryScanner"), fileFilter("*.equinox", "", "Presets"), state(state)
{
}

PresetManager::~PresetManager()
{
}

void PresetManager::loadDirectory(String directoryPath)
{
    directoryScanThread.startThread();
    directoryList = std::make_unique<DirectoryContentsList>(&fileFilter, directoryScanThread);
    
    this->directoryPath = directoryPath;
    
    directory = File(directoryPath);

    // Creates directory if it doesnt exist
    if (!directory.exists()) { directory.createDirectory(); }
    
    // Sets the directoryList to scan the default directory
    directoryList->setDirectory(directory, true, true);
    
    waitForDirectoryToLoad();
    
    // Directory loaded, setting the preset to match the state
    if (state.getPresetName() == nullptr)
    {
        // No previous loaded state
        if (directoryContainsFiles())
        {
            // Loading first preset file if directory contains files
            File preset = directoryList->getFile(0);
            if (state.loadStateFromFile(preset))
            {
                currentPresetName = preset.getFileNameWithoutExtension();
                currentPresetIndex = 0;
            }
        }
        else
        {
            // Initializing if no preset files exists in directory
            initializePreset();
        }
    }
    else
    {
        // Matching the previous loaded preset
        currentPresetName = *state.getPresetName();
        currentPresetIndex = getPresetIndexFromName(currentPresetName.toString());
    }
    directoryLoaded = true;
}
    
void PresetManager::savePreset()
{
    if (directoryLoaded)
    {
        FileChooser fileChooser("Save preset", getPresetFileFromName(currentPresetName.toString()), "", true, false, nullptr);

        if (fileChooser.browseForFileToSave(true))
        {
            File preset = fileChooser.getResult();
            preset.create();
            
            directoryList->refresh();
            waitForDirectoryToLoad();
            
            state.setPresetName(preset.getFileNameWithoutExtension());
            currentPresetName = *state.getPresetName();
            currentPresetIndex = getPresetIndexFromName(currentPresetName.toString());
            state.saveStateToFile(preset);
        }
    }
}
    
void PresetManager::loadPreset()
{
    if (directoryLoaded)
    {
        FileChooser fileChooser("Load preset", directory, "*.equinox", true, false, nullptr);
        
        if (fileChooser.browseForFileToOpen())
        {
            File preset = fileChooser.getResult();
            if (state.loadStateFromFile(preset))
            {
                currentPresetName = *state.getPresetName();
                currentPresetIndex = -1;
            }
        }
    }
}
    
void PresetManager::getNextPreset()
{
    if (directoryContainsFiles())
    {
        currentPresetIndex = currentPresetIndex < (directoryList->getNumFiles() - 1) ? ++currentPresetIndex : 0;
        
        File presetFile = directoryList->getFile(currentPresetIndex);
        if (state.loadStateFromFile(presetFile))
        {
            currentPresetName = *state.getPresetName();
        }
    }
}
    
void PresetManager::getPreviousPreset()
{
    if (directoryContainsFiles())
    {
        currentPresetIndex = currentPresetIndex > 0 ? --currentPresetIndex : directoryList->getNumFiles() - 1;
        
        File presetFile = directoryList->getFile(currentPresetIndex);
        if (state.loadStateFromFile(presetFile))
        {
            currentPresetName = *state.getPresetName();
        }
    }
}
    
void PresetManager::overwritePreset()
{
    File presetFile = getPresetFileFromName(currentPresetName.toString());
    state.saveStateToFile(presetFile);
}
    
void PresetManager::initializePreset()
{
    state.resetStateToDefault();
    currentPresetName = "Init";
    currentPresetIndex = -1;
    state.setPresetName(currentPresetName.toString());
}
    
Value* PresetManager::getCurrentPresetName()
{
    return &currentPresetName;
}

bool PresetManager::currentPresetExistsAsFile()
{
    if (getPresetFileFromName(currentPresetName.toString()).exists())
    {
        return true;
    }
    return false;
}


int PresetManager::getPresetIndexFromName(String presetName)
{
    File presetFile = getPresetFileFromName(presetName);
    
    if (directoryList->contains(presetFile))
    {
        DirectoryContentsList::FileInfo fileInfo;
        for (int i = 0; i < directoryList->getNumFiles() - 1; i++)
        {
            // Searching through the directoryList for a matching file
            if (directoryList->getFileInfo(i, fileInfo))
            {
                if (presetFile.getFileName() == fileInfo.filename)
                {
                    // Found the preset files index
                    return i;
                }
            }
        }
    }
    // preset couldn't be found / doesn't exist
    return -1;
}

File PresetManager::getPresetFileFromName(String presetName)
{
    return File(directoryPath + presetName + ".equinox");
}

bool PresetManager::directoryContainsFiles()
{
    return directoryList->getNumFiles() > 0;
}

void PresetManager::waitForDirectoryToLoad()
{
    while (directoryList->isStillLoading())
    {
        Time::waitForMillisecondCounter(Time::getMillisecondCounter() + 50);
    }
}


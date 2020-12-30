/*
  ==============================================================================

    PresetManager.cpp
    Created: 21 Dec 2020 12:07:57pm
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
    directoryList->addChangeListener(this);
    
    this->directoryPath = directoryPath;
    
    defaultDirectory = File(directoryPath);

    // Creates directory if it doesnt exist
    if (!defaultDirectory.exists()) { defaultDirectory.createDirectory(); }
    
    // Sets the directoryList to scan the default directory
    directoryList->setDirectory(defaultDirectory, true, true);
    
    scanningForFiles = true;
}
    
void PresetManager::savePreset()
{
    if (directoryLoaded)
    {
        FileChooser fileChooser("Save preset", File(directoryPath + currentPresetName.toString() + ".equinox"), "", true, false, nullptr);

        if (fileChooser.browseForFileToSave(true))
        {
            File preset = fileChooser.getResult();
            state.saveStateToFile(preset);
            setCurrentPreset(preset);
            directoryList->refresh();
            scanningForFiles = true;
        }
    }
}
    
void PresetManager::loadPreset()
{
    if (directoryLoaded)
    {
        FileChooser fileChooser("Load preset", File(directoryPath), "*.equinox", true, false, nullptr);
        
        if (fileChooser.browseForFileToOpen())
        {
            File preset = fileChooser.getResult();
            setCurrentPreset(preset);
            state.loadStateFromFile(currentPresetFile);
            state.setPresetInfo(-1, currentPresetName.toString());
        }
    }
}
    
void PresetManager::getNextPreset()
{
    if (directoryContainsFiles())
    {
        int index = state.getPresetInfo()->index;
        index = index < (directoryList->getNumFiles() - 1) ? ++index : 0;
        setCurrentPreset(directoryList->getFile(index));
        state.loadStateFromFile(currentPresetFile);
        state.setPresetInfo(index, currentPresetName.toString());
    }
}
    
void PresetManager::getPreviousPreset()
{
    if (directoryContainsFiles())
    {
        int index = state.getPresetInfo()->index;
        index = index > 0 ? --index : directoryList->getNumFiles() - 1;
        setCurrentPreset(directoryList->getFile(index));
        state.loadStateFromFile(currentPresetFile);
        state.setPresetInfo(index, currentPresetName.toString());
    }
}
    
void PresetManager::overwritePreset()
{
    state.saveStateToFile(currentPresetFile);
}
    
void PresetManager::initializePreset()
{
    state.resetStateToDefault();
    currentPresetName = "Init";
    state.setPresetInfo(-1, currentPresetName.toString());
}
    
Value* PresetManager::getCurrentPresetName()
{
    return &currentPresetName;
}

bool PresetManager::currentPresetFileExists() const
{
    return currentPresetFile.exists();
}
    
void PresetManager::setCurrentPreset(File presetFile)
{
    if (presetFile.exists())
    {
        // Setting the current preset file if it exists
        currentPresetFile = presetFile;
        currentPresetName = currentPresetFile.getFileNameWithoutExtension();
    }
    else
    {
        // Initializing the preset and state if the file doesnt exist
        initializePreset();
    }
}

int PresetManager::getPresetIndexFromFile(File& presetFile)
{
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
    // preset couldn't be found
    return -1;
}

bool PresetManager::directoryContainsFiles()
{
    return directoryList->getNumFiles() > 0;
}

void PresetManager::initializeFromLastUsedPreset()
{
    if (state.getPresetInfo() == nullptr)
    {
        // No previous loaded preset - loading first preset
        File preset = directoryList->getFile(0);
        setCurrentPreset(preset);
        state.loadStateFromFile(currentPresetFile);
    }
    else if (state.getPresetInfo()->index == -1)
    {
        // preset was not saved as a file when closed - only setting the current preset name to match
        currentPresetName = state.getPresetInfo()->name;
    }
    else if (directoryList->getFile(state.getPresetInfo()->index).getFileNameWithoutExtension() == state.getPresetInfo()->name)
    {
        // preset file was used - loading matching preset
        setCurrentPreset(directoryList->getFile(state.getPresetInfo()->index));
    }
    else
    {
        // preset file could not be found - loading initialized preset
        initializePreset();
    }
}

void PresetManager::changeListenerCallback (ChangeBroadcaster* source)
{
    // Checks if the directory has been scanning for files
    if (scanningForFiles && !directoryList->isStillLoading())
    {
        if (!directoryLoaded)
        {
            initializeFromLastUsedPreset();
        }
        state.setPresetInfo(getPresetIndexFromFile(currentPresetFile), currentPresetName.toString());
        scanningForFiles = false;
        directoryLoaded = true;
    }
}

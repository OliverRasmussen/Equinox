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

PresetManager::PresetManager(StateManager& state) : fileFilter("*.equinox", "", "Presets"),
                                                    directoryScanThread("directoryScanner"),
                                                    directoryList(&fileFilter, directoryScanThread),
                                                    currentPresetName(Value(state.getPresetName())),
                                                    currentPresetHasBeenEdited(var(false)), state(state)
{
    // Adding the PresetManager to the state as a listener
    state.addListener(this);
    
    // Loading the default directory
    String defaultDirectoryPath = File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName() + "/Equinox/Presets/";
    loadDirectory(defaultDirectoryPath, true);
}

PresetManager::~PresetManager()
{
    state.removeListener(this);
    directoryList.clear();
}

void PresetManager::loadDirectory(String directoryPath, bool createDirectoryIfNotExisting)
{
    this->directoryPath = directoryPath;
    
    directory = File(directoryPath);
    
    if (createDirectoryIfNotExisting)
    {
        // Creates directory if it doesnt exist
        if (!directory.exists()) { directory.createDirectory(); }
    }
    
    // Sets the directoryList to scan the default directory
    directoryList.setDirectory(directory, true, true);
    directoryScanThread.startThread();

    waitForDirectoryToLoad();
    
    // Directory loaded, setting the first preset as the state
    if (directoryContainsFiles())
    {
        File presetFile = directoryList.getFile(0);
        state.loadStateFromFile(presetFile);
    }
}
    
void PresetManager::savePreset()
{
    FileChooser fileChooser("Save preset", getPresetFileFromName(currentPresetName.toString()), "", true, false, nullptr);
    if (fileChooser.browseForFileToSave(true))
    {
        File presetFile = fileChooser.getResult();

        if (!presetFile.existsAsFile())
        {
            presetFile.create();

            state.setPresetName(presetFile.getFileNameWithoutExtension());

            directoryList.refresh();
            waitForDirectoryToLoad();
        }


        state.saveStateToFile(presetFile);
        state.loadStateFromFile(presetFile);
    }
}
    
void PresetManager::loadPreset()
{
    FileChooser fileChooser("Load preset", directory, "*.equinox", true, false, nullptr);

    if (fileChooser.browseForFileToOpen())
    {
        File presetFile = fileChooser.getResult();

        state.loadStateFromFile(presetFile);
    }
}
    
void PresetManager::getNextPreset()
{
    if (directoryContainsFiles())
    {
        int index = currentPresetIndex < (directoryList.getNumFiles() - 1) ? currentPresetIndex + 1 : 0;
        
        File presetFile = directoryList.getFile(index);
        
        state.loadStateFromFile(presetFile);
    }
}
    
void PresetManager::getPreviousPreset()
{
    if (directoryContainsFiles())
    {
        int index = currentPresetIndex > 0 ? currentPresetIndex - 1 : (directoryList.getNumFiles() - 1);
        
        File presetFile = directoryList.getFile(index);
        
        state.loadStateFromFile(presetFile);
    }
}
    
void PresetManager::overwritePreset()
{
    File presetFile = directoryList.getFile(currentPresetIndex);
    state.saveStateToFile(presetFile);
    state.loadStateFromFile(presetFile);
}
    
void PresetManager::initializePreset()
{
    state.resetStateToDefault();
}
    
Value* PresetManager::getCurrentPresetName()
{
    return &currentPresetName;
}

bool PresetManager::currentPresetExistsAsFile() const
{
    if (directoryList.getFile(currentPresetIndex).existsAsFile())
    {
        return true;
    }
    return false;
}

Value* PresetManager::getCurrentPresetHasBeenEdited()
{
    return &currentPresetHasBeenEdited;
}


int PresetManager::getPresetIndexFromName(String presetName) const
{
    File presetFile = getPresetFileFromName(presetName);
    
    if (directoryList.contains(presetFile))
    {
        DirectoryContentsList::FileInfo fileInfo;
        for (int i = 0; i < directoryList.getNumFiles(); i++)
        {
            // Searching through the directoryList for a matching file
            if (directoryList.getFileInfo(i, fileInfo))
            {
                if (presetFile.getFileName() == fileInfo.filename)
                {
                    // Found the preset files index
                    return i;
                }
            }
        }
    }
    // preset wasnt found in directory / doesn't exist
    return -1;
}

File PresetManager::getPresetFileFromName(String presetName) const
{
    return File(directoryPath + presetName + ".equinox");
}

bool PresetManager::directoryContainsFiles() const
{
    return directoryList.getNumFiles() > 0;
}

void PresetManager::waitForDirectoryToLoad()
{
    while (directoryList.isStillLoading())
    {
        Time::waitForMillisecondCounter(Time::getMillisecondCounter() + 10);
    }
}

void PresetManager::valueTreeChildAdded (ValueTree &parentTree, ValueTree &childWhichHasBeenAdded)
{
    // New state loaded
    if (childWhichHasBeenAdded.getType() == state.getParameters().state.getType())
    {
        currentPresetHasBeenEdited = false;
    }
}

void PresetManager::valueTreePropertyChanged(ValueTree& valueTree, const Identifier& propertyId)
{
    // Checking if the presetname has changed
    if (propertyId.toString() == "presetname")
    {
        // Sets the preset index to match the preset
        currentPresetIndex = getPresetIndexFromName(currentPresetName.toString());

    }
    
    // Checking if any parameter has been changed
    if (valueTree.getType().toString() == "PARAM")
    {
        currentPresetHasBeenEdited = true;
    }
}


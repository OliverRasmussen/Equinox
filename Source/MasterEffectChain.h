/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    MasterEffectChain.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "StateManager.h"
#include "ChorusFX.h"
#include "PhaserFX.h"
#include "ReverbFX.h"
#include "DelayFX.h"

class MasterEffectChain : public ValueTree::Listener
{
public:
    MasterEffectChain(StateManager& state);
    ~MasterEffectChain();
    
    /** Initializes the MasterEffectChain object*/
    void initialize();
    
    /** Adds the effect parameters to a vector*/
    void addParameters(std::vector<std::unique_ptr<RangedAudioParameter>>& params);
    
    /** Prepares the effects*/
    void prepareToPlay(int samplerate, int samplesPerBlock, int numChannels);
    
    /** Resets the MasterEffectChain and all the effects*/
    void reset();
    
    /** Processes the AudioBuffer reference through the various effects*/
    void process(AudioBuffer<float>& bufferToProcess, double& bpm);
    
private:
    /** Updates all the effects parameters*/
    void updateParameters();
    
    /** Receives callback whenever a ValueTree child is added*/
    void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override;
    
    /** Receives callback whenever a property is changed in the ValueTree*/
    void valueTreePropertyChanged(ValueTree& valueTree, const Identifier& propertyId) override;
    
    ChorusFX chorusFX;
    PhaserFX phaserFX;
    ReverbFX reverbFX;
    DelayFX delayFX;
    
    StateManager& state;
    
    dsp::ProcessSpec spec;
};

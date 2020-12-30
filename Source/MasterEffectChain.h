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
    
    void initialize();
    
    void addParameters(std::vector<std::unique_ptr<RangedAudioParameter>>& params);
    
    void prepareToPlay(int samplerate, int samplesPerBlock, int numChannels);
    
    void reset();
    
    void process(AudioBuffer<float>& bufferToProcess, double& bpm);
    
private:
    void updateParameters();
    
    void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override;
    
    void valueTreePropertyChanged(ValueTree&, const Identifier&) override;
    
    ChorusFX chorusFX;
    PhaserFX phaserFX;
    ReverbFX reverbFX;
    DelayFX delayFX;
    
    StateManager& state;
    
    dsp::ProcessSpec spec;
};

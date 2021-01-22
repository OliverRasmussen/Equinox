/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    MasterEffectChain.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "MasterEffectChain.h"

MasterEffectChain::MasterEffectChain(StateManager& state) : state(state)
{
}

void MasterEffectChain::initialize()
{
    state.getState().addListener(this);
    updateParameters();
}

MasterEffectChain::~MasterEffectChain()
{
}
    
void MasterEffectChain::addParameters(std::vector<std::unique_ptr<RangedAudioParameter>>& params)
{
    // Chorus parameters
    params.push_back(std::make_unique<AudioParameterFloat>("chorusMix", "Chorus mix", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("chorusRate", "Chorus rate", NormalisableRange<float>(0.0f, 5.0f, 0.05f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("chorusDepth", "Chorus depth", NormalisableRange<float>(0.0f, 0.15f, 0.01f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("chorusDelay", "Chorus delay", NormalisableRange<float>(1.0f, 30.0f, 0.1f, 1.0f), 1.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("chorusFeedback", "Chorus feedback", NormalisableRange<float>(-1.0f, 1.0f, 0.01f, 1.0f), 0.0f));
    
    // Phaser parameters
    params.push_back(std::make_unique<AudioParameterFloat>("phaserMix", "Phaser mix", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("phaserRate", "Phaser rate", NormalisableRange<float>(0.0f, 1.0f, 0.00060f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("phaserDepth", "Phaser depth", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("phaserFrequency", "Phaser frequency", NormalisableRange<float>(100.0f, 22000.0f, 20.0f, 1.0f), 11000.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("phaserFeedback", "Phaser feedback", NormalisableRange<float>(-0.9f, 0.9f, 0.01f, 1.0f), 0.0f));
    
    // Reverb parameters
    params.push_back(std::make_unique<AudioParameterFloat>("reverbMix", "Reverb mix", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("reverbRoomsize", "Reverb roomsize", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("reverbDamping", "Reverb damping", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("reverbWidth", "Reverb width", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f), 0.0f));
    
    // Delay parameters
    params.push_back(std::make_unique<AudioParameterFloat>("delayMix", "Delay mix", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("delayTime", "Delay time", NormalisableRange<float>(1.0f, 8.0f, 1.0f, 1.0f), 1.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("delayFeedback", "Delay feedback", NormalisableRange<float>(0.0f, 100.0f, 1.0f, 1.0f), 0.0f));
}
    
void MasterEffectChain::prepareToPlay(int samplerate, int samplesPerBlock, int numChannels)
{
    spec.sampleRate = samplerate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = numChannels;
    
    chorusFX.prepare(spec);

    phaserFX.prepare(spec);

    reverbFX.prepare(spec);
    
    delayFX.prepare(spec);
}
    
void MasterEffectChain::reset()
{
    chorusFX.reset();

    phaserFX.reset();
    
    reverbFX.reset();
    
    delayFX.reset();
}

void MasterEffectChain::updateParameters()
{
    chorusFX.setParameters(*state.getAudioParameterValue("chorusRate"),
                           *state.getAudioParameterValue("chorusDepth"),
                           *state.getAudioParameterValue("chorusDelay"),
                           *state.getAudioParameterValue("chorusFeedback"),
                           *state.getAudioParameterValue("chorusMix"));
    
    phaserFX.setParameters(*state.getAudioParameterValue("phaserRate"),
                           *state.getAudioParameterValue("phaserDepth"),
                           *state.getAudioParameterValue("phaserFrequency"),
                           *state.getAudioParameterValue("phaserFeedback"),
                           *state.getAudioParameterValue("phaserMix"));
    
    reverbFX.setParameters(*state.getAudioParameterValue("reverbRoomsize"),
                           *state.getAudioParameterValue("reverbDamping"),
                           *state.getAudioParameterValue("reverbWidth"),
                           *state.getAudioParameterValue("reverbMix"));
    
    delayFX.setParameters(*state.getAudioParameterValue("delayTime"),
                          *state.getAudioParameterValue("delayFeedback"),
                          *state.getAudioParameterValue("delayMix"));
}
    
void MasterEffectChain::process(AudioBuffer<float>& bufferToProcess, double& bpm)
{
    if (needsUpdate)
    {
        updateParameters();
        needsUpdate = false;
    }
    
    if (chorusFX.isActive())
    {
        chorusFX.process(bufferToProcess);
    }

    if (phaserFX.isActive())
    {
        phaserFX.process(bufferToProcess);
    }

    if (reverbFX.isActive())
    {
        reverbFX.process(bufferToProcess);
    }
    
    if (delayFX.isActive())
    {
        delayFX.process(bufferToProcess, bpm);        
    }
}
    
void MasterEffectChain::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
    // Updating the effects parameter values if the added child is the params
    if (childWhichHasBeenAdded.getType() == state.getParameters().state.getType())
    {
        needsUpdate = true;
    }
}
    
void MasterEffectChain::valueTreePropertyChanged(ValueTree& valueTree, const Identifier& propertyId)
{
    // Updating the effects parameter values if the valuetree which property has changed is a parameter
    if (valueTree.getType().toString() == "PARAM")
    {
        needsUpdate = true;
    }
}

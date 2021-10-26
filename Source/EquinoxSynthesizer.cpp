/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    EquinoxSynthesizer.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "EquinoxSynthesizer.h"

EquinoxSynthesizer::EquinoxSynthesizer(StateManager& state, int synthNum) : oscillatorSynth(Synth::voiceType::oscillator), sampleSynth(Synth::voiceType::sampler), stateManager(state)
{
    instanceNum = synthNum;
    formatManager.registerBasicFormats();
}

void EquinoxSynthesizer::initialize()
{
    stateManager.addListener(this);
    
    oscillatorSynth.addVoices(numVoices);
    sampleSynth.addVoices(numVoices);
}

EquinoxSynthesizer::~EquinoxSynthesizer()
{
}

std::string EquinoxSynthesizer::instanceNumAsString() const
{
    return std::to_string(instanceNum);
}

void EquinoxSynthesizer::valueTreeChildAdded (ValueTree &parentTree, ValueTree &childWhichHasBeenAdded)
{
    // resetting and updating the synth and its voices if the added child is the parameters
    if (childWhichHasBeenAdded.getType() == stateManager.getParameters().state.getType())
    {
        needsReset = true;
        needsUpdate = true;
        return;
    }
    
    String audioSampleStateId = "audiosamplestate";
    String audioSampleId = "audiosample" + instanceNumAsString();
    
    // Checking wether the added child is an audiosample or the audiosamplestate.
    if (childWhichHasBeenAdded.hasType(audioSampleStateId) || childWhichHasBeenAdded.hasType(audioSampleId))
    {
        ValueTree audioSampleState = stateManager.getChildWithName(audioSampleStateId);
        if (audioSampleState.isValid())
        {
            loadNewAudioSample = true;
            needsUpdate = true;
            return;
        }
    }
}

void EquinoxSynthesizer::valueTreePropertyChanged(ValueTree& valueTree, const Identifier& propertyId)
{
    // Updating the synth if the valuetree which property has changed is a parameter
    if (valueTree.getType().toString() == "PARAM")
    {
        needsUpdate = true;
    }
}

void EquinoxSynthesizer::loadAudioSample(AudioSample& audioSample)
{
    sampleSynth.clearSounds();
    sampleSynth.addSound(new SampleSynthSound(audioSample, sampleRate));
    loadNewAudioSample = false;
}

// sets the current synth mode
void EquinoxSynthesizer::setSynthMode(int newSynthMode)
{
    if (currentSynthMode != newSynthMode)
    {
        currentSynthMode = static_cast<synthMode>(newSynthMode);
        oscillatorSynth.clearAllCurrentNotes();
        sampleSynth.clearAllCurrentNotes();
    }
}

// Prepares the objects that needs to be prepared
void EquinoxSynthesizer::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;
    this->numChannels = numChannels;
    
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = numChannels;
    
    oscillatorSynth.prepare(spec);
    sampleSynth.prepare(spec);
    
    update();
}

// Adds all the needed parameters for controlling the synth
void EquinoxSynthesizer::addParameters(std::vector<std::unique_ptr<RangedAudioParameter>> &params)
{
    // AmpEnvelope parameters
    params.push_back(std::make_unique<AudioParameterFloat>("ampAttack" + instanceNumAsString(), "AmpAttack", NormalisableRange<float>(0.001f, 5.0f, 0.1f, 1.0f), 0.001f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("ampDecay" + instanceNumAsString(), "AmpDecay", NormalisableRange<float>(0.0f, 5.0f, 0.1f, 1.0f), 1.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("ampSustain" + instanceNumAsString(), "AmpSustain", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f), 0.8f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("ampRelease" + instanceNumAsString(), "AmpRelease", NormalisableRange<float>(0.001f, 5.0f, 0.1f, 1.1f), 0.001f));
    
    
    // FilterEnvelope parameters
    params.push_back(std::make_unique<AudioParameterFloat>("filterAttack" + instanceNumAsString(), "FilterAttack", NormalisableRange<float>(0.0f, 99.0f, 0.1f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("filterDecay" + instanceNumAsString(), "FilterDecay", NormalisableRange<float>(0.0f, 99.0f, 0.1f, 1.1f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("filterSustain" + instanceNumAsString(), "FilterSustain", NormalisableRange<float>(0.0f, 99.0f, 0.1f, 1.1f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("filterRelease" + instanceNumAsString(), "FilterRelease", NormalisableRange<float>(0.0f, 200.0f, 0.1f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("envelopeCutoffLimit" + instanceNumAsString(), "EnvelopeCutoffLimit", NormalisableRange<float>(200.0f, 22050.0f, 0.1f, 0.5f), 10000.0f));
    
    // Waveform parameter
    params.push_back(std::make_unique<AudioParameterFloat>("waveform" + instanceNumAsString(), "Waveform", 0.0f, 4.0f, 0.0f));
    
    // isActive parameter - only setting the first EquinoxSynthesizer instance to active
    bool initializeAsActive = instanceNum == 1 ? true : false;
    params.push_back(std::make_unique<AudioParameterBool>("isActive" + instanceNumAsString(), "On/Off", initializeAsActive));

    params.push_back(std::make_unique<AudioParameterFloat>("amplitude" + instanceNumAsString(), "Amplitude", 0.0f, 0.5f, 0.4f));
    
    // General synth parameters
    params.push_back(std::make_unique<AudioParameterFloat>("detune" + instanceNumAsString(), "Detune", -20.0f, 20.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("finePitch" + instanceNumAsString(), "FinePitch", -100.0f, 100.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("oscPanning" + instanceNumAsString(), "OscPanning", -1.0f, 1.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("pitchTranspose" + instanceNumAsString(), "PitchTranspose", NormalisableRange<float>(-24.0f, 24.0f, 1.0f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("analogValue" + instanceNumAsString(), "AnalogValue", NormalisableRange<float>(1.0f, 40.0f, 1.0f, 1.0f), 1.0f));
    
    // Filter parameters
    params.push_back(std::make_unique<AudioParameterFloat>("filterType" + instanceNumAsString(), "FilterType", 0.0f, 3.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("cutoff" + instanceNumAsString(), "Cutoff", NormalisableRange<float>(50.0f, 22050.0f, 0.1f, 0.5f), 22050.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("resonance" + instanceNumAsString(), "Resonance", NormalisableRange<float>(0.0f, 0.9f, 0.01f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("drive" + instanceNumAsString(), "Drive", NormalisableRange<float>(1.0f, 15.0f, 0.01f, 1.0f), 1.0f));
    
    // Synth Mode
    params.push_back(std::make_unique<AudioParameterFloat>("synthMode" + instanceNumAsString(), "SynthMode", 0.0f, 1.0f, 0.0f));
    
    // Mono & Portamento
    params.push_back(std::make_unique<AudioParameterBool>("monoEnabled" + instanceNumAsString(), "Mono", false));
    params.push_back(std::make_unique<AudioParameterFloat>("portamento" + instanceNumAsString(), "Portamento", NormalisableRange<float>(0.0f, 40000.0f, 100.0f, 1.0f), 0.0f));
    
    // Oscillator Phase
    params.push_back(std::make_unique<AudioParameterFloat>("phase" + instanceNumAsString(), "Phase", NormalisableRange<float>(0.0f, 1.0f, 0.001f, 1.0f), 0.0f));
    
    // Sample start time
    params.push_back(std::make_unique<AudioParameterFloat>("sampleStartTime" + instanceNumAsString(), "Sample start time", NormalisableRange<float>(0.0f, 0.9f, 0.001f, 0.5f), 0.0f));
    
}

// Updates the synth
void EquinoxSynthesizer::update()
{
    // Check if the EquinoxSynthesizer instance has been activated or deactivated
    if (isSynthActive != *stateManager.getAudioParameterValue("isActive" + instanceNumAsString()))
    {
        isSynthActive = *stateManager.getAudioParameterValue("isActive" + instanceNumAsString());
        
        oscillatorSynth.addVoices(numVoices);
        sampleSynth.addVoices(numVoices);
        
        oscillatorSynth.prepare(spec);
        sampleSynth.prepare(spec);
    }
    // Check if mono has been turned on or off
    if (isMonophonic != *stateManager.getAudioParameterValue("monoEnabled" + instanceNumAsString()))
    {
        isMonophonic = *stateManager.getAudioParameterValue("monoEnabled" + instanceNumAsString());
        
        numVoices = isMonophonic ? 1 : MAX_VOICES;
        
        oscillatorSynth.addVoices(numVoices);
        sampleSynth.addVoices(numVoices);
        
        oscillatorSynth.prepare(spec);
        sampleSynth.prepare(spec);
    }
    
    // Check if currentSynthmode has changed
    if (currentSynthMode != (int)*stateManager.getAudioParameterValue("synthMode" + instanceNumAsString()))
    {
        currentSynthMode = static_cast<synthMode>((int)*stateManager.getAudioParameterValue("synthMode" + instanceNumAsString()));
    }
    
    // Check if new audio sample should be added to the samplesynth
    if (currentSynthMode == sampleSynthMode && loadNewAudioSample)
    {
        if (auto sample = stateManager.getAudioSample("audiosample" + instanceNumAsString()))
        {
            loadAudioSample(*sample);
        }
    }
    
    if (currentSynthMode == synthMode::oscSynthMode)
    {
        // Updating the oscSynthVoices parameters
        for (int i = 0; i < numVoices; i++)
        {
            if (auto oscVoice = dynamic_cast<OscSynthVoice*>(oscillatorSynth.getVoice(i)))
            {
                setVoiceParameters<OscSynthVoice*>(oscVoice);
                
                // sets oscillators waveform
                oscVoice->setWaveform((float*)stateManager.getAudioParameterValue("waveform" + instanceNumAsString()));
                
                // sets oscillator phase
                oscVoice->setPhase((float)*stateManager.getAudioParameterValue("phase" + instanceNumAsString()));
            }
        }
    }
    else if (currentSynthMode == synthMode::sampleSynthMode)
    {
        // Updating the sampleSynthVoices parameters
        for (int i = 0; i < numVoices; i++)
        {
            if (auto sampleVoice = dynamic_cast<SampleSynthVoice*>(sampleSynth.getVoice(i)))
            {
                setVoiceParameters<SampleSynthVoice*>(sampleVoice);
                
                sampleVoice->setSampleStartTime((float)*stateManager.getAudioParameterValue("sampleStartTime" + instanceNumAsString()));
            }
        }
    }
    
}

// Sets the parameters for both types of voices
template<typename T>
void EquinoxSynthesizer::setVoiceParameters(T voice)
{
    // sets amplitude
    voice->setAmplitude((float*)stateManager.getAudioParameterValue("amplitude" + instanceNumAsString()));
    
    // sets detune
    voice->setDetune((float*)stateManager.getAudioParameterValue("detune" + instanceNumAsString()));
    
    // sets fine pitch
    voice->setFinePitch((float*)stateManager.getAudioParameterValue("finePitch" + instanceNumAsString()));
    
    // sets analog value
    voice->setAnalogFactor((float*)stateManager.getAudioParameterValue("analogValue" + instanceNumAsString()));
    
    voice->setPitchTranspose((float*)stateManager.getAudioParameterValue("pitchTranspose" + instanceNumAsString()));
    
    voice->setPanning((float*)stateManager.getAudioParameterValue("oscPanning" + instanceNumAsString()));
    
    voice->setPortamento((float*)stateManager.getAudioParameterValue("portamento" + instanceNumAsString()));
    
    // sets filter
    voice->getFilter().setFilter((float*)stateManager.getAudioParameterValue("cutoff" + instanceNumAsString()),
    (float*)stateManager.getAudioParameterValue("resonance" + instanceNumAsString()),
    (float*)stateManager.getAudioParameterValue("drive" + instanceNumAsString()));
    
    // Sets filter mode
    voice->getFilter().setMode((float*)stateManager.getAudioParameterValue("filterType" + instanceNumAsString()));
    
    // sets amp Envelope
    voice->getAmpEnvelope().setEnvelope((float*)stateManager.getAudioParameterValue("ampAttack" + instanceNumAsString()),
                                   (float*)stateManager.getAudioParameterValue("ampDecay" + instanceNumAsString()),
                                   (float*)stateManager.getAudioParameterValue("ampSustain" + instanceNumAsString()),
                                   (float*)stateManager.getAudioParameterValue("ampRelease" + instanceNumAsString()));

    
    // sets filterEnvelope
    voice->getFilterEnvelope().setEnvelope((float*)stateManager.getAudioParameterValue("filterAttack" + instanceNumAsString()),
                                      (float*)stateManager.getAudioParameterValue("filterDecay" + instanceNumAsString()),
                                      (float*)stateManager.getAudioParameterValue("filterSustain" + instanceNumAsString()),
                                      (float*)stateManager.getAudioParameterValue("filterRelease" + instanceNumAsString()));
    voice->getFilterEnvelope().setCutoffLimit((float*)stateManager.getAudioParameterValue("envelopeCutoffLimit" + instanceNumAsString()));
}

// Updates the synth and renders all the voices
void EquinoxSynthesizer::renderNextBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    if (needsUpdate)
    {
        if (needsReset)
        {
            oscillatorSynth.addVoices(numVoices);
            sampleSynth.addVoices(numVoices);
            
            oscillatorSynth.prepare(spec);
            sampleSynth.prepare(spec);
            
            needsReset = false;
        }
        update();
        needsUpdate = false;
    }
    
    if (isSynthActive)
    {
        if (currentSynthMode == synthMode::oscSynthMode)
        {
            oscillatorSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
        }
        else if (currentSynthMode == synthMode::sampleSynthMode)
        {
            sampleSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
        }
    }
}

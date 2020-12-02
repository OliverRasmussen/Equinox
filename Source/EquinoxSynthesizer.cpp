/*
  ==============================================================================

    EquinoxSynthesizer.cpp
    Created: 8 Apr 2020 9:27:00pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "EquinoxSynthesizer.h"

int EquinoxSynthesizer::objCounter;

EquinoxSynthesizer::EquinoxSynthesizer(AudioProcessorValueTreeState& _treeState) : treeState(_treeState)
{
    currentSynthMode = synthMode::oscSynthMode;
    instanceNum = ++objCounter;
    formatManager.registerBasicFormats();
    setVoices();
}

EquinoxSynthesizer::~EquinoxSynthesizer()
{
    --objCounter;
    
    oscVoice = nullptr;
    sampleVoice = nullptr;
    delete oscVoice;
    delete sampleVoice;
}

int EquinoxSynthesizer::getNumInstances()
{
    return objCounter;
}

std::string EquinoxSynthesizer::instanceNumAsString() const
{
    return std::to_string(instanceNum);
}

// Initializes and add voices to the synth
void EquinoxSynthesizer::setVoices()
{
    clearAllCurrentNotes();
    
    numVoices = isMonophonic ? 1 : MAX_VOICES;
    
    oscillatorSynth.clearVoices();
    sampleSynth.clearVoices();
    
    for (int i = 0; i < numVoices; i++)
    {
        oscillatorSynth.addVoice(new OscSynthVoice(isMonophonic));
    }
    oscillatorSynth.clearSounds();
    oscillatorSynth.addSound(new OscSynthSound());

    
    for (int i = 0; i < numVoices; i++)
    {
        sampleSynth.addVoice(new SampleSynthVoice(isMonophonic));
    }
}

// Loads a file into a sample synth sound
void EquinoxSynthesizer::loadSampleFromFile(File sampleFile, String sampleName)
{
    if (auto formatReader = std::unique_ptr<AudioFormatReader>(formatManager.createReaderFor(sampleFile)))
    {
        sampleSynth.clearSounds();
        sampleSynth.addSound(new SampleSynthSound(sampleName, *formatReader, sampleRate));
    }
}

// sets the current synth mode
void EquinoxSynthesizer::setSynthMode(int newSynthMode)
{
    if (currentSynthMode != newSynthMode)
    {
        currentSynthMode = static_cast<synthMode>(newSynthMode);
        clearAllCurrentNotes();
    }
}

// Clear all current playing notes
void EquinoxSynthesizer::clearAllCurrentNotes()
{
    for (int i = 0; i < numVoices; i++)
    {
        if ((oscVoice = dynamic_cast<OscSynthVoice*>(oscillatorSynth.getVoice(i))))
        {
            oscVoice->clearCurrentNote();
        }
        
        if ((sampleVoice = dynamic_cast<SampleSynthVoice*>(sampleSynth.getVoice(i))))
        {
            sampleVoice->clearCurrentNote();
        }
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
    
    oscillatorSynth.setCurrentPlaybackSampleRate(sampleRate);
    sampleSynth.setCurrentPlaybackSampleRate(sampleRate);
    
    prepareVoices();
    
}

// Prepares all the voices
void EquinoxSynthesizer::prepareVoices()
{
    for (int i = 0; i < numVoices; i++)
    {
        if ((oscVoice = dynamic_cast<OscSynthVoice*>(oscillatorSynth.getVoice(i))))
        {
            oscVoice->prepareVoice(sampleRate, samplesPerBlock, numChannels, spec);
        }
        
        if ((sampleVoice = dynamic_cast<SampleSynthVoice*>(sampleSynth.getVoice(i))))
        {
            sampleVoice->prepareVoice(sampleRate, samplesPerBlock, numChannels, spec);
        }
    }
}

// Adds all the needed parameters for controlling the synth
void EquinoxSynthesizer::addParameters(std::vector<std::unique_ptr<RangedAudioParameter>> &params)
{
    // AmpEnvelope parameters
    params.push_back(std::make_unique<AudioParameterFloat>("ampAttack" + instanceNumAsString(), "AmpAttack", NormalisableRange<float>(0.01f, 5.0f, 0.1f, 1.0f), 0.01f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("ampDecay" + instanceNumAsString(), "AmpDecay", NormalisableRange<float>(0.0f, 5.0f, 0.1f, 1.0f), 1.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("ampSustain" + instanceNumAsString(), "AmpSustain", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f), 0.8f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("ampRelease" + instanceNumAsString(), "AmpRelease", NormalisableRange<float>(0.1f, 5.0f, 0.1f, 1.1f), 0.5f));
    
    
    // FilterEnvelope parameters
    params.push_back(std::make_unique<AudioParameterFloat>("filterAttack" + instanceNumAsString(), "FilterAttack", NormalisableRange<float>(0.0f, 99.0f, 0.1f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("filterDecay" + instanceNumAsString(), "FilterDecay", NormalisableRange<float>(0.0f, 99.0f, 0.1f, 1.1f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("filterSustain" + instanceNumAsString(), "FilterSustain", NormalisableRange<float>(0.0f, 99.0f, 0.1f, 1.1f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("filterRelease" + instanceNumAsString(), "FilterRelease", NormalisableRange<float>(0.0f, 200.0f, 0.1f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("envelopeCutoffLimit" + instanceNumAsString(), "EnvelopeCutoffLimit", NormalisableRange<float>(200.0f, 22050.0f, 0.1f, 0.5f), 10000.0f));
    
    // Oscillator parameters
    params.push_back(std::make_unique<AudioParameterFloat>("waveform" + instanceNumAsString(), "Waveform", 0.0f, 4.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("amplitude" + instanceNumAsString(), "Amplitude", 0.0f, 0.5f, 0.4f));
    
    // General synth parameters
    params.push_back(std::make_unique<AudioParameterFloat>("detune" + instanceNumAsString(), "Detune", -20.0f, 20.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("finePitch" + instanceNumAsString(), "FinePitch", -100.0f, 100.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("oscPanning" + instanceNumAsString(), "OscPanning", -1.0f, 1.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterInt>("pitchTranspose" + instanceNumAsString(), "PitchTranspose", -24, 24, 0));
    
    params.push_back(std::make_unique<AudioParameterInt>("analogValue" + instanceNumAsString(), "AnalogValue", 1, 40, 1));
    
    // Filter parameters
    params.push_back(std::make_unique<AudioParameterFloat>("filterType" + instanceNumAsString(), "FilterType", 0.0f, 3.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("cutoff" + instanceNumAsString(), "Cutoff", NormalisableRange<float>(50.0f, 22050.0f, 0.1f, 0.5f), 22050.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("resonance" + instanceNumAsString(), "Resonance", NormalisableRange<float>(0.0f, 0.9f, 0.01f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("drive" + instanceNumAsString(), "Drive", NormalisableRange<float>(1.0f, 15.0f, 0.01f, 1.0f), 1.0f));
    
    // SynthMode
    params.push_back(std::make_unique<AudioParameterFloat>("synthMode" + instanceNumAsString(), "SynthMode", 0.0f, 1.0f, 0.0f));
    
    // Mono & Portamento
    params.push_back(std::make_unique<AudioParameterBool>("monoEnabled" + instanceNumAsString(), "MonoEnabled", false));
    params.push_back(std::make_unique<AudioParameterFloat>("portamento" + instanceNumAsString(), "Portamento", NormalisableRange<float>(0.0f, 40000.0f, 100.0f, 1.0f), 0.0f));
    
}

bool EquinoxSynthesizer::isSynthActive() const
{
    return *treeState.getRawParameterValue("amplitude" + instanceNumAsString()) > 0.0f;
}

// Updates the synth
void EquinoxSynthesizer::updateSynth()
{
    // Check if mono has been turned on or off
    if (isMonophonic != *treeState.getRawParameterValue("monoEnabled" + instanceNumAsString()))
    {
        isMonophonic = *treeState.getRawParameterValue("monoEnabled" + instanceNumAsString());
        setVoices();
        prepareVoices();
    }
    
    // Check if currentSynthmode has changed
    if (currentSynthMode != (int)*treeState.getRawParameterValue("synthMode" + instanceNumAsString()))
    {
        currentSynthMode = static_cast<synthMode>((int)*treeState.getRawParameterValue("synthMode" + instanceNumAsString()));
    }
    
}

// Sets the parameters for both types of voices
template<typename T>
void EquinoxSynthesizer::setVoiceParameters(T voice)
{
    // sets amplitude
    voice->setAmplitude((float*)treeState.getRawParameterValue("amplitude" + instanceNumAsString()));
    
    // sets detune
    voice->setDetune((float*)treeState.getRawParameterValue("detune" + instanceNumAsString()));
    
    // sets fine pitch
    voice->setFinePitch((float*)treeState.getRawParameterValue("finePitch" + instanceNumAsString()));
    
    // sets analog value
    voice->setAnalogValue((float*)treeState.getRawParameterValue("analogValue" + instanceNumAsString()));
    
    voice->setPitchTranspose((float*)treeState.getRawParameterValue("pitchTranspose" + instanceNumAsString()));
    
    voice->setPanning((float*)treeState.getRawParameterValue("oscPanning" + instanceNumAsString()));
    
    voice->setPortamento((float*)treeState.getRawParameterValue("portamento" + instanceNumAsString()));
    
    // sets amp Envelope
    voice->getAmpEnvelope().setEnvelope((float*)treeState.getRawParameterValue("ampAttack" + instanceNumAsString()),
                                   (float*)treeState.getRawParameterValue("ampDecay" + instanceNumAsString()),
                                   (float*)treeState.getRawParameterValue("ampSustain" + instanceNumAsString()),
                                   (float*)treeState.getRawParameterValue("ampRelease" + instanceNumAsString()));

    
    // sets filterEnvelope
    voice->getFilterEnvelope().setEnvelope((float*)treeState.getRawParameterValue("filterAttack" + instanceNumAsString()),
                                      (float*)treeState.getRawParameterValue("filterDecay" + instanceNumAsString()),
                                      (float*)treeState.getRawParameterValue("filterSustain" + instanceNumAsString()),
                                      (float*)treeState.getRawParameterValue("filterRelease" + instanceNumAsString()));
    voice->getFilterEnvelope().setCutoffLimit((float*)treeState.getRawParameterValue("envelopeCutoffLimit" + instanceNumAsString()));
    
    // sets filter
    voice->getFilter().setFilter((float*)treeState.getRawParameterValue("cutoff" + instanceNumAsString()),
    (float*)treeState.getRawParameterValue("resonance" + instanceNumAsString()),
    (float*)treeState.getRawParameterValue("drive" + instanceNumAsString()));
    
    
    if (!voice->isVoiceActive())
    {
        // Sets filter mode
        voice->getFilter().setMode((float*)treeState.getRawParameterValue("filterType" + instanceNumAsString()));
    }
}

// Updates the synth and renders all the voices
void EquinoxSynthesizer::renderNextBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    updateSynth();
    
    //Only render voices if synth is active
    if (isSynthActive())
    {
        if (currentSynthMode == synthMode::oscSynthMode)
        {
            // Updating the oscSynthVoice parameters before rendering
            for (int i = 0; i < numVoices; i++)
            {
                if ((oscVoice = dynamic_cast<OscSynthVoice*>(oscillatorSynth.getVoice(i))))
                {
                    setVoiceParameters<OscSynthVoice*>(oscVoice);
                    
                    // sets oscillators waveform
                    oscVoice->setWaveform((float*)treeState.getRawParameterValue("waveform" + instanceNumAsString()));
                }
            }
            oscillatorSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
        }
        else if (currentSynthMode == synthMode::sampleSynthMode)
        {
            // Updating the oscSynthVoice parameters before rendering
            for (int i = 0; i < numVoices; i++)
            {
                if ((sampleVoice = dynamic_cast<SampleSynthVoice*>(sampleSynth.getVoice(i))))
                {
                    setVoiceParameters<SampleSynthVoice*>(sampleVoice);
                }
            }
            sampleSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
        }
        
        notesPlaying = true;
        return;
    }
    
    if (notesPlaying)
    {
        clearAllCurrentNotes();
        notesPlaying = false;
    }
}

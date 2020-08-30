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
    currentVoicingMode = voicingMode::polyphonicMode;
    instanceNum = ++objCounter;
    formatManager.registerBasicFormats();
    setVoices();
}

EquinoxSynthesizer::~EquinoxSynthesizer()
{
    formatReader = nullptr;
    --objCounter;
}

int EquinoxSynthesizer::getNumInstances()
{
    return objCounter;
}

std::string EquinoxSynthesizer::instanceNumAsStr() const
{
    return std::to_string(instanceNum);
}

// Initializes and add voices to the synth
void EquinoxSynthesizer::setVoices(int newNumberOfVoices)
{
    bool isMonoVoice = false;
    clearAllCurrentNotes();
    numVoices = newNumberOfVoices;
    
    if (numVoices == 1)
    {
        isMonoVoice = true;
    }
    
    oscillatorSynth.clearVoices();
    sampleSynth.clearVoices();
    
    
    for (int i = 0; i < numVoices; i++)
    {
        oscillatorSynth.addVoice(new OscSynthVoice(isMonoVoice));
    }
    oscillatorSynth.clearSounds();
    oscillatorSynth.addSound(new OscSynthSound());

    
    for (int i = 0; i < numVoices; i++)
    {
        sampleSynth.addVoice(new SampleSynthVoice(isMonoVoice));
    }
}

// Loads sample into a sample synth sound
void EquinoxSynthesizer::loadNewSample()
{
    FileChooser fileChooser {"Load sample"};
    
    if (fileChooser.browseForFileToOpen())
    {
        auto file = fileChooser.getResult();
        formatReader = formatManager.createReaderFor(file);
    }
    
    if (formatReader != nullptr)
    {
        BigInteger range;
        range.setRange(0, 128, true);
        sampleSynth.clearSounds();
        sampleSynth.addSound(new SampleSynthSound("Sample", *formatReader, range, 60, 10.0, sampleRate));
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

// Switches the current voicing mode
void EquinoxSynthesizer::switchVoicingMode(bool enableMono)
{
    bool shouldSwitchVoicingMode = false;

    // Checks if mono already is / isnt enabled
    for (int i = 0; i < numVoices; i++)
    {
        if ((oscVoice = dynamic_cast<OscSynthVoice*>(oscillatorSynth.getVoice(i))))
        {
            if (oscVoice->isMonoEnabled() != enableMono)
            {
                shouldSwitchVoicingMode = true;
            }
        }
        
        if ((sampleVoice = dynamic_cast<SampleSynthVoice*>(sampleSynth.getVoice(i))))
        {
            if (sampleVoice->isMonoEnabled() != enableMono)
            {
                shouldSwitchVoicingMode = true;
            }
        }
    }
    
    // Switches the voicing mode
    if (shouldSwitchVoicingMode)
    {
        if (enableMono)
        {
            currentVoicingMode = voicingMode::monophonicMode;
            setVoices(1);
        }
        else
        {
            currentVoicingMode = voicingMode::polyphonicMode;
            setVoices();
        }
        prepareVoices();
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

// Used to create AudioParameterFloats, AudioParameterInts and AudioParameterBools for the specific synth instance
// Needs improvement
//template<typename ParameterType, typename ValueType>
//std::unique_ptr<ParameterType> Synth::createSynthParameter(std::string& paramId, std::string& paramName, bool parameterIsBool, ValueType defaultValue, ValueType minValue, ValueType maxValue, ValueType intervalValue, ValueType skewFactor, bool useSymmetricSkew)
//{
//    paramId += std::to_string(instanceNum);
//    paramName += std::to_string(instanceNum);
//    
//    if (parameterIsBool)
//    {
//        return std::make_unique<ParameterType>(paramId, paramName, defaultValue);
//    }
//    else if (intervalValue)
//    {
//        return std::make_unique<ParameterType>(paramId, paramName, NormalisableRange<float>(minValue, maxValue, intervalValue, skewFactor, useSymmetricSkew), defaultValue);
//    }
//    else
//    {
//        return std::make_unique<ParameterType>(paramId, paramName, minValue, maxValue, defaultValue);
//    }
//}

// Adds all the needed parameters for controlling the synth
void EquinoxSynthesizer::addParameters(std::vector<std::unique_ptr<RangedAudioParameter>> &params)
{
    
    // AmpEnvelope parameters
    params.push_back(std::make_unique<AudioParameterFloat>("ampAttack" + instanceNumAsStr(), "AmpAttack", NormalisableRange<float>(0.0f, 5.0f, 0.1f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("ampDecay" + instanceNumAsStr(), "AmpDecay", NormalisableRange<float>(0.0f, 5.0f, 0.1f, 1.0f), 1.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("ampSustain" + instanceNumAsStr(), "AmpSustain", NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f), 0.8f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("ampRelease" + instanceNumAsStr(), "AmpRelease", NormalisableRange<float>(0.0f, 5.0f, 0.1f, 1.1f), 0.5f));
    
    
    // FilterEnvelope parameters
    params.push_back(std::make_unique<AudioParameterFloat>("filterAttack" + instanceNumAsStr(), "FilterAttack", NormalisableRange<float>(0.0f, 99.0f, 0.1f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("filterDecay" + instanceNumAsStr(), "FilterDecay", NormalisableRange<float>(0.0f, 99.0f, 0.1f, 1.1f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("filterSustain" + instanceNumAsStr(), "FilterSustain", NormalisableRange<float>(0.0f, 99.0f, 0.1f, 1.1f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("filterRelease" + instanceNumAsStr(), "FilterRelease", NormalisableRange<float>(0.0f, 200.0f, 0.1f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("envelopeCutoffLimit" + instanceNumAsStr(), "EnvelopeCutoffLimit", NormalisableRange<float>(200.0f, 22050.0f, 0.1f, 0.5f), 10000.0f));
    
    // Oscillator parameters
    params.push_back(std::make_unique<AudioParameterFloat>("waveform" + instanceNumAsStr(), "Waveform", 0.0f, 4.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("amplitude" + instanceNumAsStr(), "Amplitude", 0.0f, 0.5f, 0.4f));
    
    // General synth parameters
    params.push_back(std::make_unique<AudioParameterFloat>("detune" + instanceNumAsStr(), "Detune", -20.0f, 20.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("finePitch" + instanceNumAsStr(), "FinePitch", -100.0f, 100.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("oscPanning" + instanceNumAsStr(), "OscPanning", -1.0f, 1.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterInt>("pitchTranspose" + instanceNumAsStr(), "PitchTranspose", -24, 24, 0));
    
    params.push_back(std::make_unique<AudioParameterInt>("analogValue" + instanceNumAsStr(), "AnalogValue", 1, 40, 1));
    
    // Filter parameters
    params.push_back(std::make_unique<AudioParameterFloat>("filterType" + instanceNumAsStr(), "FilterType", 0.0f, 3.0f, 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("cutoff" + instanceNumAsStr(), "Cutoff", NormalisableRange<float>(50.0f, 22050.0f, 0.1f, 0.5f), 22050.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("resonance" + instanceNumAsStr(), "Resonance", NormalisableRange<float>(0.0f, 0.9f, 0.01f, 1.0f), 0.0f));
    
    params.push_back(std::make_unique<AudioParameterFloat>("drive" + instanceNumAsStr(), "Drive", NormalisableRange<float>(1.0f, 15.0f, 0.01f, 1.0f), 1.0f));
    
    // SynthMode
    params.push_back(std::make_unique<AudioParameterFloat>("synthMode" + instanceNumAsStr(), "SynthMode", 0.0f, 1.0f, 0.0f));
    
    // Mono & Portamento
    params.push_back(std::make_unique<AudioParameterBool>("monoEnabled" + instanceNumAsStr(), "MonoEnabled", false));
    params.push_back(std::make_unique<AudioParameterFloat>("portamento" + instanceNumAsStr(), "Portamento", NormalisableRange<float>(0.0f, 40000.0f, 100.0f, 1.0f), 0.0f));
}

// Updates the synth
void EquinoxSynthesizer::update()
{
    
    for (int i = 0; i < numVoices; i++)
    {
        if (currentSynthMode == synthMode::oscSynthMode)
        {
            if ((oscVoice = dynamic_cast<OscSynthVoice*>(oscillatorSynth.getVoice(i))))
            {
                setVoiceParameters<OscSynthVoice*>(oscVoice);
                
                // sets oscillators waveform
                oscVoice->setWaveform((float*)treeState.getRawParameterValue("waveform" + instanceNumAsStr()));
            }
        }
        else
        {
            if ((sampleVoice = dynamic_cast<SampleSynthVoice*>(sampleSynth.getVoice(i))))
            {
                setVoiceParameters<SampleSynthVoice*>(sampleVoice);
            }
        }
    }
}

// Sets the parameters for both types of voices
template<typename T>
void EquinoxSynthesizer::setVoiceParameters(T voice)
{
    // sets amplitude
    voice->setAmplitude((float*)treeState.getRawParameterValue("amplitude" + instanceNumAsStr()));
    
    // sets detune
    voice->setDetune((float*)treeState.getRawParameterValue("detune" + instanceNumAsStr()));
    
    // sets fine pitch
    voice->setFinePitch((float*)treeState.getRawParameterValue("finePitch" + instanceNumAsStr()));
    
    // sets analog value
    voice->setAnalogValue((float*)treeState.getRawParameterValue("analogValue" + instanceNumAsStr()));
    
    voice->setPitchTranspose((float*)treeState.getRawParameterValue("pitchTranspose" + instanceNumAsStr()));
    
    voice->setPanning((float*)treeState.getRawParameterValue("oscPanning" + instanceNumAsStr()));
    
    voice->setPortamento((float*)treeState.getRawParameterValue("portamento" + instanceNumAsStr()));
    
    // sets amp Envelope
    voice->getAmpEnvelope().setEnvelope((float*)treeState.getRawParameterValue("ampAttack" + instanceNumAsStr()),
                                   (float*)treeState.getRawParameterValue("ampDecay" + instanceNumAsStr()),
                                   (float*)treeState.getRawParameterValue("ampSustain" + instanceNumAsStr()),
                                   (float*)treeState.getRawParameterValue("ampRelease" + instanceNumAsStr()));

    
    // sets filterEnvelope
    voice->getFilterEnvelope().setEnvelope((float*)treeState.getRawParameterValue("filterAttack" + instanceNumAsStr()),
                                      (float*)treeState.getRawParameterValue("filterDecay" + instanceNumAsStr()),
                                      (float*)treeState.getRawParameterValue("filterSustain" + instanceNumAsStr()),
                                      (float*)treeState.getRawParameterValue("filterRelease" + instanceNumAsStr()));
    voice->getFilterEnvelope().setCutoffLimit((float*)treeState.getRawParameterValue("envelopeCutoffLimit" + instanceNumAsStr()));
    
    // sets filter
    voice->getFilter().setFilter((float*)treeState.getRawParameterValue("cutoff" + instanceNumAsStr()),
    (float*)treeState.getRawParameterValue("resonance" + instanceNumAsStr()),
    (float*)treeState.getRawParameterValue("drive" + instanceNumAsStr()));
    
    
    if (!voice->isVoiceActive())
    {
        // Sets filter mode
        voice->getFilter().setMode((float*)treeState.getRawParameterValue("filterType" + instanceNumAsStr()));
    }
}

// Renders all the voices
void EquinoxSynthesizer::renderNextBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    update();
    
    if (currentSynthMode == synthMode::oscSynthMode)
    {
        oscillatorSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    }
    else
    {
        sampleSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    }
}

/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SynthVoice.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice(bool isMonoVoice) : filterEnvelope(voiceFilter)
{
    monoMode = isMonoVoice;
    srand((unsigned int)time(nullptr)); // used for analog factor
    
}

SynthVoice::~SynthVoice()
{
}

// Used for preparing the voice and its objects
void SynthVoice::prepareVoice(double sampleRate, int samplesPerBlock, int numChannels, dsp::ProcessSpec &spec)
{
    setCurrentPlaybackSampleRate(sampleRate);
    
    voiceFilter.prepareToPlay(spec);
    
    ampEnvelope.prepareToPlay(sampleRate);
    
    filterEnvelope.prepareToPlay(sampleRate);
    
    voiceBuffer.setSize(numChannels, samplesPerBlock);
}

void SynthVoice::setFrequency(double frequency)
{
    previousModifiedFrequency = getFrequency();
    this->frequency = frequency;
}

double SynthVoice::getFrequency() const
{
    return frequency * frequencyModifications();
}

float SynthVoice::getKeyVelocity() const
{
    return midiKeyVelocity;
}

float SynthVoice::getDetune() const
{
    return detune;
}

float SynthVoice::frequencyModifications() const
{
    if (applyPortamento)
    {
        return finePitch * pitchTranspose * analogFactor * getNextPortamentoValue();
    }
    return finePitch * pitchTranspose * analogFactor;
}


Filter& SynthVoice::getFilter()
{
    return voiceFilter;
}

FilterEnvelope& SynthVoice::getFilterEnvelope()
{
    return filterEnvelope;
}

AmpEnvelope& SynthVoice::getAmpEnvelope()
{
    return ampEnvelope;
}

void SynthVoice::setPanning(float* panValue)
{
    panningValue = *panValue;
}

float SynthVoice::getPanning(int currentChannel) const
{
    float panning = 1;
    short LeftChannel = 0;
    short rightChannel = 1;
    
    // Turns down the left channel if panning right
    if (currentChannel == LeftChannel && panningValue > 0)
    {
        return panning -= panningValue;
    }
    
    // Turns down the right channel if panning left
    if (currentChannel == rightChannel && panningValue < 0)
    {
        return panning += panningValue;
    }
    return panning; //returns panning at default value of 1 if panningValue is 0 (no active panning)
}

void SynthVoice::setPortamento(float* timeValue)
{
    portamentoTime = static_cast<int>(*timeValue);
}

bool SynthVoice::isMonoEnabled() const
{
    return monoMode;
}

double SynthVoice::getNextPortamentoValue() const
{
    double targetValue = 1;
    
    if (portamentoTime > 0 && portamentoValue != targetValue)
    {
        double startRatio = previousModifiedFrequency / currentModifiedFrequency;
        
        if (!portamentoStartValueHasBeenSet)
        {
            portamentoValue = startRatio;
            portamentoStartValueHasBeenSet = true;
        }
        
        double glideRate = (targetValue - startRatio) / portamentoTime;
        
        portamentoValue += glideRate;
        
        if (targetValue > startRatio && portamentoValue > targetValue)
        {
            portamentoValue = targetValue;
        }
        else if (targetValue < startRatio && portamentoValue < targetValue)
        {
            portamentoValue = targetValue;
        }
        return portamentoValue;
    }
    
    return 1;
}

void SynthVoice::setAmplitude(float* ampValue)
{
    masterAmplitude = *ampValue;
    
    if (masterAmplitude > 1)
    {
        masterAmplitude = 1;
    }
}

void SynthVoice::setDetune(float* detuneValue)
{
    detune = noteOffsetInHertz(*detuneValue);

}

void SynthVoice::setAnalogValue(float* analogValue)
{
    this->analogValue = static_cast<int>(*analogValue);
}

float SynthVoice::getRandomAnalogFactor() const
{
    if (analogValue == 1)
    {
        return analogValue;
    }
    return noteOffsetInHertz(rand() % (analogValue + 1) + (-((analogValue / 2) + 1)));
}

void SynthVoice::setPitchTranspose(float* transposeValue)
{
    pitchTranspose = noteOffsetInHertz(*transposeValue * 100);
}

void SynthVoice::setFinePitch(float* pitchValue)
{
    finePitch = noteOffsetInHertz(*pitchValue);
}


void SynthVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    applyPortamento = false;
    setPitchBend(currentPitchWheelPosition);
    analogFactor = getRandomAnalogFactor();
    currentModifiedFrequency = getFrequency();
    
    if (monoMode && noteHasBeenTriggered && portamentoTime > 0)
    {
        applyPortamento = true;
        portamentoStartValueHasBeenSet = false;
        portamentoValue = 0;
    }
    
    if (!noteHasBeenTriggered || inRelease)
    {
        voiceFilter.reset();
        midiKeyVelocity = velocity;
        ampEnvelope.noteOn();
        filterEnvelope.noteOn();
        noteHasBeenTriggered = true;
        inRelease = false;
    }
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    if (monoMode && isKeyDown()) { return; }
    
    ampEnvelope.noteOff();
    filterEnvelope.noteOff();
    inRelease = true;
}

void SynthVoice::resetNote()
{
    noteHasBeenTriggered = false;
    clearCurrentNote();
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    setPitchBend(newPitchWheelValue);
    setFrequency(noteInHertz(currentNoteNumber, getPitchBendCents()));
}

void SynthVoice::setPitchBend(int pitchWheelValue)
{
    if (pitchWheelValue > 8192)
    {
        pitchBend = float(pitchWheelValue - 8192) / (16383 - 8192);
    }
    else
    {
        pitchBend = float(8192 - pitchWheelValue) / -8192;
    }
}

float SynthVoice::getPitchBendCents() const
{
    return pitchBend * pitchBendSemitones * 100;
}

void SynthVoice::setFrequencyByMidiNote(int midiNote)
{
    setFrequency(noteInHertz(midiNote, getPitchBendCents()));
    currentNoteNumber = midiNote;
}

double SynthVoice::noteInHertz(int midiNoteNumber, double centsOffset) const
{
    double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    hertz *= noteOffsetInHertz(centsOffset);
    return hertz;
}

double SynthVoice::noteOffsetInHertz(double offset) const
{
    return std::pow(2.0, offset / 1200);
}

bool SynthVoice::isVoiceActive() const
{
    return getCurrentlyPlayingNote() >= 0 && masterAmplitude > 0.0f;
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::addBufferToOutput(AudioBuffer<float> &bufferToAdd, AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    getFilterEnvelope().calculateNextValue();
    
    //Pocesses the buffer through the filter and replaces it
    voiceFilter.process(bufferToAdd);
    
    for (int sample = 0; sample < numSamples; ++sample)
    {
        currentVoiceAmplitude = ampEnvelope.getNextSample() * getKeyVelocity();
        
        for (int channel = 0; channel < bufferToAdd.getNumChannels(); ++channel)
        {
            outputBuffer.addSample (channel, startSample, bufferToAdd.getSample(channel, sample) * currentVoiceAmplitude * masterAmplitude * getPanning(channel));
        }
        ++startSample;
    }
    
    if (currentVoiceAmplitude == 0.0f)
    {
        resetNote();
    }
}

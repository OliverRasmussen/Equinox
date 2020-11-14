/*
  ==============================================================================

    SynthVoice.cpp
    Created: 2 May 2020 4:50:30pm
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


// Returns frequency with modifications applied
double SynthVoice::getFrequency() const
{
    return frequency * frequencyModifications();
}

float SynthVoice::getKeyVelocity() const
{
    return midiKeyVelocity;
}

float SynthVoice::getAmplitude() const
{
    return amplitude;
}

float SynthVoice::getDetune() const
{
    return detune;
}

// method used for applying various modifications to the frequency
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

// returns the current panning
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

// Calculates and returns the next portamento value
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
    amplitude = *ampValue;
    
    if (amplitude > 1)
    {
        amplitude = 1;
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

// returns a random value factor. Randomness is determined by Analogvalue
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
    
    if (!noteHasBeenTriggered)
    {
        voiceFilter.reset();
        midiKeyVelocity = velocity;
        ampEnvelope.noteOn();
        filterEnvelope.noteOn();
        noteHasBeenTriggered = true;
    }
    
    if (monoMode && !voiceStoppedPlaying && portamentoTime > 0)
    {
        applyPortamento = true;
        portamentoStartValueHasBeenSet = false;
        portamentoValue = 0;
    }
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    if (!isKeyDown())
    {
        ampEnvelope.noteOff();
        filterEnvelope.noteOff();
        if (!ampEnvelope.isActive() || velocity == 0)
        {
            resetNote();
        }        
    }
}

void SynthVoice::resetNote()
{
    clearCurrentNote();
    noteHasBeenTriggered = false;
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

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::addBufferToOutput(AudioBuffer<float> &bufferToAdd, AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    getAmpEnvelope().setParameters();
    getFilterEnvelope().setParameters();
    
    //Pocesses the buffer through the filter and replaces it
    voiceFilter.process(bufferToAdd);
    
    for (int sample = 0; sample < numSamples; ++sample)
    {
        for (int channel = 0; channel < bufferToAdd.getNumChannels(); ++channel)
        {
            outputBuffer.addSample (channel, startSample, bufferToAdd.getSample(channel, sample) * ampEnvelope.getNextSample() * getKeyVelocity() * getAmplitude() * getPanning(channel));
        }
        ++startSample;
    }
}

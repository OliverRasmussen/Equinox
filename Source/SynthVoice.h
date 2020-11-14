/*
  ==============================================================================

    SynthVoice.h
    Created: 2 May 2020 4:50:30pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Filter.h"
#include "AmpEnvelope.h"
#include "FilterEnvelope.h"

class SynthVoice : public SynthesiserVoice
{
public:
    
    SynthVoice(bool isMonoVoice);
    
    virtual ~SynthVoice() override;
    
    virtual void prepareVoice(double sampleRate, int samplesPerBlock, int numChannels, dsp::ProcessSpec&);
    
    void setPanning(float* panValue);
    
    void setAmplitude(float* ampValue);
    
    void setDetune(float* detuneValue);
    
    void setAnalogValue(float* analogValue);
    
    void setPitchTranspose(float* transposeValue);
    
    void setFinePitch(float* pitchValue);
    
    void setPortamento(float* timeValue);
    
    bool isMonoEnabled() const;
    
    Filter& getFilter();
    
    FilterEnvelope& getFilterEnvelope();
    
    AmpEnvelope& getAmpEnvelope();
    
    using SynthesiserVoice::clearCurrentNote;
    
protected:
    
    void setFrequency(double frequency);
    
    float frequencyModifications() const;
    
    double getFrequency() const;
    
    float getKeyVelocity() const;
    
    float getAmplitude() const;
    
    float getDetune() const;
    
    float getPanning(int currentChannel) const;
    
    float getRandomAnalogFactor() const;
    
    double getNextPortamentoValue() const;
    
    virtual void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    virtual void stopNote(float velocity, bool allowTailOff) override;
    
    virtual void resetNote();
    
    void addBufferToOutput(AudioBuffer<float> &bufferToAdd, AudioBuffer<float> &outputBuffer, int startSample, int numSamples);
    
    void pitchWheelMoved(int newPitchWheelValue) override;
    
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    
    void setPitchBend(int pitchWheelValue);
    
    void setFrequencyByMidiNote(int midiNote);
    
    float getPitchBendCents() const;
    
    double noteInHertz(int midiNoteNumber, double centsOffset) const;
    
    double noteOffsetInHertz(double offset) const;
    
    AudioBuffer<float> voiceBuffer;
    
    int currentNoteNumber;
    
    bool noteHasBeenTriggered = false;
    
    bool voiceStoppedPlaying = true;
    
    double currentModifiedFrequency = 0;
    
    double previousModifiedFrequency = 0;    
    
private:
    
    bool applyPortamento = false;
    
    double frequency;
    
    
    float detune = 0.0f;
    
    float amplitude = 1.0f;
    
    float midiKeyVelocity;
    
    Filter voiceFilter;
    
    FilterEnvelope filterEnvelope;
    
    AmpEnvelope ampEnvelope;
    
    float finePitch = 0.0f;
    
    float pitchTranspose = 0.0f;
    
    int analogValue = 0;
    
    float panningValue = 0;
    
    float analogFactor = 0.0f;
    
    float pitchBend = 0.0f;
    
    float pitchBendSemitones = 1.0f;
    
    bool monoMode = false;
    
    float portamentoTime = 4000;
    
    mutable double portamentoValue = 0.0;
    
    mutable bool portamentoStartValueHasBeenSet = false;
    
};

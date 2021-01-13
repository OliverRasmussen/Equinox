/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SynthVoice.h
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
    
    /** Prepares the voices*/
    virtual void prepareVoice(double sampleRate, int samplesPerBlock, int numChannels, dsp::ProcessSpec&);
    
    /** Sets the stereo panning of the voice*/
    void setPanning(float* panValue);
    
    /** Sets the voice amplitude*/
    void setAmplitude(float* ampValue);
    
    /** Sets the voice detune*/
    void setDetune(float* detuneValue);
    
    /** Sets the voice analog value*/
    void setAnalogValue(float* analogValue);
    
    /** Sets the voice pitch transpose*/
    void setPitchTranspose(float* transposeValue);
    
    /** Sets the voice fine pitch*/
    void setFinePitch(float* pitchValue);
    
    /** Sets the amount of portamento*/
    void setPortamento(float* timeValue);
    
    /** Returns true if mono is enabled*/
    bool isMonoEnabled() const;
    
    /** Returns a reference to the voice filter object*/
    Filter& getFilter();
    
    /** Returns a reference to the voice filter envelope object*/
    FilterEnvelope& getFilterEnvelope();
    
    /** Returns a reference to the voice amp envelope object*/
    AmpEnvelope& getAmpEnvelope();
    
    using SynthesiserVoice::clearCurrentNote;
    
protected:
    
    /** Sets the frequency of the voice*/
    void setFrequency(double frequency);
    
    /** Returns the frequency modifications*/
    float frequencyModifications() const;
    
    /** Returns the voice current frequency WITH modifications applied*/
    double getFrequency() const;
    
    /** Returns the key velocity*/
    float getKeyVelocity() const;
    
    /** Returns the detune amount*/
    float getDetune() const;
    
    /** Returns the amount of panning*/
    float getPanning(int currentChannel) const;
    
    /** Returns a random generated value*/
    float getRandomAnalogFactor() const;
    
    /** Returns the next portamento value*/
    double getNextPortamentoValue() const;
    
    /** Called when a note starts*/
    virtual void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    /** Called when a note ends*/
    virtual void stopNote(float velocity, bool allowTailOff) override;
    
    /** Resets the note*/
    virtual void resetNote();
    
    /** Adds an audiobuffer to another audiobuffer*/
    void addBufferToOutput(AudioBuffer<float> &bufferToAdd, AudioBuffer<float> &outputBuffer, int startSample, int numSamples);
    
    /** Called when the pitch wheel has been moved*/
    void pitchWheelMoved(int newPitchWheelValue) override;
    
    /** Called when the controller has been moved*/
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    
    /** Sets the amount of pitchbend*/
    void setPitchBend(int pitchWheelValue);
    
    /** Sets the frequency by midinote number*/
    void setFrequencyByMidiNote(int midiNote);
    
    /** Returns the current pitch bend in cents*/
    float getPitchBendCents() const;
    
    /** Converts and returns the passed in midinote number and offset in cents as hertz*/
    double noteInHertz(int midiNoteNumber, double centsOffset) const;
    
    /** Converts and returns a notes offset to hertz*/
    double noteOffsetInHertz(double offset) const;
    
    AudioBuffer<float> voiceBuffer;
    
    int currentNoteNumber;
    
    bool noteHasBeenTriggered = false;
    
    bool inRelease = false;
    
    double currentModifiedFrequency = 0;
    
    double previousModifiedFrequency = 0;
    
    float currentVoiceAmplitude = 0;
    
private:
    
    bool applyPortamento = false;
    
    double frequency;
    
    float detune = 0.0f;
    
    float masterAmplitude = 1.0f;
    
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

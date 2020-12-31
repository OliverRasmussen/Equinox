/*
  ==============================================================================

    SynthGUI.cpp
    Created: 13 May 2020 9:21:08pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "SynthGUI.h"

//==============================================================================
SynthGUI::SynthGUI(StateManager& stateManager, std::string synthInstance) : stateManager(stateManager), synthInstance(synthInstance)
{
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 0.5f, 0.4f, 40, 40, "amplitude" + synthInstance, "Amp", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, -24, 24, 0.0f, 40, 40, "pitchTranspose" + synthInstance, "Transpose", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, -100.0f, 100.0f, 0.0f, 40, 40, "finePitch" + synthInstance, "Fine Pitch", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 1.0f, 40.0f, 1.0f, 40, 40, "analogValue" + synthInstance, "Analog Factor", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, -1.0f, 1.0f, 0.0f, 40, 40, "oscPanning" + synthInstance, "Pan", stateManager));
    
    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, -20.0f, 20.0f, 0.0f, 40, 40, "detune" + synthInstance, "Detune", stateManager));

    addLabelSlider(std::make_shared<LabelSlider>(Slider::SliderStyle::RotaryHorizontalVerticalDrag, 0.0f, 40000.0f, 0.0f, 40, 40, "portamento" + synthInstance, "Portamento", stateManager));
    

    // Mono button
    monoButton.setClickingTogglesState(true);
    monoAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(stateManager.getParameters(), "monoEnabled" + synthInstance, monoButton);
    addAndMakeVisible(monoButton);
}

SynthGUI::~SynthGUI()
{
}

void SynthGUI::paint (Graphics& g)
{
    
}

void SynthGUI::resized()
{
    LabelSlider& amplitudeSlider = *getSlider("amplitude" + synthInstance);
    amplitudeSlider.setBounds(105, 2, 40, 70);
    amplitudeSlider.setSliderComponentBounds(amplitudeSlider.getSliderComponentBounds().getX(), 14);
    amplitudeSlider.setLabelComponentBounds(amplitudeSlider.getLabelComponentBounds().getX(), 2, amplitudeSlider.getWidth(), 30);
    amplitudeSlider.center();
    
    LabelSlider& panningSlider = *getSlider("oscPanning" + synthInstance);
    panningSlider.setBounds(140, 2, 40, 70);
    panningSlider.setSliderComponentBounds(panningSlider.getSliderComponentBounds().getX(), 14);
    panningSlider.setLabelComponentBounds(panningSlider.getLabelComponentBounds().getX(), 2, panningSlider.getWidth(), 30);
    panningSlider.center();
    
    LabelSlider& portamentoSlider = *getSlider("portamento" + synthInstance);
    portamentoSlider.setBounds(75, 46, 50, 70);
    portamentoSlider.setSliderComponentBounds(portamentoSlider.getSliderComponentBounds().getX(), 14);
    portamentoSlider.setLabelComponentBounds(portamentoSlider.getLabelComponentBounds().getX(), 2, portamentoSlider.getWidth(), 30);
    portamentoSlider.center();
    
    LabelSlider& analogSlider = *getSlider("analogValue" + synthInstance);
    analogSlider.setBounds(5, 93, 50, 70);
    analogSlider.setSliderComponentBounds(analogSlider.getSliderComponentBounds().getX(), 14);
    analogSlider.setLabelComponentBounds(analogSlider.getLabelComponentBounds().getX(), 2, analogSlider.getWidth(), 30);
    analogSlider.center();
    
    LabelSlider& finePitchSlider = *getSlider("finePitch" + synthInstance);
    finePitchSlider.setBounds(50, 93, 50, 70);
    finePitchSlider.setSliderComponentBounds(finePitchSlider.getSliderComponentBounds().getX(), 14);
    finePitchSlider.setLabelComponentBounds(finePitchSlider.getLabelComponentBounds().getX(), 2, finePitchSlider.getWidth(), 30);
    finePitchSlider.center();
    
    LabelSlider& transposeSlider = *getSlider("pitchTranspose" + synthInstance);
    transposeSlider.setBounds(105, 93, 50, 70);
    transposeSlider.setSliderComponentBounds(transposeSlider.getSliderComponentBounds().getX(), 14);
    transposeSlider.setLabelComponentBounds(transposeSlider.getLabelComponentBounds().getX(), 2, transposeSlider.getWidth(), 30);
    transposeSlider.center();
    
    LabelSlider& detuneSlider = *getSlider("detune" + synthInstance);
    detuneSlider.setBounds(155, 93, 50, 70);
    detuneSlider.setSliderComponentBounds(detuneSlider.getSliderComponentBounds().getX(), 14);
    detuneSlider.setLabelComponentBounds(detuneSlider.getLabelComponentBounds().getX(), 2, detuneSlider.getWidth(), 30);
    detuneSlider.center();
    
    monoButton.setBounds(5, 68, 70, 20);
}

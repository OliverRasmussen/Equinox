/*
  ==============================================================================

    SynthGUI.cpp
    Created: 13 May 2020 9:21:08pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/
#include "SynthGUI.h"

//==============================================================================
SynthGUI::SynthGUI(EquinoxAudioProcessor& p, EquinoxSynthesizer& s) : processor(p), synth(s)
{
    setSize(200, 200);
    
    // Amplitude slider
    ampSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ampSlider.setRange(0.0f, 0.5f);
    ampSlider.setValue (0.4f);
    ampSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&ampSlider);
    
    ampAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "amplitude" + synth.instanceNumAsStr(), ampSlider);
    
    // Amplitude Label
    ampLabel.setText("Amp", NotificationType::dontSendNotification);
    ampLabel.setSize(46, 18);
    ampLabel.setMinimumHorizontalScale(0.1f);
    ampLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&ampLabel);
    
    // Pitch transpose menu
    pitchTransposeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pitchTransposeSlider.setRange(-24, 24, 1);
    pitchTransposeSlider.setValue(0);
    pitchTransposeSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&pitchTransposeSlider);
    
    pitchTransposeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "pitchTranspose" + synth.instanceNumAsStr(), pitchTransposeSlider);
    
    // Pitchtranspose Label
    pitchTransposeLabel.setText("Transpose", NotificationType::dontSendNotification);
    pitchTransposeLabel.setSize(46, 18);
    pitchTransposeLabel.setMinimumHorizontalScale(0.1f);
    pitchTransposeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&pitchTransposeLabel);
    
    
    // Fine pitch slider
    finePitchSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    finePitchSlider.setRange(-100.0f, 100.0f);
    finePitchSlider.setValue(0.0f);
    finePitchSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&finePitchSlider);
    
    finePitchAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "finePitch" + synth.instanceNumAsStr(), finePitchSlider);
    
    // finePitch Label
    finePitchLabel.setText("Fine Pitch", NotificationType::dontSendNotification);
    finePitchLabel.setSize(46, 18);
    finePitchLabel.setMinimumHorizontalScale(0.1f);
    finePitchLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&finePitchLabel);
    
    // Analog slider
    analogSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    analogSlider.setRange(1, 40, 1);
    analogSlider.setValue(1);
    analogSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&analogSlider);
    
    analogAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "analogValue" + synth.instanceNumAsStr(), analogSlider);
    
    // Analog Label
    analogLabel.setText("Analog Factor", NotificationType::dontSendNotification);
    analogLabel.setSize(55, 18);
    analogLabel.setMinimumHorizontalScale(0.3f);
    analogLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&analogLabel);
    
    // Panning slider
    panningSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    panningSlider.setRange(-1.0f, 1.0f);
    panningSlider.setValue(0);
    panningSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&panningSlider);
    
    panningAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "oscPanning" + synth.instanceNumAsStr(), panningSlider);
    
    // Panning Label
    panningLabel.setText("Pan", NotificationType::dontSendNotification);
    panningLabel.setSize(46, 18);
    panningLabel.setMinimumHorizontalScale(0.1f);
    panningLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&panningLabel);
    
    // Detune slider
    detuneSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    detuneSlider.setRange(-20.0f, 20.0f);
    detuneSlider.setValue(0.0f);
    detuneSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&detuneSlider);
    
    detuneAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "detune" + synth.instanceNumAsStr(), detuneSlider);
    
    // Detune Label
    detuneLabel.setText("Detune", NotificationType::dontSendNotification);
    detuneLabel.setSize(46, 14);
    detuneLabel.setMinimumHorizontalScale(0.1f);
    detuneLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&detuneLabel);
    
    // Portamento slider
    portamentoSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    portamentoSlider.setRange(0, 40000);
    portamentoSlider.setValue(0);
    portamentoSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&portamentoSlider);
    
    portamentoAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "portamento" + synth.instanceNumAsStr(), portamentoSlider);
    
    // Portamento Label
    portamentoLabel.setText("Portamento", NotificationType::dontSendNotification);
    portamentoLabel.setSize(54, 22);
    portamentoLabel.setMinimumHorizontalScale(0.1f);
    portamentoLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&portamentoLabel);
    
    
    // Mono button
    processor.treeState.addParameterListener("monoEnabled" + synth.instanceNumAsStr(), this);
    if (AudioParameterBool* monoEnabledParameter = dynamic_cast<AudioParameterBool*>(processor.treeState.getParameter("monoEnabled" + synth.instanceNumAsStr())))
    {
        currentVoicingModeState = std::make_unique<AudioParameterBool*>(monoEnabledParameter);
    }
    monoButton.setClickingTogglesState(true);
    monoButton.onClick = [&]() { monoSwitch(); };
    addAndMakeVisible(monoButton);

}

SynthGUI::~SynthGUI()
{
}

void SynthGUI::monoSwitch()
{
    if (monoButton.getToggleState())
    {
        synth.switchVoicingMode(true);
    }
    else
    {
        synth.switchVoicingMode(false);
    }
    
    // Sets currentVoicingModeState to same value as the button if it isnt equal
    if (processor.treeState.getParameterAsValue("monoEnabled" + synth.instanceNumAsStr()) != monoButton.getToggleState())
    {
        **currentVoicingModeState = monoButton.getToggleState();
    }
}

void SynthGUI::parameterChanged(const String &parameterID, float newValue)
{
    juce::String monoEnabledId = "monoEnabled" + synth.instanceNumAsStr();
    if (parameterID == monoEnabledId)
    {
        if (newValue != monoButton.getToggleState())
        {
            monoButton.triggerClick();
        }
    }
}

void SynthGUI::paint (Graphics& g)
{
    
}

void SynthGUI::resized()
{
    ampSlider.setBounds(105, 14, 40, 40);
    ampLabel.setBounds(104, 2, 40, 30);
    
    panningSlider.setBounds(140, 14, 40, 40);
    panningLabel.setBounds(137, 2, 40, 30);
    
    portamentoSlider.setBounds(75, 58, 40, 40);
    portamentoLabel.setBounds(68, 46, 40, 30);
    
    monoButton.setBounds(5, 68, 70, 20);
    
    analogSlider.setBounds(5, 105, 40, 40);
    analogLabel.setBounds(0, 93, 40, 30);
    
    finePitchSlider.setBounds(55, 105, 40, 40);
    finePitchLabel.setBounds(53, 93, 40, 30);
    
    pitchTransposeSlider.setBounds(105, 105, 40, 40);
    pitchTransposeLabel.setBounds(102, 93, 40, 30);
    
    detuneSlider.setBounds(155, 105, 40, 40);
    detuneLabel.setBounds(155, 87, 40, 30);
}

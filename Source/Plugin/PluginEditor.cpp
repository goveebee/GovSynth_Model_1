#include "PluginEditor.h"

EmilSynthAudioProcessorEditor::EmilSynthAudioProcessorEditor(EmilSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    setSize(600, 400);
}

EmilSynthAudioProcessorEditor::~EmilSynthAudioProcessorEditor() {}

void EmilSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(24.0f));
    g.drawFittedText("Emil Synth - M0", getLocalBounds().withTrimmedTop(20), juce::Justification::centredTop, 1);
}

void EmilSynthAudioProcessorEditor::resized() {}

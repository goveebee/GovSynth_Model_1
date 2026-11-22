#pragma once
#include "PluginProcessor.h"

class EmilSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit EmilSynthAudioProcessorEditor(EmilSynthAudioProcessor&);
    ~EmilSynthAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    EmilSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EmilSynthAudioProcessorEditor)
};

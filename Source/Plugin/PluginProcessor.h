#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "../Parameters/ParameterLayout.h"
#include "../Engine/SynthEngine.h"

class GovSynthModel1AudioProcessor : public juce::AudioProcessor,
                                          public juce::MidiKeyboardState::Listener
{
public:
    GovSynthModel1AudioProcessor();
    ~GovSynthModel1AudioProcessor() override;


    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "GovSynthModel1"; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    void triggerTestNote(bool on) { engine.triggerNote(60, on); }


    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState& getAPVTS() { return apvts; }
    juce::MidiKeyboardState& getKeyboardState() { return keyboardState; }

    // MidiKeyboardState::Listener overrides
    void handleNoteOn(juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;

private:
    juce::AudioProcessorValueTreeState apvts;
    SynthEngine engine;
    juce::MidiKeyboardState keyboardState;
    std::unique_ptr<juce::FileLogger> fileLogger;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GovSynthModel1AudioProcessor)
};

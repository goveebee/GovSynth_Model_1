#pragma once
#include "PluginProcessor.h"

class GovSynthModel1AudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit GovSynthModel1AudioProcessorEditor(GovSynthModel1AudioProcessor&);
    ~GovSynthModel1AudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    GovSynthModel1AudioProcessor& processor;

    juce::ComboBox osc1WaveBox;
    juce::ComboBox osc2WaveBox;
    juce::Slider osc1LevelSlider;
    juce::Slider osc2LevelSlider;
    juce::Slider osc1OctaveSlider;
    juce::Slider osc1SemitoneSlider;
    juce::Slider osc1DetuneSlider;
    juce::Slider osc2OctaveSlider;
    juce::Slider osc2SemitoneSlider;
    juce::Slider osc2DetuneSlider;
    juce::Slider ampAttackSlider;
    juce::Slider ampDecaySlider;
    juce::Slider ampSustainSlider;
    juce::Slider ampReleaseSlider;
    juce::Slider masterVolumeSlider;

    juce::Label osc1WaveLabel;
    juce::Label osc2WaveLabel;
    juce::Label osc1LevelLabel;
    juce::Label osc2LevelLabel;
    juce::Label osc1OctaveLabel;
    juce::Label osc1SemitoneLabel;
    juce::Label osc1DetuneLabel;
    juce::Label osc2OctaveLabel;
    juce::Label osc2SemitoneLabel;
    juce::Label osc2DetuneLabel;
    juce::Label ampAttackLabel;
    juce::Label ampDecayLabel;
    juce::Label ampSustainLabel;
    juce::Label ampReleaseLabel;
    juce::Label masterVolumeLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> osc1WaveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> osc2WaveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc1LevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc2LevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc1OctaveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc1SemitoneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc1DetuneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc2OctaveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc2SemitoneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc2DetuneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ampAttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ampDecayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ampSustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ampReleaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterVolumeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GovSynthModel1AudioProcessorEditor)
};

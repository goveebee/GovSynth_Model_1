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

    juce::ComboBox oscWaveBox;
    juce::Slider oscLevelSlider;
    juce::Slider ampAttackSlider;
    juce::Slider ampDecaySlider;
    juce::Slider ampSustainSlider;
    juce::Slider ampReleaseSlider;
    juce::Slider masterVolumeSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscLevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ampAttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ampDecayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ampSustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ampReleaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterVolumeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GovSynthModel1AudioProcessorEditor)
};

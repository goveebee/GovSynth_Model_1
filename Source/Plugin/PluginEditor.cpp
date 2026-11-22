#include "PluginEditor.h"
#include "../Parameters/ParameterIDs.h"

GovSynthModel1AudioProcessorEditor::GovSynthModel1AudioProcessorEditor(GovSynthModel1AudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    auto& apvts = processor.getAPVTS();

    oscWaveBox.setTextWhenNothingSelected("Waveform");
    addAndMakeVisible(oscWaveBox);
    oscWaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, Params::OscWave, oscWaveBox);

    addAndMakeVisible(oscLevelSlider);
    oscLevelSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    oscLevelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    oscLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::OscLevel, oscLevelSlider);

    addAndMakeVisible(ampAttackSlider);
    ampAttackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    ampAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    ampAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpAttack, ampAttackSlider);

    addAndMakeVisible(ampDecaySlider);
    ampDecaySlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    ampDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    ampDecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpDecay, ampDecaySlider);

    addAndMakeVisible(ampSustainSlider);
    ampSustainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    ampSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    ampSustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpSustain, ampSustainSlider);

    addAndMakeVisible(ampReleaseSlider);
    ampReleaseSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    ampReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    ampReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpRelease, ampReleaseSlider);

    addAndMakeVisible(masterVolumeSlider);
    masterVolumeSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    masterVolumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    masterVolumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::MasterVolume, masterVolumeSlider);

    setSize(700, 500);
}

GovSynthModel1AudioProcessorEditor::~GovSynthModel1AudioProcessorEditor() {}

void GovSynthModel1AudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(juce::FontOptions(24.0f)));
    g.drawFittedText("GovSynth Model 1 - M1", getLocalBounds().withTrimmedTop(20), juce::Justification::centredTop, 1);
}

void GovSynthModel1AudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto top = area.removeFromTop(40);
    oscWaveBox.setBounds(top.removeFromLeft(200));

    auto row = area.removeFromTop(120);
    auto col1 = row.removeFromLeft(100);
    oscLevelSlider.setBounds(col1);
    auto col2 = row.removeFromLeft(100);
    ampAttackSlider.setBounds(col2);
    auto col3 = row.removeFromLeft(100);
    ampDecaySlider.setBounds(col3);
    auto col4 = row.removeFromLeft(100);
    ampSustainSlider.setBounds(col4);
    auto col5 = row.removeFromLeft(100);
    ampReleaseSlider.setBounds(col5);
    auto col6 = row.removeFromLeft(100);
    masterVolumeSlider.setBounds(col6);
}

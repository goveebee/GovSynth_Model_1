#include "PluginEditor.h"
#include "../Parameters/ParameterIDs.h"

GovSynthModel1AudioProcessorEditor::GovSynthModel1AudioProcessorEditor(GovSynthModel1AudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    auto& apvts = processor.getAPVTS();

    osc1WaveBox.setTextWhenNothingSelected("Osc 1 Wave");
    addAndMakeVisible(osc1WaveBox);
    osc1WaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, Params::Osc1Wave, osc1WaveBox);
    osc1WaveLabel.setText("Osc 1 Wave", juce::dontSendNotification);
    addAndMakeVisible(osc1WaveLabel);

    osc2WaveBox.setTextWhenNothingSelected("Osc 2 Wave");
    addAndMakeVisible(osc2WaveBox);
    osc2WaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, Params::Osc2Wave, osc2WaveBox);
    osc2WaveLabel.setText("Osc 2 Wave", juce::dontSendNotification);
    addAndMakeVisible(osc2WaveLabel);

    addAndMakeVisible(osc1LevelSlider);
    osc1LevelSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    osc1LevelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    osc1LevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc1Level, osc1LevelSlider);
    osc1LevelLabel.setText("Osc 1 Level", juce::dontSendNotification);
    addAndMakeVisible(osc1LevelLabel);

    addAndMakeVisible(osc2LevelSlider);
    osc2LevelSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    osc2LevelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    osc2LevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc2Level, osc2LevelSlider);
    osc2LevelLabel.setText("Osc 2 Level", juce::dontSendNotification);
    addAndMakeVisible(osc2LevelLabel);

    addAndMakeVisible(ampAttackSlider);
    ampAttackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    ampAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    ampAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpAttack, ampAttackSlider);
    ampAttackLabel.setText("Amp Attack", juce::dontSendNotification);
    addAndMakeVisible(ampAttackLabel);

    addAndMakeVisible(ampDecaySlider);
    ampDecaySlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    ampDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    ampDecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpDecay, ampDecaySlider);
    ampDecayLabel.setText("Amp Decay", juce::dontSendNotification);
    addAndMakeVisible(ampDecayLabel);

    addAndMakeVisible(ampSustainSlider);
    ampSustainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    ampSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    ampSustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpSustain, ampSustainSlider);
    ampSustainLabel.setText("Amp Sustain", juce::dontSendNotification);
    addAndMakeVisible(ampSustainLabel);

    addAndMakeVisible(ampReleaseSlider);
    ampReleaseSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    ampReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    ampReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpRelease, ampReleaseSlider);
    ampReleaseLabel.setText("Amp Release", juce::dontSendNotification);
    addAndMakeVisible(ampReleaseLabel);

    addAndMakeVisible(masterVolumeSlider);
    masterVolumeSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    masterVolumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    masterVolumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::MasterVolume, masterVolumeSlider);
    masterVolumeLabel.setText("Master Volume", juce::dontSendNotification);
    addAndMakeVisible(masterVolumeLabel);

    setSize(800, 600);
}

GovSynthModel1AudioProcessorEditor::~GovSynthModel1AudioProcessorEditor() {}

void GovSynthModel1AudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(juce::FontOptions(24.0f)));
    g.drawFittedText("GovSynthModel1 - M1", getLocalBounds().withTrimmedTop(20), juce::Justification::centredTop, 1);
}

void GovSynthModel1AudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto top = area.removeFromTop(40);
    osc1WaveBox.setBounds(top.removeFromLeft(200));
    osc2WaveBox.setBounds(top.removeFromLeft(200));

    auto row = area.removeFromTop(150);
    auto makeCol = [&](auto& slider, auto& label) {
        auto col = row.removeFromLeft(120);
        auto labelArea = col.removeFromTop(20);
        label.setBounds(labelArea);
        slider.setBounds(col.reduced(0,20));
    };
    makeCol(osc1LevelSlider, osc1LevelLabel);
    makeCol(osc2LevelSlider, osc2LevelLabel);
    makeCol(ampAttackSlider, ampAttackLabel);
    makeCol(ampDecaySlider, ampDecayLabel);
    makeCol(ampSustainSlider, ampSustainLabel);
    makeCol(ampReleaseSlider, ampReleaseLabel);
    makeCol(masterVolumeSlider, masterVolumeLabel);
}

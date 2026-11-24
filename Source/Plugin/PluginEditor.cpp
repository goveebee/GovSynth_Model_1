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

    auto makeSlider = [&](juce::Slider& s, const juce::String& labelText) {
        s.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        addAndMakeVisible(s);
    };

    makeSlider(osc1LevelSlider, "Osc 1 Level");
    osc1LevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc1Level, osc1LevelSlider);
    osc1LevelLabel.setText("Osc 1 Level", juce::dontSendNotification);
    addAndMakeVisible(osc1LevelLabel);

    makeSlider(osc2LevelSlider, "Osc 2 Level");
    osc2LevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc2Level, osc2LevelSlider);
    osc2LevelLabel.setText("Osc 2 Level", juce::dontSendNotification);
    addAndMakeVisible(osc2LevelLabel);

    makeSlider(osc1OctaveSlider, "Osc 1 Oct");
    osc1OctaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc1Octave, osc1OctaveSlider);
    osc1OctaveLabel.setText("Osc 1 Oct", juce::dontSendNotification);
    addAndMakeVisible(osc1OctaveLabel);

    makeSlider(osc1SemitoneSlider, "Osc 1 Semi");
    osc1SemitoneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc1Semitone, osc1SemitoneSlider);
    osc1SemitoneLabel.setText("Osc 1 Semi", juce::dontSendNotification);
    addAndMakeVisible(osc1SemitoneLabel);

    makeSlider(osc1DetuneSlider, "Osc 1 Detune");
    osc1DetuneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc1Detune, osc1DetuneSlider);
    osc1DetuneLabel.setText("Osc 1 Detune", juce::dontSendNotification);
    addAndMakeVisible(osc1DetuneLabel);

    makeSlider(osc2OctaveSlider, "Osc 2 Oct");
    osc2OctaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc2Octave, osc2OctaveSlider);
    osc2OctaveLabel.setText("Osc 2 Oct", juce::dontSendNotification);
    addAndMakeVisible(osc2OctaveLabel);

    makeSlider(osc2SemitoneSlider, "Osc 2 Semi");
    osc2SemitoneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc2Semitone, osc2SemitoneSlider);
    osc2SemitoneLabel.setText("Osc 2 Semi", juce::dontSendNotification);
    addAndMakeVisible(osc2SemitoneLabel);

    makeSlider(osc2DetuneSlider, "Osc 2 Detune");
    osc2DetuneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc2Detune, osc2DetuneSlider);
    osc2DetuneLabel.setText("Osc 2 Detune", juce::dontSendNotification);
    addAndMakeVisible(osc2DetuneLabel);

    makeSlider(ampAttackSlider, "Amp Attack");
    ampAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpAttack, ampAttackSlider);
    ampAttackLabel.setText("Amp Attack", juce::dontSendNotification);
    addAndMakeVisible(ampAttackLabel);

    makeSlider(ampDecaySlider, "Amp Decay");
    ampDecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpDecay, ampDecaySlider);
    ampDecayLabel.setText("Amp Decay", juce::dontSendNotification);
    addAndMakeVisible(ampDecayLabel);

    makeSlider(ampSustainSlider, "Amp Sustain");
    ampSustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpSustain, ampSustainSlider);
    ampSustainLabel.setText("Amp Sustain", juce::dontSendNotification);
    addAndMakeVisible(ampSustainLabel);

    makeSlider(ampReleaseSlider, "Amp Release");
    ampReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpRelease, ampReleaseSlider);
    ampReleaseLabel.setText("Amp Release", juce::dontSendNotification);
    addAndMakeVisible(ampReleaseLabel);

    makeSlider(masterVolumeSlider, "Master Vol");
    masterVolumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::MasterVolume, masterVolumeSlider);
    masterVolumeLabel.setText("Master Vol", juce::dontSendNotification);
    addAndMakeVisible(masterVolumeLabel);

    setSize(1000, 700);
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

    auto row = area.removeFromTop(180);
    auto makeCol = [&](auto& slider, auto& label) {
        auto col = row.removeFromLeft(110);
        auto labelArea = col.removeFromTop(20);
        label.setBounds(labelArea);
        slider.setBounds(col.reduced(0,20));
    };
    makeCol(osc1LevelSlider, osc1LevelLabel);
    makeCol(osc2LevelSlider, osc2LevelLabel);
    makeCol(osc1OctaveSlider, osc1OctaveLabel);
    makeCol(osc1SemitoneSlider, osc1SemitoneLabel);
    makeCol(osc1DetuneSlider, osc1DetuneLabel);
    makeCol(osc2OctaveSlider, osc2OctaveLabel);
    makeCol(osc2SemitoneSlider, osc2SemitoneLabel);
    makeCol(osc2DetuneSlider, osc2DetuneLabel);
    makeCol(ampAttackSlider, ampAttackLabel);
    makeCol(ampDecaySlider, ampDecayLabel);
    makeCol(ampSustainSlider, ampSustainLabel);
    makeCol(ampReleaseSlider, ampReleaseLabel);
    makeCol(masterVolumeSlider, masterVolumeLabel);
}

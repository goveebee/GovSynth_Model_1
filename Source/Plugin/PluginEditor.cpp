#include "PluginEditor.h"
#include "../Parameters/ParameterIDs.h"

GovSynthModel1AudioProcessorEditor::GovSynthModel1AudioProcessorEditor(GovSynthModel1AudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    auto& apvts = processor.getAPVTS();

    // Waveform radio buttons
    osc1WaveGroup.addButtonToGroup(&osc1SineButton);
    osc1WaveGroup.addButtonToGroup(&osc1TriangleButton);
    osc1WaveGroup.addButtonToGroup(&osc1SawButton);
    osc1SineButton.setButtonText("Sine");
    osc1TriangleButton.setButtonText("Triangle");
    osc1SawButton.setButtonText("Saw");
    addAndMakeVisible(osc1SineButton);
    addAndMakeVisible(osc1TriangleButton);
    addAndMakeVisible(osc1SawButton);
    osc1WaveLabel.setText("Osc 1 Wave", juce::dontSendNotification);
    addAndMakeVisible(osc1WaveLabel);

    osc2WaveGroup.addButtonToGroup(&osc2SineButton);
    osc2WaveGroup.addButtonToGroup(&osc2TriangleButton);
    osc2WaveGroup.addButtonToGroup(&osc2SawButton);
    osc2SineButton.setButtonText("Sine");
    osc2TriangleButton.setButtonText("Triangle");
    osc2SawButton.setButtonText("Saw");
    addAndMakeVisible(osc2SineButton);
    addAndMakeVisible(osc2TriangleButton);
    addAndMakeVisible(osc2SawButton);
    osc2WaveLabel.setText("Osc 2 Wave", juce::dontSendNotification);
    addAndMakeVisible(osc2WaveLabel);

    // Sync radio buttons with parameters
    auto syncWave = [&](juce::ToggleButton& b0, juce::ToggleButton& b1, juce::ToggleButton& b2, const juce::String& paramId) {
        auto* param = apvts.getParameter(paramId);
        int idx = static_cast<int>(param->getValue() * 2.0f); // 0..2
        if (idx < 0) idx = 0;
        if (idx > 2) idx = 2;
        b0.setToggleState(idx == 0, juce::dontSendNotification);
        b1.setToggleState(idx == 1, juce::dontSendNotification);
        b2.setToggleState(idx == 2, juce::dontSendNotification);
    };
    syncWave(osc1SineButton, osc1TriangleButton, osc1SawButton, Params::Osc1Wave);
    syncWave(osc2SineButton, osc2TriangleButton, osc2SawButton, Params::Osc2Wave);

    auto bindWave = [&](juce::ToggleButton& b0, juce::ToggleButton& b1, juce::ToggleButton& b2, const juce::String& paramId) {
        auto update = [&]() {
            int idx = b0.getToggleState() ? 0 : b1.getToggleState() ? 1 : 2;
            if (auto* p = apvts.getParameter(paramId))
                p->setValueNotifyingHost(idx / 2.0f);
        };
        b0.onClick = update;
        b1.onClick = update;
        b2.onClick = update;
    };
    bindWave(osc1SineButton, osc1TriangleButton, osc1SawButton, Params::Osc1Wave);
    bindWave(osc2SineButton, osc2TriangleButton, osc2SawButton, Params::Osc2Wave);

    apvts.addParameterListener(Params::Osc1Wave, this);
    apvts.addParameterListener(Params::Osc2Wave, this);

    // Sliders
    auto makeSlider = [&](juce::Slider& s) {
        s.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        addAndMakeVisible(s);
    };

    makeSlider(osc1LevelSlider);
    osc1LevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc1Level, osc1LevelSlider);
    osc1LevelLabel.setText("Osc 1 Level", juce::dontSendNotification);
    addAndMakeVisible(osc1LevelLabel);

    makeSlider(osc2LevelSlider);
    osc2LevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc2Level, osc2LevelSlider);
    osc2LevelLabel.setText("Osc 2 Level", juce::dontSendNotification);
    addAndMakeVisible(osc2LevelLabel);

    makeSlider(osc1OctaveSlider);
    osc1OctaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc1Octave, osc1OctaveSlider);
    osc1OctaveLabel.setText("Osc 1 Oct", juce::dontSendNotification);
    addAndMakeVisible(osc1OctaveLabel);

    makeSlider(osc1SemitoneSlider);
    osc1SemitoneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc1Semitone, osc1SemitoneSlider);
    osc1SemitoneLabel.setText("Osc 1 Semi", juce::dontSendNotification);
    addAndMakeVisible(osc1SemitoneLabel);

    makeSlider(osc1DetuneSlider);
    osc1DetuneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc1Detune, osc1DetuneSlider);
    osc1DetuneLabel.setText("Osc 1 Detune", juce::dontSendNotification);
    addAndMakeVisible(osc1DetuneLabel);

    makeSlider(osc2OctaveSlider);
    osc2OctaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc2Octave, osc2OctaveSlider);
    osc2OctaveLabel.setText("Osc 2 Oct", juce::dontSendNotification);
    addAndMakeVisible(osc2OctaveLabel);

    makeSlider(osc2SemitoneSlider);
    osc2SemitoneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc2Semitone, osc2SemitoneSlider);
    osc2SemitoneLabel.setText("Osc 2 Semi", juce::dontSendNotification);
    addAndMakeVisible(osc2SemitoneLabel);

    makeSlider(osc2DetuneSlider);
    osc2DetuneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::Osc2Detune, osc2DetuneSlider);
    osc2DetuneLabel.setText("Osc 2 Detune", juce::dontSendNotification);
    addAndMakeVisible(osc2DetuneLabel);

    makeSlider(ampAttackSlider);
    ampAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpAttack, ampAttackSlider);
    ampAttackLabel.setText("Amp Attack", juce::dontSendNotification);
    addAndMakeVisible(ampAttackLabel);

    makeSlider(ampDecaySlider);
    ampDecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpDecay, ampDecaySlider);
    ampDecayLabel.setText("Amp Decay", juce::dontSendNotification);
    addAndMakeVisible(ampDecayLabel);

    makeSlider(ampSustainSlider);
    ampSustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpSustain, ampSustainSlider);
    ampSustainLabel.setText("Amp Sustain", juce::dontSendNotification);
    addAndMakeVisible(ampSustainLabel);

    makeSlider(ampReleaseSlider);
    ampReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::AmpRelease, ampReleaseSlider);
    ampReleaseLabel.setText("Amp Release", juce::dontSendNotification);
    addAndMakeVisible(ampReleaseLabel);

    makeSlider(masterVolumeSlider);
    masterVolumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, Params::MasterVolume, masterVolumeSlider);
    masterVolumeLabel.setText("Master Vol", juce::dontSendNotification);
    addAndMakeVisible(masterVolumeLabel);

    setSize(1000, 700);
}

GovSynthModel1AudioProcessorEditor::~GovSynthModel1AudioProcessorEditor() 
{
    auto& apvts = processor.getAPVTS();
    apvts.removeParameterListener(Params::Osc1Wave, this);
    apvts.removeParameterListener(Params::Osc2Wave, this);
}

void GovSynthModel1AudioProcessorEditor::parameterChanged(const juce::String& parameterID, float newValue)
{
    int idx = static_cast<int>(newValue * 2.0f);
    if (idx < 0) idx = 0;
    if (idx > 2) idx = 2;
    if (parameterID == Params::Osc1Wave)
    {
        osc1SineButton.setToggleState(idx == 0, juce::dontSendNotification);
        osc1TriangleButton.setToggleState(idx == 1, juce::dontSendNotification);
        osc1SawButton.setToggleState(idx == 2, juce::dontSendNotification);
    }
    else if (parameterID == Params::Osc2Wave)
    {
        osc2SineButton.setToggleState(idx == 0, juce::dontSendNotification);
        osc2TriangleButton.setToggleState(idx == 1, juce::dontSendNotification);
        osc2SawButton.setToggleState(idx == 2, juce::dontSendNotification);
    }
}

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

    // Waveform radio buttons
    auto waveArea = area.removeFromTop(80);
    auto osc1Area = waveArea.removeFromLeft(waveArea.getWidth() / 2);
    osc1WaveLabel.setBounds(osc1Area.removeFromTop(20));
    auto btnArea1 = osc1Area.reduced(0, 0);
    int btnW = btnArea1.getWidth() / 3;
    osc1SineButton.setBounds(btnArea1.removeFromLeft(btnW).reduced(5));
    osc1TriangleButton.setBounds(btnArea1.removeFromLeft(btnW).reduced(5));
    osc1SawButton.setBounds(btnArea1.removeFromLeft(btnW).reduced(5));

    auto osc2Area = waveArea;
    osc2WaveLabel.setBounds(osc2Area.removeFromTop(20));
    auto btnArea2 = osc2Area.reduced(0, 0);
    int btnW2 = btnArea2.getWidth() / 3;
    osc2SineButton.setBounds(btnArea2.removeFromLeft(btnW2).reduced(5));
    osc2TriangleButton.setBounds(btnArea2.removeFromLeft(btnW2).reduced(5));
    osc2SawButton.setBounds(btnArea2.removeFromLeft(btnW2).reduced(5));

    auto row1 = area.removeFromTop(180);
    auto makeCol = [&](auto& slider, auto& label) {
        auto col = row1.removeFromLeft(110);
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

    auto row2 = area.removeFromTop(180);
    auto makeCol2 = [&](auto& slider, auto& label) {
        auto col = row2.removeFromLeft(110);
        auto labelArea = col.removeFromTop(20);
        label.setBounds(labelArea);
        slider.setBounds(col.reduced(0,20));
    };
    makeCol2(ampAttackSlider, ampAttackLabel);
    makeCol2(ampDecaySlider, ampDecayLabel);
    makeCol2(ampSustainSlider, ampSustainLabel);
    makeCol2(ampReleaseSlider, ampReleaseLabel);
    makeCol2(masterVolumeSlider, masterVolumeLabel);
}

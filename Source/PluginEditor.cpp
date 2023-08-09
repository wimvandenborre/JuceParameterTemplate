//#include "PluginProcessor.h"
#include "PluginEditor.h"

PolynatorAudioProcessorEditor::PolynatorAudioProcessorEditor(
    PolynatorAudioProcessor& p)
    : AudioProcessorEditor(&p), aP (p), singlePanel(aP.parameters.newPanelParams), leftPanel(params)

{

  addAndMakeVisible(leftPanel);
  addAndMakeVisible(singlePanel);
    addAndMakeVisible(allLFOs);

    setSize(1200, 800);
    setResizable(true, true);
 
}

void PolynatorAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PolynatorAudioProcessorEditor::resized()
{
    // Left Panel
    juce::FlexBox leftFlexBox;
    leftFlexBox.flexDirection = juce::FlexBox::Direction::column; // Vertical layout

    // Assuming leftTopPanel and leftBottomPanel are the actual names of your components
    leftFlexBox.items.add({(float) getWidth() / 4.0f, (float) getHeight() / 2.0f, leftPanel});
    leftFlexBox.items.add({(float) getWidth() / 4.0f, (float) getHeight() / 2.0f, singlePanel});
    leftFlexBox.performLayout(juce::Rectangle<float>(0, 0, getWidth() / 2.0f, getHeight()));

    // Right Panel
    juce::FlexBox rightFlexBox;
    
    // Assuming rightPanel is the actual name of your component
    rightFlexBox.items.add({(float) getWidth() / 2.0f, (float) getHeight(), allLFOs});
    rightFlexBox.performLayout(juce::Rectangle<float>(getWidth() / 2.0f, 0, getWidth() / 2.0f, getHeight()));
}





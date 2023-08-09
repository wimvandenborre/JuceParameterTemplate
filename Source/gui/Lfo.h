/*
  ==============================================================================

    Lfo.h
    Created: 7 Aug 2023 3:39:36pm
    Author:  Wim Van den Borre

  ==============================================================================
*/

#pragma once

#include "..//PluginProcessor.h"
#include "../params/LfoParams.h"

struct SingleLFOVisualizer : public juce::Component
{
  
  // hier kan je de naam "Gain" mss ook van de parameters nemen?
  SingleLFOVisualizer(LFOParameter& paramsToUse)
    : gainSlider(paramsToUse.gain->name), speedSlider(paramsToUse.speed->name)
  {
    // Configure and add the gain slider
    
    gainSlider.setValue(*paramsToUse.gain);
    gainAttachment = std::make_unique<juce::SliderParameterAttachment>(*paramsToUse.gain, gainSlider);
    gainSlider.onValueChange = [this, &paramsToUse] { *paramsToUse.gain = gainSlider.getValue(); };
    addAndMakeVisible(gainSlider);
    gainLabel.setText(paramsToUse.gain->name, juce::dontSendNotification);
    addAndMakeVisible(gainLabel);

    speedSlider.setValue(*paramsToUse.speed);
    speedAttachment = std::make_unique<juce::SliderParameterAttachment>(*paramsToUse.speed, speedSlider);
    speedSlider.onValueChange = [this, &paramsToUse] { *paramsToUse.speed = speedSlider.getValue(); };
    addAndMakeVisible(speedSlider);
    speedLabel.setText(paramsToUse.speed->name, juce::dontSendNotification);
    addAndMakeVisible(speedLabel);

    
  }

  void paint (juce::Graphics& g) override
  {
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1); 
  }
  void resized() override
  {
    juce::FlexBox flexBox;

    // Configure the FlexBox layout for sliders
    flexBox.flexDirection = juce::FlexBox::Direction::column; // Vertical layout

    juce::FlexItem gainItem(gainSlider);
    gainItem.flexGrow = 1.0f;
    gainItem.minWidth = 100.0f;
    gainItem.minHeight = 30.0f;
    flexBox.items.add(std::move(gainItem));

    juce::FlexItem speedItem(speedSlider);
    speedItem.flexGrow = 1.0f;
    speedItem.minWidth = 100.0f;
    speedItem.minHeight = 30.0f;
    flexBox.items.add(std::move(speedItem));

    auto bounds = getLocalBounds();
    bounds.setWidth(std::max(bounds.getWidth(), 200));
    bounds.setHeight(std::max(bounds.getHeight(), 200));
    flexBox.performLayout(bounds);

    // Position the labels
    int labelHeight = static_cast<int>(gainSlider.getHeight() * 0.1);

      // Set the label bounds relative to the slider positions
      // Position them 10% above the sliders' height
      gainLabel.setBounds(gainSlider.getX(), gainSlider.getY() + (labelHeight / 0.8) , gainSlider.getWidth(), labelHeight);
      speedLabel.setBounds(speedSlider.getX(), speedSlider.getY() + (labelHeight / 0.8), speedSlider.getWidth(), labelHeight);
  }


private:
  juce::Slider gainSlider, speedSlider;
  juce::Label  gainLabel, speedLabel;
  std::unique_ptr<juce::SliderParameterAttachment> gainAttachment, speedAttachment;

};

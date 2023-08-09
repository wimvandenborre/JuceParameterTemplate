/*
  ==============================================================================

    Lfos.h
    Created: 7 Aug 2023 3:16:41pm
    Author:  Wim Van den Borre

  ==============================================================================
*/

#pragma once

#include "../PluginProcessor.h"
#include "../params/LfoParams.h"
#include "Lfo.h"

template<typename T>
using OwnedVector = std::vector<std::unique_ptr<T>>;


struct AllLFOVisualizer : public juce::Component
{
  AllLFOVisualizer(LFOs& lfos)
  {
    for (auto& lfo : lfos)
    {
      auto newLFO = std::make_unique<SingleLFOVisualizer>(lfo);

      addAndMakeVisible(*newLFO);
      singleLFOLabel.setText("LFO" + juce::String((lfos.size()+1)), juce::dontSendNotification);
      addAndMakeVisible(singleLFOLabel);
      visualizers.emplace_back(std::move(newLFO));
    }
  }

  void resized() override {
    
    juce::FlexBox flexBox;
      
      // Configure the FlexBox layout
      flexBox.flexWrap = juce::FlexBox::Wrap::wrap;
      flexBox.flexDirection = juce::FlexBox::Direction::row;
      flexBox.alignContent = juce::FlexBox::AlignContent::stretch;

      // Define the size of each visualizer
      float widthPerVisualizer = static_cast<float>(getWidth()) / 2.0f; // Two visualizers per row
      float heightPerVisualizer = static_cast<float>(getHeight()) / (visualizers.size() / 2.0f); // Assume an even number of visualizers

      // Add each visualizer as a flex item
      for (auto& visualizer : visualizers)
      {
        juce::FlexItem item(*visualizer);
        item.width = widthPerVisualizer;
        item.height = heightPerVisualizer;
        flexBox.items.add(std::move(item));
      }

      // Perform the layout
      flexBox.performLayout(getLocalBounds());
    
  } 
  
  
  OwnedVector<SingleLFOVisualizer> visualizers;
  juce::Label singleLFOLabel;
};

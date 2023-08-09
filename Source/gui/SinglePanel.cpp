/*
  ==============================================================================

    NewPanel.cpp
    Created: 25 Jul 2023 5:22:51pm
    Author:  Wim Van den Borre

  ==============================================================================
*/

#include "SinglePanel.h"

//==============================================================================
SinglePanel::SinglePanel(SinglePanelParams& newPanelParamsToUse):
newPanelParams(newPanelParamsToUse)

{
  
  
  for (int i = 0; i < sliders.size(); ++i)
  {
      sliders[i] = &addComponent<juce::Slider>();
      addAndMakeVisible(sliders[i]);
      attachments[i] = std::make_unique<juce::SliderParameterAttachment>(*newPanelParams.params[i], *sliders[i]);
    labels[i].setText(newPanelParams.params[i]->getName(10), juce::dontSendNotification);
        labels[i].attachToComponent(sliders[i], false);
    
  }
  

}

void SinglePanel::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

}

void SinglePanel::resized()
{

  juce::FlexBox fb;
      fb.flexWrap = juce::FlexBox::Wrap::wrap;
      fb.justifyContent = juce::FlexBox::JustifyContent::center;
      fb.alignContent = juce::FlexBox::AlignContent::center;

      for (auto& s : sliders)
        fb.items.add (juce::FlexItem (*s) .withMinWidth (100.0f).withMinHeight (70.0f) .withWidth(getLocalBounds().getWidth() / 2) .withHeight(getLocalBounds().getWidth() / 4));

      fb.performLayout (getLocalBounds());

}

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceHeader.h"

/*AnimatedComponent::AnimatedComponent() {
	knobImage = bg;
	prevImage = bg;
	bgAlpha = 1.f;
}*/

void AnimatedComponent::paint(juce::Graphics &g)
{
	DBG("PAINTING");
	//prevImage.multiplyAllAlphas(1-bgAlpha);
	//currentImage.multiplyAllAlphas(bgAlpha);
	//knobImage.multiplyAllAlphas(1-bgAlpha);
	//bg.multiplyAllAlphas(bgAlpha);

	//g.drawImageAt(prevImage, 0, 0);
	//g.drawImageAt(currentImage, 0, 0);
	g.drawImageAt(bg, 0, 0);
	g.drawImageAt(knobImage, 0, 0);
}

//bgAlphaMultiple should be 1
//going into a knob, BG fade out
void AnimatedComponent::mouseExit(const juce::MouseEvent &e)  
{
	Point<int> p = e.getPosition();
	int x = p.getX();
	int y = p.getY(); 
	DBG("blaExit");

	//new DelayedOneShotLambda(refreshRate, [this]() {this->bgfadeOut(bgMul); });

	if (y > 256 && y < 360)setKnobImage(x);
	//prevImage = crrentImage;
	repaint();
	
}


/*
@param m - amountToMultiplyBy
fading in, m > 1
*/
/*void AnimatedComponent::bgfadeIn(float m) {
	bgMul = m;
	bgAlpha = bgAlpha * bgMul;
	if (bgAlpha < 0.9f) {
		m += 0.1;
		new DelayedOneShotLambda(refreshRate, [this, m]() {this->bgfadeIn(m); });
	}
	repaint();
}


//bgAlphaMultiple should be 0
//going to bg, bg fade in
//current image fade in
*/void AnimatedComponent::mouseEnter(const juce::MouseEvent &e)
{
	knobImage = bg;
	//new DelayedOneShotLambda(refreshRate, [this]() {this->bgfadeIn(bgMul); });
	repaint();
	DBG("blaEnering-------");
}

/*
@param m - amountToMultiplyBy
fading out, m < 1

void AnimatedComponent::bgfadeOut(float m) {
	bgMul = m;
	bgAlpha = bgAlpha*bgMul;
	if (bgAlpha > 0.1f) {
		m -= 0.1;
		new DelayedOneShotLambda(refreshRate, [this, m]() {this->bgfadeIn(m); });
	}

	repaint();
}
*/
void AnimatedComponent::setKnobImage(int x) {
	if (x >= 58 && x <= 137) {
		knobImage = k7;
	}
	else if (x >= 158 && x <= 237) {
		knobImage = k8;
	}
	else if (x >= 258 && x <= 337) {
		knobImage = k3;
	}
	else if (x >= 358 && x <= 437) {
		knobImage = k4;
	}
	else if (x >= 458 && x <= 537) {
		knobImage = k5;
	}
	else if (x >= 558 && x <= 637) {
		knobImage = k6;
	}

}


//==============================================================================
TokyoRe_verbAudioProcessorEditor::TokyoRe_verbAudioProcessorEditor (TokyoRe_verbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

	addAndMakeVisible(Comp);
	//addAndMakeVisible(Comp1);
    setOpaque(true);
    setSize (700, 394);
    //knob one
    filterCutoffDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterCutoffDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterCutoffDial.setSize(80, 80);
    
    // dont change these two
    filterCutoffDial.addListener(this);
    addAndMakeVisible(filterCutoffDial);
    
	//knob two
    filterResDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterResDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterResDial.setSize(80, 80);
    
    // dont change these two
    filterResDial.addListener(this);
    addAndMakeVisible(filterResDial);
    
    // dont change these two
    filterCutoffValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "cutoff", filterCutoffDial);
    filterResValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "resonance", filterResDial);
    
    filterCutoffDial.setLookAndFeel(&otherLookAndFeel);
    filterResDial.setLookAndFeel(&otherLookAndFeel);
    
    //addAndMakeVisible(filterCutoffLabel);
    mixLabel.attachToComponent(&filterCutoffDial, false);
    
    addAndMakeVisible(filterResLabel);
    filterResLabel.attachToComponent(&filterResDial, false);
    
	//knob 3
    reverbMixDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    reverbMixDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbMixDial.setSize(80, 80);
    
    // dont change these two
    reverbMixDial.addListener(this);
    addAndMakeVisible(reverbMixDial);
    
	//knob 4
    reverbRoomDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    reverbRoomDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbRoomDial.setSize(80, 80);
    
    // dont change these two
    reverbRoomDial.addListener(this);
    addAndMakeVisible(reverbRoomDial);
    //knob 5
    reverbDampDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    reverbDampDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbDampDial.setSize(80, 80);

    // dont change these two
    reverbDampDial.addListener(this);
    addAndMakeVisible(reverbDampDial);
    //knob 6
    reverbWidthDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	reverbWidthDial.setSize(80, 80);
	reverbWidthDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    
	// dont change these two
    reverbWidthDial.addListener(this);
    addAndMakeVisible(reverbWidthDial);
    
    //reverbDryValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "dry", reverbDryDial);
    //reverbWetValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "wet", reverbWetDial);
    reverbMixValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "mix", reverbMixDial);
    reverbRoomValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "room", reverbRoomDial);
    reverbDampValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "damp", reverbDampDial);
    reverbWidthValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "width", reverbWidthDial);


	//////////////////////////HERE
    reverbMixDial.setLookAndFeel(&otherLookAndFeel);
    reverbRoomDial.setLookAndFeel(&otherLookAndFeel);
    reverbDampDial.setLookAndFeel(&otherLookAndFeel);
    reverbWidthDial.setLookAndFeel(&otherLookAndFeel);
    
    addAndMakeVisible(reverbMixLabel);
    reverbMixLabel.attachToComponent(&reverbMixDial, false);
    
    addAndMakeVisible(reverbRoomLabel);
    reverbRoomLabel.attachToComponent(&reverbRoomDial, false);
    
    addAndMakeVisible(reverbDampLabel);
    reverbDampLabel.attachToComponent(&reverbDampDial, false);
    
    addAndMakeVisible(reverbWidthLabel);
    reverbWidthLabel.attachToComponent(&reverbWidthDial, false);
    

    
}

TokyoRe_verbAudioProcessorEditor::~TokyoRe_verbAudioProcessorEditor()
{
}

//==============================================================================
void TokyoRe_verbAudioProcessorEditor::paint (Graphics& g)
{
    // (Our plugin background is opaque, so we must completely fill the background with a solid colour or image)
    
    Image background = ImageCache::getFromMemory(BinaryData::Animation1_png, BinaryData::Animation1_pngSize);
	//MYpaint(g, background);
	g.drawImageAt(background, 0, 0);
 
}

void TokyoRe_verbAudioProcessorEditor::MYpaint(Graphics& g, Image i) {
	g.drawImageAt(i, 0, 0);
}

void TokyoRe_verbAudioProcessorEditor::resized()
{
	//area where you progam the position of the sliders 

	filterCutoffDial.setBounds(53, getHeight() - 113, 80, 80);
	filterResDial.setBounds(158, getHeight() - 113, 80, 80);
  
	reverbWidthDial.setBounds(258, getHeight() - 113, 80, 80);
    reverbRoomDial.setBounds(358, getHeight()-113, 80, 80);
    reverbDampDial.setBounds(458, getHeight()-113, 80, 80);
	reverbMixDial.setBounds(568, getHeight() - 113, 80, 80);

	Comp.setBounds(getLocalBounds());
	//Comp1.setBounds(getLocalBounds());
	
}

void TokyoRe_verbAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &mixSlider)
    {
        // dont change any of this void function
        // get the value on the current slider, pass to audio processor
        processor.mixLevel.setTargetValue(mixSlider.getValue());
        
    }
    
    /*if (slider == &filterCutoffDial)
     {
     
     // get the value on the current slider, pass to audio processor
     processor.freqLevel.setTargetValue(filterCutoffDial.getValue());
     
     }
     
     if (slider == &filterResDial)
     {
     
     // get the value on the current slider, pass to audio processor
     processor.resLevel.setTargetValue(filterResDial.getValue());
     
     }*/
    
}

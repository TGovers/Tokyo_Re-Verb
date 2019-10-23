/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/**
*/


class AnimatedComponent : public Component
{
	public:
		void paint(Graphics&) override;

		Image bg = ImageCache::getFromMemory(BinaryData::Animation1_png, BinaryData::Animation1_pngSize);

		Image k3 = ImageCache::getFromMemory(BinaryData::Animation2_png, BinaryData::Animation2_pngSize);

		Image k4 = ImageCache::getFromMemory(BinaryData::Animation3_png, BinaryData::Animation3_pngSize);
	
		Image k5 = ImageCache::getFromMemory(BinaryData::Animation4_png, BinaryData::Animation4_pngSize);

		Image k6 = ImageCache::getFromMemory(BinaryData::Animation5_png, BinaryData::Animation5_pngSize);

		Image k7 = ImageCache::getFromMemory(BinaryData::Animation6_png, BinaryData::Animation6_pngSize);

		Image k8 = ImageCache::getFromMemory(BinaryData::Animation7_png, BinaryData::Animation7_pngSize);
	
	
		Image knobImage;
		Image prevImage;
		void mouseEnter(const MouseEvent& e) override; 
		void mouseExit(const MouseEvent& e) override;
		void setKnobImage(int x);

		/*void bgfadeIn(float m);
		void bgfadeOut(float m);
		float bgAlpha;
		float bgMul;
		float refreshRate = 1000.f/2.f;
		*/
		//AnimatedComponent();
	
	
};

/*class DelayedOneShotLambda : public Timer {
	public:
		//Constructor, need an int and a FUNCTINO
		DelayedOneShotLambda(int ms, std::function<void()> fn) :
			func(fn)
		{
			startTimer(ms);
		}
		//destrucor
		~DelayedOneShotLambda(){ stopTimer(); }

		void timerCallback() override {
			auto f = func;
			delete this; //timer delete itself, calls destructor
			f();
		}
	private:
		std::function<void()>func;
};
*/
class OtherLookAndFeel : public LookAndFeel_V4
{
public:
	
	Image img1 = ImageCache::getFromMemory(BinaryData::PurpleAnimate_png, BinaryData::PurpleAnimate_pngSize);
	
	void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override
	{
		if (img1.isValid())
		{
			const double rotation = (slider.getValue()
				- slider.getMinimum())
				/ (slider.getMaximum()
					- slider.getMinimum());

			const int frames = img1.getHeight() / img1.getWidth();
			const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
			const float radius = jmin(width / 2.0f, height / 2.0f);
			const float centerX = x + width * 0.5f;
			const float centerY = y + height * 0.5f;
			const float rx = centerX - radius - 1.0f;
			const float ry = centerY - radius;

			g.drawImage(img1,
				(int)rx,
				(int)ry,
				2 * (int)radius,
				2 * (int)radius,
				0,
				frameId*img1.getWidth(),
				img1.getWidth(),
				img1.getWidth());
		}
		
		
		
	}
		
};

	class TokyoRe_verbAudioProcessorEditor : public AudioProcessorEditor, Slider::Listener
	{
	public:
		TokyoRe_verbAudioProcessorEditor(TokyoRe_verbAudioProcessor&);
		~TokyoRe_verbAudioProcessorEditor();

		//==============================================================================
		void paint(Graphics&) override;
		void resized() override;
		void MYpaint(Graphics&, Image i);
		void rotateImage();


		
	private:
		AnimatedComponent Comp;
		//AnimatedComponent Comp1;

		juce::Image backGround;
		

		OtherLookAndFeel otherLookAndFeel;

		Slider filterCutoffDial;
		Slider filterResDial;
		ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
		ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterResValue;
		//std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
		//std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterResValue;


		Label filterCutoffLabel;
		Label filterResLabel;

		//Slider reverbDryDial;
		//Slider reverbWetDial;
		Slider reverbMixDial; //3
		Slider reverbRoomDial; //4
		Slider reverbDampDial; //5
		Slider reverbWidthDial; //6

		ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> reverbMixValue;
		ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> reverbRoomValue;
		ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> reverbDampValue;
		ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> reverbWidthValue;

		//Label reverbDryLabel;
		//Label reverbWetLabel;
		Label reverbMixLabel;
		Label reverbRoomLabel;
		Label reverbDampLabel;
		Label reverbWidthLabel;



		Slider mixSlider;
		Label mixLabel;

		std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

		void sliderValueChanged(Slider * slider) override;

		// This reference is provided as a quick way for your editor to
		// access the processor object that created it.
		TokyoRe_verbAudioProcessor& processor;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TokyoRe_verbAudioProcessorEditor);
	};

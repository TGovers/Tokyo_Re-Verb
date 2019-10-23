# TOKYO RE:VERB

**DO YOU LIKE ANIME? DO YOU LIKE MEMES? DO YOU OCCASSIONALLY PARTAKE IN AUDIO CREATION WHERE YOU DESPERATELY NEED AN ANIME-THEMED PLUGIN???** 

**DON’T LIE MY FELLOW ~~WEEBS~~ ANIME ENTHUSIASTS, WE KNOW YOU DO AND _BOY OH BOY_ DO WE HAVE THE PRODUCT FOR YOU!**

![alt text](https://i.imgur.com/T8RQQ2r.png "Tokyo Ghoul")

### /// INTRODUCING ///
### /// TOKYO RE:VERB ///

![alt text](https://i.imgur.com/iANcxUj.png "Tokyo Re:Verb")

## Table of Contents  
[Tokyo Re:Verb Demostration Video](#tokyoreverbdemonstrationvideo)

[Tokyo Re:Verb TLDR](#tokyoreverbtldr)

[Installation Guide](#installation-guide)

[Tokyo Re:Verb In-depth](#tokyo-reverb-in-depth)

[Contributing](#contributing)

[License](#license)

<a name="tokyoreverbdemonstrationvideo"/>
<a name="tokyoreverbtldr"/>
<a name="installationguide"/>
<a name="tokyoreverbindepth"/>

## Tokyo Re:Verb Demonstration Video

### Omoide (思い出) Demonstration

[![IMAGE ALT TEXT HERE](https://i.imgur.com/GYrOufe.png)](https://vimeo.com/367559235)

## Tokyo Re:Verb TLDR 

Tokyo Re:Verb is a part of a greater plugin suite by Studio Nani called 

### Omoide (思い出)

Check out our other awesome plugins through the following links!

- https://github.com/TGovers/Angry_Ayaya

- https://github.com/TGovers/Initial_Delay

- https://github.com/TGovers/Initial_Demon

Tokyo Re:Verb is a simple and intuitive VST plugin with an anime aesthetic. It utilises a 2-parameter IRR filter and a 4-parameter Reverb. Tokyo Re:Verb was designed for use with a multitude of different instruments in mind, such as
* Synths
* Baritone Electric Guitars
* 7/8 String Electric Guitars
* Bass Guitars
* And anything else you want to put through it, it's completely up to you!

Tokyo Re:Verb has full automation and save state capabilities for easy use within your favourite DAW! Tokyo Re:Verb features installers for both Windows and Mac systems, as well as access to the JUCE project itself (please refer to license)

Tokyo Re:Verb was inspired by the manga/anime "Tokyo Ghoul/Tokyo Ghoul Re", click the link to the Youtube video below to **_witness the majesty that is Tokyo Ghoul_** 

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/7aMOurgDB-o/0.jpg)](https://www.youtube.com/watch?v=7aMOurgDB-o)

We created the plugin with the mindset of making a great-sounding plugin first and foremost, with a visually-appealing aesthetic following that. 

We wanted to release Tokyo Re:Verb for free, but if you wish to donate it would be hugely appreciated! We are two university students from Wellington, New Zealand in our final year of a Bachelor of Commercial Music at Massey University. We will always keep this plug-in free, but feel free to throw us a nickel or two via the Paypal button below if you enjoy our work!


[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=YP29EFC3QEU4L)

Additionally, if you want to get in contact with us please refer to our personal websites:

- https://tgovers1998.wixsite.com/taylorgovers

- https://ethanzacharypunter.wixsite.com/studionani

We'd love to hear from you about our plug-in, whether it be recommendations, issues or just a nice message to us!

From the team behind **_Tokyo Re:Verb_**, we really hope that you enjoy our plugin and make some awesome tunes with it!
Thank you!

-- Studio Nani --

## Installation Guide 

For Mac users, we recommend cloning/downloading the repository to your computer and installing the plugin through the easy-to-use DMG installer. Simply mount the disk image/DMG (TokyoReVerb_MAC.dmg) and then open the .pkg file found inside. Follow the instructions within the .pkg installer and you'll be good to go!

For Windows users, we recommend downloading the repository to your computer and installing the plugin through the easy-to-use EXE installer (TokyoReVerb_WINDOWS.exe)

If using the JUCE project directly, please refer to a youtube guide or the JUCE website if you are unsure on how to begin! We recommend this [video by Miskat Music](https://www.youtube.com/watch?v=rGzSSNjbXlA "https://www.youtube.com/watch?v=rGzSSNjbXlA") or the [JUCE Tutorials Page](https://juce.com/learn/tutorials "https://juce.com/learn/tutorials").

Another great source of help we can recommend is [The Audio Programmer Youtube Page](https://www.youtube.com/channel/UCpKb02FsH4WH4X_2xhIoJ1A "https://www.youtube.com/channel/UCpKb02FsH4WH4X_2xhIoJ1A") 

## Tokyo Re:Verb In-depth 

Tokyo Re:Verb was primarily built with [Projucer](https://juce.com/ "https://juce.com/")/[XCode](https://developer.apple.com/xcode/ "https://developer.apple.com/xcode/") as a plugin suited specifically to those who maybe don’t know their way round plugins, but are wanting something cool and intuitive to add that extra “oomph!” to their work.

It utilises an always-active low-pass IIR filter and an optional reverb. IIR filter stands for an Infinite Impulse Response filter, which is unique with how the decay never really reaches zero (to put it simply!). We choose to use this as we personally thought it sounded the best out of the different kinds of filters that we tested. 

The IIR filter has two parameters that you can change; the frequency Cutoff and the Q-Factor. 
* The Cuttoff knob changes the maximum frequency that the filter will let through (as a low-pass filter)
* The Q-Factor knob changes the resonance or **Q** of the filter

The Reverb feature has four parameters that you can change; Width, Room Size, Damp and Mix 
* The Width knob changes the width of the stereo field
* The Room Size knob changes how 'roomy' you want the reverb to sound 
* The Damp knob changes the damping of the reverb, which can help round of the sound and make it warmer (lower high frequencies)
* The Mix knob changes the wet/dry mix of the reverb and original audio

If you want to essentially “turn off” the reverb, just turn the reverb Mix knob to its lowest value.

## Contributing and Inspiration

Currently Tokyo Re:Verb is not open to contribution, but this could change in the future!

Taylor Govers: Processor Editor, Repository/README/License Management, Assistant GUI Editor

Ethan Punter: GUI Editor, GUI Repository Management, Photoshop Editor

For this project, we had inspiration and were helped with code by this youtuber. They make awesome work so please check them out and support them!

[The Audio Programmer](https://www.youtube.com/channel/UCpKb02FsH4WH4X_2xhIoJ1A "https://www.youtube.com/channel/UCpKb02FsH4WH4X_2xhIoJ1A")

And of course, huge inspiration from the anime behind the meme [Tokyo Ghoul](https://myanimelist.net/anime/22319/Tokyo_Ghoul "https://myanimelist.net/anime/22319/Tokyo_Ghoul"), the creator [Sui Ishida](https://myanimelist.net/people/15753/Sui_Ishida "https://myanimelist.net/people/15753/Sui_Ishida") and the studio that created it [Studio Pierrot](https://myanimelist.net/anime/producer/1/Studio_Pierrot "https://myanimelist.net/anime/producer/1/Studio_Pierrot")  

## License

[GNU GPLv3](https://github.com/TGovers/Tokyo_Re-Verb/blob/master/LICENSE.txt)

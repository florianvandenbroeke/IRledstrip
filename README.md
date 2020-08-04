# IRledstrip

This Arduino code is used to control a WS2812 style ledstrip with an IR remote control. The code is written for a remote control with 16 static color buttons, 4 animation buttons, dimmer and on/off buttons.

## Animations

The animations are largely based on the "Button Cycler" example sketch, adapted in such a way they can be interrupted while going on.
The extra sketches are used to test and debug the animations on their own.

- Random: this animation sets a random pixel to a random predefined color
- Colorwipe: this animation fills the ledstrip pixel by pixel with a random color
- Fade: regular fading of the entire strip through all colors
- Rainbow: shifts the rainbow colors over the strip

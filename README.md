
# DaisySeed Arcade Pedal

An audio effect unit built using the Daisy Seed Microcontoller that uses an arcade joystick and buttons to control the effects.

This project reuses code from my [Daisy Seed MultiFX pedal project](https://github.com/bbw1081/DaisySeed-MultiFXPedal)

## PEDAL FUNCTIONALITY

This is a digital auido effect unit primarily ustilizing the DaisySP library for audio effects. The unit contains a 2-axis analog joystick, 2 buttons, an OLED screen (optional), and analog audio I/O.

The unit functions by having 1 effect selected at a time (for example chorus). The name of the effect is displayed on the OLED display, and the x and y axes of joystick each control a parameter of the active effect. The buttons change the active effect.

## TO PROGRAM MICROCONTROLLER

1. Clone the GitHub repository

2. In the terminal, move into the root directory of the project

3. Run the command `git submodule update --init --recursive`

4. Flash the [daisy bootloader](https://flash.daisy.audio/) onto the microcontroller

5. On the microcontroller, rapidly press the button reset twice and boot once

6. On VSCode, in the command pallete run `task build_and_program_dfu`. Alternatively, run the follwing string of commands: `make clean; make build; make program-dfu`

## PARTS LIST

[Daisy Seed Microcontroller](https://daisy.audio/products/seed3)

[Analog Joystick](https://www.adafruit.com/product/3102)

[Arcade Buttons](https://www.adafruit.com/product/3487)

[OLED Screen](https://www.amazon.com/dp/B0FSRQG23K?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1) (not necessary for functionality)

[1/4" Audio Jacks](https://stompboxparts.com/audio-jacks/1-4-ts-enclosed-jack-panel-mount-skinny-lug/) (can use any, these are just the ones I bought):

3D model for enclosure coming soon TM

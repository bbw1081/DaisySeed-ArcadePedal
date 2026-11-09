# DaisySeed-ArcadePedal
A guitar effects unit build using the Daisy Seed Microcontoller that uses and arcade joystick and buttons to control the effects.

This project reuses code from my Daisy Seed MultiFX pedal project: https://github.com/bbw1081/DaisySeed-MultiFXPedal

## TO USE PEDAL

### Downloading Dependencies

In the root of the project run the command `git submodule update --init --recursive`

### Flashing the Microcontroller

Flash the daisy bootloader onto the microcontroller: https://flash.daisy.audio/

On the microcontroller, rapidly press the buttons reset twice and boot once

On VSCode, in the command pallete run `task build_and_program_dfu`. Or you can run the follwing string of commands:
`make clean; make build; make program-dfu`

## PARTS LIST

Daisy Seed Microcontroller:
https://daisy.audio/products/seed3

Analog Joystick:
https://www.adafruit.com/product/3102

Arcade Buttons:
https://www.adafruit.com/product/3487

OLED Screen (not necessary for functionality):
https://www.amazon.com/dp/B0FSRQG23K?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1

1/4" Audio Jacks (can use any, these are just the ones I bought):
https://stompboxparts.com/audio-jacks/1-4-ts-enclosed-jack-panel-mount-skinny-lug/

3D model for enclosure coming soon TM
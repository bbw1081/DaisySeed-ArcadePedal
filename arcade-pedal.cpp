/**
 *  arcade-pedal.cpp, main program for a guitar pedal to be controlled by
 *  an arcade joystick and buttons
 *  Copyright (C) 2026  Richard B. Wilkinson

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * DAISY SEED PINOUT
 * 
 * pin 22	<-- X-Axis Potentiometer 	(10k ohms)
 * pin 23	<-- Y-Axis Potentiometer 	(10k ohms)
 * pin 24 	<-- Green arcade button 	(SPST switch)
 * pin 25	<-- Red arcade button 		(SPST switch)
 */

/* Daisy Seed Libraries */
#include "daisy_seed.h"
#include "daisysp.h"

/* Display Libraries */
#include <stdio.h>
#include <string.h>
#include "dev/oled_ssd130x.h"

#include "effects.h"

/* Declare Namespaces */
using namespace daisy;
using namespace daisysp;
using MyOledDisplay = OledDisplay<SSD130xI2c128x64Driver>;

/* Declare Variables */
DaisySeed hw; //daisy seed hardware
MyOledDisplay display;
MyOledDisplay::Config disp_cfg;
const int num_adc_channels = 2; //number of adc channels in use, 1 for each pot
AdcChannelConfig adc_config[num_adc_channels]; //0 is x-xis, 1 is y-axis
GPIO green_button;
GPIO red_button;
const int num_effects = 2;
struct EffectListing {
	BaseEffect* effects[num_effects];
	int current_effect;
};
EffectListing* effect_listing;

/**
 * Initializes the struct to hold all of the effects
 */
EffectListing* InitEffects(float sample_rate){
	EffectListing* e;

	ChorusEffect* ce;
	ce->Init(sample_rate);
	e->effects[0] = ce;

	FlangerEffect* fe;
	fe->Init(sample_rate);
	e->effects[1] = fe;

	e->current_effect = 0;

	return e;
} /* end InitEffects() */

/**
 * Calculates the maximum font size based on the number of characters in a line
 */
FontDef CalculateFontSize(const char* text){
	if(strlen(text) < 11) {
		return Font_11x18;
	} else if(strlen(text) < 18) {
		return Font_7x10;
	} else {
		return Font_6x8;
	}
} /* end CalculateFontSize() */

/**
 * Displays a string to the screen, can be 1 word or 2
 */
void DisplayText(const char* text){
	display.Fill(false); //clear the display
	display.DrawRect(0, 0, 127, 63, true); //draw a rectangle around the edge

	const char* spacePos = strchr(text, ' ');
	if(spacePos == nullptr) {
		//one line
		display.WriteStringAligned(text, CalculateFontSize(text), Rectangle(0, 0, 128, 64), Alignment::centered, true);
	} else {
		//two lines
		char line1[32];
		char line2[32];

		int i = spacePos - text;

		strncpy(line1, text, i);
		line1[i] = '\0';
		strcpy(line2, text + i + 1);

		display.WriteStringAligned(line1, CalculateFontSize(line1), Rectangle(0, 0, 128, 32), Alignment::centered, true);
		display.WriteStringAligned(line2, CalculateFontSize(line2), Rectangle(0, 32, 128, 32), Alignment::centered, true);
	}

    display.Update();
} /* end DisplayText() */


void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	BaseEffect* e = effect_listing->effects[effect_listing->current_effect];
	e->SetParams(hw.adc.GetFloat(0), hw.adc.GetFloat(1));
	for (size_t i = 0; i < size; i++)
	{
		out[0][i] = e->Process(in[0][i]);
	}
} /* end AudioCallBack() */

int main(void)
{
	/* Initialize hardware and audio parameters */
	hw.Init();

	//audio block size and sample rate
	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);

	//configure the display
    disp_cfg.driver_config.transport_config.i2c_config.periph = I2CHandle::Config::Peripheral::I2C_1;
    disp_cfg.driver_config.transport_config.i2c_config.mode   = I2CHandle::Config::Mode::I2C_MASTER;
    disp_cfg.driver_config.transport_config.i2c_config.speed  = I2CHandle::Config::Speed::I2C_400KHZ;
    disp_cfg.driver_config.transport_config.i2c_config.pin_config.scl = seed::D11;
    disp_cfg.driver_config.transport_config.i2c_config.pin_config.sda = seed::D12;
	display.Init(disp_cfg);
	display.Fill(false);
	display.Update();

	/* Initialize peripheral I/O */
	//potentiometers for 2-axis joystick
	adc_config[0].InitSingle(seed::A0); //X-Axis pot
	adc_config[1].InitSingle(seed::A1); //Y-Axis pot
	hw.adc.Init(adc_config, num_adc_channels);
	hw.adc.Start();

	//2 arcade buttons
	green_button.Init(seed::A2, GPIO::Mode::INPUT, GPIO::Pull::PULLUP);
	red_button.Init(seed::A3, GPIO::Mode::INPUT, GPIO::Pull::PULLUP);

	//start audio
	hw.StartAudio(AudioCallback);

	bool green_pressed = false;
	bool red_pressed = false;

	effect_listing = InitEffects(hw.AudioSampleRate());
	DisplayText(effect_listing->effects[effect_listing->current_effect]->GetName());

	/* MAIN LOOP*/
	while(1) {
		bool green_state = green_button.Read();
		bool red_state = red_button.Read();
		//dumb implementation, TODO test and make smarter
		if(!green_state && !green_pressed){
			green_pressed = true;

			effect_listing->current_effect -= 1;
			if(effect_listing->current_effect < 0){
				//wraparound
				effect_listing->current_effect = num_effects - 1;
			} /* end if */

			DisplayText(effect_listing->effects[effect_listing->current_effect]->GetName());
		} else if(green_state){
			green_pressed = false;
		} /* end if */
		
		if(!red_state && !red_pressed){
			red_pressed = true;

			effect_listing->current_effect += 1;
			if(effect_listing->current_effect >= num_effects){
				//wraparound
				effect_listing->current_effect = 0;
			} /* end if */

			DisplayText(effect_listing->effects[effect_listing->current_effect]->GetName());
		} else if(red_state){
			red_pressed = false;
		} /* end if */
	} /* end while */
} /* end main() */

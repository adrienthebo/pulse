#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

//#include "controller-talik-functions.h"
#include "controller-timing.h"
#include "controller-audio.h"

using namespace std;

Timing timing;

Audio_controller audio_controller;

void setup() {
//Delay to give me time to open the serial monitor
	for(int i=0;i<10;i++)
	{
		Serial.println(i);
		delay(1000);
	}
	Serial.println("begin");

	audio_controller.setup();
}

void loop() {
	Serial.println("loop");
			audio_controller.audio_process();
			Serial.printf("bass=%4d (%d-%d)",audio_controller.led_intensity_norm(0),audio_controller.led_intensity_min(0),audio_controller.led_intensity_max(0));
			Serial.printf(", mid=%4d (%d-%d)",audio_controller.led_intensity_norm(1),audio_controller.led_intensity_min(1),audio_controller.led_intensity_max(1));
			Serial.printf(", treble=%4d (%d-%d)",audio_controller.led_intensity_norm(2),audio_controller.led_intensity_min(2),audio_controller.led_intensity_max(2));
	
	timing.do_delay();
}
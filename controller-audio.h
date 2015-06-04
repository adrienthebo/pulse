#include <Audio.h>
#include <SD.h>

//const int myInput = AUDIO_INPUT_MIC;
const int myInput = AUDIO_INPUT_LINEIN;

AudioInputI2S        audioInput;
AudioSynthWaveformSine sinewave;
AudioAnalyzeFFT1024  myFFT;
AudioOutputI2S       audioOutput;
AudioConnection      c1(audioInput, 0, audioOutput, 0);
AudioConnection      c2(audioInput, 0, myFFT, 0);
AudioConnection      c3(audioInput, 1, audioOutput, 1);

AudioControlSGTL5000 audioShield;


File settingsFile;

class Audio_controller
{
	private:
		const int BASS = 0;
		const int MID = 1;
		const int TREBLE = 2;
		int imgFiles = 3;
		int led_intensity_history[3][1000];  //1000 is about 40 seconds.
		int led_intensity_history_total[3];
		int led_intensity_history_offset[3];
		int baseline[512];
		int baseline_counter;
	public:
		void setup()
		{
			Serial.println("initializing audio");
			Serial.println("AudioMemory");
			AudioMemory(12);
			Serial.println("audioShield.enable");
			audioShield.enable();
			Serial.println("audioShield.inputSelect");
			audioShield.inputSelect(myInput);
			Serial.println("audioShield.volume");
			
			audioShield.volume(0.5);
			for(int i=0;i<=3;i++)
			{
				led_intensity_history_offset[i] = 0;
				for(int j=0;j<=sizeof(led_intensity_history[i])/sizeof(int);j++)
					set_led_intensity(i,-1);
			}
//			Serial.println("loading audio.cfg");
//			settingsFile = SD.open("audio.cfg");
//			Serial.println("setting baseline");
//			int i=2;
//			while (settingsFile.available()) {
//				baseline[i] = settingsFile.read();
//				i++;
//				if(i>511)
//					break;
//			}
//			settingsFile.close();
		}
		int led_intensity_max(int spect)
		{
			int max = (3-spect)*50;
			int i;
			for(int i=0;i<sizeof(led_intensity_history[spect])/sizeof(int);i++)
			{
				if(led_intensity_history[spect][i] > max)
					max = led_intensity_history[spect][i];
			}
			return max;
		}
		int led_intensity_min(int spect)
		{
			int min = 1000;
			int i,j=0;
			for(int i=0;i<sizeof(led_intensity_history[spect])/sizeof(int);i++)
			{
				if(led_intensity_history[spect][i]!=-1)
					j++;
				if(led_intensity_history[spect][i] < min && led_intensity_history[spect][i]!=-1)
					min = led_intensity_history[spect][i];
			}
			return min;
		}

		int led_intensity_avg(int spect)
		{
		//	return led_intensity_history_total[spect]/(sizeof(led_intensity_history[spect])/sizeof(int));
		
			long total = 0;
			int i,j=0;
			for(int i=0;i<sizeof(led_intensity_history[spect])/sizeof(int);i++)
			{
				if(led_intensity_history[spect][i]!=-1)
					j++;
				total += led_intensity_history[spect][i];
				
			}
			int avg = total/j;
			if(avg>5)
				return avg;
			return 5;
		}
		int led_intensity_avg_all()
		{
			return (led_intensity_avg(BASS)+led_intensity_avg(MID)+led_intensity_avg(TREBLE))/3;
		}
		int led_intensity_avg_norm(int spect)
		{
			return 1000 * led_intensity_avg(spect) / led_intensity_max(spect);
		}
		int led_intensity_avg_norm_all()
		{
			return (led_intensity_avg_norm(BASS)+led_intensity_avg_norm(MID)+led_intensity_avg_norm(TREBLE))/3;
		}
		int led_intensity(int spect)
		{
			return led_intensity_history[spect][led_intensity_history_offset[spect]];
		}
		int led_intensity_norm(int spect)
		{
			return 1000 * (led_intensity(spect)-led_intensity_min(spect)) / (led_intensity_max(spect)-led_intensity_min(spect));
		}
		int led_intensity_norm_all()
		{
			return (led_intensity_norm(BASS)+led_intensity_norm(MID)+led_intensity_norm(TREBLE))/3;
		}
		void set_led_intensity(int spect,int intensity)
		{
			led_intensity_history_offset[spect]++;
			if(led_intensity_history_offset[spect]>=sizeof(led_intensity_history[spect])/sizeof(int)) led_intensity_history_offset[spect]=0;
			//led_intensity_history_total[spect] -= led_intensity_history[spect][led_intensity_history_offset[spect]];
			//led_intensity_history_total[spect] += intensity;
			led_intensity_history[spect][led_intensity_history_offset[spect]] = intensity;
		}
		void audio_process() {
			int i;
			int bass_value=0, mid_value=0, treble_value=0,all=0;
				Serial.println("audio1");
			if (myFFT.available()) {
				Serial.println("audio2");
				/*for (i=2; i < 511; i++) {
					Serial.printf(",%d",max(0,myFFT.output[i]-baseline[i]));
					
				}
				Serial.println();
				for (i=2; i < 511; i++) {
					Serial.printf(",%d",baseline[i]);
				}
				Serial.println();*/
				for (i=2; i < 20; i++) {
					bass_value += max(0,myFFT.output[i]-baseline[i]-1);
				}
				for (i=21; i < 100; i++) {
					mid_value += max(0,myFFT.output[i]-baseline[i]-1);
				}
				for (i=101; i < 511; i++) {
					treble_value += max(0,myFFT.output[i]-baseline[i]-1);
				}
				all = bass_value+mid_value+treble_value;

				
				int spect = 0;
				for(spect=0;spect<3;spect++)
				{
					if(spect==BASS)
						set_led_intensity(spect,bass_value);
					else if(spect==MID)
						set_led_intensity(spect,mid_value);
					else if(spect==TREBLE)
						set_led_intensity(spect,treble_value);
					/*Serial.print(", intensity_cur=");
					Serial.print(led_intensity_history[spect][led_intensity_history_offset[spect]]);
					Serial.print(", intensity_max=");
					Serial.print(led_intensity_max(spect));
					Serial.print(", intensity_min=");
					Serial.print(led_intensity_min(spect));
					Serial.print(", intensity_avg=");
					Serial.print(led_intensity_avg(spect));
					Serial.print(", intensity=");
					Serial.print(led_intensity(spect));*/
				}
			}
		}
/*	bool gatherBaseline()
	{
		int counterGoal = 100;
		int i, n;
		baseline_counter=0;
		for (i=2; i < 511; i++) {
			baseline[i] = 0;
		}
		while(1)
		{
			if (digitalRead(5) == HIGH) break;
			if (myFFT.available()) {
					for (i=2; i < 511; i++) {
						baseline[i] += myFFT.output[i];
						//Serial.printf(",%d",baseline[i]);
					}
					
					//Serial.println();
					baseline_counter++;
				//Serial.println("asdf");
			}
			if(baseline_counter==counterGoal)
			{
				for (n=0;n < lightCount*3;n+=1) {
					dmx_buffer[n] = 255;
				}
//				dmx_transmit();
				delay(100);
				for (n=0;n < lightCount*3;n+=1) {
					dmx_buffer[n] = 0;
				}
//				dmx_transmit();
			}
			delay(40);
		}*/
/*		Serial.println(baseline_counter);

		if(baseline_counter>counterGoal)
		{
			SD.remove("audio.cfg");
			settingsFile = SD.open("audio.cfg", FILE_WRITE);
			if(!settingsFile)
				Serial.println("can not write to file");
			for (i=2; i < 511; i++) {
				baseline[i] = 2*baseline[i]/baseline_counter;
				settingsFile.println(baseline[i]);
			}
			settingsFile.close();
			return true;
		}else
			return false;
	}*/
};

#include <elapsedMillis.h>



class Timing
{
	private:
		elapsedMillis _timer_msec = 0;
		int _fps = 0;
		int _framedelay = 0;
		int _frame = 0;
	public:
	Timing()
	{
		//TODO - Load framerate from settings class
		_fps = 30;//SETTINGS_FPS;
		_framedelay = 1000/_fps;
	}
	void do_delay()
	{
		int delaytime = _framedelay-_timer_msec;
		Serial.printf(" sleeping=%d ",delaytime);
		if(delaytime>0)
			delay(delaytime);
		_frame++;
		if(_frame >= 2147483647) _frame = 0;
		_timer_msec = 0;
	}
};

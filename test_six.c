#include <ev3.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#define EV3SENSOR_H
#define THRESHOLD_LIGHT 10 //light sensor threshold
#define THRESHOLD_SONAR 45 //sonar sensor threshold 45cm

//rotate factor variable
float rf = 2.75; //rotation in place
float mf = 21; //rotation to move forward

//declare counter, increment
int i;
int a;
int b;

//declare motor rotation angle
char str[20];
int r;


/*void startSumo()
{
	RotateMotorEx(OUT_A, 40, 90, 0 , true, true);
	RotateMotorEx(OUT_BC, -100, 160*rf, 200 , true, true);
	Off(OUT_ABC);
}*/

//function to randomly move robot
void pushObject()
{
	while(1)
	{
		if (ReadSensor(IN_3) < THRESHOLD_LIGHT)
		{
			Off(OUT_BC);
			break;
		}

		else
		{
			OnFwdEx(OUT_BC, 90, true);
		}
	}
}

int main()
{
	InitEV3();
	setAllSensorMode(NO_SEN, NO_SEN, COL_REFLECT, US_DIST_CM);

	//		startSumo();
	while(1)
	{
		if (ButtonIsDown(BTNCENTER) == 1)
		{
			return;
			Off(OUT_BC);
			break;
		}

		else
		{
			while(1)
			{
				for(i=1;i<=30;i++)
				{
					if(ReadSensor(IN_4) > THRESHOLD_SONAR)
					{
						//rotate and find
						RotateMotorEx(OUT_BC, -50, 15, 200 , true, true);
					}

					else
					{
						pushObject();
						RotateMotorEx(OUT_BC, -100, 460, 0 , true, true);
					}
				}
				pushObject();
				break;
			}
		}
	}
	FreeEV3();
	return 0;
}

#include <fcntl.h>
#include <linux/input.h>
#include <pca9685.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

#define servo0 302 // GPIO 4
#define servo1 301 // GPIO 3
#define servo2 300 // GPIO 2

#define servo3 304  // GPIO 18
#define servo4 305 // GPIO 15
#define servo5 306 // GPIO 14

#define servo6 311 // GPIO 13
#define servo7 310 // GPIO 19
#define servo8 309 // GPIO 26

#define servo9 315 // GPIO 16
#define servo10 314 // GPIO 20
#define servo11 313 // GPIO 21

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

/* float millis = 1.5;
int tick = calcTicks(millis, HERTZ); */

int calcTicks(float impulseMs, int hertz) {
	float cycleMs = 1000.0f / hertz;
	return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

int main(int argc, char *argv[]) {
	float millis = 1.5;
	int tick = calcTicks(millis, HERTZ);

	if (argc != 2) {
		printf("Usage: %s <event-file-path>\n", argv[0]);
		exit(-1);
	}

	printf("Keylogger active\n");

	int controllerFd = open(argv[1], O_RDONLY, 0);
	printf("Opened file descriptor: %d\n", controllerFd);

	struct input_event ie;

	wiringPiSetup();

	// Setup with pinbase 300 and i2c location 0x40
	int pcaFd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (pcaFd < 0)
	{
		printf("Error in setup\n");
		return pcaFd;
	}

	// Reset all output
	pca9685PWMReset(pcaFd);

	// Front left leg
	printf("Front left leg base\n");
	pwmWrite(servo0, calcTicks(1.5, HERTZ));
	pwmWrite(servo1, calcTicks(1.5, HERTZ)); // Good
	pwmWrite(servo2, calcTicks(1.5, HERTZ)); // Good */
	delay(1000);

	// Front right leg
	printf("Front right leg base\n");
	pwmWrite(servo3, calcTicks(1.5, HERTZ)); // Good
	pwmWrite(servo4, calcTicks(1.5, HERTZ)); // Good 
	pwmWrite(servo5, calcTicks(1.5, HERTZ)); // Good 
	delay(1000);

	// Back left leg
	printf("Back left leg base \n");
	pwmWrite(servo6, calcTicks(1.5, HERTZ)); // Good 
	pwmWrite(servo7, calcTicks(1.5, HERTZ)); // Good
	pwmWrite(servo8, calcTicks(1.5, HERTZ)); // Good
	delay(1000);

	// Back right leg
	printf("Back right leg base\n");
	pwmWrite(servo9, calcTicks(1.5, HERTZ)); // Good
	pwmWrite(servo10, calcTicks(1.5, HERTZ)); // Good
	pwmWrite(servo11, calcTicks(1.5, HERTZ)); // Good
	delay(1000);

	while (1) {
		read(controllerFd, &ie, sizeof(ie));

		if (ie.code == 307 && ie.value == 1) {

			printf("Front\n");

			pwmWrite(servo1, calcTicks(1.7, HERTZ));
			/* softPwmWrite(servo1, 10);
			softPwmWrite(servo0, 10);
			delay(250);

			softPwmWrite(servo1, 15);
			delay(250);

			softPwmWrite(servo7, 10);
			softPwmWrite(servo6, 20);
			delay(250);

			softPwmWrite(servo7, 15);

			// Search in front to walk (left side)
			softPwmWrite(servo1, 10);
			softPwmWrite(servo0, 15);
			softPwmWrite(servo2, 25);

			softPwmWrite(servo1, 15);
			delay(250);

			softPwmWrite(servo2, 15);
			
			softPwmWrite(servo6, 15);

			softPwmWrite(servo3, 20);

			softPwmWrite(servo10, 10);
			softPwmWrite(servo9, 10);
			delay(250);

			softPwmWrite(servo10, 15);

			// Search in front to walk (right side)
			softPwmWrite(servo4, 10);
			softPwmWrite(servo3, 15);
			softPwmWrite(servo5, 20);

			softPwmWrite(servo4, 15);
			softPwmWrite(servo5, 15);
			// softPwmWrite(servo0, 10);
			softPwmWrite(servo9, 15); */

		} else if (ie.code == 307 && ie.value == 0) {

			printf("Idle\n");

			// Front left leg
			pwmWrite(servo0, tick);
			pwmWrite(servo1, tick);
			pwmWrite(servo2, tick);

			// Front right leg
			pwmWrite(servo3, tick);
			pwmWrite(servo4, tick);
			pwmWrite(servo5, tick);

			// Back left leg
			pwmWrite(servo6, tick);
			pwmWrite(servo7, tick);
			pwmWrite(servo8, tick);

			// Back right leg
			pwmWrite(servo9, tick);
			pwmWrite(servo10, tick);
			pwmWrite(servo11, tick);

		}





		if (ie.code == 305 && ie.value == 1) {

			/* printf("Turn right\n");

			// Front left leg
			softPwmWrite(servo0, 20);
			softPwmWrite(servo1, 15);
			softPwmWrite(servo2, 15);

			// Front right leg
			softPwmWrite(servo3, 20);
			softPwmWrite(servo4, 15);
			softPwmWrite(servo5, 15);

			// Back left leg
			softPwmWrite(servo6, 20);
			softPwmWrite(servo7, 15);
			softPwmWrite(servo8, 15);

			// Back right leg
			softPwmWrite(servo9, 20);
			softPwmWrite(servo10, 15);
			softPwmWrite(servo11, 15); */

		} else if (ie.code == 305 && ie.value == 0) {

			printf("Idle\n");

			// Front left leg
			pwmWrite(servo0, tick);
			pwmWrite(servo1, tick);
			pwmWrite(servo2, tick);

			// Front right leg
			pwmWrite(servo3, tick);
			pwmWrite(servo4, tick);
			pwmWrite(servo5, tick);

			// Back left leg
			pwmWrite(servo6, tick);
			pwmWrite(servo7, tick);
			pwmWrite(servo8, tick);

			// Back right leg
			pwmWrite(servo9, tick);
			pwmWrite(servo10, tick);
			pwmWrite(servo11, tick);

		}





		if (ie.code == 304 && ie.value == 1) {

			printf("Back\n");

		} else if (ie.code == 304 && ie.value == 0) {

			printf("Idle\n");
			
			// Front left leg
			pwmWrite(servo0, tick);
			pwmWrite(servo1, tick);
			pwmWrite(servo2, tick);
			
			// Front right leg
			pwmWrite(servo3, tick);
			pwmWrite(servo4, tick);
			pwmWrite(servo5, tick);

			// Back left leg
			pwmWrite(servo6, tick);
			pwmWrite(servo7, tick);
			pwmWrite(servo8, tick);

			// Back right leg
			pwmWrite(servo9, tick);
			pwmWrite(servo10, tick);
			pwmWrite(servo11, tick);

		}





		if (ie.code == 308 && ie.value == 1) {

			printf("Turn left\n");

			/* // Front left leg
			pwmWrite(servo0, tick);
			pwmWrite(servo1, tick);
			pwmWrite(servo2, tick);

			// Front right leg
			pwmWrite(servo3, tick);
			pwmWrite(servo4, tick);
			pwmWrite(servo5, tick);

			// Back left leg
			softPwmWrite(servo6, 10);
			softPwmWrite(servo7, 15);
			softPwmWrite(servo8, 15);

			// Back right leg
			softPwmWrite(servo9, 10);
			softPwmWrite(servo10, 15);
			softPwmWrite(servo11, 15); */

		} else if (ie.code == 308 && ie.value == 0) {

			printf("Idle\n");

			// Front left leg
			pwmWrite(servo0, tick);
			pwmWrite(servo1, tick);
			pwmWrite(servo2, tick);

			// Front right leg
			pwmWrite(servo3, tick);
			pwmWrite(servo4, tick);
			pwmWrite(servo5, tick);

			// Back left leg
			pwmWrite(servo6, tick);
			pwmWrite(servo7, tick);
			pwmWrite(servo8, tick);

			// Back right leg
			pwmWrite(servo9, tick);
			pwmWrite(servo10, tick);
			pwmWrite(servo11, tick);

		}

		if (ie.code == 316) {

			digitalWrite(servo0, 0);
			digitalWrite(servo1, 0);
			digitalWrite(servo2, 0);

			digitalWrite(servo3, 0);
			digitalWrite(servo4, 0);
			digitalWrite(servo5, 0);

			digitalWrite(servo6, 0);
			digitalWrite(servo7, 0);
			digitalWrite(servo8, 0);

			digitalWrite(servo9, 0);
			digitalWrite(servo10, 0);
			digitalWrite(servo11, 0);

			exit(0);
		
		}
	}

	return 0;
}

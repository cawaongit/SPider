#include <fcntl.h>
#include <linux/input.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

#define MIN_PULSE_WIDTH 10
#define MAX_PULSE_WIDTH 30

#define servo0 8 // GPIO 2
#define servo1 9 // GPIO 3
#define servo2 7 // GPIO 4

#define servo3 15 // GPIO 14
#define servo4 16 // GPIO 15
#define servo5 1 // GPIO 18

#define servo6 23 // GPIO 13
#define servo7 24 // GPIO 19
#define servo8 25 // GPIO 26

#define servo9 27 // GPIO 16
#define servo10 28 // GPIO 20
#define servo11 29 // GPIO 21

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <event-file-path>\n", argv[0]);
		exit(-1);
	}

	printf("Keylogger active\n");

	int fd = open(argv[1], O_RDONLY, 0);
	printf("Opened file descriptor: %d\n", fd);

	struct input_event ie;

	// 10 is 0 degrees
	// 20 is 180 degrees
	// 15 is middle (start position)
	wiringPiSetup();

	// Front left leg
	printf("Front left leg base\n");
	softPwmCreate(servo0, 15, 100); // Good
	softPwmCreate(servo1, 15, 100); // Good
	softPwmCreate(servo2, 15, 100); // Good

	// Front right leg
	printf("Front right leg base\n");
	softPwmCreate(servo3, 15, 100); // Good
	softPwmCreate(servo4, 15, 100); // Good 
	softPwmCreate(servo5, 15, 100); // Good 

	// Back left leg
	printf("Back left leg base \n");
	softPwmCreate(servo6, 15, 100); // Good 
	softPwmCreate(servo7, 15, 100); // Good
	softPwmCreate(servo8, 15, 100); // Good

	// Back right leg
	printf("Back right leg base\n");
	softPwmCreate(servo9, 15, 100); // Good
	softPwmCreate(servo10, 15, 100); // Good
	softPwmCreate(servo11, 15, 100); // Good

	while (1) {
		read(fd, &ie, sizeof(ie));

		if (ie.code == 307 && ie.value == 1) {

			printf("Front\n");

			softPwmWrite(servo0, 10);
			// delay(500);

			softPwmWrite(servo7, 10);
			softPwmWrite(servo6, 20);
			delay(500);

			softPwmWrite(servo7, 15);

			softPwmWrite(servo1, 10);
			softPwmWrite(servo0, 15);
			softPwmWrite(servo2, 22);
			delay(500);

			softPwmWrite(servo1, 15);
			delay(1000);

			softPwmWrite(servo2, 15);
			
			softPwmWrite(servo3, 20);

		} else if (ie.code == 307 && ie.value == 0) {

			printf("Idle\n");

			// Front left leg
			softPwmWrite(servo0, 15);
			softPwmWrite(servo1, 15);
			softPwmWrite(servo2, 15);

			// Front right leg
			softPwmWrite(servo3, 15);
			softPwmWrite(servo4, 15);
			softPwmWrite(servo5, 15);

			// Back left leg
			softPwmWrite(servo6, 15);
			softPwmWrite(servo7, 15);
			softPwmWrite(servo8, 15);

			// Back right leg
			softPwmWrite(servo9, 15);
			softPwmWrite(servo10, 15);
			softPwmWrite(servo11, 15);

		}





		if (ie.code == 305 && ie.value == 1) {

			printf("Turn right\n");

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
			softPwmWrite(servo11, 15);

		} else if (ie.code == 305 && ie.value == 0) {

			printf("Idle\n");

			// Front left leg
			softPwmWrite(servo0, 15);
			softPwmWrite(servo1, 15);
			softPwmWrite(servo2, 15);

			// Front right leg
			softPwmWrite(servo3, 15);
			softPwmWrite(servo4, 15);
			softPwmWrite(servo5, 15);

			// Back left leg
			softPwmWrite(servo6, 15);
			softPwmWrite(servo7, 15);
			softPwmWrite(servo8, 15);

			// Back right leg
			softPwmWrite(servo9, 15);
			softPwmWrite(servo10, 15);
			softPwmWrite(servo11, 15);

		}





		if (ie.code == 304 && ie.value == 1) {

			printf("Back\n");

		} else if (ie.code == 304 && ie.value == 0) {

			printf("Idle\n");
			
			// Front left leg
			softPwmWrite(servo0, 15);
			softPwmWrite(servo1, 15);
			softPwmWrite(servo2, 15);
			
			// Front right leg
			softPwmWrite(servo3, 15);
			softPwmWrite(servo4, 15);
			softPwmWrite(servo5, 15);

			// Back left leg
			softPwmWrite(servo6, 15);
			softPwmWrite(servo7, 15);
			softPwmWrite(servo8, 15);

			// Back right leg
			softPwmWrite(servo9, 15);
			softPwmWrite(servo10, 15);
			softPwmWrite(servo11, 15);

		}





		if (ie.code == 308 && ie.value == 1) {

			printf("Turn left\n");

			// Front left leg
			softPwmWrite(servo0, 10);
			softPwmWrite(servo1, 15);
			softPwmWrite(servo2, 15);

			// Front right leg
			softPwmWrite(servo3, 10);
			softPwmWrite(servo4, 15);
			softPwmWrite(servo5, 15);

			// Back left leg
			softPwmWrite(servo6, 10);
			softPwmWrite(servo7, 15);
			softPwmWrite(servo8, 15);

			// Back right leg
			softPwmWrite(servo9, 10);
			softPwmWrite(servo10, 15);
			softPwmWrite(servo11, 15);

		} else if (ie.code == 308 && ie.value == 0) {

			printf("Idle\n");

			// Front left leg
			softPwmWrite(servo0, 15);
			softPwmWrite(servo1, 15);
			softPwmWrite(servo2, 15);

			// Front right leg
			softPwmWrite(servo3, 15);
			softPwmWrite(servo4, 15);
			softPwmWrite(servo5, 15);

			// Back left leg
			softPwmWrite(servo6, 15);
			softPwmWrite(servo7, 15);
			softPwmWrite(servo8, 15);

			// Back right leg
			softPwmWrite(servo9, 15);
			softPwmWrite(servo10, 15);
			softPwmWrite(servo11, 15);

		}
	}

	return 0;
}

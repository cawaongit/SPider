#include <fcntl.h>
#include <linux/input.h>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
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

int calcTicks(float impulseMs, int hertz) {
	float cycleMs = 1000.0f / hertz;
	return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

int facial_recognition() {
	cv::namedWindow("Frame", 0);
	cv::String detectionModelPath = "/home/sasha/SPider/face_detection_yunet_2023mar.onnx";
	cv::String recognizerModelPath = "/home/sasha/SPider/face_recognition_sface_2021dec.onnx";

	cv::Mat refImg = cv::imread("/home/sasha/SPider/.png");
	cv::Mat frame, faceRef, alignedRedFace, featureRef, facesGlobal;

	cv::Ptr<cv::FaceDetectorYN> detectorRef = cv::FaceDetectorYN::create(detectionModelPath, "", cv::Size(320, 320));
	detectorRef->setInputSize(refImg.size());
	detectorRef->detect(refImg, faceRef);

	cv::Ptr<cv::FaceRecognizerSF> recognizerRef = cv::FaceRecognizerSF::create(recognizerModelPath, "");
	recognizerRef->alignCrop(refImg, faceRef(0), alignedRedFace);
	recognizerRef->feature(alignedRedFace, featureRef);

	cv::Ptr<cv::FaceDetectorYN> detectorGlobal = cv::FaceDetectorYN::create(detectionModelPath, "", cv::Size(320, 320));
	cv::Ptr<cv::FaceRecognizerSF> recognizerGlobal = cv::FaceRecognizerSF::create(recognizerModelPath, "");

	detectorGlobal->setInputSize(cv::Size(1280, 720));


	cv::VideoCapture cap(0);

	while (1) {

		cap >> frame;
		detectorGlobal->detect(frame, facesGlobal);

		for (int i = 0; i < facesGlobal.rows; i++) {
			cv::Rect box(facesGlobal.at<float>(i, 0), facesGlobal.at<float>(i, 1), facesGlobal.at<float>(i, 2), facesGlobal.at<float>(i, 3));
			cv::rectangle(frame, box, cv::Scalar(0, 255, 255, 255), 3);
		}

		cv::imshow("Frame", frame);
		if (cv::waitKey(1) == 'q') {
			break;
		}
	
	}

	cap.release();

	return 0;
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
	pwmWrite(servo2, calcTicks(1.5, HERTZ)); // Good
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


			// Left side movement


			// Front left leg
			pwmWrite(servo0, calcTicks(1, HERTZ));
			delay(250);

			// Back left leg
			pwmWrite(servo6, calcTicks(2, HERTZ));
			pwmWrite(servo7, calcTicks(1, HERTZ));
			delay(250);

			// Back left leg
			pwmWrite(servo7, calcTicks(1.5, HERTZ));

			// Front left leg
			pwmWrite(servo0, calcTicks(1.5, HERTZ));
			pwmWrite(servo1, calcTicks(1.7, HERTZ));
			pwmWrite(servo2, calcTicks(2.2, HERTZ));
			delay(250);

			// Front left leg
			pwmWrite(servo1, calcTicks(1.5, HERTZ));
			pwmWrite(servo2, calcTicks(1.5, HERTZ));

			// Back left leg
			pwmWrite(servo6, calcTicks(1.5, HERTZ));


			// Right side movement


			// Front right
			pwmWrite(servo3, calcTicks(2, HERTZ));
			delay(250);
			
			// Back right leg
			pwmWrite(servo9, calcTicks(1, HERTZ));
			pwmWrite(servo10, calcTicks(1, HERTZ));
			delay(250);

			// Front right leg
			pwmWrite(servo10, calcTicks(1.5, HERTZ));

			// Front right leg
			pwmWrite(servo3, calcTicks(1.5, HERTZ));
			pwmWrite(servo4, calcTicks(1.7, HERTZ));
			pwmWrite(servo5, calcTicks(2.2, HERTZ));
			delay(250);

			// Front right leg
			pwmWrite(servo4, calcTicks(1.5, HERTZ));
			pwmWrite(servo5, calcTicks(1.5, HERTZ));

			pwmWrite(servo0, calcTicks(1, HERTZ));
			delay(250);

			// pwmWrite(servo9, calcTicks(1.5, HERTZ));

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

			printf("Turn right\n");

			pwmWrite(servo4, calcTicks(1.3, HERTZ)); // Ok
			delay(250);

			pwmWrite(servo3, calcTicks(2, HERTZ)); // Ok
			delay(250);

			pwmWrite(servo4, calcTicks(1.5, HERTZ)); // Ok
			delay(250);

			pwmWrite(servo7, calcTicks(1.3, HERTZ)); // Ok
			delay(250);

			pwmWrite(servo6, calcTicks(2, HERTZ)); // Ok
			delay(250);

			pwmWrite(servo7, calcTicks(1.5, HERTZ)); // Ok
			delay(250);
			
			pwmWrite(servo3, calcTicks(1.5, HERTZ));

			pwmWrite(servo0, calcTicks(1, HERTZ));

			pwmWrite(servo9, calcTicks(1, HERTZ));

			pwmWrite(servo6, calcTicks(1.5, HERTZ));

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

			pwmWrite(servo1, calcTicks(1.3, HERTZ));
			delay(250);

			pwmWrite(servo0, calcTicks(1, HERTZ));
			delay(250);

			pwmWrite(servo1, calcTicks(1.5, HERTZ));
			delay(250);

			pwmWrite(servo10, calcTicks(1.3, HERTZ));
			delay(250);

			pwmWrite(servo9, calcTicks(1, HERTZ));
			delay(250);

			pwmWrite(servo10, calcTicks(1.5, HERTZ));
			delay(250);
			
			pwmWrite(servo0, calcTicks(1.5, HERTZ));

			pwmWrite(servo3, calcTicks(2, HERTZ));

			pwmWrite(servo6, calcTicks(2, HERTZ));

			pwmWrite(servo9, calcTicks(1.5, HERTZ));

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



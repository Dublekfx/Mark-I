/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {
	riceBotInitialize();

	driveTrainStyle = DTFOURWHEELS;
	controlStyle = CTCHEEZYDRIVE;

//	MOTDTFrontLeft = initRicemotor(9, 1);
	MOTDTFrontRight = initRicemotor(8, -1);
	MOTDTBackLeft = initRicemotor(3, 1);
	MOTDTBackRight = initRicemotor(2, -1);

	MOTARMLeft = initRicemotor(6, -1);
	MOTARMRight = initRicemotor(5, -1);

	MOTARMFront = initRicemotor(7, 1);
	MOTConveyor = initRicemotor(4, 1);
	MOTCLAW = initRicemotor(10, -1);
	MOTCOL = initRicemotor(9, 1);

	EncDTLeft = initRicencoderIME(627.2, 1, 0, false);
	EncDTRight = initRicencoderIME(627.2, 1, 1, true);

	EncARMLeft = initRicencoderIME(627.2, 1, 3, true);
	EncARMRight = initRicencoderIME(627.2, 1, 2, false);
	EncARMFront = initRicencoderIME(627.2, 1, 4, false);

//	ButConLeft = initRicebutton(2);
//	ButConRight = initRicebutton(1);
	ButARMBase = initRicebutton(4);
//	ButARMFrontLeft = initRicebutton(5);
//	ButARMFrontRight = initRicebutton(6);

	gyro = initRicegyro(1, 196);

	Ricemotor* armLeft[2] = {MOTARMLeft, MOTDefault};
	Ricemotor* armRight[2] = {MOTARMRight, MOTDefault};
	PidARMLeft = initRicepid(&(EncARMLeft->adjustedValue), .2, 0, 0, armLeft);
	PidARMRight = initRicepid(&(EncARMRight->adjustedValue), .2, 0, 0, armRight);
	PidARMLeft->running = 1;
	PidARMRight->running = 1;

	delay(500);

	taskCreate(IOTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_HIGHEST);
	taskCreate(PidTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	taskCreate(miscTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void miscTask(void *ignore) {
	while(1) {

		if(ButARMBase->state == LOW) {
			imeReset(EncARMLeft->imeAddress);
			imeReset(EncARMRight->imeAddress);
			updateRicencoder(EncARMLeft);
			updateRicencoder(EncARMRight);
		}

//		printf("EncARMFront: %d\n\r", EncARMFront->adjustedValue);
		printf("Buttons: %d|%d|%d|%d|%d\n\r", ButConLeft->state, ButConRight->state, ButARMBase->state,
				ButARMFrontLeft->state, ButARMFrontRight->state);

//		printf("DriveTrain: %d|%d | %d|%d\n\r", MOTDTFrontLeft->out, MOTDTFrontRight->out,
//				MOTDTBackLeft->out, MOTDTBackRight->out);
//
//		printf("Setpoint: %d|%d, Raw: %d|%d, Adj: %d|%d, Out: %d|%d, Pid: %d|%d\n\r",
//				PidARMLeft->setPoint, PidARMRight->setPoint,
//				EncARMLeft->rawValue, EncARMRight->rawValue,
//				EncARMLeft->adjustedValue, EncARMRight->adjustedValue,
//				MOTARMLeft->out, MOTARMRight->out,
//				PidARMLeft->running, PidARMRight->running);
//
//		printf("Gyro: %d\n\r", gyro->value);
//
//		printf("Power: %dmV\n\r", powerLevelMain());
		delay(20);
	}
}

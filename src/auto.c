/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
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

#define PICKUP -1
#define SKYRISE 1

void armLeft(long timeout);
void armRight(long timeout);
void autoARMHori(int direction, long timeout);
void autoARMVert(int distance, int pow, long timeout);
void autoARMVertT(int pow, long timeout);
void autoARMVH(int direction, int pow, long timeoutARMV, long timeoutARMH);

int team = BLUE;

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {

	autoARMVertT(127, 100);
	autoARMHori(PICKUP, 1000);
	autonomousTask(AUTOCLAW, NULL, 127, NULL);
	delay(750);
	autoARMVert(500, 127, 2000);
	autonomousTask(AUTOCLAW, NULL, 0, NULL);
	autoARMHori(SKYRISE, 3000);
	autoARMVert(-750, -127, 2000);
	autonomousTask(AUTOCLAW, NULL, -127, 750);
//	autoARMVertT(-127, 500);

	autoARMVertT(127, 750);
	autoARMHori(PICKUP, 3000);
	autonomousTask(AUTOCLAW, NULL, 127, NULL);
	delay(500);
	autoARMVertT(127, 2000);
	autonomousTask(AUTOCLAW, NULL, 0, NULL);
	autoARMHori(SKYRISE, 3000);
	autoARMVertT(-127, 1000);
	autonomousTask(AUTOCLAW, NULL, -127, 750);
	autoARMVH(PICKUP, -127, 1250, 1000);

	autoARMVertT(127, 250);
	autoARMHori(PICKUP, 1500);
	autonomousTask(AUTOCLAW, NULL, 127, NULL);
	delay(500);
	autoARMVertT(127, 2000);
	autonomousTask(AUTOCLAW, NULL, 0, NULL);
	autoARMVH(SKYRISE, 127, 3000, 1500);
	autoARMHori(SKYRISE, 1500);
//	autoARMVertT(-127, 1000);
	autonomousTask(AUTOCLAW, NULL, -127, 750);
	autoARMVH(PICKUP, -127, 3250, 3000);

	autonomousTask(AUTOCLAW, NULL, 127, NULL);
	delay(500);
	autoARMVertT(127, 2000);
	autonomousTask(AUTOCLAW, NULL, 0, NULL);
	autoARMVH(SKYRISE, 127, 5500, 1500);
	autoARMHori(SKYRISE, 1500);
//	autoARMVertT(-127, 1000);
	autonomousTask(AUTOCLAW, NULL, -127, 750);
	autoARMVH(PICKUP, -127, 5000, 3000);
//---------------------------------------------------------------------------------------------
//	autoARMVert(10, 127, 1000);
//	autoARMHori(PICKUP, 2000);
//	autonomousTask(AUTOCLAW, NULL, 127, NULL);
//	delay(750);
//	autoARMVert(500, 127, 2000);
//	autonomousTask(AUTOCLAW, NULL, 0, NULL);
//	autoARMHori(SKYRISE, 3000);
//	autoARMVert(-500, -127, 2000);
//	autonomousTask(AUTOCLAW, NULL, -127, 750);
//	autoARMVertT(-127, 500);
//
//	autoARMVert(10, 127, 1000); //LOW
//	autoARMHori(PICKUP, 3000);
//	autonomousTask(AUTOCLAW, NULL, 127, NULL);
//	delay(500);
//	autoARMVert(1000, 127, 2000);
//	autonomousTask(AUTOCLAW, NULL, 0, NULL);
//	autoARMHori(SKYRISE, 3000);
//	autoARMVertT(-127, 500);
//	autonomousTask(AUTOCLAW, NULL, -127, 750);
//	autoARMVertT(-127, 500);	//LOWER
//
//	autoARMVert(10, 127, 1000);	//TOO HIGH
//	autoARMHori(PICKUP, 3000);
//	autonomousTask(AUTOCLAW, NULL, 127, NULL);
//	delay(500);
//	autoARMVertT(127, 5000);
//	autonomousTask(AUTOCLAW, NULL, 0, NULL);
//	autoARMHori(SKYRISE, 3000);
//	autoARMVertT(-127, 500);
//	autonomousTask(AUTOCLAW, NULL, -127, 750);
//	autoARMVertT(-127, 2000);
//
//	//starts way too high
//	autoARMVert(10, 127, 1000);
//	autoARMHori(PICKUP, 3000);
//	autonomousTask(AUTOCLAW, NULL, 127, NULL);
//	delay(500);
//	autoARMVertT(127, 9000);
//	autonomousTask(AUTOCLAW, NULL, 0, NULL);
//	autoARMHori(SKYRISE, 3000);
//	autoARMVertT(-127, 500);
//	autonomousTask(AUTOCLAW, NULL, -127, 750);
//	autoARMVertT(-127, 5000);
}

void armLeft(long timeout) {
	long startTime = millis();
	while(millis() < startTime + timeout) {
		MOTConveyor->out = -127;
		MOTARMFront->out = -127;
		delay(20);
	}
	MOTConveyor->out = 0;
	MOTARMFront->out = 0;
}

void armRight(long timeout) {
	long startTime = millis();
	while(millis() < startTime + timeout) {
		MOTConveyor->out = 127;
		MOTARMFront->out = 127;
		delay(20);
	}
	MOTConveyor->out = 0;
	MOTARMFront->out = 0;
}

void autoARMHori(int direction, long timeout) {
	if(direction * team > 0) {
		armRight(timeout);
	}
	else {
		armLeft(timeout);
	}
}

void autoARMVert(int distance, int pow, long timeout) {
	long startTime = millis();
	int currentEnc[2] = {EncARMLeft->adjustedValue, EncARMRight->adjustedValue};
	int target[2] = {currentEnc[0] + distance, currentEnc[1] + distance};

	PidARMLeft->running = 0;
	PidARMRight->running = 0;
	if(distance > 0) {
		while (currentEnc[0] < target[0] && currentEnc[1] < target[1] && millis() < startTime + timeout) {
			MOTARMLeft->out = pow;
			MOTARMRight->out = pow;
			delay(20);
		}
	}
	else {
		while (currentEnc[0] > target[0] && currentEnc[1] > target[1] && millis() < startTime + timeout) {
			MOTARMLeft->out = pow;
			MOTARMRight->out = pow;
			delay(20);
		}
	}
	PidARMLeft->running = 1;
	PidARMRight->running = 1;
	PidARMLeft->setPoint = EncARMLeft->adjustedValue + 60;
	PidARMRight->setPoint = EncARMRight->adjustedValue + 60;
}

void autoARMVertT(int pow, long timeout) {
	long startTime = millis();

	PidARMLeft->running = 0;
	PidARMRight->running = 0;
	while (millis() < startTime + timeout) {
		MOTARMLeft->out = pow;
		MOTARMRight->out = pow;
		delay(20);
	}
	PidARMLeft->running = 1;
	PidARMRight->running = 1;
	PidARMLeft->setPoint = EncARMLeft->adjustedValue + 60;
	PidARMRight->setPoint = EncARMRight->adjustedValue + 60;
}

void autoARMVH(int direction, int pow, long timeoutARMV, long timeoutARMH) {
	long startTime = millis();

	PidARMLeft->running = 0;
	PidARMRight->running = 0;
	while (millis() < startTime + timeoutARMV) {
		MOTARMLeft->out = pow;
		MOTARMRight->out = pow;
		if(direction * team > 0) {
			if(millis() < startTime + timeoutARMH) {
				MOTConveyor->out = 127;
				MOTARMFront->out = 127;
			}
			else {
				MOTConveyor->out = 0;
				MOTARMFront->out = 0;
			}
		}
		else {
			if(millis() < startTime + timeoutARMH) {
				MOTConveyor->out = -127;
				MOTARMFront->out = -127;
			}
			else {
				MOTConveyor->out = 0;
				MOTARMFront->out = 0;
			}
		}
		delay(20);
	}
	PidARMLeft->running = 1;
	PidARMRight->running = 1;
	PidARMLeft->setPoint = EncARMLeft->adjustedValue + 60;
	PidARMRight->setPoint = EncARMRight->adjustedValue + 60;
}

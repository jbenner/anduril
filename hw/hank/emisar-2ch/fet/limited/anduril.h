// Emisar 2-channel generic (plus FET) config options for Anduril (based on Noctigon K9.3)
// Copyright (C) 2021-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "hank/emisar-2ch/fet/hwdef.h"
#include "hank/anduril.h"

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS
// the aux LEDs are front-facing, so turn them off while main LEDs are on
// it also has an independent LED in the button
#define USE_BUTTON_LED
// TODO: the whole "indicator LED" thing needs to be refactored into
//       "aux LED(s)" and "button LED(s)" since they work a bit differently
// enabling this option breaks the button LED on D4v2.5
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif

// channel modes...
// CM_CH1, CM_CH2, CM_BOTH, CM_BLEND, CM_AUTO
// enable max brightness out of the box
#define DEFAULT_CHANNEL_MODE           CM_BOTH

#define USE_CONFIG_COLORS

// blink numbers on the main LEDs by default (but allow user to change it)
#define DEFAULT_BLINK_CHANNEL  CM_BOTH

#define POLICE_COLOR_STROBE_CH1        CM_CH1
#define POLICE_COLOR_STROBE_CH2        CM_CH2

// how much to increase total brightness at middle tint
// (0 = 100% brightness, 64 = 200% brightness)
#define TINT_RAMPING_CORRECTION 0  // none, linear regulator doesn't need it


// channel 1 / main LEDs (w/ DD FET)
//   output: unknown, 1750 lm?
//   FET: unknown, 3000 lm?
// channel 2
//   output: unknown, 1750 lm?
// combined: 4000 to 5000 lm?
#define RAMP_SIZE 150

// linear+FET ramp: maxreg at 140/150
// level_calc.py 5.01 2 150 7135 1 0.1 1924 FET 1 10 2600 --pwm dyn:68:4096:255:3 --clock 8:16:0
// linear segment
#define PWM1_LEVELS 1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,7,7,7,7,8,8,8,9,9,9,10,10,11,12,13,13,14,15,16,17,17,18,19,20,21,22,23,25,26,27,28,30,31,33,34,36,37,39,41,43,44,46,48,50,53,55,57,60,62,65,67,70,73,76,79,82,85,88,92,95,99,103,106,110,114,119,123,127,132,137,142,147,152,157,162,168,174,179,185,192,198,204,211,218,225,232,240,247,255,255,255,255,255,255,255,255,255,255,255
// DD FET segment
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,20,44,68,93,118,144,171,198,226,255
// PWM TOPS values
#define PWM3_LEVELS 4096,3831,3570,3314,3063,2817,2577,2342,2115,1894,1682,1477,1281,2237,2005,1784,1576,1380,1196,1111,1026,1442,1348,1215,1091,976,871,774,1031,942,860,784,714,650,591,538,652,602,555,513,473,437,403,372,343,398,370,345,322,299,278,311,292,273,255,278,261,245,263,247,232,246,231,243,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255

// linear-only ramp
// level_calc.py 3.11 1 150 7135 1 0.1 1750 --pwm dyn:64:4096:255:3 --clock 8:16:0
// level_calc.py 3.11 1 163 7135 1 0.1 1750 --pwm dyn:64:4096:255:3 --clock 8:16:0 - remove last 13 steps from both values, limit ~10%
#define PWM4_LEVELS 1,1,1,1,1,1,1,2,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,11,11,11,12,12,12,13,13,14,14,15,16,17,18,18,19,20,21,21,22,23,24,25,26,27,28,29,30,31,32,33,35,36,37,38,40,41,42,44,45,46,48,49,51,52,54,56,57,59,61,63,64,66,68,70,72,74,76,78,80,82,84,87,89,91,93,96,98,101,103,106,108,111,114,116,119,122,125,127,130,133,136,139,143,146,149,152,156,159,162,166,169,173,176,180,184,188,191,195,199
// PWM_TOPS values for linear-only ramp
#define PWM5_LEVELS 4096,3703,3297,2880,2457,2031,1608,2674,2198,1738,1299,2212,1871,1552,1984,1725,1486,1723,1525,1344,1484,1331,1193,1068,1159,1052,956,868,925,850,781,719,662,611,647,601,559,521,486,454,425,398,373,350,370,349,329,311,294,277,292,277,262,273,260,247,257,245,252,241,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255

#define DEFAULT_LEVEL      75
#define MAX_1x7135         140
#define MAX_Nx7135         MAX_1x7135
#define HALFSPEED_LEVEL    16
#define QUARTERSPEED_LEVEL 8

#define RAMP_SMOOTH_FLOOR  10  // level 1 is unreliable (?)
#define RAMP_SMOOTH_CEIL   140
// 10, 31, 53, [75], 96, 118, [140]
#define RAMP_DISCRETE_FLOOR 10
#define RAMP_DISCRETE_CEIL  RAMP_SMOOTH_CEIL
#define RAMP_DISCRETE_STEPS 7

// safe limit highest regulated power (no FET or turbo)
// 10, 42, [75], 107, 140
#define SIMPLE_UI_FLOOR  RAMP_DISCRETE_FLOOR
#define SIMPLE_UI_CEIL   RAMP_DISCRETE_CEIL
#define SIMPLE_UI_STEPS  5

// stop panicking at ~1500 lm
#define THERM_FASTER_LEVEL 130
#define MIN_THERM_STEPDOWN 65  // should be above highest dyn_pwm level

#define USE_POLICE_COLOR_STROBE_MODE
#undef  TACTICAL_LEVELS
#define TACTICAL_LEVELS 140,30,(RAMP_SIZE+3)  // high, low, police strobe

// use the brightest setting for strobe
#define STROBE_BRIGHTNESS MAX_LEVEL
// slow down party strobe; this driver can't pulse for 1ms or less
#define PARTY_STROBE_ONTIME 2
// TODO: change speed per channel mode
// (the FET is really fast, but the regulator is not)
//#undef PARTY_STROBE_ONTIME

// the default of 26 looks a bit flat, so increase it
#define CANDLE_AMPLITUDE 33

// the power regulator is a bit slow, so push it harder for a quick response from off
#define DEFAULT_JUMP_START_LEVEL 20
#define BLINK_BRIGHTNESS 45
#define BLINK_ONCE_TIME 12  // longer blink, since main LEDs are slow

#define THERM_CAL_OFFSET 5

// don't blink while ramping
#ifdef BLINK_AT_RAMP_MIDDLE
#undef BLINK_AT_RAMP_MIDDLE
#endif


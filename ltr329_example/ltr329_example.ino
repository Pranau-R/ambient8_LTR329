/*
Module: ltr329_example.ino

Function:
        It collects data from the sensor, calculates the light intensity 
        to a diggital format, and then logs it.

Copyright notice:
        This file copyright (C) 2022 by
        MCCI Corporation
        3520 Krums Corners Road
        Ithaca, NY 14850
        An unpublished work. All rights reserved.
        This file is proprietary information, and may not be disclosed or
        copied without the prior permission of MCCI Corporation.

Author:
        Pranau R, MCCI Corporation   June 2022
*/

#include "ambient8.h"

/****************************************************************************\
|
|	VARIABLES
|
\****************************************************************************/

using namespace std;

static ambient8_t ambient8;

static uint8_t status_flag;
static float lux_level;
static float window_factor;
static float IR_factor;

ambient8_cfg_t cfg;

ambient8_cfg_setup (&cfg);
ambient8_init (&ambient8, &cfg);

/****************************************************************************\
|
|   Setup Function.
|
\****************************************************************************/

/*
Name: setup()

Function:
        Initializes device and I2C driver

Definition:
        void setup (void);

Returns:
        Functions returning type void: nothing.
*/

void setup ()
        {
        Serial.begin (115200);
        while (!Serial);

        while(!ambient8_init (&ambient8, &cfg))
                {
                Serial.println ("LTR329 Sensor not connected!\n");
                delay (2000);
                }

        Serial.println("LTR329 Sensor connected successfully!\n");
        delay (2000);

        window_factor = 1;
        IR_factor = 0;
        }

/****************************************************************************\
|
|   Loop Function.
|
\****************************************************************************/

/*
Name:   loop()

Function:
        Performs Lux calculation based on window and IR factor and log results

Definition:
        void loop (void);

Returns:
        Functions returning type void: nothing.
*/

void loop ()
        {
        status_flag = ambient8_get_lux_level (&ambient8,
                &lux_level, window_factor,
                IR_factor
                );
        
        if (status_flag == 0)
                {
                Serial.print("[LTR329] Lux: "); 
                Serial.println(lux_level);
                }
        }
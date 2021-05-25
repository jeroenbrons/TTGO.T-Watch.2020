/****************************************************************************
              my-ttgo-watch.ino

    Tu May 22 21:23:51 2020
    Copyright  2020  Dirk Brosswick
 *  Email: dirk.brosswick@googlemail.com
 ****************************************************************************/
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include "config.h"
#include <Arduino.h>
#include "esp_task_wdt.h"
#include <TTGO.h>

#include "gui/gui.h"

#include "hardware/hardware.h"
#include "hardware/powermgm.h"

#include "app/weather/weather.h"
#include "app/stopwatch/stopwatch_app.h"
#include "app/alarm_clock/alarm_clock.h"
#include "app/IRController/IRController.h"
#include "app/activity/activity.h"
#include "app/calendar/calendar.h"
#include "app/FindPhone/FindPhone.h"
#include "app/NetTools/NetTools.h"
#include "app/ping/ping_app.h"
#include "app/wireless/wireless_app.h"
#include "app/wifimon/wifimon_app.h"

void setup() {
    /**
     * hardware setup
     * 
     * /hardware/hardware.cpp
     */
    Serial.begin(115200);
    log_i("starting t-watch %s, version: " __FIRMWARE__ " core: %d", WATCH_VERSION_NAME, xPortGetCoreID() );
    log_i("Configure watchdog to 30s: %d", esp_task_wdt_init( 30, true ) );
    hardware_setup();
    /**
     * gui setup
     * 
     * /gui/gui.cpp
     */
    gui_setup();
    /**
     * add apps here!!!
     * 
     * inlude your header file
     * and call your app setup
     */
    weather_app_setup();
    stopwatch_app_setup();
    alarm_clock_setup();
    activity_app_setup();
    calendar_app_setup();
    IRController_setup();
	FindPhone_setup();
    NetTools_setup();
    ping_app_setup();
    wireless_app_setup();
    wifimon_app_setup();
    /**
     * post hardware setup
     * 
     * /hardware/hardware.cpp
     */
    hardware_post_setup();
}

void loop() {
    powermgm_loop();
}

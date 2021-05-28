/****************************************************************************
 *   Mo May 23 00:08:51 2021
 *   Copyright  2021  Dirk Sarodnick
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

#ifndef _MQTT_H
    #define _MQTT_H
    
    #include <AsyncMqttClient.h>
    #include "stdint.h"

    /**
     *  @brief setup builtin mqtt, call after first wifi-connection.
     */
    void mqtt_start( const char *id, bool ssl, const char *server, int32_t port, const char *user, const char *pass );

    /**
     *  @brief stop builtin mqtt.
     */
    void mqtt_stop();

    /**
     *  @brief publish online state.
     */
    void mqtt_publish_state();

    /**
     *  @brief publish battery state.
     */
    void mqtt_publish_battery();

    /**
     *  @brief publish version.
     */
    void mqtt_publish_version();

    /**
     *  @brief publish ambient temperature state.
     */
    void mqtt_publish_ambient_temperature();

    /**
     *  @brief publish power temperature state.
     */
    void mqtt_publish_power_temperature();

    /**
     *  @brief publish heap state.
     */
    void mqtt_publish_heap();

    /**
     *  @brief publish psram state.
     */
    void mqtt_publish_psram();

    /**
     *  @brief publish sketch state.
     */
    void mqtt_publish_sketch();

    /**
     *  @brief get connection state.
     */
    bool mqtt_get_connected();
    
    /**
     *  @brief get mqtt client for raw handling.
     */
    AsyncMqttClient mqtt_get_client();

#endif // _MQTT_H
/****************************************************************************
 *   Tu May 22 21:23:51 2020
 *   Copyright  2020  Dirk Brosswick
 *   Email: dirk.brosswick@googlemail.com
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
#include "wifictlconfig.h"
#ifdef ENABLE_WEBSERVER
    #include "utils/webserver/webserver.h"
#endif
#ifdef ENABLE_FTPSERVER
    #include "utils/ftpserver/ftpserver.h"
#endif
#ifdef ENABLE_MQTT
    #include "utils/mqtt/mqtt.h"
#endif
#include "utils/alloc.h"

wifictl_config_t::wifictl_config_t() : BaseJsonConfig( WIFICTL_JSON_CONFIG_FILE ) {}

bool wifictl_config_t::onSave(JsonDocument& doc) {
    /*
     * save config structure into json file
     */
    doc["autoon"] = autoon;
    doc["enable_on_standby"] = enable_on_standby;
    doc["hostname"] = hostname;

    #ifdef ENABLE_WEBSERVER
        doc["webserver"] = webserver;
    #endif
    #ifdef ENABLE_FTPSERVER
        doc["ftpserver"] = ftpserver;
        doc["ftpuser"] = ftpuser;
        doc["ftppass"] = ftppass;
    #endif
    #ifdef ENABLE_MQTT
        doc["mqtt"] = mqtt;
        doc["mqttssl"] = mqttssl;
        doc["mqttserver"] = mqttserver;
        doc["mqttport"] = mqttport;
        doc["mqttuser"] = mqttuser;
        doc["mqttpass"] = mqttpass;
    #endif
    for ( int i = 0 ; i < NETWORKLIST_ENTRYS ; i++ ) {
        doc["networklist"][ i ]["ssid"] = networklist[ i ].ssid;
        doc["networklist"][ i ]["psk"] = networklist[ i ].password;
    }

    return true;
}

bool wifictl_config_t::onLoad(JsonDocument& doc) {
    /*
     * allocate networklist if needed
     */
    if ( networklist == NULL ) {
        networklist = ( wifictl_networklist* )CALLOC( sizeof( wifictl_networklist ) * NETWORKLIST_ENTRYS, 1 );
        if( !networklist ) {
            log_e("wifictl_networklist calloc faild");
            while(true);
        }
    }
    /*
     * clean networklist
     */
    for ( int entry = 0 ; entry < NETWORKLIST_ENTRYS ; entry++ ) {
      networklist[ entry ].ssid[ 0 ] = '\0';
      networklist[ entry ].password[ 0 ] = '\0';
    }
    /*
     * read values from json
     */
    autoon = doc["autoon"] | true;
    enable_on_standby = doc["enable_on_standby"] | false;
    if ( doc["hostname"] ) {
        strlcpy( hostname, doc["hostname"], sizeof( hostname ) );
    }

    #ifdef ENABLE_WEBSERVER
        webserver = doc["webserver"] | false;
    #endif

    #ifdef ENABLE_FTPSERVER
        ftpserver = doc["ftpserver"] | false;
        if ( doc["ftpuser"] ) {
            strlcpy( ftpuser, doc["ftpuser"], sizeof( ftpuser ) );
        }
        else {
            strlcpy( ftpuser, FTPSERVER_USER, sizeof( ftpuser ) );
        }
        if ( doc["ftppass"] ) {
            strlcpy( ftppass, doc["ftppass"], sizeof( ftppass ) );
        }
        else {
            strlcpy( ftppass, FTPSERVER_PASSWORD, sizeof( ftppass ) );
        }
    #endif

    #ifdef ENABLE_MQTT
        mqtt = doc["mqtt"] | false;
        mqttssl = doc["mqttssl"] | false;
        if ( doc["mqttserver"] ) {
            strlcpy( mqttserver, doc["mqttserver"], sizeof( mqttserver ) );
        }
        mqttport = doc["mqttport"] | 1883;
        if ( doc["mqttuser"] ) {
            strlcpy( mqttuser, doc["mqttuser"], sizeof( mqttuser ) );
        }
        if ( doc["mqttpass"] ) {
            strlcpy( mqttpass, doc["mqttpass"], sizeof( mqttpass ) );
        }
    #endif

    for ( int i = 0 ; i < NETWORKLIST_ENTRYS ; i++ ) {
        if ( doc["networklist"][ i ]["ssid"] && doc["networklist"][ i ]["psk"] ) {
            strlcpy( networklist[ i ].ssid    , doc["networklist"][ i ]["ssid"], sizeof( networklist[ i ].ssid ) );
            strlcpy( networklist[ i ].password, doc["networklist"][ i ]["psk"], sizeof( networklist[ i ].password ) );
        }
    }

    return true;
}

bool wifictl_config_t::onDefault( void ) {
    /*
     * allocate networklist if needed
     */
    if ( networklist == NULL ) {
        networklist = ( wifictl_networklist* )CALLOC( sizeof( wifictl_networklist ) * NETWORKLIST_ENTRYS, 1 );
        if( !networklist ) {
            log_e("wifictl_networklist calloc faild");
            while(true);
        }
    }
    /*
     * clean networklist
     */
    for ( int entry = 0 ; entry < NETWORKLIST_ENTRYS ; entry++ ) {
      networklist[ entry ].ssid[ 0 ] = '\0';
      networklist[ entry ].password[ 0 ] = '\0';
    }

    /*
     * read values from json
     */
    autoon = true;
    enable_on_standby = false;
    strlcpy( hostname, "", sizeof( hostname ) );

    #ifdef ENABLE_WEBSERVER
        webserver = false;
    #endif

    #ifdef ENABLE_FTPSERVER
        ftpserver = false;
        strlcpy( ftpuser, FTPSERVER_USER, sizeof( ftpuser ) );
        strlcpy( ftppass, FTPSERVER_PASSWORD, sizeof( ftppass ) );
    #endif

    #ifdef ENABLE_MQTT
        mqtt = false;
        mqttssl = false;
        strlcpy( mqttserver, "", sizeof( mqttserver ) );
        mqttport = 1883;
        strlcpy( mqttuser, "", sizeof( mqttuser ) );
        strlcpy( mqttpass, "", sizeof( mqttpass ) );
    #endif

    return( true );
}
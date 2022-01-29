#include "AusExOutputPlugin.h"

AuxExSensorIO::AuxExSensorIO() {}

//void AuxExSensorIO::SetIO(uint8_t type, OutputChannel outputChannel, format_type_t format=FORMAT_TYPE_PLAIN_TEXT)
void AuxExSensorIO::SetIO(uint8_t type, OutputChannel outputChannel, format_type_t format)
{
    channelType = type;
    formatType = format;
    channel = outputChannel;
#ifdef __USE_MQTT_CLIENT__
    size = 0;
#endif /* __USE_MQTT_CLIENT__ */
}

void AuxExSensorIO::SetLogParam(String defaultHostName, String defaultAppName) {
    hostName = defaultHostName;
    appName  = defaultAppName;
}

#ifdef __USE_RTC__
void AuxExSensorIO::SetRtc(RTC_Unified *rtcObject) {
    rtc = rtcObject;
}
#endif /* __USE_RTC__ */

#ifdef __USE_HTTP_CLIENT__
void AuxExSensorIO::SetHttpPostParam(String url_Path, String typeString){
    contentType = typeString;
    urlPath = url_Path;
}
#endif /* __USE_HTTP_CLIENT__ */

#ifdef __USE_MQTT_CLIENT__
void AuxExSensorIO::SetMqttTopic(char * t){
    topic=t;
}

void AuxExSensorIO::SetMessageParam(unsigned long s, bool r, uint8_t q, bool d) {
    size = s;
    retain = r;
    qos = q;
    dup = d;
}
#endif /* __USE_MQTT_CLIENT__ */

bool AuxExSensorIO::InfoOutputJson(sensor_t sensor) {
    switch(sensor.type){
        case SENSOR_TYPE_ACCELEROMETER:
        case SENSOR_TYPE_MAGNETIC_FIELD:
        case SENSOR_TYPE_ORIENTATION:
        case SENSOR_TYPE_GYROSCOPE:
        case SENSOR_TYPE_LIGHT:
        case SENSOR_TYPE_PRESSURE:
        case SENSOR_TYPE_PROXIMITY:
        case SENSOR_TYPE_GRAVITY:
        case SENSOR_TYPE_LINEAR_ACCELERATION:
        case SENSOR_TYPE_ROTATION_VECTOR:
        case SENSOR_TYPE_RELATIVE_HUMIDITY:
        case SENSOR_TYPE_AMBIENT_TEMPERATURE:
        case SENSOR_TYPE_VOLTAGE:
        case SENSOR_TYPE_CURRENT:
        case SENSOR_TYPE_COLOR:
        case SENSOR_TYPE_SIMPLE:
        case SENSOR_TYPE_ANGLE:
        case SENSOR_TYPE_1AXIS_GYRO:
        case SENSOR_TYPE_DISTANCE:
        case SENSOR_TYPE_LARGE_INT:
        case SENSOR_TYPE_DUST:
        case SENSOR_TYPE_IRREMOTE:
        case SENSOR_TYPE_POSITION:
        case SENSOR_TYPE_DATE:
        case SENSOR_TYPE_SPEED_KNOT:
        case SENSOR_TYPE_SIMPLE_ANALOG:
            break;
        default:
            return false;
    }
    switch(channelType) {
#ifdef __USE_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SERIAL :
            channel.serial->println(F("{"));
            channel.serial->print  (F("\"type\": "));
	        channel.serial->print  (sensor.type);
	        channel.serial->println(F(","));
            channel.serial->print  (F("\"name\": \"")); channel.serial->print(sensor.name);channel.serial->println(F("\","));
            channel.serial->print  (F("\"version\": ")); channel.serial->print(sensor.version);channel.serial->println(F(","));
            channel.serial->print  (F("\"id\":   ")); channel.serial->print(sensor.sensor_id);channel.serial->println(F(","));
            channel.serial->print  (F("\"max_value\":   ")); channel.serial->print(sensor.max_value);channel.serial->println(F(","));
            channel.serial->print  (F("\"min_value\":   ")); channel.serial->print(sensor.min_value);channel.serial->println(F(","));
            channel.serial->print  (F("\"resolution\":  ")); channel.serial->println(sensor.resolution);
            channel.serial->println(F("}"));
            return true;
#endif /* __USE_SERIAL__ */
#ifdef __USE_SOFT_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SOFT_SERIAL :
            channel.sserial->println(F("{"));
            channel.sserial->print  (F("\"type\": "));
	        channel.sserial->print  (sensor.type);
	        channel.sserial->println(F(","));
            channel.sserial->print  (F("\"name\": \"")); channel.sserial->print(sensor.name);channel.sserial->println(F("\","));
            channel.sserial->print  (F("\"version\": ")); channel.sserial->print(sensor.version);channel.sserial->println(F(","));
            channel.sserial->print  (F("\"id\":   ")); channel.sserial->print(sensor.sensor_id);channel.sserial->println(F(","));
            channel.sserial->print  (F("\"max_value\":   ")); channel.sserial->print(sensor.max_value);channel.sserial->println(F(","));
            channel.sserial->print  (F("\"min_value\":   ")); channel.sserial->print(sensor.min_value);channel.sserial->println(F(","));
            channel.sserial->print  (F("\"resolution\":  ")); channel.sserial->println(sensor.resolution);
            channel.sserial->println(F("}"));
            return true;
#endif /* __USE_SOFT_SERIAL__ */
#ifdef __USE_SD__
        case AUSEX_OUTPUT_CHANNEL_FILE :
            channel.file->println(F("{"));
            channel.file->print  (F("\"type\": "));
	        channel.file->print  (sensor.type);
	        channel.file->println(F(","));
            channel.file->print  (F("\"name\": \"")); channel.file->print(sensor.name);channel.file->println(F("\","));
            channel.file->print  (F("\"version\": ")); channel.file->print(sensor.version);channel.file->println(F(","));
            channel.file->print  (F("\"id\":   ")); channel.file->print(sensor.sensor_id);channel.file->println(F(","));
            channel.file->print  (F("\"max_value\":   ")); channel.file->print(sensor.max_value);channel.file->println(F(","));
            channel.file->print  (F("\"min_value\":   ")); channel.file->print(sensor.min_value);channel.file->println(F(","));
            channel.file->print  (F("\"resolution\":  ")); channel.file->println(sensor.resolution);
            channel.file->println(F("}"));
            return true;
#endif /* __USE_SD__ */
#ifdef __USE_ETHERNET_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_ETHERNET_CLIENT :
            channel.client->println(F("{"));
            channel.client->print  (F("\"type\": "));
	        channel.client->print  (sensor.type);
	        channel.client->println(F(","));
            channel.client->print  (F("\"name\": \"")); channel.client->print(sensor.name);channel.client->println(F("\","));
            channel.client->print  (F("\"version\": ")); channel.client->print(sensor.version);channel.client->println(F(","));
            channel.client->print  (F("\"id\":   ")); channel.client->print(sensor.sensor_id);channel.client->println(F(","));
            channel.client->print  (F("\"max_value\":   ")); channel.client->print(sensor.max_value);channel.client->println(F(","));
            channel.client->print  (F("\"min_value\":   ")); channel.client->print(sensor.min_value);channel.client->println(F(","));
            channel.client->print  (F("\"resolution\":  ")); channel.client->println(sensor.resolution);
            channel.client->println(F("}"));
            return true;
#endif /* __USE_ETHERNET_CLIENT__ */
#ifdef __USE_WIFI_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_WIFI_CLIENT :
            channel.wifi_client->println(F("{"));
            channel.wifi_client->print  (F("\"type\": "));
	        channel.wifi_client->print  (sensor.type);
	        channel.wifi_client->println(F(","));
            channel.wifi_client->print  (F("\"name\": \"")); channel.wifi_client->print(sensor.name);channel.wifi_client->println(F("\","));
            channel.wifi_client->print  (F("\"version\": ")); channel.wifi_client->print(sensor.version);channel.wifi_client->println(F(","));
            channel.wifi_client->print  (F("\"id\":   ")); channel.wifi_client->print(sensor.sensor_id);channel.wifi_client->println(F(","));
            channel.wifi_client->print  (F("\"max_value\":   ")); channel.wifi_client->print(sensor.max_value);channel.wifi_client->println(F(","));
            channel.wifi_client->print  (F("\"min_value\":   ")); channel.wifi_client->print(sensor.min_value);channel.wifi_client->println(F(","));
            channel.wifi_client->print  (F("\"resolution\":  ")); channel.wifi_client->println(sensor.resolution);
            channel.wifi_client->println(F("}"));
            return true;
#endif /* __USE_WIFI_CLIENT__ */
#ifdef __USE_HTTP_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_HTTP_CLIENT :
            String workString="{\n\"type\": "+String(sensor.type)+",\n"
                +"\"name\": \""+String(sensor.name)+"\",\n"
                +"\"version\": "+String(sensor.version)+"\",\n"
                +"\"id\":   "+String(sensor.sensor_id)+"\",\n"
                +"\"max_value\":   "+String(sensor.max_value)+"\",\n"
                +"\"min_value\":   "+String(sensor.min_value)+"\",\n"
                +"\"resolution\":  "+String(sensor.resolution)+"\"\n"
                +"}\n";
            channel.httpClient->post(urlPath, contentType, workString);
            return true;
#endif /* __USE_HTTP_CLIENT__ */
#ifdef __USE_MQTT_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_MQTT_CLIENT :
            if (size==0) {
                channel.mqttClient->beginMessage(topic);
            } else {
                channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
            }
            channel.mqttClient->println(F("{"));
            channel.mqttClient->print  (F("\"type\": "));
	        channel.mqttClient->print  (sensor.type);
	        channel.mqttClient->println(F(","));
            channel.mqttClient->print  (F("\"name\": \"")); channel.mqttClient->print(sensor.name);channel.mqttClient->println(F("\","));
            channel.mqttClient->print  (F("\"version\": ")); channel.mqttClient->print(sensor.version);channel.mqttClient->println(F(","));
            channel.mqttClient->print  (F("\"id\":   ")); channel.mqttClient->print(sensor.sensor_id);channel.mqttClient->println(F(","));
            channel.mqttClient->print  (F("\"max_value\":   ")); channel.mqttClient->print(sensor.max_value);channel.mqttClient->println(F(","));
            channel.mqttClient->print  (F("\"min_value\":   ")); channel.mqttClient->print(sensor.min_value);channel.mqttClient->println(F(","));
            channel.mqttClient->print  (F("\"resolution\":  ")); channel.mqttClient->println(sensor.resolution);
            channel.mqttClient->println(F("}"));
            channel.mqttClient->endMessage();
            return true;
#endif /* __USE_MQTT_CLIENT__ */
        //default:
            //return false;
    }
    return false;
}

bool AuxExSensorIO::InfoOutputPlain(sensor_t sensor) {
    switch(channelType) {
#ifdef __USE_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SERIAL :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.serial->println(F("Temperature Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("C"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("C"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("C"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.serial->println(F("Humidity Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("%"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("%"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("%"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                channel.serial->println(F("Accelerometer"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("m/s^2"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("m/s^2"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                channel.serial->println(F("Magnetic Field Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("microT"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("microT"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("microT"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                channel.serial->println(F("Gyroscope"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("Rad/s"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("Rad/s"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("Rad/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                channel.serial->println(F("Light Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("lux"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("lux"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("lux"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                channel.serial->println(F("Barometric Pressure Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("hPa"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("hPa"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("hPa"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                channel.serial->println(F("Proximity Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                channel.serial->println(F("Gravity Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                channel.serial->println(F("Linear Acceleration Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("m/s^2"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("m/s^2"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                channel.serial->println(F("Rotation Vector Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                channel.serial->println(F("Voltage Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("V"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("V"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("V"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                channel.serial->println(F("Current Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("mA"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("mA"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("mA"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                channel.serial->println(F("Color Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                channel.serial->println(F("Simple Digital Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                channel.serial->println(F("Angle Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("deg"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("deg"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                channel.serial->println(F("1 axis Gyro Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("deg/s"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("deg/s"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("deg/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                channel.serial->println(F("Distance Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("cm"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("cm"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("cm"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                channel.serial->println(F("Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                channel.serial->println(F("Dust Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("pcs/0.01cf"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("pcs/0.01cf"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("pcs/0.01cf"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                channel.serial->println(F("IR Remote Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                channel.serial->println(F("Position Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("[deg|m]"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("[deg|m]"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("[deg|m]"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                channel.serial->println(F("Clock"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                channel.serial->println(F("Speed Sensor(knot)"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("knot"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("knot"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("knot"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                channel.serial->println(F("Orientation Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("deg"));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("deg"));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                channel.serial->println(F("Simple Analog Sensor"));
                channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            return false;
#endif /* __USE_SERIAL__ */
#ifdef __USE_SOFT_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SOFT_SERIAL :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.sserial->println(F("Temperature Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("C"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("C"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("C"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.sserial->println(F("Humidity Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("%"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("%"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("%"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                channel.sserial->println(F("Accelerometer"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("m/s^2"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("m/s^2"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                channel.sserial->println(F("Magnetic Field Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("microT"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("microT"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("microT"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                channel.sserial->println(F("Gyroscope"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("Rad/s"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("Rad/s"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("Rad/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                channel.sserial->println(F("Light Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("lux"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("lux"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("lux"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                channel.sserial->println(F("Barometric Pressure Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("hPa"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("hPa"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("hPa"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                channel.sserial->println(F("Proximity Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                channel.sserial->println(F("Gravity Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                channel.sserial->println(F("Linear Acceleration Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("m/s^2"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("m/s^2"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                channel.sserial->println(F("Rotation Vector Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                channel.sserial->println(F("Voltage Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("V"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("V"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("V"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                channel.sserial->println(F("Current Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("mA"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("mA"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("mA"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                channel.sserial->println(F("Color Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                channel.sserial->println(F("Simple Digital Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                channel.sserial->println(F("Angle Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("deg"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("deg"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                channel.sserial->println(F("1 axis Gyro Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("deg/s"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("deg/s"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("deg/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                channel.sserial->println(F("Distance Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("cm"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("cm"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("cm"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                channel.sserial->println(F("Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                channel.sserial->println(F("Dust Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("pcs/0.01cf"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("pcs/0.01cf"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("pcs/0.01cf"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                channel.sserial->println(F("IR Remote Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                channel.sserial->println(F("Position Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("[deg|m]"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("[deg|m]"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("[deg|m]"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                channel.sserial->println(F("Clock"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                channel.sserial->println(F("Speed Sensor(knot)"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("knot"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("knot"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("knot"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                channel.sserial->println(F("Orientation Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("deg"));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("deg"));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                channel.sserial->println(F("Simple Analog Sensor"));
                channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            return false;
#endif /* __USE_SOFT_SERIAL__ */
#ifdef __USE_SD__
        case AUSEX_OUTPUT_CHANNEL_FILE :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.file->println(F("Temperature Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("C"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("C"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("C"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.file->println(F("Humidity Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("%"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("%"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("%"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                channel.file->println(F("Accelerometer"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("m/s^2"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("m/s^2"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                channel.file->println(F("Magnetic Field Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("microT"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("microT"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("microT"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                channel.file->println(F("Gyroscope"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("Rad/s"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("Rad/s"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("Rad/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                channel.file->println(F("Light Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("lux"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("lux"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("lux"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                channel.file->println(F("Barometric Pressure Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("hPa"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("hPa"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("hPa"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                channel.file->println(F("Proximity Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                channel.file->println(F("Gravity Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                channel.file->println(F("Linear Acceleration Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("m/s^2"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("m/s^2"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                channel.file->println(F("Rotation Vector Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                channel.file->println(F("Voltage Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("V"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("V"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("V"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                channel.file->println(F("Current Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("mA"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("mA"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("mA"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                channel.file->println(F("Color Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                channel.file->println(F("Simple Digital Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                channel.file->println(F("Angle Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("deg"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("deg"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                channel.file->println(F("1 axis Gyro Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("deg/s"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("deg/s"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("deg/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                channel.file->println(F("Distance Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("cm"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("cm"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("cm"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                channel.file->println(F("Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                channel.file->println(F("Dust Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("pcs/0.01cf"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("pcs/0.01cf"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("pcs/0.01cf"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                channel.file->println(F("IR Remote Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                channel.file->println(F("Position Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("[deg|m]"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("[deg|m]"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("[deg|m]"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                channel.file->println(F("Clock"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                channel.file->println(F("Speed Sensor(knot)"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("knot"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("knot"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("knot"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                channel.file->println(F("Orientation Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("deg"));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("deg"));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                channel.file->println(F("Simple Analog Sensor"));
                channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            return false;
#endif /* __USE_SD__ */
#ifdef __USE_ETHERNET_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_ETHERNET_CLIENT :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.client->println(F("Temperature Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("C"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("C"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("C"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.client->println(F("Humidity Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("%"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("%"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("%"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                channel.client->println(F("Accelerometer"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("m/s^2"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("m/s^2"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                channel.client->println(F("Magnetic Field Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("microT"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("microT"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("microT"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                channel.client->println(F("Gyroscope"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("Rad/s"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("Rad/s"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("Rad/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                channel.client->println(F("Light Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("lux"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("lux"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("lux"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                channel.client->println(F("Barometric Pressure Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("hPa"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("hPa"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("hPa"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                channel.client->println(F("Proximity Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                channel.client->println(F("Gravity Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                channel.client->println(F("Linear Acceleration Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("m/s^2"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("m/s^2"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                channel.client->println(F("Rotation Vector Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                channel.client->println(F("Voltage Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("V"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("V"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("V"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                channel.client->println(F("Current Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("mA"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("mA"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("mA"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                channel.client->println(F("Color Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                channel.client->println(F("Simple Digital Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                channel.client->println(F("Angle Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("deg"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("deg"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                channel.client->println(F("1 axis Gyro Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("deg/s"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("deg/s"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("deg/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                channel.client->println(F("Distance Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("cm"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("cm"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("cm"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                channel.client->println(F("Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                channel.client->println(F("Dust Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("pcs/0.01cf"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("pcs/0.01cf"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("pcs/0.01cf"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                channel.client->println(F("IR Remote Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                channel.client->println(F("Position Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("[deg|m]"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("[deg|m]"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("[deg|m]"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                channel.client->println(F("Clock"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                channel.client->println(F("Speed Sensor (knot)"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("knot"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("knot"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("knot"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                channel.client->println(F("Orientation Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("deg"));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("deg"));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                channel.client->println(F("Simple Analog Sensor"));
                channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            return false;
#endif /* __USE_ETHERNET_CLIENT__ */
#ifdef __USE_WIFI_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_WIFI_CLIENT :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.wifi_client->println(F("Temperature Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("C"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("C"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("C"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.wifi_client->println(F("Humidity Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("%"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("%"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("%"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                channel.wifi_client->println(F("Accelerometer"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("m/s^2"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("m/s^2"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                channel.wifi_client->println(F("Magnetic Field Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("microT"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("microT"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("microT"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                channel.wifi_client->println(F("Gyroscope"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("Rad/s"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("Rad/s"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("Rad/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                channel.wifi_client->println(F("Light Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("lux"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("lux"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("lux"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                channel.wifi_client->println(F("Barometric Pressure Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("hPa"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("hPa"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("hPa"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                channel.wifi_client->println(F("Proximity Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                channel.wifi_client->println(F("Gravity Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                channel.wifi_client->println(F("Linear Acceleration Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("m/s^2"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("m/s^2"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                channel.wifi_client->println(F("Rotation Vector Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                channel.wifi_client->println(F("Voltage Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("V"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("V"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("V"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                channel.wifi_client->println(F("Current Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("mA"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("mA"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("mA"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                channel.wifi_client->println(F("Color Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                channel.wifi_client->println(F("Simple Digital Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                channel.wifi_client->println(F("Angle Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("deg"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("deg"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                channel.wifi_client->println(F("1 axis Gyro Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("deg/s"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("deg/s"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("deg/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                channel.wifi_client->println(F("Distance Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("cm"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("cm"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("cm"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                channel.wifi_client->println(F("Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                channel.wifi_client->println(F("Dust Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("pcs/0.01cf"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("pcs/0.01cf"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("pcs/0.01cf"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                channel.wifi_client->println(F("IR Remote Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                channel.wifi_client->println(F("Position Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("[deg|m]"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("[deg|m]"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("[deg|m]"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                channel.wifi_client->println(F("Clock"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                channel.wifi_client->println(F("Speed Sensor (knot)"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("knot"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("knot"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("knot"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                channel.wifi_client->println(F("Orientation Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("deg"));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("deg"));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                channel.wifi_client->println(F("Simple Analog Sensor"));
                channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            return false;
#endif /* __USE_WIFI_CLIENT__ */
#ifdef __USE_HTTP_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_HTTP_CLIENT :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                String workString="Temperature Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"C\n"
                    +"Min Value:   "+String(sensor.min_value)+"C\n"
                    +"Resolution:  "+String(sensor.resolution)+"C\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                String workString="Humidity Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"%\n"
                    +"Min Value:   "+String(sensor.min_value)+"%\n"
                    +"Resolution:  "+String(sensor.resolution)+"%\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                String workString="Accelerometer\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"m/s^2\n"
                    +"Min Value:   "+String(sensor.min_value)+"m/s^2\n"
                    +"Resolution:  "+String(sensor.resolution)+"m/s^2\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                String workString="Magnetic Field Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"microT\n"
                    +"Min Value:   "+String(sensor.min_value)+"microT\n"
                    +"Resolution:  "+String(sensor.resolution)+"microT\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                String workString="Gyroscope\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"Rad/s\n"
                    +"Min Value:   "+String(sensor.min_value)+"Rad/s\n"
                    +"Resolution:  "+String(sensor.resolution)+"Rad/s\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                String workString="Light Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"lux\n"
                    +"Min Value:   "+String(sensor.min_value)+"lux\n"
                    +"Resolution:  "+String(sensor.resolution)+"lux\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                String workString="Barometric Pressure Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"hPa\n"
                    +"Min Value:   "+String(sensor.min_value)+"hPa\n"
                    +"Resolution:  "+String(sensor.resolution)+"hPa\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                String workString="Proximity Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"\n"
                    +"Min Value:   "+String(sensor.min_value)+"\n"
                    +"Resolution:  "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                String workString="Gravity Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"\n"
                    +"Min Value:   "+String(sensor.min_value)+"\n"
                    +"Resolution:  "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                String workString="Linear Acceleration Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"m/s^2\n"
                    +"Min Value:   "+String(sensor.min_value)+"m/s^2\n"
                    +"Resolution:  "+String(sensor.resolution)+"m/s^2\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                String workString="Rotation Vector Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"\n"
                    +"Min Value:   "+String(sensor.min_value)+"\n"
                    +"Resolution:  "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                String workString="Voltage Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"V\n"
                    +"Min Value:   "+String(sensor.min_value)+"V\n"
                    +"Resolution:  "+String(sensor.resolution)+"V\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                String workString="Current Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"mA\n"
                    +"Min Value:   "+String(sensor.min_value)+"mA\n"
                    +"Resolution:  "+String(sensor.resolution)+"mA\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                String workString="Color Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"\n"
                    +"Min Value:   "+String(sensor.min_value)+"\n"
                    +"Resolution:  "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                String workString="Simple Digital Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"\n"
                    +"Min Value:   "+String(sensor.min_value)+"\n"
                    +"Resolution:  "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                String workString="Angle Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"deg\n"
                    +"Min Value:   "+String(sensor.min_value)+"deg\n"
                    +"Resolution:  "+String(sensor.resolution)+"deg\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                String workString="1 axis Gyro Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"deg/s\n"
                    +"Min Value:   "+String(sensor.min_value)+"deg/s\n"
                    +"Resolution:  "+String(sensor.resolution)+"deg/s\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                String workString="Distance Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"cm\n"
                    +"Min Value:   "+String(sensor.min_value)+"cm\n"
                    +"Resolution:  "+String(sensor.resolution)+"cm\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                String workString="Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"\n"
                    +"Min Value:   "+String(sensor.min_value)+"\n"
                    +"Resolution:  "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                String workString="Dust Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"pcs/0.01cf\n"
                    +"Min Value:   "+String(sensor.min_value)+"pcs/0.01cf\n"
                    +"Resolution:  "+String(sensor.resolution)+"pcs/0.01cf\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                String workString="IR Remote Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"\n"
                    +"Min Value:   "+String(sensor.min_value)+"\n"
                    +"Resolution:  "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                String workString="Position Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"[deg|m]\n"
                    +"Min Value:   "+String(sensor.min_value)+"[deg|m]\n"
                    +"Resolution:  "+String(sensor.resolution)+"[deg|m]\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                String workString="Clock\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"\n"
                    +"Min Value:   "+String(sensor.min_value)+"\n"
                    +"Resolution:  "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                String workString="Speed Sensor(knot)\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"knot\n"
                    +"Min Value:   "+String(sensor.min_value)+"knot\n"
                    +"Resolution:  "+String(sensor.resolution)+"knot\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                String workString="Orientation Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"deg\n"
                    +"Min Value:   "+String(sensor.min_value)+"deg\n"
                    +"Resolution:  "+String(sensor.resolution)+"deg\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                String workString="Simple Analog Sensor\nSensor Type: "+String(sensor.name)+"\n"
                    +"Driver Ver:  "+String(sensor.version)+"\n"
                    +"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +"Max Value:   "+String(sensor.max_value)+"\n"
                    +"Min Value:   "+String(sensor.min_value)+"\n"
                    +"Resolution:  "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            return false;
#endif /* __USE_HTTP_CLIENT__ */
#ifdef __USE_MQTT_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_MQTT_CLIENT :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Temperature Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("C"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("C"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("C"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Humidity Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("%"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("%"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("%"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Accelerometer"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Magnetic Field Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("microT"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("microT"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("microT"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Gyroscope"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("Rad/s"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("Rad/s"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("Rad/s"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Light Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("lux"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("lux"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("lux"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Barometric Pressure Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("hPa"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("hPa"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("hPa"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Proximity Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Gravity Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Linear Acceleration Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Rotation Vector Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Voltage Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("V"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("V"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("V"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Current Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("mA"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("mA"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("mA"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Color Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Simple Digital Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Angle Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("deg"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("deg"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("deg"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("1 axis Gyro Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("deg/s"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("deg/s"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("deg/s"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Distance Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("cm"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("cm"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("cm"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Dust Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("pcs/0.01cf"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("pcs/0.01cf"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("pcs/0.01cf"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("IR Remote Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Position Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("[deg|m]"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("[deg|m]"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("[deg|m]"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Clock"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Speed Sensor (knot)"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("knot"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("knot"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("knot"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Orientation Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("deg"));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("deg"));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("deg"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->println(F("Simple Analog Sensor"));
                channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            return false;
#endif /* __USE_MQTT_CLIENT__ */
        //default:
            //return false;
    }
    return false;
}

bool AuxExSensorIO::InfoOutputSyslog(sensor_t sensor) {
#ifdef __USE_RTC__
    date_t nowTime;
    rtc->getTime(&nowTime);
    String currentTime=String(nowTime.year)+"/"+String(nowTime.month)+"/"+String(nowTime.mday)+" "+rtc->getWday(nowTime.wday)+" "
        + String(nowTime.hour)+":"+String(nowTime.minute)+":"+String(nowTime.second);
#else /* __USE_RTC__ */
    String currentTime=String(millis());
#endif /* __USE_RTC__ */
    switch(channelType) {
#ifdef __USE_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SERIAL :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Temperature Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("C"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("C"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("C"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Humidity Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("%"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("%"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("%"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Accelerometer"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("m/s^2"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("m/s^2"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Magnetic Field Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("microT"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("microT"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("microT"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Gyroscope"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("Rad/s"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("Rad/s"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("Rad/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Light Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("lux"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("lux"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("lux"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Barometric Pressure Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("hPa"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("hPa"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("hPa"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Proximity Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Gravity Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Linear Acceleration Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("m/s^2"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("m/s^2"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Rotation Vector Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Voltage Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("V"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("V"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("V"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Current Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("mA"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("mA"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("mA"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Color Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Simple Digital Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Angle Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("deg"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("deg"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("1 axis Gyro Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("deg/s"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("deg/s"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("deg/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Distance Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("cm"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("cm"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("cm"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Dust Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("pcs/0.01cf"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("pcs/0.01cf"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("pcs/0.01cf"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("IR Remote Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Position Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("[deg|m]"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("[deg|m]"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("[deg|m]"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Clock"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Speed Sensor(knot)"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("knot"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("knot"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("knot"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Orientation Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F("deg"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F("deg"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->println(F("Simple Analog Sensor"));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Sensor Type: ")); channel.serial->println(sensor.name);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Driver Ver:  ")); channel.serial->println(sensor.version);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Unique ID:   ")); channel.serial->println(sensor.sensor_id);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Max Value:   ")); channel.serial->print(sensor.max_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Min Value:   ")); channel.serial->print(sensor.min_value); channel.serial->println(F(""));
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print  (F("Resolution:  ")); channel.serial->print(sensor.resolution); channel.serial->println(F(""));
                return true;
            }
            return false;
#endif /* __USE_SERIAL__ */
#ifdef __USE_SOFT_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SOFT_SERIAL :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Temperature Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("C"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("C"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("C"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Humidity Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("%"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("%"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("%"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Accelerometer"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("m/s^2"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("m/s^2"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Magnetic Field Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("microT"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("microT"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("microT"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Gyroscope"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("Rad/s"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("Rad/s"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("Rad/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Light Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("lux"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("lux"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("lux"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Barometric Pressure Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("hPa"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("hPa"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("hPa"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Proximity Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Gravity Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Linear Acceleration Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("m/s^2"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("m/s^2"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Rotation Vector Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Voltage Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("V"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("V"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("V"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Current Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("mA"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("mA"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("mA"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Color Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Simple Digital Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Angle Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("deg"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("deg"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("1 axis Gyro Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("deg/s"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("deg/s"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("deg/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Distance Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("cm"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("cm"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("cm"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Dust Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("pcs/0.01cf"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("pcs/0.01cf"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("pcs/0.01cf"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("IR Remote Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Position Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("[deg|m]"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("[deg|m]"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("[deg|m]"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Clock"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Speed Sensor(knot)"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("knot"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("knot"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("knot"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Orientation Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F("deg"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F("deg"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->println(F("Simple Analog Sensor"));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Sensor Type: ")); channel.sserial->println(sensor.name);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Driver Ver:  ")); channel.sserial->println(sensor.version);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Unique ID:   ")); channel.sserial->println(sensor.sensor_id);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Max Value:   ")); channel.sserial->print(sensor.max_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Min Value:   ")); channel.sserial->print(sensor.min_value); channel.sserial->println(F(""));
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print  (F("Resolution:  ")); channel.sserial->print(sensor.resolution); channel.sserial->println(F(""));
                return true;
            }
            return false;
#endif /* __USE_SOFT_SERIAL__ */
#ifdef __USE_SD__
        case AUSEX_OUTPUT_CHANNEL_FILE :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Temperature Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("C"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("C"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("C"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Humidity Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("%"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("%"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("%"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Accelerometer"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("m/s^2"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("m/s^2"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Magnetic Field Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("microT"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("microT"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("microT"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Gyroscope"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("Rad/s"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("Rad/s"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("Rad/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Light Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("lux"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("lux"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("lux"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Barometric Pressure Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("hPa"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("hPa"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("hPa"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Proximity Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Gravity Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Linear Acceleration Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("m/s^2"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("m/s^2"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Rotation Vector Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Voltage Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("V"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("V"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("V"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Current Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("mA"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("mA"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("mA"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Color Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Simple Digital Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Angle Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("deg"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("deg"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("1 axis Gyro Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("deg/s"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("deg/s"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("deg/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Distance Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("cm"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("cm"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("cm"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Dust Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("pcs/0.01cf"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("pcs/0.01cf"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("pcs/0.01cf"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("IR Remote Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Position Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("[deg|m]"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("[deg|m]"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("[deg|m]"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Clock"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Speed Sensor(knot)"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("knot"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("knot"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("knot"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Orientation Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F("deg"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F("deg"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->println(F("Simple Analog Sensor"));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Sensor Type: ")); channel.file->println(sensor.name);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Driver Ver:  ")); channel.file->println(sensor.version);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Unique ID:   ")); channel.file->println(sensor.sensor_id);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Max Value:   ")); channel.file->print(sensor.max_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Min Value:   ")); channel.file->print(sensor.min_value); channel.file->println(F(""));
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print  (F("Resolution:  ")); channel.file->print(sensor.resolution); channel.file->println(F(""));
                return true;
            }
            return false;
#endif /* __USE_SD__ */
#ifdef __USE_ETHERNET_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_ETHERNET_CLIENT :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Temperature Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("C"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("C"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("C"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Humidity Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("%"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("%"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("%"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Accelerometer"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("m/s^2"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("m/s^2"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Magnetic Field Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("microT"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("microT"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("microT"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Gyroscope"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("Rad/s"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("Rad/s"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("Rad/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Light Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("lux"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("lux"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("lux"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Barometric Pressure Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("hPa"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("hPa"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("hPa"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Proximity Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Gravity Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Linear Acceleration Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("m/s^2"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("m/s^2"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Rotation Vector Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Voltage Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("V"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("V"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("V"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Current Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("mA"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("mA"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("mA"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Color Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Simple Digital Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Angle Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("deg"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("deg"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("1 axis Gyro Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("deg/s"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("deg/s"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("deg/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Distance Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("cm"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("cm"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("cm"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Dust Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("pcs/0.01cf"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("pcs/0.01cf"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("pcs/0.01cf"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("IR Remote Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Position Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("[deg|m]"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("[deg|m]"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("[deg|m]"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Clock"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Speed Sensor(knot)"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("knot"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("knot"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("knot"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Orientation Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F("deg"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F("deg"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->println(F("Simple Analog Sensor"));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Sensor Type: ")); channel.client->println(sensor.name);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Driver Ver:  ")); channel.client->println(sensor.version);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Unique ID:   ")); channel.client->println(sensor.sensor_id);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Max Value:   ")); channel.client->print(sensor.max_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Min Value:   ")); channel.client->print(sensor.min_value); channel.client->println(F(""));
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print  (F("Resolution:  ")); channel.client->print(sensor.resolution); channel.client->println(F(""));
                return true;
            }
            return false;
#endif /* __USE_ETHERNET_CLIENT__ */
#ifdef __USE_WIFI_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_WIFI_CLIENT :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Temperature Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("C"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("C"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("C"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Humidity Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("%"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("%"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("%"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Accelerometer"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("m/s^2"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("m/s^2"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Magnetic Field Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("microT"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("microT"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("microT"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Gyroscope"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("Rad/s"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("Rad/s"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("Rad/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Light Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("lux"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("lux"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("lux"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Barometric Pressure Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("hPa"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("hPa"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("hPa"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Proximity Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Gravity Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Linear Acceleration Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("m/s^2"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("m/s^2"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("m/s^2"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Rotation Vector Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Voltage Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("V"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("V"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("V"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Current Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("mA"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("mA"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("mA"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Color Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Simple Digital Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Angle Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("deg"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("deg"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("1 axis Gyro Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("deg/s"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("deg/s"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("deg/s"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Distance Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("cm"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("cm"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("cm"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Dust Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("pcs/0.01cf"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("pcs/0.01cf"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("pcs/0.01cf"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("IR Remote Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Position Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("[deg|m]"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("[deg|m]"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("[deg|m]"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Clock"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Speed Sensor(knot)"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("knot"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("knot"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("knot"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Orientation Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F("deg"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F("deg"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F("deg"));
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->println(F("Simple Analog Sensor"));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Sensor Type: ")); channel.wifi_client->println(sensor.name);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Driver Ver:  ")); channel.wifi_client->println(sensor.version);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Unique ID:   ")); channel.wifi_client->println(sensor.sensor_id);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Max Value:   ")); channel.wifi_client->print(sensor.max_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Min Value:   ")); channel.wifi_client->print(sensor.min_value); channel.wifi_client->println(F(""));
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print  (F("Resolution:  ")); channel.wifi_client->print(sensor.resolution); channel.wifi_client->println(F(""));
                return true;
            }
            return false;
#endif /* __USE_WIFI_CLIENT__ */
#ifdef __USE_HTTP_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_HTTP_CLIENT :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Temperature Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"C\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"C\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"C\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Humidity Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"%\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"%\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"%\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Accelerometer"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"m/s^2\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"m/s^2\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"m/s^2\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Magnetic Field Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"microT\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"microT\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"microT\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Gyroscope"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"Rad/s\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"Rad/s\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"Rad/s\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Light Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"lux\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"lux\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"lux\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Barometric Pressure Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"hPa\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"hPa\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"hPa\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Proximity Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Gravity Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Linear Acceleration Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"m/s^2\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"m/s^2\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"m/s^2\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Rotation Vector Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Voltage Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"V\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"V\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"V\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Current Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"mA\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"mA\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"mA\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Color Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Simple Digital Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Angle Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"deg\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"deg\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"deg\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"1 axis Gyro Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"deg/s\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"deg/s\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"deg/s\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Distance Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"cm\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"cm\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"cm\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Dust Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"pcs/0.01cf\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"pcs/0.01cf\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"pcs/0.01cf\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"IR Remote Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Position Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"[deg|m]\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"[deg|m]\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"[deg|m]\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Clock"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Speed Sensor(knot)"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"knot\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"knot\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"knot\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Orientation Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"deg\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"deg\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"deg\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                String workString=currentTime+" " + hostName + " " + appName +" : "+"Simple Analog Sensor"+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Sensor Type: "+String(sensor.name)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Driver Ver:  "+String(sensor.version)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Unique ID:   "+String(sensor.sensor_id)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Max Value:   "+String(sensor.max_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Min Value:   "+String(sensor.min_value)+"\n"
                    +currentTime+" " + hostName + " " + appName +" : "+"Resolution:   "+String(sensor.resolution)+"\n";
                channel.httpClient->post(urlPath, contentType, workString);
                return true;
            }
            return false;
#endif /* __USE_HTTP_CLIENT__ */
#ifdef __USE_MQTT_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_MQTT_CLIENT :
            if ( sensor.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Temperature Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("C"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("C"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("C"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Humidity Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("%"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("%"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("%"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ACCELEROMETER ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Accelerometer"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Magnetic Field Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("microT"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("microT"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("microT"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GYROSCOPE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Gyroscope"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("Rad/s"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("Rad/s"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("Rad/s"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LIGHT ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Light Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("lux"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("lux"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("lux"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PRESSURE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Barometric Pressure Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("hPa"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("hPa"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("hPa"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_PROXIMITY ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Proximity Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_GRAVITY ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Gravity Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Linear Acceleration Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("m/s^2"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ROTATION_VECTOR ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Rotation Vector Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_VOLTAGE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Voltage Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("V"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("V"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("V"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_CURRENT ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Current Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("mA"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("mA"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("mA"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_COLOR ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Color Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Simple Digital Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ANGLE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Angle Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("deg"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("deg"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("deg"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_1AXIS_GYRO ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("1 axis Gyro Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("deg/s"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("deg/s"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("deg/s"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DISTANCE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Distance Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("cm"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("cm"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("cm"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_LARGE_INT ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DUST ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Dust Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("pcs/0.01cf"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("pcs/0.01cf"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("pcs/0.01cf"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_IRREMOTE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("IR Remote Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_POSITION ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Position Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("[deg|m]"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("[deg|m]"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("[deg|m]"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_DATE ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Clock"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SPEED_KNOT ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Speed Sensor(knot)"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("knot"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("knot"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("knot"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_ORIENTATION ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Orientation Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F("deg"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F("deg"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F("deg"));
                channel.mqttClient->endMessage();
                return true;
            }
            if ( sensor.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                if (size==0) {
                    channel.mqttClient->beginMessage(topic);
                } else {
                    channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
                }
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->println(F("Simple Analog Sensor"));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Sensor Type: ")); channel.mqttClient->println(sensor.name);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Driver Ver:  ")); channel.mqttClient->println(sensor.version);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Unique ID:   ")); channel.mqttClient->println(sensor.sensor_id);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Max Value:   ")); channel.mqttClient->print(sensor.max_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Min Value:   ")); channel.mqttClient->print(sensor.min_value); channel.mqttClient->println(F(""));
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print  (F("Resolution:  ")); channel.mqttClient->print(sensor.resolution); channel.mqttClient->println(F(""));
                channel.mqttClient->endMessage();
                return true;
            }
            return false;
#endif /* __USE_MQTT_CLIENT__ */
        //default:
            //return false;
    }
    return false;
}



bool AuxExSensorIO::InfoOutput(sensor_t sensor) {
    switch(formatType) {
        case FORMAT_TYPE_PLAIN_TEXT:
            return InfoOutputPlain(sensor);
        case FORMAT_TYPE_JSON:
            return InfoOutputJson(sensor);
        case FORMAT_TYPE_SYSLOG:
            return InfoOutputSyslog(sensor);
        default:
            return false;
    }
}


bool AuxExSensorIO::EventOutputJson(sensors_event_t event) {
    switch(event.type){
        case SENSOR_TYPE_ACCELEROMETER:
        case SENSOR_TYPE_MAGNETIC_FIELD:
        case SENSOR_TYPE_ORIENTATION:
        case SENSOR_TYPE_GYROSCOPE:
        case SENSOR_TYPE_LIGHT:
        case SENSOR_TYPE_PRESSURE:
        case SENSOR_TYPE_PROXIMITY:
        case SENSOR_TYPE_GRAVITY:
        case SENSOR_TYPE_LINEAR_ACCELERATION:
        case SENSOR_TYPE_ROTATION_VECTOR:
        case SENSOR_TYPE_RELATIVE_HUMIDITY:
        case SENSOR_TYPE_AMBIENT_TEMPERATURE:
        case SENSOR_TYPE_VOLTAGE:
        case SENSOR_TYPE_CURRENT:
        case SENSOR_TYPE_COLOR:
        case SENSOR_TYPE_SIMPLE:
        case SENSOR_TYPE_ANGLE:
        case SENSOR_TYPE_1AXIS_GYRO:
        case SENSOR_TYPE_DISTANCE:
        case SENSOR_TYPE_LARGE_INT:
        case SENSOR_TYPE_DUST:
        case SENSOR_TYPE_IRREMOTE:
        case SENSOR_TYPE_POSITION:
        case SENSOR_TYPE_DATE:
        case SENSOR_TYPE_SPEED_KNOT:
        case SENSOR_TYPE_SIMPLE_ANALOG:
            break;
        default:
            return false;
    }
    switch(channelType) {
#ifdef __USE_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SERIAL :
            channel.serial->println(F("{"));
            channel.serial->print  (F("\"id\": "));
            channel.serial->print  (event.sensor_id);
            channel.serial->println(F(","));
            channel.serial->print  (F("\"type\": "));
            channel.serial->print  (event.type);
            channel.serial->println(F(","));
            channel.serial->print  (F("\"time\": "));
            channel.serial->print  (event.timestamp);
            channel.serial->println(F(","));
            channel.serial->println(F("\"data\": ["));
            switch(event.type){
                case SENSOR_TYPE_ACCELEROMETER:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"x\": "));
                    channel.serial->print  (event.acceleration.x);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"y\": "));
                    channel.serial->print  (event.acceleration.y);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"z\": "));
                    channel.serial->print  (event.acceleration.z);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_GYROSCOPE:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"x\": "));
                    channel.serial->print  (event.gyro.x);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"y\": "));
                    channel.serial->print  (event.gyro.y);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"z\": "));
                    channel.serial->print  (event.gyro.z);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_LIGHT:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"light\": "));
                    channel.serial->print  (event.light);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_LUX);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_PRESSURE:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"air_pressure\": "));
                    channel.serial->print  (event.pressure);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_HECTO_PASCAL);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_LINEAR_ACCELERATION:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"x\": "));
                    channel.serial->print  (event.acceleration.x);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"y\": "));
                    channel.serial->print  (event.acceleration.y);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"z\": "));
                    channel.serial->print  (event.acceleration.z);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_RELATIVE_HUMIDITY:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"humidity\": "));
                    channel.serial->print  (event.relative_humidity);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_PERCENTAGE);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_AMBIENT_TEMPERATURE:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"temperature\": "));
                    channel.serial->print  (event.temperature);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_CELCIUS);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_CURRENT:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"current\": "));
                    channel.serial->print  (event.current);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_MILLI_ANPERE);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_COLOR:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"r\": "));
                    channel.serial->print  (event.color.r);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"g\": "));
                    channel.serial->print  (event.color.g);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"b\": "));
                    channel.serial->print  (event.color.b);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"rgba\": "));
                    channel.serial->print  (event.color.rgba);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"value\": "));
                    channel.serial->print  (event.value);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_ANGLE:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"angle\": "));
                    channel.serial->print  (event.angle);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_DEGREE);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_1AXIS_GYRO:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"roll\": "));
                    channel.serial->print  (event.roll);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_DISTANCE:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"distance\": "));
                    channel.serial->print  (event.distance);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_CENTI_METER);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_DUST:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"dust\": "));
                    channel.serial->print  (event.dust);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_PCS_PER_CF);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_POSITION:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"latitude\": "));
                    channel.serial->print  (event.position.latitude);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_DEGREE);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"longtitude\": "));
                    channel.serial->print  (event.position.longtitude);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_DEGREE);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"altitude\": "));
                    channel.serial->print  (event.position.altitude);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_METER);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"dop\": "));
                    channel.serial->print  (event.position.dop);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_DATE:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"year\": "));
                    channel.serial->print  (event.date.year);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"month\": "));
                    channel.serial->print  (event.date.month);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"day\": "));
                    channel.serial->print  (event.date.day);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"dayOfWeek\": "));
                    channel.serial->print  (event.date.dayOfWeek);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"hour\": "));
                    channel.serial->print  (event.date.hour);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"minute\": "));
                    channel.serial->print  (event.date.minute);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"second\": "));
                    channel.serial->print  (event.date.second);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("},"));
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"millisecond\": "));
                    channel.serial->print  (event.date.millisecond);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_SPEED_KNOT:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"speed_knot\": "));
                    channel.serial->print  (event.speed);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_KNOT);
                    channel.serial->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE_ANALOG:
                    channel.serial->println(F("{"));
                    channel.serial->print  (F("\"value\": "));
                    channel.serial->print  (event.value);
                    channel.serial->println(F(","));
                    channel.serial->print  (F("\"unit\": "));
                    channel.serial->print  (UNIT_TYPE_UNDEF);
                    channel.serial->println(F("}"));
                    break;
                //case SENSOR_TYPE_MAGNETIC_FIELD:
                //case SENSOR_TYPE_ORIENTATION:
                //case SENSOR_TYPE_PROXIMITY:
                //case SENSOR_TYPE_GRAVITY:
                //case SENSOR_TYPE_ROTATION_VECTOR:
                //case SENSOR_TYPE_VOLTAGE:
                //case SENSOR_TYPE_LARGE_INT:
                //case SENSOR_TYPE_IRREMOTE:
                default:
                    return false;
            }
            channel.serial->println(F("]"));
            channel.serial->println(F("}"));
            return true;
#endif /* __USE_SERIAL__ */
#ifdef __USE_SOFT_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SOFT_SERIAL :
            channel.sserial->println(F("{"));
            channel.sserial->print  (F("\"id\": "));
            channel.sserial->print  (event.sensor_id);
            channel.sserial->println(F(","));
            channel.sserial->print  (F("\"type\": "));
            channel.sserial->print  (event.type);
            channel.sserial->println(F(","));
            channel.sserial->print  (F("\"time\": "));
            channel.sserial->print  (event.timestamp);
            channel.sserial->println(F(","));
            channel.sserial->println(F("\"data\": ["));
            switch(event.type){
                case SENSOR_TYPE_ACCELEROMETER:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"x\": "));
                    channel.sserial->print  (event.acceleration.x);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"y\": "));
                    channel.sserial->print  (event.acceleration.y);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"z\": "));
                    channel.sserial->print  (event.acceleration.z);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_GYROSCOPE:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"x\": "));
                    channel.sserial->print  (event.gyro.x);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"y\": "));
                    channel.sserial->print  (event.gyro.y);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"z\": "));
                    channel.sserial->print  (event.gyro.z);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_LIGHT:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"light\": "));
                    channel.sserial->print  (event.light);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_LUX);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_PRESSURE:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"air_pressure\": "));
                    channel.sserial->print  (event.pressure);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_HECTO_PASCAL);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_LINEAR_ACCELERATION:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"x\": "));
                    channel.sserial->print  (event.acceleration.x);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"y\": "));
                    channel.sserial->print  (event.acceleration.y);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"z\": "));
                    channel.sserial->print  (event.acceleration.z);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_RELATIVE_HUMIDITY:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"humidity\": "));
                    channel.sserial->print  (event.relative_humidity);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_PERCENTAGE);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_AMBIENT_TEMPERATURE:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"temperature\": "));
                    channel.sserial->print  (event.temperature);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_CELCIUS);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_CURRENT:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"current\": "));
                    channel.sserial->print  (event.current);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_MILLI_ANPERE);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_COLOR:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"r\": "));
                    channel.sserial->print  (event.color.r);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"g\": "));
                    channel.sserial->print  (event.color.g);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"b\": "));
                    channel.sserial->print  (event.color.b);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"rgba\": "));
                    channel.sserial->print  (event.color.rgba);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"value\": "));
                    channel.sserial->print  (event.value);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_ANGLE:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"angle\": "));
                    channel.sserial->print  (event.angle);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_DEGREE);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_1AXIS_GYRO:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"roll\": "));
                    channel.sserial->print  (event.roll);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_DISTANCE:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"distance\": "));
                    channel.sserial->print  (event.distance);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_CENTI_METER);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_DUST:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"dust\": "));
                    channel.sserial->print  (event.dust);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_PCS_PER_CF);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_POSITION:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"latitude\": "));
                    channel.sserial->print  (event.position.latitude);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_DEGREE);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"longtitude\": "));
                    channel.sserial->print  (event.position.longtitude);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_DEGREE);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"altitude\": "));
                    channel.sserial->print  (event.position.altitude);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_METER);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"dop\": "));
                    channel.sserial->print  (event.position.dop);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_DATE:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"year\": "));
                    channel.sserial->print  (event.date.year);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"month\": "));
                    channel.sserial->print  (event.date.month);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"day\": "));
                    channel.sserial->print  (event.date.day);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"dayOfWeek\": "));
                    channel.sserial->print  (event.date.dayOfWeek);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"hour\": "));
                    channel.sserial->print  (event.date.hour);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"minute\": "));
                    channel.sserial->print  (event.date.minute);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"second\": "));
                    channel.sserial->print  (event.date.second);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("},"));
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"millisecond\": "));
                    channel.sserial->print  (event.date.millisecond);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_SPEED_KNOT:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"speed_knot\": "));
                    channel.sserial->print  (event.speed);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_KNOT);
                    channel.sserial->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE_ANALOG:
                    channel.sserial->println(F("{"));
                    channel.sserial->print  (F("\"value\": "));
                    channel.sserial->print  (event.value);
                    channel.sserial->println(F(","));
                    channel.sserial->print  (F("\"unit\": "));
                    channel.sserial->print  (UNIT_TYPE_UNDEF);
                    channel.sserial->println(F("}"));
                    break;
                //case SENSOR_TYPE_MAGNETIC_FIELD:
                //case SENSOR_TYPE_ORIENTATION:
                //case SENSOR_TYPE_PROXIMITY:
                //case SENSOR_TYPE_GRAVITY:
                //case SENSOR_TYPE_ROTATION_VECTOR:
                //case SENSOR_TYPE_VOLTAGE:
                //case SENSOR_TYPE_LARGE_INT:
                //case SENSOR_TYPE_IRREMOTE:
                default:
                    return false;
            }
            channel.sserial->println(F("]"));
            channel.sserial->println(F("}"));
            return true;

#endif /* __USE_SOFT_SERIAL__ */
#ifdef __USE_SD__
        case AUSEX_OUTPUT_CHANNEL_FILE :
            channel.file->println(F("{"));
            channel.file->print  (F("\"id\": "));
            channel.file->print  (event.sensor_id);
            channel.file->println(F(","));
            channel.file->print  (F("\"type\": "));
            channel.file->print  (event.type);
            channel.file->println(F(","));
            channel.file->print  (F("\"time\": "));
            channel.file->print  (event.timestamp);
            channel.file->println(F(","));
            channel.file->println(F("\"data\": ["));
            switch(event.type){
                case SENSOR_TYPE_ACCELEROMETER:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"x\": "));
                    channel.file->print  (event.acceleration.x);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"y\": "));
                    channel.file->print  (event.acceleration.y);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"z\": "));
                    channel.file->print  (event.acceleration.z);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_GYROSCOPE:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"x\": "));
                    channel.file->print  (event.gyro.x);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"y\": "));
                    channel.file->print  (event.gyro.y);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"z\": "));
                    channel.file->print  (event.gyro.z);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_LIGHT:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"light\": "));
                    channel.file->print  (event.light);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_LUX);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_PRESSURE:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"air_pressure\": "));
                    channel.file->print  (event.pressure);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_HECTO_PASCAL);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_LINEAR_ACCELERATION:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"x\": "));
                    channel.file->print  (event.acceleration.x);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"y\": "));
                    channel.file->print  (event.acceleration.y);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"z\": "));
                    channel.file->print  (event.acceleration.z);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_RELATIVE_HUMIDITY:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"humidity\": "));
                    channel.file->print  (event.relative_humidity);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_PERCENTAGE);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_AMBIENT_TEMPERATURE:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"temperature\": "));
                    channel.file->print  (event.temperature);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_CELCIUS);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_CURRENT:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"current\": "));
                    channel.file->print  (event.current);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_MILLI_ANPERE);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_COLOR:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"r\": "));
                    channel.file->print  (event.color.r);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"g\": "));
                    channel.file->print  (event.color.g);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"b\": "));
                    channel.file->print  (event.color.b);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"rgba\": "));
                    channel.file->print  (event.color.rgba);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"value\": "));
                    channel.file->print  (event.value);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_ANGLE:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"angle\": "));
                    channel.file->print  (event.angle);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_DEGREE);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_1AXIS_GYRO:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"roll\": "));
                    channel.file->print  (event.roll);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_DISTANCE:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"distance\": "));
                    channel.file->print  (event.distance);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_CENTI_METER);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_DUST:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"dust\": "));
                    channel.file->print  (event.dust);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_PCS_PER_CF);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_POSITION:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"latitude\": "));
                    channel.file->print  (event.position.latitude);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_DEGREE);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"longtitude\": "));
                    channel.file->print  (event.position.longtitude);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_DEGREE);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"altitude\": "));
                    channel.file->print  (event.position.altitude);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_METER);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"dop\": "));
                    channel.file->print  (event.position.dop);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_DATE:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"year\": "));
                    channel.file->print  (event.date.year);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"month\": "));
                    channel.file->print  (event.date.month);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"day\": "));
                    channel.file->print  (event.date.day);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"dayOfWeek\": "));
                    channel.file->print  (event.date.dayOfWeek);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"hour\": "));
                    channel.file->print  (event.date.hour);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"minute\": "));
                    channel.file->print  (event.date.minute);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"second\": "));
                    channel.file->print  (event.date.second);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("},"));
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"millisecond\": "));
                    channel.file->print  (event.date.millisecond);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_SPEED_KNOT:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"speed_knot\": "));
                    channel.file->print  (event.speed);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_KNOT);
                    channel.file->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE_ANALOG:
                    channel.file->println(F("{"));
                    channel.file->print  (F("\"value\": "));
                    channel.file->print  (event.value);
                    channel.file->println(F(","));
                    channel.file->print  (F("\"unit\": "));
                    channel.file->print  (UNIT_TYPE_UNDEF);
                    channel.file->println(F("}"));
                    break;
                //case SENSOR_TYPE_MAGNETIC_FIELD:
                //case SENSOR_TYPE_ORIENTATION:
                //case SENSOR_TYPE_PROXIMITY:
                //case SENSOR_TYPE_GRAVITY:
                //case SENSOR_TYPE_ROTATION_VECTOR:
                //case SENSOR_TYPE_VOLTAGE:
                //case SENSOR_TYPE_LARGE_INT:
                //case SENSOR_TYPE_IRREMOTE:
                default:
                    return false;
            }
            channel.file->println(F("]"));
            channel.file->println(F("}"));
            return true;
#endif /* __USE_SD__ */
#ifdef __USE_ETHERNET_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_ETHERNET_CLIENT :
            channel.client->println(F("{"));
            channel.client->print  (F("\"id\": "));
            channel.client->print  (event.sensor_id);
            channel.client->println(F(","));
            channel.client->print  (F("\"type\": "));
            channel.client->print  (event.type);
            channel.client->println(F(","));
            channel.client->print  (F("\"time\": "));
            channel.client->print  (event.timestamp);
            channel.client->println(F(","));
            channel.client->println(F("\"data\": ["));
            switch(event.type){
                case SENSOR_TYPE_ACCELEROMETER:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"x\": "));
                    channel.client->print  (event.acceleration.x);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"y\": "));
                    channel.client->print  (event.acceleration.y);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"z\": "));
                    channel.client->print  (event.acceleration.z);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_GYROSCOPE:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"x\": "));
                    channel.client->print  (event.gyro.x);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"y\": "));
                    channel.client->print  (event.gyro.y);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"z\": "));
                    channel.client->print  (event.gyro.z);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_LIGHT:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"light\": "));
                    channel.client->print  (event.light);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_LUX);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_PRESSURE:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"air_pressure\": "));
                    channel.client->print  (event.pressure);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_HECTO_PASCAL);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_LINEAR_ACCELERATION:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"x\": "));
                    channel.client->print  (event.acceleration.x);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"y\": "));
                    channel.client->print  (event.acceleration.y);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"z\": "));
                    channel.client->print  (event.acceleration.z);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_RELATIVE_HUMIDITY:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"humidity\": "));
                    channel.client->print  (event.relative_humidity);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_PERCENTAGE);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_AMBIENT_TEMPERATURE:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"temperature\": "));
                    channel.client->print  (event.temperature);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_CELCIUS);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_CURRENT:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"current\": "));
                    channel.client->print  (event.current);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_MILLI_ANPERE);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_COLOR:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"r\": "));
                    channel.client->print  (event.color.r);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"g\": "));
                    channel.client->print  (event.color.g);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"b\": "));
                    channel.client->print  (event.color.b);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"rgba\": "));
                    channel.client->print  (event.color.rgba);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"value\": "));
                    channel.client->print  (event.value);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_ANGLE:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"angle\": "));
                    channel.client->print  (event.angle);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_DEGREE);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_1AXIS_GYRO:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"roll\": "));
                    channel.client->print  (event.roll);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_DISTANCE:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"distance\": "));
                    channel.client->print  (event.distance);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_CENTI_METER);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_DUST:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"dust\": "));
                    channel.client->print  (event.dust);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_PCS_PER_CF);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_POSITION:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"latitude\": "));
                    channel.client->print  (event.position.latitude);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_DEGREE);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"longtitude\": "));
                    channel.client->print  (event.position.longtitude);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_DEGREE);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"altitude\": "));
                    channel.client->print  (event.position.altitude);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_METER);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"dop\": "));
                    channel.client->print  (event.position.dop);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_DATE:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"year\": "));
                    channel.client->print  (event.date.year);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"month\": "));
                    channel.client->print  (event.date.month);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"day\": "));
                    channel.client->print  (event.date.day);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"dayOfWeek\": "));
                    channel.client->print  (event.date.dayOfWeek);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"hour\": "));
                    channel.client->print  (event.date.hour);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"minute\": "));
                    channel.client->print  (event.date.minute);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"second\": "));
                    channel.client->print  (event.date.second);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("},"));
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"millisecond\": "));
                    channel.client->print  (event.date.millisecond);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_SPEED_KNOT:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"speed_knot\": "));
                    channel.client->print  (event.speed);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_KNOT);
                    channel.client->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE_ANALOG:
                    channel.client->println(F("{"));
                    channel.client->print  (F("\"value\": "));
                    channel.client->print  (event.value);
                    channel.client->println(F(","));
                    channel.client->print  (F("\"unit\": "));
                    channel.client->print  (UNIT_TYPE_UNDEF);
                    channel.client->println(F("}"));
                    break;
                //case SENSOR_TYPE_MAGNETIC_FIELD:
                //case SENSOR_TYPE_ORIENTATION:
                //case SENSOR_TYPE_PROXIMITY:
                //case SENSOR_TYPE_GRAVITY:
                //case SENSOR_TYPE_ROTATION_VECTOR:
                //case SENSOR_TYPE_VOLTAGE:
                //case SENSOR_TYPE_LARGE_INT:
                //case SENSOR_TYPE_IRREMOTE:
                default:
                    return false;
            }
            channel.client->println(F("]"));
            channel.client->println(F("}"));
            return true;
#endif /* __USE_ETHERNET_CLIENT__ */
#ifdef __USE_WIFI_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_WIFI_CLIENT :
            channel.wifi_client->println(F("{"));
            channel.wifi_client->print  (F("\"id\": "));
            channel.wifi_client->print  (event.sensor_id);
            channel.wifi_client->println(F(","));
            channel.wifi_client->print  (F("\"type\": "));
            channel.wifi_client->print  (event.type);
            channel.wifi_client->println(F(","));
            channel.wifi_client->print  (F("\"time\": "));
            channel.wifi_client->print  (event.timestamp);
            channel.wifi_client->println(F(","));
            channel.wifi_client->println(F("\"data\": ["));
            switch(event.type){
                case SENSOR_TYPE_ACCELEROMETER:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"x\": "));
                    channel.wifi_client->print  (event.acceleration.x);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"y\": "));
                    channel.wifi_client->print  (event.acceleration.y);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"z\": "));
                    channel.wifi_client->print  (event.acceleration.z);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_GYROSCOPE:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"x\": "));
                    channel.wifi_client->print  (event.gyro.x);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"y\": "));
                    channel.wifi_client->print  (event.gyro.y);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"z\": "));
                    channel.wifi_client->print  (event.gyro.z);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_LIGHT:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"light\": "));
                    channel.wifi_client->print  (event.light);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_LUX);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_PRESSURE:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"air_pressure\": "));
                    channel.wifi_client->print  (event.pressure);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_HECTO_PASCAL);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_LINEAR_ACCELERATION:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"x\": "));
                    channel.wifi_client->print  (event.acceleration.x);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"y\": "));
                    channel.wifi_client->print  (event.acceleration.y);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"z\": "));
                    channel.wifi_client->print  (event.acceleration.z);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_RELATIVE_HUMIDITY:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"humidity\": "));
                    channel.wifi_client->print  (event.relative_humidity);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_PERCENTAGE);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_AMBIENT_TEMPERATURE:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"temperature\": "));
                    channel.wifi_client->print  (event.temperature);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_CELCIUS);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_CURRENT:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"current\": "));
                    channel.wifi_client->print  (event.current);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_MILLI_ANPERE);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_COLOR:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"r\": "));
                    channel.wifi_client->print  (event.color.r);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"g\": "));
                    channel.wifi_client->print  (event.color.g);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"b\": "));
                    channel.wifi_client->print  (event.color.b);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"rgba\": "));
                    channel.wifi_client->print  (event.color.rgba);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"value\": "));
                    channel.wifi_client->print  (event.value);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_ANGLE:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"angle\": "));
                    channel.wifi_client->print  (event.angle);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_DEGREE);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_1AXIS_GYRO:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"roll\": "));
                    channel.wifi_client->print  (event.roll);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_DISTANCE:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"distance\": "));
                    channel.wifi_client->print  (event.distance);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_CENTI_METER);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_DUST:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"dust\": "));
                    channel.wifi_client->print  (event.dust);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_PCS_PER_CF);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_POSITION:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"latitude\": "));
                    channel.wifi_client->print  (event.position.latitude);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_DEGREE);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"longtitude\": "));
                    channel.wifi_client->print  (event.position.longtitude);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_DEGREE);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"altitude\": "));
                    channel.wifi_client->print  (event.position.altitude);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_METER);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"dop\": "));
                    channel.wifi_client->print  (event.position.dop);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_DATE:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"year\": "));
                    channel.wifi_client->print  (event.date.year);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"month\": "));
                    channel.wifi_client->print  (event.date.month);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"day\": "));
                    channel.wifi_client->print  (event.date.day);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"dayOfWeek\": "));
                    channel.wifi_client->print  (event.date.dayOfWeek);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"hour\": "));
                    channel.wifi_client->print  (event.date.hour);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"minute\": "));
                    channel.wifi_client->print  (event.date.minute);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"second\": "));
                    channel.wifi_client->print  (event.date.second);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("},"));
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"millisecond\": "));
                    channel.wifi_client->print  (event.date.millisecond);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_SPEED_KNOT:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"speed_knot\": "));
                    channel.wifi_client->print  (event.speed);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_KNOT);
                    channel.wifi_client->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE_ANALOG:
                    channel.wifi_client->println(F("{"));
                    channel.wifi_client->print  (F("\"value\": "));
                    channel.wifi_client->print  (event.value);
                    channel.wifi_client->println(F(","));
                    channel.wifi_client->print  (F("\"unit\": "));
                    channel.wifi_client->print  (UNIT_TYPE_UNDEF);
                    channel.wifi_client->println(F("}"));
                    break;
                //case SENSOR_TYPE_MAGNETIC_FIELD:
                //case SENSOR_TYPE_ORIENTATION:
                //case SENSOR_TYPE_PROXIMITY:
                //case SENSOR_TYPE_GRAVITY:
                //case SENSOR_TYPE_ROTATION_VECTOR:
                //case SENSOR_TYPE_VOLTAGE:
                //case SENSOR_TYPE_LARGE_INT:
                //case SENSOR_TYPE_IRREMOTE:
                default:
                    return false;
            }
            channel.wifi_client->println(F("]"));
            channel.wifi_client->println(F("}"));
            return true;
#endif /* __USE_WIFI_CLIENT__ */
#ifdef __USE_HTTP_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_HTTP_CLIENT :
            String workString = "{\n\"id\": " + String(event.sensor_id) + ",\n"
                + "\"type\": " + String(event.type) + ",\n"
                + "\"time\": " + String(event.timestamp) + ",\n"
                + "\"data\": [\n";
            switch(event.type){
                case SENSOR_TYPE_ACCELEROMETER:
                    workString = workString + "{\n\"x\": " + String(event.acceleration.x) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_METER_PER_SEC_2) + "},\n"
                        + "{\n\"y\": " + String(event.acceleration.y) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_METER_PER_SEC_2) + "},\n"
                        + "{\n\"z\": " + String(event.acceleration.z) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_METER_PER_SEC_2) + "}\n";
                    break;
                case SENSOR_TYPE_GYROSCOPE:
                    workString = workString + "{\n\"x\": " + String(event.gyro.x) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_DEGREE_PER_SEC) + "},\n"
                        + "{\n\"y\": " + String(event.gyro.y) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_DEGREE_PER_SEC) + "},\n"
                        + "{\n\"z\": " + String(event.gyro.z) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_DEGREE_PER_SEC) + "}\n";
                    break;
                case SENSOR_TYPE_LIGHT:
                    workString = workString + "{\n\"light\": " + String(event.light) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_LUX) + "}\n";
                    break;
                case SENSOR_TYPE_PRESSURE:
                    workString = workString + "{\n\"air_pressure\": " + String(event.pressure) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_HECTO_PASCAL) + "}\n";
                    break;
                case SENSOR_TYPE_LINEAR_ACCELERATION:
                    workString = workString + "{\n\"x\": " + String(event.acceleration.x) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_METER_PER_SEC_2) + "},\n"
                        + "{\n\"y\": " + String(event.acceleration.y) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_METER_PER_SEC_2) + "},\n"
                        + "{\n\"z\": " + String(event.acceleration.z) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_METER_PER_SEC_2) + "}\n";
                    break;
                case SENSOR_TYPE_RELATIVE_HUMIDITY:
                    workString = workString + "{\n\"humidity\": " + String(event.relative_humidity)
                        + ",\n\"unit\": " + String(UNIT_TYPE_PERCENTAGE) + "}\n";
                    break;
                case SENSOR_TYPE_AMBIENT_TEMPERATURE:
                    workString = workString + "{\n\"temperature\": " + String(event.temperature)
                        + ",\n\"unit\": " + String(UNIT_TYPE_CELCIUS) + "}\n";
                    break;
                case SENSOR_TYPE_CURRENT:
                    workString = workString + "{\n\"current\": " + String(event.current)
                        + ",\n\"unit\": " + String(UNIT_TYPE_MILLI_ANPERE) + "}\n";
                    break;
                case SENSOR_TYPE_COLOR:
                    workString = workString
                        + "{\n\"r\": " + String(event.color.r) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_UNDEF) + "},\n"
                        + "{\n\"g\": " + String(event.color.g) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_UNDEF) + "},\n"
                        + "{\n\"b\": " + String(event.color.b) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_UNDEF) + "},\n"
                        + "{\n\"rgba\": " + String(event.color.rgba) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_UNDEF) + "}\n";
                    break;
                case SENSOR_TYPE_SIMPLE:
                    workString = workString + "{\n\"value\": " + String(event.value)
                        + ",\n\"unit\": " + String(UNIT_TYPE_UNDEF) + "}\n";
                    break;
                case SENSOR_TYPE_ANGLE:
                    workString = workString + "{\n\"angle\": " + String(event.angle)
                        + ",\n\"unit\": " + String(UNIT_TYPE_DEGREE) + "}\n";
                    break;
                case SENSOR_TYPE_1AXIS_GYRO:
                    workString = workString + "{\n\"roll\": " + String(event.roll)
                        + ",\n\"unit\": " + String(UNIT_TYPE_DEGREE_PER_SEC) + "}\n";
                    break;
                case SENSOR_TYPE_DISTANCE:
                    workString = workString + "{\n\"distance\": " + String(event.distance)
                        + ",\n\"unit\": " + String(UNIT_TYPE_CENTI_METER) + "}\n";
                    break;
                case SENSOR_TYPE_DUST:
                    workString = workString + "{\n\"dust\": " + String(event.dust)
                        + ",\n\"unit\": " + String(UNIT_TYPE_PCS_PER_CF) + "}\n";
                    break;
                case SENSOR_TYPE_POSITION:
                    workString = workString
                        + "{\n\"latitude\": " + String(event.position.latitude)
                        + ",\n\"unit\": " + String(UNIT_TYPE_DEGREE)
                        + "},\n{\n\"longtitude\": " + String(event.position.longtitude)
                        + ",\n\"unit\": " + String(UNIT_TYPE_DEGREE)
                        + "},\n{\n\"altitude\": " + String(event.position.altitude)
                        + ",\n\"unit\": " + String(UNIT_TYPE_METER)
                        + "},\n{\n\"dop\": " + String(event.position.dop)
                        + ",\n\"unit\": " + String(UNIT_TYPE_UNDEF)
                        + "}\n";
                    break;
                case SENSOR_TYPE_DATE:
                    workString = workString
                        + "{\n\"year\": " + String(event.date.year)
                        + ",\n\"unit\": " + String(UNIT_TYPE_UNDEF)
                        + "},\n{\n\"month\": " + String(event.date.month)
                        + ",\n\"unit\": " + String(UNIT_TYPE_UNDEF)
                        + "},\n{\n\"day\": " + String(event.date.day)
                        + ",\n\"unit\": " + String(UNIT_TYPE_UNDEF)
                        + "},\n{\n\"dayOfWeek\": " + String(event.date.dayOfWeek)
                        + ",\n\"unit\": " + String(UNIT_TYPE_UNDEF)
                        + "},\n{\n\"hour\": " + String(event.date.hour)
                        + ",\n\"unit\": " + String(UNIT_TYPE_UNDEF)
                        + "},\n{\n\"minute\": " + String(event.date.minute)
                        + ",\n\"unit\": " + String(UNIT_TYPE_UNDEF)
                        + "},\n{\n\"second\": " + String(event.date.second)
                        + ",\n\"unit\": " + String(UNIT_TYPE_UNDEF)
                        + "},\n{\n\"millisecond\": " + String(event.date.millisecond)
                        + ",\n\"unit\": " + String(UNIT_TYPE_UNDEF)
                        + "}\n{\n\"dop\": " + String(event.position.dop)
                        + ",\n\"unit\": " + String(UNIT_TYPE_UNDEF)
                        + "}\n";
                    break;
                case SENSOR_TYPE_SPEED_KNOT:
                    workString = workString + "{\n\"speed_knot\": " + String(event.speed) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_KNOT) + "}\n";
                    break;
                case SENSOR_TYPE_SIMPLE_ANALOG:
                    workString = workString + "{\n\"value\": " + String(event.value) + ",\n"
                        + "\"unit\": " + String(UNIT_TYPE_KNOT) + "}\n";
                    break;
                //case SENSOR_TYPE_MAGNETIC_FIELD:
                //case SENSOR_TYPE_ORIENTATION:
                //case SENSOR_TYPE_PROXIMITY:
                //case SENSOR_TYPE_GRAVITY:
                //case SENSOR_TYPE_ROTATION_VECTOR:
                //case SENSOR_TYPE_VOLTAGE:
                //case SENSOR_TYPE_LARGE_INT:
                //case SENSOR_TYPE_IRREMOTE:
                default:
                    return false;
            }
            workString = workString + "]\n}\n";
            channel.httpClient->post(urlPath, contentType, workString);
            return true;
#endif /* __USE_HTTP_CLIENT__ */
#ifdef __USE_MQTT_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_MQTT_CLIENT :
            if (size==0) {
                channel.mqttClient->beginMessage(topic);
            } else {
                channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
            }
            channel.mqttClient->println(F("{"));
            channel.mqttClient->print  (F("\"id\": "));
            channel.mqttClient->print  (event.sensor_id);
            channel.mqttClient->println(F(","));
            channel.mqttClient->print  (F("\"type\": "));
            channel.mqttClient->print  (event.type);
            channel.mqttClient->println(F(","));
            channel.mqttClient->print  (F("\"time\": "));
            channel.mqttClient->print  (event.timestamp);
            channel.mqttClient->println(F(","));
            channel.mqttClient->println(F("\"data\": ["));
            switch(event.type){
                case SENSOR_TYPE_ACCELEROMETER:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"x\": "));
                    channel.mqttClient->print  (event.acceleration.x);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"y\": "));
                    channel.mqttClient->print  (event.acceleration.y);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"z\": "));
                    channel.mqttClient->print  (event.acceleration.z);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_GYROSCOPE:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"x\": "));
                    channel.mqttClient->print  (event.gyro.x);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"y\": "));
                    channel.mqttClient->print  (event.gyro.y);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"z\": "));
                    channel.mqttClient->print  (event.gyro.z);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_LIGHT:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"light\": "));
                    channel.mqttClient->print  (event.light);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_LUX);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_PRESSURE:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"air_pressure\": "));
                    channel.mqttClient->print  (event.pressure);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_HECTO_PASCAL);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_LINEAR_ACCELERATION:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"x\": "));
                    channel.mqttClient->print  (event.acceleration.x);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"y\": "));
                    channel.mqttClient->print  (event.acceleration.y);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"z\": "));
                    channel.mqttClient->print  (event.acceleration.z);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_METER_PER_SEC_2);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_RELATIVE_HUMIDITY:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"humidity\": "));
                    channel.mqttClient->print  (event.relative_humidity);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_PERCENTAGE);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_AMBIENT_TEMPERATURE:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"temperature\": "));
                    channel.mqttClient->print  (event.temperature);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_CELCIUS);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_CURRENT:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"current\": "));
                    channel.mqttClient->print  (event.current);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_MILLI_ANPERE);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_COLOR:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"r\": "));
                    channel.mqttClient->print  (event.color.r);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"g\": "));
                    channel.mqttClient->print  (event.color.g);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"b\": "));
                    channel.mqttClient->print  (event.color.b);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"rgba\": "));
                    channel.mqttClient->print  (event.color.rgba);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"value\": "));
                    channel.mqttClient->print  (event.value);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_ANGLE:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"angle\": "));
                    channel.mqttClient->print  (event.angle);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_DEGREE);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_1AXIS_GYRO:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"roll\": "));
                    channel.mqttClient->print  (event.roll);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_DEGREE_PER_SEC);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_DISTANCE:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"distance\": "));
                    channel.mqttClient->print  (event.distance);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_CENTI_METER);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_DUST:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"dust\": "));
                    channel.mqttClient->print  (event.dust);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_PCS_PER_CF);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_POSITION:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"latitude\": "));
                    channel.mqttClient->print  (event.position.latitude);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_DEGREE);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"longtitude\": "));
                    channel.mqttClient->print  (event.position.longtitude);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_DEGREE);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"altitude\": "));
                    channel.mqttClient->print  (event.position.altitude);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_METER);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"dop\": "));
                    channel.mqttClient->print  (event.position.dop);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_DATE:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"year\": "));
                    channel.mqttClient->print  (event.date.year);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"month\": "));
                    channel.mqttClient->print  (event.date.month);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"day\": "));
                    channel.mqttClient->print  (event.date.day);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"dayOfWeek\": "));
                    channel.mqttClient->print  (event.date.dayOfWeek);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"hour\": "));
                    channel.mqttClient->print  (event.date.hour);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"minute\": "));
                    channel.mqttClient->print  (event.date.minute);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"second\": "));
                    channel.mqttClient->print  (event.date.second);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("},"));
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"millisecond\": "));
                    channel.mqttClient->print  (event.date.millisecond);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_SPEED_KNOT:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"speed_knot\": "));
                    channel.mqttClient->print  (event.speed);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_KNOT);
                    channel.mqttClient->println(F("}"));
                    break;
                case SENSOR_TYPE_SIMPLE_ANALOG:
                    channel.mqttClient->println(F("{"));
                    channel.mqttClient->print  (F("\"value\": "));
                    channel.mqttClient->print  (event.value);
                    channel.mqttClient->println(F(","));
                    channel.mqttClient->print  (F("\"unit\": "));
                    channel.mqttClient->print  (UNIT_TYPE_UNDEF);
                    channel.mqttClient->println(F("}"));
                    break;
                //case SENSOR_TYPE_MAGNETIC_FIELD:
                //case SENSOR_TYPE_ORIENTATION:
                //case SENSOR_TYPE_PROXIMITY:
                //case SENSOR_TYPE_GRAVITY:
                //case SENSOR_TYPE_ROTATION_VECTOR:
                //case SENSOR_TYPE_VOLTAGE:
                //case SENSOR_TYPE_LARGE_INT:
                //case SENSOR_TYPE_IRREMOTE:
                default:
                    return false;
            }
            channel.mqttClient->println(F("]"));
            channel.mqttClient->println(F("}"));
            channel.mqttClient->endMessage();
            return true;
#endif /* __USE_MQTT_CLIENT__ */
        //default:
        //    return false;
    }
    return false;
}

bool AuxExSensorIO::EventOutputPlain(sensors_event_t event) {
    switch(event.type){
        case SENSOR_TYPE_ACCELEROMETER:
        case SENSOR_TYPE_MAGNETIC_FIELD:
        case SENSOR_TYPE_ORIENTATION:
        case SENSOR_TYPE_GYROSCOPE:
        case SENSOR_TYPE_LIGHT:
        case SENSOR_TYPE_PRESSURE:
        case SENSOR_TYPE_PROXIMITY:
        case SENSOR_TYPE_GRAVITY:
        case SENSOR_TYPE_LINEAR_ACCELERATION:
        case SENSOR_TYPE_ROTATION_VECTOR:
        case SENSOR_TYPE_RELATIVE_HUMIDITY:
        case SENSOR_TYPE_AMBIENT_TEMPERATURE:
        case SENSOR_TYPE_VOLTAGE:
        case SENSOR_TYPE_CURRENT:
        case SENSOR_TYPE_COLOR:
        case SENSOR_TYPE_SIMPLE:
        case SENSOR_TYPE_ANGLE:
        case SENSOR_TYPE_1AXIS_GYRO:
        case SENSOR_TYPE_DISTANCE:
        case SENSOR_TYPE_LARGE_INT:
        case SENSOR_TYPE_DUST:
        case SENSOR_TYPE_IRREMOTE:
        case SENSOR_TYPE_POSITION:
        case SENSOR_TYPE_DATE:
        case SENSOR_TYPE_SPEED_KNOT:
        case SENSOR_TYPE_SIMPLE_ANALOG:
            break;
        default:
            return false;
    }
    switch(channelType) {
#ifdef __USE_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SERIAL :
            channel.serial->print(F("Sensor_ID="));channel.serial->println(event.sensor_id);
	        channel.serial->print(F("Sensor_Type="));channel.serial->println(event.type);
	        channel.serial->print(F("Data_Time="));channel.serial->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.serial->print(F("Temperature="));channel.serial->print(event.temperature);channel.serial->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.serial->print(F("Humidity="));channel.serial->print(event.relative_humidity);channel.serial->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.serial->print(F("Acceleration.x="));channel.serial->print(event.acceleration.x);channel.serial->println(F("m/s^2"));
	            channel.serial->print(F("Acceleration.y="));channel.serial->print(event.acceleration.y);channel.serial->println(F("m/s^2"));
	            channel.serial->print(F("Acceleration.z="));channel.serial->print(event.acceleration.z);channel.serial->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.serial->print(F("Gyro.x="));channel.serial->print(event.gyro.x);channel.serial->println(F("deg/s"));
	            channel.serial->print(F("Gyro.y="));channel.serial->print(event.gyro.y);channel.serial->println(F("deg/s"));
	            channel.serial->print(F("Gyro.z="));channel.serial->print(event.gyro.z);channel.serial->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.serial->print(F("Light="));channel.serial->print(event.light);channel.serial->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.serial->print(F("AirPressure="));channel.serial->print(event.pressure);channel.serial->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.serial->print(F("LinearAcceleration.x="));channel.serial->print(event.acceleration.x);channel.serial->println(F("m/s^2"));
	            channel.serial->print(F("LinearAcceleration.y="));channel.serial->print(event.acceleration.y);channel.serial->println(F("m/s^2"));
	            channel.serial->print(F("LinearAcceleration.z="));channel.serial->print(event.acceleration.z);channel.serial->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.serial->print(F("Current="));channel.serial->print(event.current);channel.serial->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.serial->print(F("ColorR="));channel.serial->println(event.color.r);
	            channel.serial->print(F("ColorG="));channel.serial->println(event.color.g);
	            channel.serial->print(F("ColorG="));channel.serial->println(event.color.b);
	            channel.serial->print(F("ColorRGBA="));channel.serial->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.serial->print(F("Value="));channel.serial->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.serial->print(F("Angle="));channel.serial->print(event.angle);channel.serial->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.serial->print(F("1AxisGyro="));channel.serial->print(event.roll);channel.serial->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.serial->print(F("Distance="));channel.serial->print(event.distance);channel.serial->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.serial->print(F("Dust="));channel.serial->print(event.dust);channel.serial->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.serial->print(F("Latitude="));channel.serial->print(event.position.latitude);channel.serial->println(F("deg"));
	            channel.serial->print(F("Longtitude="));channel.serial->print(event.position.longtitude);channel.serial->println(F("deg"));
	            channel.serial->print(F("Altitude="));channel.serial->print(event.position.altitude);channel.serial->println(F("m"));
	            channel.serial->print(F("Dop="));channel.serial->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.serial->print(F("Year="));channel.serial->println(event.date.year);
	            channel.serial->print(F("Month="));channel.serial->println(event.date.month);
	            channel.serial->print(F("Day="));channel.serial->println(event.date.day);
                channel.serial->print(F("DayOfWeek="));channel.serial->println(event.date.dayOfWeek);
	            channel.serial->print(F("Hour="));channel.serial->println(event.date.hour);
	            channel.serial->print(F("Minute="));channel.serial->println(event.date.minute);
	            channel.serial->print(F("Second="));channel.serial->println(event.date.second);
	            channel.serial->print(F("Millisecond="));channel.serial->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.serial->print(F("SpeedKnot="));channel.serial->print(event.speed);channel.serial->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.serial->print(F("Orientation="));channel.serial->print(event.orientation.heading);channel.serial->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.serial->print(F("Value="));channel.serial->println(event.value);
            }
            return true;
#endif /* __USE_SERIAL__ */
#ifdef __USE_SOFT_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SOFT_SERIAL :
            channel.sserial->print(F("Sensor_ID="));channel.sserial->println(event.sensor_id);
	        channel.sserial->print(F("Sensor_Type="));channel.sserial->println(event.type);
	        channel.sserial->print(F("Data_Time="));channel.sserial->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.sserial->print(F("Temperature="));channel.sserial->print(event.temperature);channel.sserial->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.sserial->print(F("Humidity="));channel.sserial->print(event.relative_humidity);channel.sserial->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.sserial->print(F("Acceleration.x="));channel.sserial->print(event.acceleration.x);channel.sserial->println(F("m/s^2"));
	            channel.sserial->print(F("Acceleration.y="));channel.sserial->print(event.acceleration.y);channel.sserial->println(F("m/s^2"));
	            channel.sserial->print(F("Acceleration.z="));channel.sserial->print(event.acceleration.z);channel.sserial->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.sserial->print(F("Gyro.x="));channel.sserial->print(event.gyro.x);channel.sserial->println(F("deg/s"));
	            channel.sserial->print(F("Gyro.y="));channel.sserial->print(event.gyro.y);channel.sserial->println(F("deg/s"));
	            channel.sserial->print(F("Gyro.z="));channel.sserial->print(event.gyro.z);channel.sserial->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.sserial->print(F("Light="));channel.sserial->print(event.light);channel.sserial->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.sserial->print(F("AirPressure="));channel.sserial->print(event.pressure);channel.sserial->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.sserial->print(F("LinearAcceleration.x="));channel.sserial->print(event.acceleration.x);channel.sserial->println(F("m/s^2"));
	            channel.sserial->print(F("LinearAcceleration.y="));channel.sserial->print(event.acceleration.y);channel.sserial->println(F("m/s^2"));
	            channel.sserial->print(F("LinearAcceleration.z="));channel.sserial->print(event.acceleration.z);channel.sserial->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.sserial->print(F("Current="));channel.sserial->print(event.current);channel.sserial->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.sserial->print(F("ColorR="));channel.sserial->println(event.color.r);
	            channel.sserial->print(F("ColorG="));channel.sserial->println(event.color.g);
	            channel.sserial->print(F("ColorG="));channel.sserial->println(event.color.b);
	            channel.sserial->print(F("ColorRGBA="));channel.sserial->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.sserial->print(F("Value="));channel.sserial->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.sserial->print(F("Angle="));channel.sserial->print(event.angle);channel.sserial->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.sserial->print(F("1AxisGyro="));channel.sserial->print(event.roll);channel.sserial->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.sserial->print(F("Distance="));channel.sserial->print(event.distance);channel.sserial->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.sserial->print(F("Dust="));channel.sserial->print(event.dust);channel.sserial->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.sserial->print(F("Latitude="));channel.sserial->print(event.position.latitude);channel.sserial->println(F("deg"));
	            channel.sserial->print(F("Longtitude="));channel.sserial->print(event.position.longtitude);channel.sserial->println(F("deg"));
	            channel.sserial->print(F("Altitude="));channel.sserial->print(event.position.altitude);channel.sserial->println(F("m"));
	            channel.sserial->print(F("Dop="));channel.sserial->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.sserial->print(F("Year="));channel.sserial->println(event.date.year);
	            channel.sserial->print(F("Month="));channel.sserial->println(event.date.month);
	            channel.sserial->print(F("Day="));channel.sserial->println(event.date.day);
                channel.sserial->print(F("DayOfWeek="));channel.sserial->println(event.date.dayOfWeek);
	            channel.sserial->print(F("Hour="));channel.sserial->println(event.date.hour);
	            channel.sserial->print(F("Minute="));channel.sserial->println(event.date.minute);
	            channel.sserial->print(F("Second="));channel.sserial->println(event.date.second);
	            channel.sserial->print(F("Millisecond="));channel.sserial->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.sserial->print(F("SpeedKnot="));channel.sserial->print(event.speed);channel.sserial->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.sserial->print(F("Orientation="));channel.sserial->print(event.orientation.heading);channel.sserial->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.sserial->print(F("Value="));channel.sserial->println(event.value);
            }
            return true;
#endif /* __USE_SOFT_SERIAL__ */
#ifdef __USE_SD__
        case AUSEX_OUTPUT_CHANNEL_FILE :
            channel.file->print(F("Sensor_ID="));channel.file->println(event.sensor_id);
	        channel.file->print(F("Sensor_Type="));channel.file->println(event.type);
	        channel.file->print(F("Data_Time="));channel.file->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.file->print(F("Temperature="));channel.file->print(event.temperature);channel.file->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.file->print(F("Humidity="));channel.file->print(event.relative_humidity);channel.file->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.file->print(F("Acceleration.x="));channel.file->print(event.acceleration.x);channel.file->println(F("m/s^2"));
	            channel.file->print(F("Acceleration.y="));channel.file->print(event.acceleration.y);channel.file->println(F("m/s^2"));
	            channel.file->print(F("Acceleration.z="));channel.file->print(event.acceleration.z);channel.file->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.file->print(F("Gyro.x="));channel.file->print(event.gyro.x);channel.file->println(F("deg/s"));
	            channel.file->print(F("Gyro.y="));channel.file->print(event.gyro.y);channel.file->println(F("deg/s"));
	            channel.file->print(F("Gyro.z="));channel.file->print(event.gyro.z);channel.file->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.file->print(F("Light="));channel.file->print(event.light);channel.file->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.file->print(F("AirPressure="));channel.file->print(event.pressure);channel.file->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.file->print(F("LinearAcceleration.x="));channel.file->print(event.acceleration.x);channel.file->println(F("m/s^2"));
	            channel.file->print(F("LinearAcceleration.y="));channel.file->print(event.acceleration.y);channel.file->println(F("m/s^2"));
	            channel.file->print(F("LinearAcceleration.z="));channel.file->print(event.acceleration.z);channel.file->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.file->print(F("Current="));channel.file->print(event.current);channel.file->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.file->print(F("ColorR="));channel.file->println(event.color.r);
	            channel.file->print(F("ColorG="));channel.file->println(event.color.g);
	            channel.file->print(F("ColorG="));channel.file->println(event.color.b);
	            channel.file->print(F("ColorRGBA="));channel.file->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.file->print(F("Value="));channel.file->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.file->print(F("Angle="));channel.file->print(event.angle);channel.file->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.file->print(F("1AxisGyro="));channel.file->print(event.roll);channel.file->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.file->print(F("Distance="));channel.file->print(event.distance);channel.file->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.file->print(F("Dust="));channel.file->print(event.dust);channel.file->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.file->print(F("Latitude="));channel.file->print(event.position.latitude);channel.file->println(F("deg"));
	            channel.file->print(F("Longtitude="));channel.file->print(event.position.longtitude);channel.file->println(F("deg"));
	            channel.file->print(F("Altitude="));channel.file->print(event.position.altitude);channel.file->println(F("m"));
	            channel.file->print(F("Dop="));channel.file->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.file->print(F("Year="));channel.file->println(event.date.year);
	            channel.file->print(F("Month="));channel.file->println(event.date.month);
	            channel.file->print(F("Day="));channel.file->println(event.date.day);
                channel.file->print(F("DayOfWeek="));channel.file->println(event.date.dayOfWeek);
	            channel.file->print(F("Hour="));channel.file->println(event.date.hour);
	            channel.file->print(F("Minute="));channel.file->println(event.date.minute);
	            channel.file->print(F("Second="));channel.file->println(event.date.second);
	            channel.file->print(F("Millisecond="));channel.file->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.file->print(F("SpeedKnot="));channel.file->print(event.speed);channel.file->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.file->print(F("Orientation="));channel.file->print(event.orientation.heading);channel.file->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.file->print(F("Value="));channel.file->println(event.value);
            }
            return true;
#endif /* __USE_SD__ */
#ifdef __USE_ETHERNET_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_ETHERNET_CLIENT :
            channel.client->print(F("Sensor_ID="));channel.client->println(event.sensor_id);
	        channel.client->print(F("Sensor_Type="));channel.client->println(event.type);
	        channel.client->print(F("Data_Time="));channel.client->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.client->print(F("Temperature="));channel.client->print(event.temperature);channel.client->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.client->print(F("Humidity="));channel.client->print(event.relative_humidity);channel.client->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.client->print(F("Acceleration.x="));channel.client->print(event.acceleration.x);channel.client->println(F("m/s^2"));
	            channel.client->print(F("Acceleration.y="));channel.client->print(event.acceleration.y);channel.client->println(F("m/s^2"));
	            channel.client->print(F("Acceleration.z="));channel.client->print(event.acceleration.z);channel.client->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.client->print(F("Gyro.x="));channel.client->print(event.gyro.x);channel.client->println(F("deg/s"));
	            channel.client->print(F("Gyro.y="));channel.client->print(event.gyro.y);channel.client->println(F("deg/s"));
	            channel.client->print(F("Gyro.z="));channel.client->print(event.gyro.z);channel.client->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.client->print(F("Light="));channel.client->print(event.light);channel.client->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.client->print(F("AirPressure="));channel.client->print(event.pressure);channel.client->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.client->print(F("LinearAcceleration.x="));channel.client->print(event.acceleration.x);channel.client->println(F("m/s^2"));
	            channel.client->print(F("LinearAcceleration.y="));channel.client->print(event.acceleration.y);channel.client->println(F("m/s^2"));
	            channel.client->print(F("LinearAcceleration.z="));channel.client->print(event.acceleration.z);channel.client->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.client->print(F("Current="));channel.client->print(event.current);channel.client->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.client->print(F("ColorR="));channel.client->println(event.color.r);
	            channel.client->print(F("ColorG="));channel.client->println(event.color.g);
	            channel.client->print(F("ColorG="));channel.client->println(event.color.b);
	            channel.client->print(F("ColorRGBA="));channel.client->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.client->print(F("Value="));channel.client->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.client->print(F("Angle="));channel.client->print(event.angle);channel.client->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.client->print(F("1AxisGyro="));channel.client->print(event.roll);channel.client->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.client->print(F("Distance="));channel.client->print(event.distance);channel.client->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.client->print(F("Dust="));channel.client->print(event.dust);channel.client->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.client->print(F("Latitude="));channel.client->print(event.position.latitude);channel.client->println(F("deg"));
	            channel.client->print(F("Longtitude="));channel.client->print(event.position.longtitude);channel.client->println(F("deg"));
	            channel.client->print(F("Altitude="));channel.client->print(event.position.altitude);channel.client->println(F("m"));
	            channel.client->print(F("Dop="));channel.client->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.client->print(F("Year="));channel.client->println(event.date.year);
	            channel.client->print(F("Month="));channel.client->println(event.date.month);
	            channel.client->print(F("Day="));channel.client->println(event.date.day);
                channel.client->print(F("DayOfWeek="));channel.client->println(event.date.dayOfWeek);
	            channel.client->print(F("Hour="));channel.client->println(event.date.hour);
	            channel.client->print(F("Minute="));channel.client->println(event.date.minute);
	            channel.client->print(F("Second="));channel.client->println(event.date.second);
	            channel.client->print(F("Millisecond="));channel.client->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.client->print(F("SpeedKnot="));channel.client->print(event.speed);channel.client->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.client->print(F("Orientation="));channel.client->print(event.orientation.heading);channel.client->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.client->print(F("Value="));channel.client->println(event.value);
            }
            return true;
#endif /* __USE_ETHERNET_CLIENT__ */
#ifdef __USE_WIFI_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_WIFI_CLIENT :
            channel.wifi_client->print(F("Sensor_ID="));channel.wifi_client->println(event.sensor_id);
	        channel.wifi_client->print(F("Sensor_Type="));channel.wifi_client->println(event.type);
	        channel.wifi_client->print(F("Data_Time="));channel.wifi_client->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.wifi_client->print(F("Temperature="));channel.wifi_client->print(event.temperature);channel.wifi_client->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.wifi_client->print(F("Humidity="));channel.wifi_client->print(event.relative_humidity);channel.wifi_client->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.wifi_client->print(F("Acceleration.x="));channel.wifi_client->print(event.acceleration.x);channel.wifi_client->println(F("m/s^2"));
	            channel.wifi_client->print(F("Acceleration.y="));channel.wifi_client->print(event.acceleration.y);channel.wifi_client->println(F("m/s^2"));
	            channel.wifi_client->print(F("Acceleration.z="));channel.wifi_client->print(event.acceleration.z);channel.wifi_client->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.wifi_client->print(F("Gyro.x="));channel.wifi_client->print(event.gyro.x);channel.wifi_client->println(F("deg/s"));
	            channel.wifi_client->print(F("Gyro.y="));channel.wifi_client->print(event.gyro.y);channel.wifi_client->println(F("deg/s"));
	            channel.wifi_client->print(F("Gyro.z="));channel.wifi_client->print(event.gyro.z);channel.wifi_client->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.wifi_client->print(F("Light="));channel.wifi_client->print(event.light);channel.wifi_client->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.wifi_client->print(F("AirPressure="));channel.wifi_client->print(event.pressure);channel.wifi_client->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.wifi_client->print(F("LinearAcceleration.x="));channel.wifi_client->print(event.acceleration.x);channel.wifi_client->println(F("m/s^2"));
	            channel.wifi_client->print(F("LinearAcceleration.y="));channel.wifi_client->print(event.acceleration.y);channel.wifi_client->println(F("m/s^2"));
	            channel.wifi_client->print(F("LinearAcceleration.z="));channel.wifi_client->print(event.acceleration.z);channel.wifi_client->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.wifi_client->print(F("Current="));channel.wifi_client->print(event.current);channel.wifi_client->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.wifi_client->print(F("ColorR="));channel.wifi_client->println(event.color.r);
	            channel.wifi_client->print(F("ColorG="));channel.wifi_client->println(event.color.g);
	            channel.wifi_client->print(F("ColorG="));channel.wifi_client->println(event.color.b);
	            channel.wifi_client->print(F("ColorRGBA="));channel.wifi_client->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.wifi_client->print(F("Value="));channel.wifi_client->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.wifi_client->print(F("Angle="));channel.wifi_client->print(event.angle);channel.wifi_client->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.wifi_client->print(F("1AxisGyro="));channel.wifi_client->print(event.roll);channel.wifi_client->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.wifi_client->print(F("Distance="));channel.wifi_client->print(event.distance);channel.wifi_client->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.wifi_client->print(F("Dust="));channel.wifi_client->print(event.dust);channel.wifi_client->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.wifi_client->print(F("Latitude="));channel.wifi_client->print(event.position.latitude);channel.wifi_client->println(F("deg"));
	            channel.wifi_client->print(F("Longtitude="));channel.wifi_client->print(event.position.longtitude);channel.wifi_client->println(F("deg"));
	            channel.wifi_client->print(F("Altitude="));channel.wifi_client->print(event.position.altitude);channel.wifi_client->println(F("m"));
	            channel.wifi_client->print(F("Dop="));channel.wifi_client->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.wifi_client->print(F("Year="));channel.wifi_client->println(event.date.year);
	            channel.wifi_client->print(F("Month="));channel.wifi_client->println(event.date.month);
	            channel.wifi_client->print(F("Day="));channel.wifi_client->println(event.date.day);
                channel.wifi_client->print(F("DayOfWeek="));channel.wifi_client->println(event.date.dayOfWeek);
	            channel.wifi_client->print(F("Hour="));channel.wifi_client->println(event.date.hour);
	            channel.wifi_client->print(F("Minute="));channel.wifi_client->println(event.date.minute);
	            channel.wifi_client->print(F("Second="));channel.wifi_client->println(event.date.second);
	            channel.wifi_client->print(F("Millisecond="));channel.wifi_client->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.wifi_client->print(F("SpeedKnot="));channel.wifi_client->print(event.speed);channel.wifi_client->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.wifi_client->print(F("Orientation="));channel.wifi_client->print(event.orientation.heading);channel.wifi_client->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.wifi_client->print(F("Value="));channel.wifi_client->println(event.value);
            }
            return true;
#endif /* __USE_WIFI_CLIENT__ */
#ifdef __USE_HTTP_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_HTTP_CLIENT :
            String workString = "Sensor_ID=" + String(event.sensor_id) + "\n"
                + "Sensor_Type=" + String(event.type) + "\n"
                + "Data_Time=" + String(event.timestamp) + "\n";
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                workString = workString + "Temperature=" + String(event.temperature) + "C\n";
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                workString = workString + "Humidity=" + String(event.relative_humidity) + "%\n";
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
                workString = workString + "Acceleration.x=" + String(event.acceleration.x) + "m/s^2\n"
                    + "Acceleration.y=" + String(event.acceleration.y) + "m/s^2\n"
                    + "Acceleration.z=" + String(event.acceleration.z) + "m/s^2\n";
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
                workString = workString + "Gyro.x=" + String(event.gyro.x) + "deg/s\n"
                    + "Gyro.y=" + String(event.gyro.y) + "deg/s\n"
                    + "Gyro.z=" + String(event.gyro.z) + "deg/s\n";
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                workString = workString + "Light=" + String(event.light) + "lux\n";
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                workString = workString + "AirPressure=" + String(event.pressure) + "hPa\n";
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                workString = workString + "LinearAcceleration.x=" + String(event.acceleration.x) + "m/s^2\n"
                    + "LinearAcceleration.y=" + String(event.acceleration.y) + "m/s^2\n"
                    + "LinearAcceleration.z=" + String(event.acceleration.z) + "m/s^2\n";
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
                workString = workString + "Current=" + String(event.current) + "mA\n";
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
                workString = workString + "ColorR" + String(event.color.r) + "\n"
                    + "ColorG" + String(event.color.g) + "\n"
                    + "ColorB=" + String(event.color.b) + "\n"
                    + "ColorRGBA=" + String(event.color.rgba) + "\n";
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
                workString = workString + "Value=" + String(event.value) + "\n";
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
                workString = workString + "Angle=" + String(event.angle) + "deg\n";
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
                workString = workString + "1AxisGyro=" + String(event.roll) + "deg/s\n";
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
                workString = workString + "Distance=" + String(event.distance) + "cm\n";
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
                workString = workString + "Dust=" + String(event.dust) + "pcs/0.01cf\n";
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
                workString = workString + "Latitude" + String(event.position.latitude) + "deg\n"
                    + "Longtitude" + String(event.position.longtitude) + "deg\n"
                    + "Altitude=" + String(event.position.altitude) + "m\n"
                    + "Dop=" + String(event.position.dop) + "\n";
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
                workString = workString + "Year" + String(event.date.year) + "\n"
                    + "Month" + String(event.date.month) + "\n"
                    + "Day" + String(event.date.day) + "\n"
                    + "DayOfWeek" + String(event.date.dayOfWeek) + "\n"
                    + "Hour" + String(event.date.hour) + "\n"
                    + "Minute" + String(event.date.minute) + "\n"
                    + "Second" + String(event.date.second) + "\n"
                    + "Millisecond" + String(event.date.millisecond) + "\n";
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
                workString = workString + "SpeedKnot=" + String(event.speed) + "knot\n";
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
                workString = workString + "Orientation=" + String(event.orientation.heading) + "deg\n";
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                workString = workString + "Value=" + String(event.value) + "\n";
            }
            channel.httpClient->post(urlPath, contentType, workString);
            return true;
#endif /* __USE_HTTP_CLIENT__ */
#ifdef __USE_MQTT_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_MQTT_CLIENT :
            if (size==0) {
                channel.mqttClient->beginMessage(topic);
            } else {
                channel.mqttClient->beginMessage(topic,size,retain,qos,dup);
            }
            channel.mqttClient->print(F("Sensor_ID="));channel.mqttClient->println(event.sensor_id);
	        channel.mqttClient->print(F("Sensor_Type="));channel.mqttClient->println(event.type);
	        channel.mqttClient->print(F("Data_Time="));channel.mqttClient->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.mqttClient->print(F("Temperature="));channel.mqttClient->print(event.temperature);channel.mqttClient->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.mqttClient->print(F("Humidity="));channel.mqttClient->print(event.relative_humidity);channel.mqttClient->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.mqttClient->print(F("Acceleration.x="));channel.mqttClient->print(event.acceleration.x);channel.mqttClient->println(F("m/s^2"));
	            channel.mqttClient->print(F("Acceleration.y="));channel.mqttClient->print(event.acceleration.y);channel.mqttClient->println(F("m/s^2"));
	            channel.mqttClient->print(F("Acceleration.z="));channel.mqttClient->print(event.acceleration.z);channel.mqttClient->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.mqttClient->print(F("Gyro.x="));channel.mqttClient->print(event.gyro.x);channel.mqttClient->println(F("deg/s"));
	            channel.mqttClient->print(F("Gyro.y="));channel.mqttClient->print(event.gyro.y);channel.mqttClient->println(F("deg/s"));
	            channel.mqttClient->print(F("Gyro.z="));channel.mqttClient->print(event.gyro.z);channel.mqttClient->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.mqttClient->print(F("Light="));channel.mqttClient->print(event.light);channel.mqttClient->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.mqttClient->print(F("AirPressure="));channel.mqttClient->print(event.pressure);channel.mqttClient->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.mqttClient->print(F("LinearAcceleration.x="));channel.mqttClient->print(event.acceleration.x);channel.mqttClient->println(F("m/s^2"));
	            channel.mqttClient->print(F("LinearAcceleration.y="));channel.mqttClient->print(event.acceleration.y);channel.mqttClient->println(F("m/s^2"));
	            channel.mqttClient->print(F("LinearAcceleration.z="));channel.mqttClient->print(event.acceleration.z);channel.mqttClient->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.mqttClient->print(F("Current="));channel.mqttClient->print(event.current);channel.mqttClient->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.mqttClient->print(F("ColorR="));channel.mqttClient->println(event.color.r);
	            channel.mqttClient->print(F("ColorG="));channel.mqttClient->println(event.color.g);
	            channel.mqttClient->print(F("ColorG="));channel.mqttClient->println(event.color.b);
	            channel.mqttClient->print(F("ColorRGBA="));channel.mqttClient->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.mqttClient->print(F("Value="));channel.mqttClient->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.mqttClient->print(F("Angle="));channel.mqttClient->print(event.angle);channel.mqttClient->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.mqttClient->print(F("1AxisGyro="));channel.mqttClient->print(event.roll);channel.mqttClient->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.mqttClient->print(F("Distance="));channel.mqttClient->print(event.distance);channel.mqttClient->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.mqttClient->print(F("Dust="));channel.mqttClient->print(event.dust);channel.mqttClient->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.mqttClient->print(F("Latitude="));channel.mqttClient->print(event.position.latitude);channel.mqttClient->println(F("deg"));
	            channel.mqttClient->print(F("Longtitude="));channel.mqttClient->print(event.position.longtitude);channel.mqttClient->println(F("deg"));
	            channel.mqttClient->print(F("Altitude="));channel.mqttClient->print(event.position.altitude);channel.mqttClient->println(F("m"));
	            channel.mqttClient->print(F("Dop="));channel.mqttClient->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.mqttClient->print(F("Year="));channel.mqttClient->println(event.date.year);
	            channel.mqttClient->print(F("Month="));channel.mqttClient->println(event.date.month);
	            channel.mqttClient->print(F("Day="));channel.mqttClient->println(event.date.day);
                channel.mqttClient->print(F("DayOfWeek="));channel.mqttClient->println(event.date.dayOfWeek);
	            channel.mqttClient->print(F("Hour="));channel.mqttClient->println(event.date.hour);
	            channel.mqttClient->print(F("Minute="));channel.mqttClient->println(event.date.minute);
	            channel.mqttClient->print(F("Second="));channel.mqttClient->println(event.date.second);
	            channel.mqttClient->print(F("Millisecond="));channel.mqttClient->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.mqttClient->print(F("SpeedKnot="));channel.mqttClient->print(event.speed);channel.mqttClient->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.mqttClient->print(F("Orientation="));channel.mqttClient->print(event.orientation.heading);channel.mqttClient->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.mqttClient->print(F("Value="));channel.mqttClient->println(event.value);
            }
            channel.mqttClient->endMessage();
            return true;
#endif /* __USE_MQTT_CLIENT__ */
        //default:
        //    return false;
    }
    return false;
}


bool AuxExSensorIO::EventOutputSyslog(sensors_event_t event) {
#ifdef __USE_RTC__
    date_t nowTime;
    rtc->getTime(&nowTime);
    String currentTime=String(nowTime.year)+"/"+String(nowTime.month)+"/"+String(nowTime.mday)+" "+rtc->getWday(nowTime.wday)+" "
        + String(nowTime.hour)+":"+String(nowTime.minute)+":"+String(nowTime.second);
#else /* __USE_RTC__ */
    String currentTime=String(millis());
#endif /* __USE_RTC__ */
    switch(event.type){
        case SENSOR_TYPE_ACCELEROMETER:
        case SENSOR_TYPE_MAGNETIC_FIELD:
        case SENSOR_TYPE_ORIENTATION:
        case SENSOR_TYPE_GYROSCOPE:
        case SENSOR_TYPE_LIGHT:
        case SENSOR_TYPE_PRESSURE:
        case SENSOR_TYPE_PROXIMITY:
        case SENSOR_TYPE_GRAVITY:
        case SENSOR_TYPE_LINEAR_ACCELERATION:
        case SENSOR_TYPE_ROTATION_VECTOR:
        case SENSOR_TYPE_RELATIVE_HUMIDITY:
        case SENSOR_TYPE_AMBIENT_TEMPERATURE:
        case SENSOR_TYPE_VOLTAGE:
        case SENSOR_TYPE_CURRENT:
        case SENSOR_TYPE_COLOR:
        case SENSOR_TYPE_SIMPLE:
        case SENSOR_TYPE_ANGLE:
        case SENSOR_TYPE_1AXIS_GYRO:
        case SENSOR_TYPE_DISTANCE:
        case SENSOR_TYPE_LARGE_INT:
        case SENSOR_TYPE_DUST:
        case SENSOR_TYPE_IRREMOTE:
        case SENSOR_TYPE_POSITION:
        case SENSOR_TYPE_DATE:
        case SENSOR_TYPE_SPEED_KNOT:
        case SENSOR_TYPE_SIMPLE_ANALOG:
            break;
        default:
            return false;
    }
    switch(channelType) {
#ifdef __USE_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SERIAL :
            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Sensor_ID="));channel.serial->println(event.sensor_id);
	        channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Sensor_Type="));channel.serial->println(event.type);
	        channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Data_Time="));channel.serial->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Temperature="));channel.serial->print(event.temperature);channel.serial->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Humidity="));channel.serial->print(event.relative_humidity);channel.serial->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Acceleration.x="));channel.serial->print(event.acceleration.x);channel.serial->println(F("m/s^2"));
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Acceleration.y="));channel.serial->print(event.acceleration.y);channel.serial->println(F("m/s^2"));
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Acceleration.z="));channel.serial->print(event.acceleration.z);channel.serial->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Gyro.x="));channel.serial->print(event.gyro.x);channel.serial->println(F("deg/s"));
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Gyro.y="));channel.serial->print(event.gyro.y);channel.serial->println(F("deg/s"));
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Gyro.z="));channel.serial->print(event.gyro.z);channel.serial->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Light="));channel.serial->print(event.light);channel.serial->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("AirPressure="));channel.serial->print(event.pressure);channel.serial->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("LinearAcceleration.x="));channel.serial->print(event.acceleration.x);channel.serial->println(F("m/s^2"));
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("LinearAcceleration.y="));channel.serial->print(event.acceleration.y);channel.serial->println(F("m/s^2"));
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("LinearAcceleration.z="));channel.serial->print(event.acceleration.z);channel.serial->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Current="));channel.serial->print(event.current);channel.serial->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("ColorR="));channel.serial->println(event.color.r);
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("ColorG="));channel.serial->println(event.color.g);
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("ColorG="));channel.serial->println(event.color.b);
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("ColorRGBA="));channel.serial->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Value="));channel.serial->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Angle="));channel.serial->print(event.angle);channel.serial->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("1AxisGyro="));channel.serial->print(event.roll);channel.serial->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Distance="));channel.serial->print(event.distance);channel.serial->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Dust="));channel.serial->print(event.dust);channel.serial->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Latitude="));channel.serial->print(event.position.latitude);channel.serial->println(F("deg"));
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Longtitude="));channel.serial->print(event.position.longtitude);channel.serial->println(F("deg"));
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Altitude="));channel.serial->print(event.position.altitude);channel.serial->println(F("m"));
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Dop="));channel.serial->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Year="));channel.serial->println(event.date.year);
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Month="));channel.serial->println(event.date.month);
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Day="));channel.serial->println(event.date.day);
                channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("DayOfWeek="));channel.serial->println(event.date.dayOfWeek);
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Hour="));channel.serial->println(event.date.hour);
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Minute="));channel.serial->println(event.date.minute);
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Second="));channel.serial->println(event.date.second);
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Millisecond="));channel.serial->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("SpeedKnot="));channel.serial->print(event.speed);channel.serial->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Orientation="));channel.serial->print(event.orientation.heading);channel.serial->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.serial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.serial->print(F("Value="));channel.serial->println(event.value);
            }
            return true;
#endif /* __USE_SERIAL__ */
#ifdef __USE_SOFT_SERIAL__
        case AUSEX_OUTPUT_CHANNEL_SOFT_SERIAL :
            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Sensor_ID="));channel.sserial->println(event.sensor_id);
	        channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Sensor_Type="));channel.sserial->println(event.type);
	        channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Data_Time="));channel.sserial->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Temperature="));channel.sserial->print(event.temperature);channel.sserial->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Humidity="));channel.sserial->print(event.relative_humidity);channel.sserial->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Acceleration.x="));channel.sserial->print(event.acceleration.x);channel.sserial->println(F("m/s^2"));
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Acceleration.y="));channel.sserial->print(event.acceleration.y);channel.sserial->println(F("m/s^2"));
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Acceleration.z="));channel.sserial->print(event.acceleration.z);channel.sserial->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Gyro.x="));channel.sserial->print(event.gyro.x);channel.sserial->println(F("deg/s"));
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Gyro.y="));channel.sserial->print(event.gyro.y);channel.sserial->println(F("deg/s"));
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Gyro.z="));channel.sserial->print(event.gyro.z);channel.sserial->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Light="));channel.sserial->print(event.light);channel.sserial->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("AirPressure="));channel.sserial->print(event.pressure);channel.sserial->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("LinearAcceleration.x="));channel.sserial->print(event.acceleration.x);channel.sserial->println(F("m/s^2"));
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("LinearAcceleration.y="));channel.sserial->print(event.acceleration.y);channel.sserial->println(F("m/s^2"));
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("LinearAcceleration.z="));channel.sserial->print(event.acceleration.z);channel.sserial->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Current="));channel.sserial->print(event.current);channel.sserial->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("ColorR="));channel.sserial->println(event.color.r);
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("ColorG="));channel.sserial->println(event.color.g);
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("ColorG="));channel.sserial->println(event.color.b);
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("ColorRGBA="));channel.sserial->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Value="));channel.sserial->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Angle="));channel.sserial->print(event.angle);channel.sserial->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("1AxisGyro="));channel.sserial->print(event.roll);channel.sserial->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Distance="));channel.sserial->print(event.distance);channel.sserial->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Dust="));channel.sserial->print(event.dust);channel.sserial->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Latitude="));channel.sserial->print(event.position.latitude);channel.sserial->println(F("deg"));
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Longtitude="));channel.sserial->print(event.position.longtitude);channel.sserial->println(F("deg"));
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Altitude="));channel.sserial->print(event.position.altitude);channel.sserial->println(F("m"));
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Dop="));channel.sserial->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Year="));channel.sserial->println(event.date.year);
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Month="));channel.sserial->println(event.date.month);
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Day="));channel.sserial->println(event.date.day);
                channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("DayOfWeek="));channel.sserial->println(event.date.dayOfWeek);
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Hour="));channel.sserial->println(event.date.hour);
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Minute="));channel.sserial->println(event.date.minute);
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Second="));channel.sserial->println(event.date.second);
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Millisecond="));channel.sserial->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("SpeedKnot="));channel.sserial->print(event.speed);channel.sserial->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Orientation="));channel.sserial->print(event.orientation.heading);channel.sserial->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.sserial->print  (currentTime+" " + hostName + " " + appName +" : ");channel.sserial->print(F("Value="));channel.sserial->println(event.value);
            }
            return true;
#endif /* __USE_SOFT_SERIAL__ */
#ifdef __USE_SD__
        case AUSEX_OUTPUT_CHANNEL_FILE :
            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Sensor_ID="));channel.file->println(event.sensor_id);
	        channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Sensor_Type="));channel.file->println(event.type);
	        channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Data_Time="));channel.file->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Temperature="));channel.file->print(event.temperature);channel.file->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Humidity="));channel.file->print(event.relative_humidity);channel.file->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Acceleration.x="));channel.file->print(event.acceleration.x);channel.file->println(F("m/s^2"));
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Acceleration.y="));channel.file->print(event.acceleration.y);channel.file->println(F("m/s^2"));
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Acceleration.z="));channel.file->print(event.acceleration.z);channel.file->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Gyro.x="));channel.file->print(event.gyro.x);channel.file->println(F("deg/s"));
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Gyro.y="));channel.file->print(event.gyro.y);channel.file->println(F("deg/s"));
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Gyro.z="));channel.file->print(event.gyro.z);channel.file->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Light="));channel.file->print(event.light);channel.file->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("AirPressure="));channel.file->print(event.pressure);channel.file->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("LinearAcceleration.x="));channel.file->print(event.acceleration.x);channel.file->println(F("m/s^2"));
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("LinearAcceleration.y="));channel.file->print(event.acceleration.y);channel.file->println(F("m/s^2"));
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("LinearAcceleration.z="));channel.file->print(event.acceleration.z);channel.file->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Current="));channel.file->print(event.current);channel.file->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("ColorR="));channel.file->println(event.color.r);
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("ColorG="));channel.file->println(event.color.g);
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("ColorG="));channel.file->println(event.color.b);
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("ColorRGBA="));channel.file->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Value="));channel.file->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Angle="));channel.file->print(event.angle);channel.file->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("1AxisGyro="));channel.file->print(event.roll);channel.file->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Distance="));channel.file->print(event.distance);channel.file->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Dust="));channel.file->print(event.dust);channel.file->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Latitude="));channel.file->print(event.position.latitude);channel.file->println(F("deg"));
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Longtitude="));channel.file->print(event.position.longtitude);channel.file->println(F("deg"));
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Altitude="));channel.file->print(event.position.altitude);channel.file->println(F("m"));
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Dop="));channel.file->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Year="));channel.file->println(event.date.year);
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Month="));channel.file->println(event.date.month);
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Day="));channel.file->println(event.date.day);
                channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("DayOfWeek="));channel.file->println(event.date.dayOfWeek);
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Hour="));channel.file->println(event.date.hour);
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Minute="));channel.file->println(event.date.minute);
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Second="));channel.file->println(event.date.second);
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Millisecond="));channel.file->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("SpeedKnot="));channel.file->print(event.speed);channel.file->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Orientation="));channel.file->print(event.orientation.heading);channel.file->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.file->print  (currentTime+" " + hostName + " " + appName +" : ");channel.file->print(F("Value="));channel.file->println(event.value);
            }
            return true;
#endif /* __USE_SD__ */
#ifdef __USE_ETHERNET_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_ETHERNET_CLIENT :
            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Sensor_ID="));channel.client->println(event.sensor_id);
	        channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Sensor_Type="));channel.client->println(event.type);
	        channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Data_Time="));channel.client->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Temperature="));channel.client->print(event.temperature);channel.client->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Humidity="));channel.client->print(event.relative_humidity);channel.client->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Acceleration.x="));channel.client->print(event.acceleration.x);channel.client->println(F("m/s^2"));
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Acceleration.y="));channel.client->print(event.acceleration.y);channel.client->println(F("m/s^2"));
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Acceleration.z="));channel.client->print(event.acceleration.z);channel.client->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Gyro.x="));channel.client->print(event.gyro.x);channel.client->println(F("deg/s"));
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Gyro.y="));channel.client->print(event.gyro.y);channel.client->println(F("deg/s"));
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Gyro.z="));channel.client->print(event.gyro.z);channel.client->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Light="));channel.client->print(event.light);channel.client->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("AirPressure="));channel.client->print(event.pressure);channel.client->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("LinearAcceleration.x="));channel.client->print(event.acceleration.x);channel.client->println(F("m/s^2"));
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("LinearAcceleration.y="));channel.client->print(event.acceleration.y);channel.client->println(F("m/s^2"));
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("LinearAcceleration.z="));channel.client->print(event.acceleration.z);channel.client->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Current="));channel.client->print(event.current);channel.client->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("ColorR="));channel.client->println(event.color.r);
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("ColorG="));channel.client->println(event.color.g);
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("ColorG="));channel.client->println(event.color.b);
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("ColorRGBA="));channel.client->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Value="));channel.client->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Angle="));channel.client->print(event.angle);channel.client->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("1AxisGyro="));channel.client->print(event.roll);channel.client->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Distance="));channel.client->print(event.distance);channel.client->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Dust="));channel.client->print(event.dust);channel.client->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Latitude="));channel.client->print(event.position.latitude);channel.client->println(F("deg"));
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Longtitude="));channel.client->print(event.position.longtitude);channel.client->println(F("deg"));
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Altitude="));channel.client->print(event.position.altitude);channel.client->println(F("m"));
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Dop="));channel.client->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Year="));channel.client->println(event.date.year);
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Month="));channel.client->println(event.date.month);
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Day="));channel.client->println(event.date.day);
                channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("DayOfWeek="));channel.client->println(event.date.dayOfWeek);
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Hour="));channel.client->println(event.date.hour);
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Minute="));channel.client->println(event.date.minute);
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Second="));channel.client->println(event.date.second);
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Millisecond="));channel.client->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("SpeedKnot="));channel.client->print(event.speed);channel.client->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Orientation="));channel.client->print(event.orientation.heading);channel.client->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.client->print(F("Value="));channel.client->println(event.value);
            }
            return true;
#endif /* __USE_ETHERNET_CLIENT__ */
#ifdef __USE_WIFI_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_WIFI_CLIENT :
            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Sensor_ID="));channel.wifi_client->println(event.sensor_id);
	        channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Sensor_Type="));channel.wifi_client->println(event.type);
	        channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Data_Time="));channel.wifi_client->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Temperature="));channel.wifi_client->print(event.temperature);channel.wifi_client->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Humidity="));channel.wifi_client->print(event.relative_humidity);channel.wifi_client->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Acceleration.x="));channel.wifi_client->print(event.acceleration.x);channel.wifi_client->println(F("m/s^2"));
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Acceleration.y="));channel.wifi_client->print(event.acceleration.y);channel.wifi_client->println(F("m/s^2"));
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Acceleration.z="));channel.wifi_client->print(event.acceleration.z);channel.wifi_client->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Gyro.x="));channel.wifi_client->print(event.gyro.x);channel.wifi_client->println(F("deg/s"));
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Gyro.y="));channel.wifi_client->print(event.gyro.y);channel.wifi_client->println(F("deg/s"));
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Gyro.z="));channel.wifi_client->print(event.gyro.z);channel.wifi_client->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Light="));channel.wifi_client->print(event.light);channel.wifi_client->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("AirPressure="));channel.wifi_client->print(event.pressure);channel.wifi_client->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("LinearAcceleration.x="));channel.wifi_client->print(event.acceleration.x);channel.wifi_client->println(F("m/s^2"));
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("LinearAcceleration.y="));channel.wifi_client->print(event.acceleration.y);channel.wifi_client->println(F("m/s^2"));
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("LinearAcceleration.z="));channel.wifi_client->print(event.acceleration.z);channel.wifi_client->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Current="));channel.wifi_client->print(event.current);channel.wifi_client->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("ColorR="));channel.wifi_client->println(event.color.r);
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("ColorG="));channel.wifi_client->println(event.color.g);
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("ColorG="));channel.wifi_client->println(event.color.b);
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("ColorRGBA="));channel.wifi_client->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Value="));channel.wifi_client->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Angle="));channel.wifi_client->print(event.angle);channel.wifi_client->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("1AxisGyro="));channel.wifi_client->print(event.roll);channel.wifi_client->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Distance="));channel.wifi_client->print(event.distance);channel.wifi_client->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Dust="));channel.wifi_client->print(event.dust);channel.wifi_client->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Latitude="));channel.wifi_client->print(event.position.latitude);channel.wifi_client->println(F("deg"));
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Longtitude="));channel.wifi_client->print(event.position.longtitude);channel.wifi_client->println(F("deg"));
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Altitude="));channel.wifi_client->print(event.position.altitude);channel.wifi_client->println(F("m"));
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Dop="));channel.wifi_client->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Year="));channel.wifi_client->println(event.date.year);
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Month="));channel.wifi_client->println(event.date.month);
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Day="));channel.wifi_client->println(event.date.day);
                channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("DayOfWeek="));channel.wifi_client->println(event.date.dayOfWeek);
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Hour="));channel.wifi_client->println(event.date.hour);
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Minute="));channel.wifi_client->println(event.date.minute);
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Second="));channel.wifi_client->println(event.date.second);
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Millisecond="));channel.wifi_client->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("SpeedKnot="));channel.wifi_client->print(event.speed);channel.wifi_client->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Orientation="));channel.wifi_client->print(event.orientation.heading);channel.wifi_client->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.wifi_client->print  (currentTime+" " + hostName + " " + appName +" : ");channel.wifi_client->print(F("Value="));channel.wifi_client->println(event.value);
            }
            return true;
#endif /* __USE_WIFI_CLIENT__ */
#ifdef __USE_HTTP_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_HTTP_CLIENT :
            String workString = currentTime+" " + hostName + " " + appName +" : " + "Sensor_ID=" + String(event.sensor_id) + "\n"
                + currentTime+" " + hostName + " " + appName +" : " + "Sensor_Type=" + String(event.type) + "\n"
                + currentTime+" " + hostName + " " + appName +" : " + "Data_Time=" + String(event.timestamp) + "\n";
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Temperature=" + String(event.temperature) + "C\n";
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Humidity=" + String(event.relative_humidity) + "%\n";
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Acceleration.x=" + String(event.acceleration.x) + "m/s^2\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Acceleration.y=" + String(event.acceleration.y) + "m/s^2\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Acceleration.z=" + String(event.acceleration.z) + "m/s^2\n";
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Gyro.x=" + String(event.gyro.x) + "deg/s\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Gyro.y=" + String(event.gyro.y) + "deg/s\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Gyro.z=" + String(event.gyro.z) + "deg/s\n";
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Light=" + String(event.light) + "lux\n";
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "AirPressure=" + String(event.pressure) + "hPa\n";
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "LinearAcceleration.x=" + String(event.acceleration.x) + "m/s^2\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "LinearAcceleration.y=" + String(event.acceleration.y) + "m/s^2\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "LinearAcceleration.z=" + String(event.acceleration.z) + "m/s^2\n";
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Current=" + String(event.current) + "mA\n";
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "ColorR=" + String(event.color.r) + "\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "ColorG=" + String(event.color.g) + "\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "ColorB=" + String(event.color.b) + "\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "ColorRGBA=" + String(event.color.rgba) + "\n";
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Value=" + String(event.pressure) + "\n";
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Angle=" + String(event.angle) + "deg\n";
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "1AxisGyro=" + String(event.roll) + "deg/s\n";
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Distance=" + String(event.distance) + "cm\n";
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Dust=" + String(event.dust) + "pcs/0.01cf\n";
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Latitude=" + String(event.position.latitude) + "deg\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Longtitude=" + String(event.position.longtitude) + "deg\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Altitude=" + String(event.position.altitude) + "m\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Dop=" + String(event.position.dop) + "\n";
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Year=" + String(event.date.year) + "\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Month=" + String(event.date.month) + "\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Day=" + String(event.date.day) + "\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "DayOfWeek=" + String(event.date.dayOfWeek) + "\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Hour=" + String(event.date.hour) + "\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Minute=" + String(event.date.minute) + "\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Second=" + String(event.date.second) + "\n"
                    + currentTime+" " + hostName + " " + appName +" : " + "Millisecond=" + String(event.date.millisecond) + "\n";
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "SpeedKnot=" + String(event.speed) + "knot\n";
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Orientation=" + String(event.orientation.heading) + "deg\n";
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
                workString = workString + currentTime+" " + hostName + " " + appName +" : " + "Value=" + String(event.value) + "\n";
            }
            channel.httpClient->post(urlPath, contentType, workString);
            return true;
#endif /* __USE_HTTP_CLIENT__ */
#ifdef __USE_MQTT_CLIENT__
        case AUSEX_OUTPUT_CHANNEL_MQTT_CLIENT :
            if (size==0) {
                //channel.mqttClient->beginMessage(topic, 512, false, 0, false);
                channel.mqttClient->beginMessage(topic);
            } else {
                //channel.mqttClient->beginMessage(topic, size, false, 0, false);
                channel.mqttClient->beginMessage(topic, size);
            }
            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Sensor_ID="));channel.mqttClient->println(event.sensor_id);
	        channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Sensor_Type="));channel.mqttClient->println(event.type);
	        channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Data_Time="));channel.mqttClient->println(event.timestamp);
            //if ( event.type == SENSOR_TYPE_MAGNETIC_FIELD ) {
            //}
            //if ( event.type == SENSOR_TYPE_PROXIMITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_GRAVITY ) {
            //}
            //if ( event.type == SENSOR_TYPE_ROTATION_VECTOR ) {
            //}
            //if ( event.type == SENSOR_TYPE_VOLTAGE ) {
            //}
            //if ( event.type == SENSOR_TYPE_LARGE_INT ) {
            //}
            //if ( event.type == SENSOR_TYPE_IRREMOTE ) {
            //}
            if ( event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE ) {
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Temperature="));channel.mqttClient->print(event.temperature);channel.mqttClient->println(F("C"));
            }
            if ( event.type == SENSOR_TYPE_RELATIVE_HUMIDITY ) {
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Humidity="));channel.mqttClient->print(event.relative_humidity);channel.mqttClient->println(F("%"));
            }
            if ( event.type == SENSOR_TYPE_ACCELEROMETER ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Acceleration.x="));channel.mqttClient->print(event.acceleration.x);channel.mqttClient->println(F("m/s^2"));
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Acceleration.y="));channel.mqttClient->print(event.acceleration.y);channel.mqttClient->println(F("m/s^2"));
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Acceleration.z="));channel.mqttClient->print(event.acceleration.z);channel.mqttClient->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_GYROSCOPE ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Gyro.x="));channel.mqttClient->print(event.gyro.x);channel.mqttClient->println(F("deg/s"));
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Gyro.y="));channel.mqttClient->print(event.gyro.y);channel.mqttClient->println(F("deg/s"));
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Gyro.z="));channel.mqttClient->print(event.gyro.z);channel.mqttClient->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_LIGHT ) {
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Light="));channel.mqttClient->print(event.light);channel.mqttClient->println(F("lux"));
            }
            if ( event.type == SENSOR_TYPE_PRESSURE ) {
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("AirPressure="));channel.mqttClient->print(event.pressure);channel.mqttClient->println(F("hPa"));
            }
            if ( event.type == SENSOR_TYPE_LINEAR_ACCELERATION ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("LinearAcceleration.x="));channel.mqttClient->print(event.acceleration.x);channel.mqttClient->println(F("m/s^2"));
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("LinearAcceleration.y="));channel.mqttClient->print(event.acceleration.y);channel.mqttClient->println(F("m/s^2"));
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("LinearAcceleration.z="));channel.mqttClient->print(event.acceleration.z);channel.mqttClient->println(F("m/s^2"));
            }
            if ( event.type == SENSOR_TYPE_CURRENT ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Current="));channel.mqttClient->print(event.current);channel.mqttClient->println(F("mA"));
            }
            if ( event.type == SENSOR_TYPE_COLOR ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("ColorR="));channel.mqttClient->println(event.color.r);
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("ColorG="));channel.mqttClient->println(event.color.g);
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("ColorG="));channel.mqttClient->println(event.color.b);
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("ColorRGBA="));channel.mqttClient->println(event.color.rgba);
            }
            if ( event.type == SENSOR_TYPE_SIMPLE ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Value="));channel.mqttClient->println(event.value);
            }
            if ( event.type == SENSOR_TYPE_ANGLE ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Angle="));channel.mqttClient->print(event.angle);channel.mqttClient->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_1AXIS_GYRO ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("1AxisGyro="));channel.mqttClient->print(event.roll);channel.mqttClient->println(F("deg/s"));
            }
            if ( event.type == SENSOR_TYPE_DISTANCE ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Distance="));channel.mqttClient->print(event.distance);channel.mqttClient->println(F("cm"));
            }
            if ( event.type == SENSOR_TYPE_DUST ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Dust="));channel.mqttClient->print(event.dust);channel.mqttClient->println(F("pcs/0.01cf"));
            }
            if ( event.type == SENSOR_TYPE_POSITION ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Latitude="));channel.mqttClient->print(event.position.latitude);channel.mqttClient->println(F("deg"));
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Longtitude="));channel.mqttClient->print(event.position.longtitude);channel.mqttClient->println(F("deg"));
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Altitude="));channel.mqttClient->print(event.position.altitude);channel.mqttClient->println(F("m"));
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Dop="));channel.mqttClient->println(event.position.dop);
            }
            if ( event.type == SENSOR_TYPE_DATE ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Year="));channel.mqttClient->println(event.date.year);
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Month="));channel.mqttClient->println(event.date.month);
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Day="));channel.mqttClient->println(event.date.day);
                channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("DayOfWeek="));channel.mqttClient->println(event.date.dayOfWeek);
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Hour="));channel.mqttClient->println(event.date.hour);
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Minute="));channel.mqttClient->println(event.date.minute);
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Second="));channel.mqttClient->println(event.date.second);
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Millisecond="));channel.mqttClient->println(event.date.millisecond);
            }
            if ( event.type == SENSOR_TYPE_SPEED_KNOT ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("SpeedKnot="));channel.mqttClient->print(event.speed);channel.mqttClient->println(F("knot"));
            }
            if ( event.type == SENSOR_TYPE_ORIENTATION ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Orientation="));channel.mqttClient->print(event.orientation.heading);channel.mqttClient->println(F("deg"));
            }
            if ( event.type == SENSOR_TYPE_SIMPLE_ANALOG ) {
	            channel.mqttClient->print  (currentTime+" " + hostName + " " + appName +" : ");channel.mqttClient->print(F("Value="));channel.mqttClient->println(event.value);
            }
            //channel.mqttClient->flush();
            channel.mqttClient->endMessage();
            return true;
#endif /* __USE_MQTT_CLIENT__ */
        //default:
        //    return false;
    }
    return false;
}

bool AuxExSensorIO::EventOutput(sensors_event_t event){
    switch(formatType) {
        case FORMAT_TYPE_PLAIN_TEXT:
            return EventOutputPlain(event);
        case FORMAT_TYPE_JSON:
            return EventOutputJson(event);
        case FORMAT_TYPE_SYSLOG:
            return EventOutputSyslog(event);
        default:
            return false;
    }
}

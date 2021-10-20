/*
* Copyright (C) 2008 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software< /span>
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/* Update by K. Townsend (Adafruit Industries) for lighter typedefs, and
 * extended sensor support to include color, voltage and current */
 
#ifndef _ADAFRUIT_SENSOR_EXTENDED_H
#define _ADAFRUIT_SENSOR_EXTENDED_H

#if ARDUINO >= 100
  #include "Arduino.h"
  #include "Print.h"
#else
  #include "WProgram.h"
#endif

/* Intentionally modeled after sensors.h in the Android API:
 * https://github.com/android/platform_hardware_libhardware/blob/master/include/hardware/sensors.h */

/* Constants */
#define SENSORS_GRAVITY_EARTH             (9.80665F)              /**< Earth's gravity in m/s^2 */
#define SENSORS_GRAVITY_MOON              (1.6F)                  /**< The moon's gravity in m/s^2 */
#define SENSORS_GRAVITY_SUN               (275.0F)                /**< The sun's gravity in m/s^2 */
#define SENSORS_GRAVITY_STANDARD          (SENSORS_GRAVITY_EARTH)
#define SENSORS_MAGFIELD_EARTH_MAX        (60.0F)                 /**< Maximum magnetic field on Earth's surface */
#define SENSORS_MAGFIELD_EARTH_MIN        (30.0F)                 /**< Minimum magnetic field on Earth's surface */
#define SENSORS_PRESSURE_SEALEVELHPA      (1013.25F)              /**< Average sea level pressure is 1013.25 hPa */
#define SENSORS_DPS_TO_RADS               (0.017453293F)          /**< Degrees/s to rad/s multiplier */
#define SENSORS_GAUSS_TO_MICROTESLA       (100)                   /**< Gauss to micro-Tesla multiplier */

#define SENSORS_NAME_LENGTH               32


/** Sensor types */
typedef enum
{
    SENSOR_TYPE_ACCELEROMETER         = (1),   /**< Gravity + linear acceleration */
    SENSOR_TYPE_MAGNETIC_FIELD        = (2),
    SENSOR_TYPE_ORIENTATION           = (3),
    SENSOR_TYPE_GYROSCOPE             = (4),
    SENSOR_TYPE_LIGHT                 = (5),
    SENSOR_TYPE_PRESSURE              = (6),
    SENSOR_TYPE_PROXIMITY             = (8),
    SENSOR_TYPE_GRAVITY               = (9),
    SENSOR_TYPE_LINEAR_ACCELERATION   = (10),  /**< Acceleration not including gravity */
    SENSOR_TYPE_ROTATION_VECTOR       = (11),
    SENSOR_TYPE_RELATIVE_HUMIDITY     = (12),
    SENSOR_TYPE_AMBIENT_TEMPERATURE   = (13),
    SENSOR_TYPE_VOLTAGE               = (15),
    SENSOR_TYPE_CURRENT               = (16),
    SENSOR_TYPE_COLOR                 = (17),
    SENSOR_TYPE_SIMPLE                = (18),
    SENSOR_TYPE_ANGLE                 = (19),
    SENSOR_TYPE_1AXIS_GYRO            = (20),
    SENSOR_TYPE_DISTANCE              = (21),
    SENSOR_TYPE_LARGE_INT             = (22),
    SENSOR_TYPE_DUST                  = (23),
    SENSOR_TYPE_IRREMOTE              = (24),
    SENSOR_TYPE_POSITION              = (25),
    SENSOR_TYPE_DATE                  = (26),
    SENSOR_TYPE_SPEED_KNOT            = (27),
    SENSOR_TYPE_SIMPLE_ANALOG         = (28)
} sensors_type_t;

/** unit type **/
typedef enum
{
    UNIT_TYPE_UNDEF           = (1),  /* C */
    UNIT_TYPE_CELCIUS         = (2),  /* C */
    UNIT_TYPE_PERCENTAGE      = (3),  /* % */
    UNIT_TYPE_METER_PER_SEC_2 = (4),  /* m/s^2 */
    UNIT_TYPE_MICRO_TESLA     = (5),  /* micro Tesla */
    UNIT_TYPE_RAD_PER_SEC     = (6),  /* radian/sec */
    UNIT_TYPE_LUX             = (7),  /* lux */
    UNIT_TYPE_HECTO_PASCAL    = (8),  /* hPa */
    UNIT_TYPE_VOLT            = (9),  /* V */
    UNIT_TYPE_MILLI_ANPERE    = (10), /* mA */
    UNIT_TYPE_DEGREE          = (11), /* degree */
    UNIT_TYPE_DEGREE_PER_SEC  = (12), /* degree / s */
    UNIT_TYPE_CENTI_METER     = (13), /* cm */
    UNIT_TYPE_PCS_PER_CF      = (14), /* pcs/0.01cf */
    UNIT_TYPE_METER           = (15), /* m */
    UNIT_TYPE_KNOT            = (16)  /* knot */
} unit_type_t;

/** struct sensors_vec_s is used to return a vector in a common format. */
typedef struct {
    union {
        float v[3];
        struct {
            float x;
            float y;
            float z;
        };
        /* Orientation sensors */
        struct {
            float roll;    /**< Rotation around the longitudinal axis (the plane body, 'X axis'). Roll is positive and increasing when moving downward. -90ｰ<=roll<=90ｰ */
            float pitch;   /**< Rotation around the lateral axis (the wing span, 'Y axis'). Pitch is positive and increasing when moving upwards. -180ｰ<=pitch<=180ｰ) */
            float heading; /**< Angle between the longitudinal axis (the plane body) and magnetic north, measured clockwise when viewing from the top of the device. 0-359ｰ */
        };
    };
    int8_t status;
    uint8_t reserved[3];
} sensors_vec_t;

/** struct sensors_color_s is used to return color data in a common format. */
typedef struct {
    union {
        float c[3];
        /* RGB color space */
        struct {
            float r;       /**< Red component */
            float g;       /**< Green component */
            float b;       /**< Blue component */
        };
    };
    uint32_t rgba;         /**< 24-bit RGBA value */
} sensors_color_t;

/** output of IR remote receiver **/
typedef struct {
    uint8_t  overflow;    // ir data is too long
    uint8_t  decode_type; // VENDOR
    uint16_t address;     // used by Panasonic and Sharp
    uint32_t value;       // parsed data
} sensors_irremote_t;

typedef struct {
    float longtitude;
    float latitude;
    float altitude;
    float dop;
} sensors_position_t;

typedef struct {
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  dayOfWeek;
    uint8_t  hour;
    uint8_t  minute;
    uint8_t  second;
    int16_t  millisecond;
} sensors_date_t;

/* Sensor event (36 bytes) */
/** struct sensor_event_s is used to provide a single sensor event in a common format. */
typedef struct
{
    int32_t size;                             /**< must be sizeof(struct sensors_event_t) */
    int32_t sensor_id;                        /**< unique sensor identifier */
    int32_t type;                             /**< sensor type */
    int32_t reserved0;                        /**< reserved */
    unsigned long timestamp;                       /**< current time in milliseconds */
    union
    {
        float              data[4];
        sensors_vec_t      acceleration;       /**< acceleration values are in meter per second per second (m/s^2) */
        sensors_vec_t      magnetic;           /**< magnetic vector values are in micro-Tesla (uT) */
        sensors_vec_t      orientation;        /**< orientation values are in degrees */
        sensors_vec_t      gyro;               /**< gyroscope values are in rad/s */
        float              temperature;        /**< temperature is in degrees centigrade (Celsius) */
        float              distance;           /**< distance in centimeters */
        float              light;              /**< light in SI lux units */
        float              pressure;           /**< pressure in hectopascal (hPa) */
        float              relative_humidity;  /**< relative humidity in percent */
        float              current;            /**< current in milliamps (mA) */
        float              voltage;            /**< voltage in volts (V) */
        float              angle;              /**< angle (degree) */
        float              roll;               /**< 1 axis gyro (deg/s) */
        float              dust;               /**< */
        uint32_t           value;              /**< output value of analogRead() or digitalRead() */
        long               lvalue;             /**< output value of sensor that outputs large value */
        sensors_color_t    color;              /**< color in RGB component values */
        sensors_irremote_t irremote;
        sensors_position_t position;
        sensors_date_t     date;
        float              speed;
    };
} sensors_event_t;

/* Sensor details (40 bytes) */
/** struct sensor_s is used to describe basic information about a specific sensor. */
typedef struct
{
    char     name[SENSORS_NAME_LENGTH];       /**< sensor name */
    int32_t  version;                         /**< version of the hardware + driver */
    int32_t  sensor_id;                       /**< unique sensor identifier */
    int32_t  type;                            /**< this sensor's type (ex. SENSOR_TYPE_LIGHT) */
    float    max_value;                       /**< maximum value of this sensor's value in SI units */
    float    min_value;                       /**< minimum value of this sensor's value in SI units */
    float    resolution;                      /**< smallest difference between two values reported by this sensor */
    int32_t  min_delay;                       /**< min delay in microseconds between events. zero = not a constant rate */
    int32_t  init_delay;                      /**< 電源投入や初期化から計測結果が安定するまでに必要な待ち時間 */
} sensor_t;

class Adafruit_SensorEx {
    public:
        // Constructor(s)
        Adafruit_SensorEx() {}
        virtual ~Adafruit_SensorEx() {}

        // These must be defined by the subclass
        virtual bool enableAutoRange(bool enabled) = 0 ; /* レンジの変更がそもそもできないものはfalseを返す． */
        virtual int setMode(int mode) =0 ; /* 動作モード(レンジも含む)の設定を変更するための関数で動作モードがないセンサは -1 . 設定変更に失敗したら0, 設定変更に成功したら1 */
        virtual int getMode() =0 ; /* 動作モード(レンジも含む)の設定を変更するための関数で動作モードがないセンサは -1 */
        virtual bool getEvent(sensors_event_t*) = 0;
        virtual void getSensor(sensor_t*) = 0 ;
  
    private:
        bool _autoRange;
};

#endif /*  _ADAFRUIT_SENSOR_EXTENDED_H */


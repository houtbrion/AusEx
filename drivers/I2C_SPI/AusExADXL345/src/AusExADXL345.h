
#ifndef __AUSEX_ADXL345_H__
#define __AUSEX_ADXL345_H__

#include <AusEx.h>
#include <Wire.h>

#include <SPI.h>

#define _TEMPLATE_CLASS AusExADXL345

#define AUSEX_ADXL345_SENSOR_NAME "AusExADXL345"
#define AUSEX_ADXL345_SENSOR_TYPE SENSOR_TYPE_ACCELEROMETER
#define AUSEX_ADXL345_SENSOR_LIBRARY_VERSION 1
#define AUSEX_ADXL345_SENSOR_RETURN_VALUE acceleration
#define AUSEX_ADXL345_SENSOR_VALUE_TYPE sensors_vec_t
#define AUSEX_ADXL345_SENSOR_MIN_VALUE -156.9064F; /* -16g = 156.9064 m/s^2  */
#define AUSEX_ADXL345_SENSOR_MAX_VALUE  156.9064F; /*  16g = 156.9064 m/s^2  */
#define AUSEX_ADXL345_SENSOR_RESOLUTION 0.03923F;   /*  4mg = 0.0392266 m/s^2 */
#define AUSEX_ADXL345_SENSOR_MIN_DELAY 0
#define AUSEX_ADXL345_SENSOR_INIT_DELAY 0

#define AUSEX_ADXL345_DATARATE_3200_HZ     0b1111 // 1600Hz Bandwidth   140・ｽA IDD
#define AUSEX_ADXL345_DATARATE_1600_HZ     0b1110 //  800Hz Bandwidth    90・ｽA IDD
#define AUSEX_ADXL345_DATARATE_800_HZ      0b1101 //  400Hz Bandwidth   140・ｽA IDD
#define AUSEX_ADXL345_DATARATE_400_HZ      0b1100 //  200Hz Bandwidth   140・ｽA IDD
#define AUSEX_ADXL345_DATARATE_200_HZ      0b1011 //  100Hz Bandwidth   140・ｽA IDD
#define AUSEX_ADXL345_DATARATE_100_HZ      0b1010 //   50Hz Bandwidth   140・ｽA IDD
#define AUSEX_ADXL345_DATARATE_50_HZ       0b1001 //   25Hz Bandwidth    90・ｽA IDD
#define AUSEX_ADXL345_DATARATE_25_HZ       0b1000 // 12.5Hz Bandwidth    60・ｽA IDD
#define AUSEX_ADXL345_DATARATE_12_5_HZ     0b0111 // 6.25Hz Bandwidth    50・ｽA IDD
#define AUSEX_ADXL345_DATARATE_6_25HZ      0b0110 // 3.13Hz Bandwidth    45・ｽA IDD
#define AUSEX_ADXL345_DATARATE_3_13_HZ     0b0101 // 1.56Hz Bandwidth    40・ｽA IDD
#define AUSEX_ADXL345_DATARATE_1_56_HZ     0b0100 // 0.78Hz Bandwidth    34・ｽA IDD
#define AUSEX_ADXL345_DATARATE_0_78_HZ     0b0011 // 0.39Hz Bandwidth    23・ｽA IDD
#define AUSEX_ADXL345_DATARATE_0_39_HZ     0b0010 // 0.20Hz Bandwidth    23・ｽA IDD
#define AUSEX_ADXL345_DATARATE_0_20_HZ     0b0001 // 0.10Hz Bandwidth    23・ｽA IDD
#define AUSEX_ADXL345_DATARATE_0_10_HZ     0b0000  // 0.05Hz Bandwidth    23・ｽA IDD (default value)

#define AUSEX_ADXL345_RANGE_16_G           0b11   // +/- 16g
#define AUSEX_ADXL345_RANGE_8_G            0b10   // +/- 8g
#define AUSEX_ADXL345_RANGE_4_G            0b01   // +/- 4g
#define AUSEX_ADXL345_RANGE_2_G            0b00    // +/- 2g (default value)

uint8_t spixfer(uint8_t clock, uint8_t miso, uint8_t mosi, uint8_t data);
int        getModeParam(uint8_t, uint8_t);
uint8_t    getRangeParam(int);
uint8_t    getRateParam(int);

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define ADXL345_DEFAULT_ADDRESS     (0x53)  // Assumes ALT address pin low
#define AUSEX_ADXL345_SENSOR_DEFAULT_I2C_ADDR ADXL345_DEFAULT_ADDRESS
/*=========================================================================*/


/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
    #define ADXL345_REG_DEVID               (0x00)    // Device ID
    #define ADXL345_REG_THRESH_TAP          (0x1D)    // Tap threshold
    #define ADXL345_REG_OFSX                (0x1E)    // X-axis offset
    #define ADXL345_REG_OFSY                (0x1F)    // Y-axis offset
    #define ADXL345_REG_OFSZ                (0x20)    // Z-axis offset
    #define ADXL345_REG_DUR                 (0x21)    // Tap duration
    #define ADXL345_REG_LATENT              (0x22)    // Tap latency
    #define ADXL345_REG_WINDOW              (0x23)    // Tap window
    #define ADXL345_REG_THRESH_ACT          (0x24)    // Activity threshold
    #define ADXL345_REG_THRESH_INACT        (0x25)    // Inactivity threshold
    #define ADXL345_REG_TIME_INACT          (0x26)    // Inactivity time
    #define ADXL345_REG_ACT_INACT_CTL       (0x27)    // Axis enable control for activity and inactivity detection
    #define ADXL345_REG_THRESH_FF           (0x28)    // Free-fall threshold
    #define ADXL345_REG_TIME_FF             (0x29)    // Free-fall time
    #define ADXL345_REG_TAP_AXES            (0x2A)    // Axis control for single/double tap
    #define ADXL345_REG_ACT_TAP_STATUS      (0x2B)    // Source for single/double tap
    #define ADXL345_REG_BW_RATE             (0x2C)    // Data rate and power mode control
    #define ADXL345_REG_POWER_CTL           (0x2D)    // Power-saving features control
    #define ADXL345_REG_INT_ENABLE          (0x2E)    // Interrupt enable control
    #define ADXL345_REG_INT_MAP             (0x2F)    // Interrupt mapping control
    #define ADXL345_REG_INT_SOURCE          (0x30)    // Source of interrupts
    #define ADXL345_REG_DATA_FORMAT         (0x31)    // Data format control
    #define ADXL345_REG_DATAX0              (0x32)    // X-axis data 0
    #define ADXL345_REG_DATAX1              (0x33)    // X-axis data 1
    #define ADXL345_REG_DATAY0              (0x34)    // Y-axis data 0
    #define ADXL345_REG_DATAY1              (0x35)    // Y-axis data 1
    #define ADXL345_REG_DATAZ0              (0x36)    // Z-axis data 0
    #define ADXL345_REG_DATAZ1              (0x37)    // Z-axis data 1
    #define ADXL345_REG_FIFO_CTL            (0x38)    // FIFO control
    #define ADXL345_REG_FIFO_STATUS         (0x39)    // FIFO status
/*=========================================================================*/

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
    #define ADXL345_MG2G_MULTIPLIER (0.004)  // 4mg per lsb
/*=========================================================================*/


class AusExADXL345 : public Adafruit_SensorEx {
    public:
        AusExADXL345(TwoWire *theWire, int32_t sensorID = -1);
        AusExADXL345(uint8_t clock, uint8_t miso, uint8_t mosi, uint8_t cs, int32_t sensorID = -1);

        bool       begin(uint32_t addr=AUSEX_ADXL345_SENSOR_DEFAULT_I2C_ADDR);
        bool       enableAutoRange(bool enabled);
        int        setMode(int mode);
        int        getMode();
        bool       getEvent(sensors_event_t*);
        void       getSensor(sensor_t*);
        int getModeParam(uint8_t, uint8_t);
        uint8_t getRangeParam(int);
        uint8_t getRateParam(int);

    private:
        void       setRange(uint8_t );
        uint8_t    getRange(void);
        void       setDataRate(uint8_t );
        uint8_t getDataRate(void);
        inline uint8_t  i2cread(void);
        inline void     i2cwrite(uint8_t );
        void       writeRegister(uint8_t , uint8_t );
        uint8_t    readRegister(uint8_t );
        int16_t    read16(uint8_t );
        uint8_t    getDeviceID(void);
        int16_t    getX(void), getY(void), getZ(void);

        int32_t _sensorID;
        uint8_t _range;
        uint8_t _rate;
        uint8_t _clk, _do, _di, _cs;
        bool    _i2c;
        int8_t  _i2caddr;
        TwoWire *_i2c_if;
        bool _autoRange;
};


#endif /* __AUSEX_ADXL345_H__ */

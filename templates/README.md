# ドライバのテンプレート
このディレクトリには，デバイスとマイコン本体の接続インターフェース別に
ライブラリ作成のベースとなるテンプレートを収容しています．

アナログ端子のADコンバータの出力を利用するものや，デジタル端子の「0,1」を
読み取るだけのデバイスのドライバは修正する場所は非常に少なくて済むはずです．

I2Cに関しては，デバイスからのデータのリードやライトのルーチンを修正する
必要があるため，シンプルなアナログセンサや0/1を読み取るだけのデジタル
デバイスよりは手数がかかるはずですが，それほど大きな手間はいらないはずです．

面倒なのが，デバイス端子で独自のプロトコルを用いるもので，Groveのホコリセンサの
ように，デジタル端子をパルス的に0,1で変化させて，それをマイコン本体で読み取り，
解析する必要があるものは多少面倒になります．

## 作成済みテンプレート
|名前|内容|
|:---|:---|
|AusExAnalogSensorTemplate|アナログセンサのテンプレート|
|AusExDigitalTemplate|デジタル端子を読みとるタイプの機器のテンプレート|
|AusExI2cTemplate|I2Cで動作するデバイスのテンプレート|
|AusExSerialTemplate|UARTで動作するデバイスのテンプレート|

メジャーなインターフェースのうち，テンプレートがないものは「SPI」です．
(GroveはSPIをサポートしないため)

## テンプレートの使い方
アナログデバイス用のドライバを作る場合を想定して，
テンプレートの使い方を説明します．


### ヘッダ (AusExAnalogSensorTemplate.h)
ヘッダファイルはファイル名を変更し，中身は以下のコメントに従って
修正してください．
```
#ifndef __AUEX_ANALOG_SENSOR_TEMPLATE_H__　  <===ここは書き換える
#define __AUEX_ANALOG_SENSOR_TEMPLATE_H__    <===同上

#define _TEMPLATE_CLASS AnalogSensorAusExTemplate  <=== ここは作成するドライバの名前と差し替え
#define _SENSOR_NAME "AnalogSensorAusExTemplate"   <=== ここはデバイスを表すクラス名となるので，それと差し替え
#define _SENSOR_TYPE SENSOR_TYPE_SIMPLE            <=== ここはデバイスの種類に合わせて変更
#define _SENSOR_LIBRARY_VERSION 1
#define _SENSOR_RETURN_VALUE value                 <=== ここはセンサが出力する値の種類に合わせて変更
#define _SENSOR_VALUE_TYPE uint32_t                <=== 上で選んだ値の種類の型で置き換え
#define _DEFAULT_VDD_ 5                            <=== 基本5V動作のマイコンを前提にしているので5V
#define _SENSOR_MIN_VALUE 0                        <=== ここの0と下の1023はADコンバータの出力をそのまま返り値
                                                        として使う場合は変更が不要だが，なにかの変換式を通して
                                                        返り値とする場合は，その値を入れる
#define _SENSOR_MAX_VALUE 1023
#define _SENSOR_RESOLUTION 1                       <=== ここも，ADCの出力をそのまま使うか，変換式を通すか，場合に合わせて変更
#define _SENSOR_MIN_DELAY 0                        <=== センサから値を複数回取得する際に，一定時間待たないと
                                                        正確な値が取れないようなデバイスの場合に，その待ち時間(ms)を入れる

#include "AusEx.h"


class _TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  _TEMPLATE_CLASS(int pinNumber, int32_t sensorID = -1);
  _TEMPLATE_CLASS(int pinNumber,float vdd, int32_t sensorID = -1);
  bool begin(void);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);

private:
  int _pin;
  float _vdd;
  uint32_t _sensorID;
  _SENSOR_VALUE_TYPE calcValue(int);  <=== ADCの出力を変換する式が不要な場合は消す
  bool _autoRange;                    <=== センサに測定のモードなどがない場合は消す
};

#endif /* __AUEX_ANALOG_SENSOR_TEMPLATE_H__ */　  <===ここも先頭のif文と同じく書き換える
```


### クラスのプログラム本体 (AusExAnalogSensorTemplate.cpp)
シンプルなアナログセンサだと，変更場所は2箇所．
```
#include "AusExAnalogSensorTemplate.h" <=== 上で変更したファイル名と置き換え

/*
 *
 */
_TEMPLATE_CLASS::_TEMPLATE_CLASS(int pinNumber, int32_t sensorID){
  _pin=pinNumber;
  _sensorID=sensorID;
  _vdd=_DEFAULT_VDD_;
}
_TEMPLATE_CLASS::_TEMPLATE_CLASS(int pinNumber,float vdd, int32_t sensorID){
  _pin=pinNumber;
  _sensorID=sensorID;
  _vdd=vdd;
}

bool _TEMPLATE_CLASS::begin(void){
  pinMode(_pin, INPUT);
}

bool _TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  event->_SENSOR_RETURN_VALUE = calcValue(analogRead(_pin));
  return true;
}

void _TEMPLATE_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, _SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = _SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = _SENSOR_TYPE;
  sensor->min_value   = _SENSOR_MIN_VALUE;
  sensor->max_value   = _SENSOR_MAX_VALUE;
  sensor->resolution  = _SENSOR_RESOLUTION;
  sensor->min_delay   = _SENSOR_MIN_DELAY;
}


bool _TEMPLATE_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int _TEMPLATE_CLASS::setMode(int mode) {
  return -1; <=== 動作モードの変更機能があるセンサの場合は，その変更手段をここに作り込む
}

_SENSOR_VALUE_TYPE _TEMPLATE_CLASS::calcValue(int val){ <===この関数はADコンバータの出力を変換する必要がない場合は消す
  return val;
}
```

### アプリケーション (AusExAnalogSensorTemplate.ino)
シンプルなセンサだと，4行の書き換えでOKです．
```
#include "AusExAnalogSensorTemplate.h" <=== ヘッダファイルのファイル名と差し替え

#define SENSOR_PIN A3  // センサはアナログの3番ポートに接続 <===ピン番号はハードに合わせて要修正

_TEMPLATE_CLASS generalAnalogSensor = _TEMPLATE_CLASS(SENSOR_PIN); <=== クラス名はヘッダファイルで変更したものと差し替え

void setup()  
{
  Serial.begin(9600);
  generalAnalogSensor.begin();
  sensor_t sensor;
  generalAnalogSensor.getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("---------------");
}
void loop()  
{
  sensors_event_t event;
  if (generalAnalogSensor.getEvent(&event)) {
    Serial.print("sensor value = "); Serial.println(event._SENSOR_RETURN_VALUE); <=== 返り値はヘッダファイルで定義したものと差し替え
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
```

### キーワードファイル (keywords)
一箇所だけ変更
```

#######################################
# Datatypes (KEYWORD1)
#######################################

AnalogSensorAusExTemplate	KEYWORD1  <===センサのクラス名と差し替え

#######################################
# Methods and Functions (KEYWORD2)
#######################################

begin		KEYWORD2
getEvent	KEYWORD2
getSensor	KEYWORD2
enableAutoRange	KEYWORD2
setMode		KEYWORD2

#######################################
# Constants (LITERAL1)
#######################################

A0	LITERAL1
A1	LITERAL1
A2	LITERAL1
A3	LITERAL1
A4	LITERAL1
A5	LITERAL1
A6	LITERAL1
A7	LITERAL1
A8	LITERAL1
A9	LITERAL1
A10	LITERAL1
A11	LITERAL1
A12	LITERAL1
A13	LITERAL1
A14	LITERAL1
A15	LITERAL1
```

### ライブラリ定義 (library.properties)
これは，いろいろ作ったセンサ名，ファイル名，公開するURL，開発者連絡先等
いろいろ変更しないといけないので，ご注意ください．
```
name=AusExAnalogSensorTemplate
version=0.1
author=houtbrion@gmail.com
maintainer=houtbrion@gmail.com
sentence=Analog sensor library template based on  extended version of Adafruit unified sensor library.
paragraph=AusEx driver template for simple analog sensors.
category=Sensors
url=https://github.com/houtbrion/AusEx
architectures=*
includes=AusExAnalogSensorTemplate.h
```

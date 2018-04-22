#include "MuriSensors.h"

//these functions have to be declared for the vector to work
AbstractSensor::~AbstractSensor(){}
void AbstractSensor::update(){}
void AbstractSensor::init(){}

//template class functions
template<class sensor_data_format> void Sensor<sensor_data_format>::sendCommand(){}
template<class sensor_data_format> void Sensor<sensor_data_format>::init(){}
template<class sensor_data_format> void Sensor<sensor_data_format>::update(){}
template<class sensor_data_format> sensor_data_format Sensor<sensor_data_format>::getData(){}
template<class sensor_data_format> void Sensor<sensor_data_format>::setData(sensor_data_format toSet){}
template<class sensor_data_format> Sensor<sensor_data_format>::~Sensor(){}
//accelerometer functions
Accelerometer::Accelerometer(char * Name, int Delay, int * accelerations){
        //feed in so that we are modifying global variables
        this -> Data = &accelerations[0];
        this -> Name = Name;
        this -> Delay = Delay;
        adxl = ADXL345();
        this -> Data = &accelerations[0];
}
Accelerometer::~Accelerometer(){}
void Accelerometer::init(){
        adxl.powerOn();    
        //what does this do? ask Garret         
        adxl.setRangeSetting(16);  
        adxl.setSpiBit(0);                                  //once again ask Garret what the hell this does
}
int Accelerometer::getX(){return Data[0];}
int Accelerometer::getY(){return Data[1];}
int Accelerometer::getZ(){return Data[2];}
void Accelerometer::update(){
    adxl.readAccel(&Data[0],&Data[1],&Data[2]);
}
int * Accelerometer::getData(){return Data;}    


//temperature sensor functions

temperatureSensor::temperatureSensor(char* Name, int Pin, int Delay, String *temperature){
    temperature = &Data;
    this -> Name = Name;
    this -> Delay = Delay;
    OneWire oneWire(Pin);
    sensor = DallasTemperature(&oneWire);
}
temperatureSensor::~temperatureSensor(){}
void temperatureSensor::init(){
    sensor.begin();
}
void temperatureSensor::update(){
    if(millis()-Timer>Delay){
		sensor.requestTemperatures();
        Data = sensor.getTempCByIndex(0);
        Timer = millis();
      }
    }
String temperatureSensor::getData(){return Data;}


//GPS functions


GPS_sensor::GPS_sensor(char * Name, HardwareSerial * port, int baud, TinyGPSPlus GPS){
    this -> port = port;
    this -> Name = Name;
    this -> baud = baud;
	this -> GPS = GPS;
}
GPS_sensor::~GPS_sensor(){}
void GPS_sensor::init(){
    port -> begin(baud);
}
       
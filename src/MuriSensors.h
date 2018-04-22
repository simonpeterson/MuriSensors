#ifndef MuriSensors_h
#define MuriSensors_h

#include <arduino.h>
#include <SparkFun_ADXL345.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <TinyGPS++.h>
struct AbstractSensor{
	virtual ~AbstractSensor() = 0;
	virtual void update() = 0;
	virtual void init() = 0;
};
template <class sensor_data_format>class Sensor: public AbstractSensor {
  protected:
    ~Sensor() = 0;
    //identifier
    const char * Name;
    //delay for reading sensor
    unsigned int Delay;   
    //timer for last check
    unsigned long Timer;     
    //for sending commands to a sensor
    virtual void sendCommand();  
    //for initializing the sensor
    virtual void init();
    //for updating sensor readings
    virtual void update();
    //the actual data
    sensor_data_format Data;              
    virtual sensor_data_format getData();
    virtual void setData(sensor_data_format toSet);
                            //whether or not the sensor has new data. relevant for GPS
    boolean newData = 1;    //assume that the sensors always have new data       
};
class Accelerometer: public Sensor<int *> {  
  public:
      ~Accelerometer();
      Accelerometer(char * Name, int Delay, int * accelerations);
      //accelerometer class
      ADXL345 adxl;
      void init();
      int getX();
      int getY();
      int getZ();
      void update();
      int * getData();   
};
class temperatureSensor: public Sensor<String>{
  public:
    ~temperatureSensor();
    DallasTemperature sensor;
    temperatureSensor(char* Name, int Pin, int Delay, String *temperature);
    void init();
    void update();
    String getData();
};
//the sensor class for the GPS does not need to be nearly as complex
//because we are already using the tiny GPS++ library (once again, 
//it is a custom libaray whose link can be found in the TungstenCut main
//file
class GPS: public Sensor<String>{
  public:
      ~GPS();
      TinyGPSPlus GPS;
      //change to software serial if using software serial
      HardwareSerial * port;
      int baud;
      GPS(char * Name, HardwareSerial * port, int baud);
      void init();
      
    private:
       float getLong();
       float getLat();
       float altFeet();
       int GPShour();
       int GPSminute();
       int GPSsecond();
       
       
};

#endif
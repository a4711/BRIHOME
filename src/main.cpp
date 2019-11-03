#include <Arduino.h>
#include <myiot_timer_system.h>
#include <myiot_DeviceConfig.h>
#include <myiot_ota.h>
#include <myiot_mqtt.h>
#include <myiot_webserver.h>
#include "BrihomeColorControl.h"



MyIOT::DeviceConfig config;
MyIOT::TimerSystem tsystem;
MyIOT::Mqtt mqtt;
MyIOT::WebServer webServer;
MyIOT::OTA ota;

BrihomeColorControl colorControl;

void setup_system() 
{
    config.setup();
    mqtt.setup( config.getDeviceName(), config.getMqttServer() );
    webServer.setup( config);
    ota.setup(config.getDeviceName());

    tsystem.add( &mqtt, MyIOT::TimerSystem::TimeSpec(0, 110e6));
    tsystem.add( &ota, MyIOT::TimerSystem::TimeSpec(0, 99e6));
    tsystem.add( &webServer, MyIOT::TimerSystem::TimeSpec(0, 98e6));
}

void setup_bulb();

void setup() {
  Serial.begin(74880);
  setup_system();

   mqtt.setOnConnected([](){
    IPAddress ip = WiFi.localIP();
    mqtt.publish("startup", ip.toString().c_str());
   });

   setup_bulb();
}

void setup_bulb()
{
    colorControl.setup_bulb();
   
   mqtt.subscribe("off", [](const char* msg){ 
    colorControl.red(0);
    colorControl.green(0);
    colorControl.blue(0);
    colorControl.cold(0);
    colorControl.warm(0);
   });

   mqtt.subscribe("r", [](const char* msg){
       colorControl.red(::atoi(msg));
   });
   mqtt.subscribe("g", [](const char* msg){
       colorControl.green(::atoi(msg));
   });
   mqtt.subscribe("b", [](const char* msg){
       colorControl.blue(::atoi(msg));
   });
   mqtt.subscribe("cc", [](const char* msg){
       colorControl.cold(::atoi(msg));
   });
   mqtt.subscribe("cw", [](const char* msg){
       colorControl.warm(::atoi(msg));
   });

   mqtt.subscribe("control", [](const char* msg){
       colorControl.controlLeds(msg);
   });

}

void loop() {
    tsystem.run_loop(1,1);
}
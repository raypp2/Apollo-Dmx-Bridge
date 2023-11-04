#ifndef ARTNET_MANUAL_H
#define ARTNET_MANUAL_H

#include <Arduino.h>
#include <SparkFunDMX.h>
#include <WiFiUdp.h>
#include <ArtnetWifi.h>

extern WiFiUDP UdpSend;
extern ArtnetWifi artnet;

extern SparkFunDMX dmxMaster;
extern bool artnetControlActive;
// int previousDataLength = 0;
// const int startUniverse = 0;
const int endUniverse = 0; //end Universe should be total channels/512

void onDmxData(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data);
void setupArtnet();
void readArtnet();



#endif
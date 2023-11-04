#include "artnetManual.h"

void onDmxData(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data) {
  if (artnetControlActive) {
    //Read universe and put into the right part of the display buffer
    for (int channel = 0; channel < length; channel++)
    {
      dmxMaster.write(channel + 1, data[channel]); //Add one for offset
    }
    //previousDataLength = length;
    if (universe == endUniverse) //Display our data if we have received all of our universes, prevents incomplete frames when more universes are concerned.
    {
      dmxMaster.update();
      UdpSend.flush();
    }
  }
}

void setupArtnet() {
    artnet.begin();
    artnet.setArtDmxCallback(onDmxData);
}

void readArtnet() {
  artnet.read();
}
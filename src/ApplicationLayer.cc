//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <src/ApplicationLayer.h>
#include "Datapacket_m.h"
Define_Module(ApplicationLayer);

void ApplicationLayer::initialize() {


       startTime = par("StartTime");
       dataSize = par("DataSize");
       period = par("Period");

      if(startTime.dbl() >= 0) {
           cMessage *msg = new cMessage("StartTimer");
           scheduleAt(startTime, msg);
       }
   }

void ApplicationLayer::handleMessage(cMessage *msg) {
    if(msg->isSelfMessage()) {
        if(strcmp(msg->getName(), "StartTimer")== 0) {

            Applicationpacket *pkt = new Applicationpacket();
            pkt->setByteLength(dataSize);
            pkt->setGenTime(simTime());
            send(pkt, "lowerLayerOut");
            scheduleAt(simTime()+ period, msg);
            return;
        }

            error("Timer sconosciuto");
        }
    if(msg->arrivedOn("lowerLayerIn")){
        Datapacket *dpkt=dynamic_cast<Datapacket *>(msg);
     Applicationpacket *pkt =dynamic_cast<Applicationpacket *>(msg);
     pkt->setArrivTime(simTime());
     simsignal_t sig = registerSignal("E2E");
     emit(sig,pkt->getArrivalTime() - pkt->getGenTime() );
     printf("\n il pacchetto è arrivato merryxmas \n");
        }
}




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

#ifndef NETWORKLAYER_H_
#define NETWORKLAYER_H_
#include <omnetpp.h>
#include "Ieee802Ctrl.h"
#include "Datapacket_m.h"
using namespace omnetpp;

using namespace inet;
class NetworkLayer : public cSimpleModule {
    typedef double ** Matrice;
    bool discovery=true;
    int  idnodo;
    int numNodi;
    int destinazione;
    MACAddress destAddr;
    MACAddress broadcast;
    MACAddress sourceAddr;
    Matrice matrice;
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
    virtual void handleMessageUpperLayer(cMessage *msg);
    virtual void handleMessageLowerLayer(cMessage *msg);
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void transmitFrameBroadcast(Datapacket *pkt);
    virtual MACAddress resolveMACAddress(int dest );
    virtual void  transmitFrame(int dest,Datapacket *pkt);
    virtual void UpdateMatrice(Matrice matrice);
    virtual int dijkstra(Matrice matrice);
    virtual int printPath(int parent[], int j,int *vector);
    virtual int minDistance(double dist[], bool sptSet[]);
};

#endif /* NETWORKLAYER_H_ */


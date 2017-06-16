#include <NetworkLayer.h>
#include "Ieee802Ctrl.h"
#include "MACAddress.h"
#include "Ieee802Ctrl.h"
#include "RssiLinkLayerControlInfo.h"
#include "InterfaceTable.h"
#include "Datapacket_m.h"
Define_Module(NetworkLayer);
using namespace inet;
using namespace std;
void  NetworkLayer::initialize(int stage) {
    if(stage == INITSTAGE_LOCAL) {
        numNodi=getSystemModule()->par("numNodes");
        idnodo=par("Id");
        destinazione=par("Dest");

    }
    if(stage==INITSTAGE_NETWORK_LAYER){
        const char *dAddr = par("DestAddr").stringValue();

        //destAddr = resolveMACAddress(dAddr);
        matrice = new double * [numNodi];
        for(int i = 0; i< numNodi ; i++){
            matrice[i] = new double[numNodi];
            for(int j=0;j < numNodi; j++){
                matrice[i][j] = DBL_MAX;
            }
        }
    }
}
void  NetworkLayer::handleMessage(cMessage *msg) {
    if (simTime().dbl()>5){
        discovery=false;
    }
    if (msg->arrivedOn("upperLayerIn"))
        handleMessageUpperLayer(msg);
    else
        handleMessageLowerLayer(msg);

}

void NetworkLayer::handleMessageUpperLayer(cMessage *msg){
    if(discovery==true) {
        Datapacket *pkt = new Datapacket();
        pkt->encapsulate(dynamic_cast<Applicationpacket *>(msg));
        transmitFrameBroadcast(pkt);

    }

    else{
           if(idnodo==2){
            Applicationpacket *apkt=dynamic_cast<Applicationpacket *>(msg);
            Datapacket *dpkt=new Datapacket();
            dpkt->encapsulate(apkt);
            transmitFrame(dijkstra(matrice),dpkt);
           }
    }



}
void  NetworkLayer::handleMessageLowerLayer(cMessage *msg){
    if(discovery==true){
        Datapacket *pkt = dynamic_cast<Datapacket *>(msg);
        RssiLinkLayerControlInfo *ctrl = dynamic_cast<RssiLinkLayerControlInfo *>(pkt->removeControlInfo());
        if(ctrl != nullptr) {
            EV << "Packet received with RSSI: " << ctrl->getRSSI() << " W" << endl;
            matrice[idnodo][pkt->getIdSource()]=(ctrl->getRSSI())!=0 ? (1/ctrl->getRSSI()) : DBL_MAX;
            matrice[pkt->getIdSource()][idnodo]=(ctrl->getRSSI())!=0 ? (1/ctrl->getRSSI()) : DBL_MAX;
            UpdateMatrice(pkt->getMatrice());
            transmitFrameBroadcast(pkt);

            delete ctrl;
        }
    }else{


        Datapacket *pkt = dynamic_cast<Datapacket *>(msg);
        IMACProtocolControlInfo *ctrl =dynamic_cast<IMACProtocolControlInfo *>(pkt->removeControlInfo());
        // printf("\n il pacchetto per %d \n", pkt->getIdDest());
       if(ctrl->getDestinationAddress()==MACAddress::BROADCAST_ADDRESS){
           delete pkt;
       }
       else{
        if(pkt->getIdDest()==idnodo){
            printf("\n il pacchetto è arrivato a destinazione %d \n", pkt->getIdDest());
            send(pkt->decapsulate(),"UpperLayerOut");
        }
        else{
            printf("\n CACCA %d \n", pkt->getIdDest());
            transmitFrame(dijkstra(matrice),pkt);
        }
       }
    }



}

MACAddress NetworkLayer::resolveMACAddress(int dest) {
    cTopology topo("topo");
    topo.extractByProperty("networkNode");

    cModule *dhost = topo.getNode(dest)->getModule();

    IInterfaceTable *it = dynamic_cast<IInterfaceTable *>(dhost->getSubmodule("interfaceTable"));
    return (it->getInterface(0))->getMacAddress();


    return MACAddress::UNSPECIFIED_ADDRESS;
}

void NetworkLayer:: UpdateMatrice(Matrice matrix){

    for(int i=0;i<numNodi;i++)
        for(int j=0;j<numNodi;j++)
        {if (matrice[i][j]==DBL_MAX)
            matrice[i][j]=matrix[i][j];

        }

    cout<<" nodo: "<<idnodo<<endl;
    for(int i=0;i<numNodi;i++){

        cout<< " Riga \t "<<i<< endl;
        for(int j=0;j<numNodi;j++)
            cout<< "\t colonna j"<<j<<": "<< matrice[i][j]<< endl;

    }


}







void  NetworkLayer::transmitFrameBroadcast(Datapacket *pkt) {
    IMACProtocolControlInfo *ctrl = new Ieee802Ctrl();
    broadcast=MACAddress::BROADCAST_ADDRESS;

    ctrl->setDestinationAddress(broadcast);

    pkt->setMatrice(matrice);
    pkt->setIdSource(idnodo);
    pkt->setControlInfo(dynamic_cast<cObject *>(ctrl));
    send(pkt,"LowerlayerOut");
}

void  NetworkLayer::transmitFrame(int dest,Datapacket *pkt) {
    IMACProtocolControlInfo *ctrl = new Ieee802Ctrl();

    destAddr=resolveMACAddress(dest);
    ctrl->setDestinationAddress(destAddr);
    // ctrl->setSourceAddress(sourceAddr);
    pkt->setIdDest(destinazione);
    pkt->setMatrice(matrice);
    pkt->setIdSource(idnodo);
    pkt->setControlInfo(dynamic_cast<cObject *>(ctrl));
    cout<<"\t Nodo "<<idnodo<< "\t nodo destinazione "<<dest << "\t il mac address di destinazione è " << destAddr << endl;
    send(pkt,"LowerlayerOut");
}




int NetworkLayer::minDistance(double dist[], bool sptSet[])
{
    // Initialize min value
    double min = DBL_MAX;
    int min_index;

    for (int v = 0; v < numNodi; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
int  NetworkLayer::dijkstra(Matrice matrice)

{
    int vector[numNodi];
    double dist[numNodi];  // The output array. dist[i] will hold
    // the shortest distance from src to i
    ;
    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[numNodi];

    // Parent array to store shortest path tree
    int parent[numNodi];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < numNodi; i++)
    {
        parent[idnodo] = -1;
        dist[i] = DBL_MAX;
        sptSet[i] = false;


    }

    dist[idnodo] = 0;
    //cout<< "\t distanza " << dist[idnodo]<< endl;

    for (int count = 0; count < numNodi-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < numNodi; v++)

            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] && matrice[u][v] &&dist[u] + matrice[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + matrice[u][v];

            }
    }
/*
    printf("\n Siamo nel nodo %d\n",idnodo);
    // print the constructed distance array
    int src = idnodo;
    printf("Vertex\t  Distance\tPath");
    for (int i = 0; i < numNodi; i++)
    {
        printf("\n%d -> %d \t\t %f\t\t%d ", src, i, dist[i], src);
        printPath(parent, i,vector);
        printf("\n nexthop %d \n",vector[0]);

    }
*/
    printf("\n Sono il nodo %d \n",idnodo);
    printPath(parent, destinazione,vector);

    if (idnodo==destinazione)
        vector[0]=destinazione;
    printf("\n nexthop %d \n",vector[0]);
    return   vector[0];



}
int   NetworkLayer::printPath(int parent[], int j,int *vector)
{ int i=0;
// Base Case : If j is source
if (parent[j]==-1)
    return 0;
i=printPath(parent, parent[j],vector);
vector[i]=j;

printf("percorso %d \t ", j) ;
i++;
return i;
}

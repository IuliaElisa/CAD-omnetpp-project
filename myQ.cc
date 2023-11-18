#include "myQ.h"

Define_Module(MyQ);

void MyQ::initialize()
{
    queue.setName("queue");
}

void MyQ::handleMessage(cMessage *msg)
{

    int ql; //=9;
    ql = queue.getLength();
    if (msg->arrivedOn("rxPackets")){
        queue.insert(msg);
    } else if (msg->arrivedOn("rxScheduling")){
        delete msg;
        if(!queue.isEmpty()){ // if instead of while
          msg = (cMessage *)queue.pop();
          send(msg, "txPackets");
        }
    }

    ql = queue.getLength();
    cPar&  qlpar = par("qlp");
    qlpar.setIntValue(ql);  // the queue updates the lp values
    int qt = par("qlp").intValue(); // not important 
    EV << "qt= "<<qt << endl; // not important
 // scheduler send message only to the queue that won the scheduling

}

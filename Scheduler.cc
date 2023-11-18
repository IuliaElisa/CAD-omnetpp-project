#include "Scheduler.h"

Define_Module(Scheduler);

Scheduler::Scheduler()
{
    selfMsg = nullptr;
}

Scheduler::~Scheduler()
{
    cancelAndDelete(selfMsg);
}

void Scheduler::initialize()
{
//    NrUsers = par("gateSize").intValue();
//    selfMsg = new cMessage("selfMsg");
//       scheduleAt(simTime(), selfMsg);
//
//    lastServedTime = new double[NrUsers];
//    userWeights = new int[NrUsers];
//
//    for (int i = 0; i < NrUsers; i++) {
//        lastServedTime[i] = simTime().dbl();
//        userWeights[i] = i + 1; // For example
//    }

    NrUsers = par("gateSize").intValue();
    selfMsg = new cMessage("selfMsg");
    EV << "Sim time: " <<simTime()<<endl; // why is zero?
       scheduleAt(simTime(), selfMsg);
}

void Scheduler::handleMessage(cMessage *msg)
{
    //  int userWeights[NrUsers];
    int q[3];
    q[0] = getParentModule()->getSubmodule("hpq")->par("qlp");
    q[1] = getParentModule()->getSubmodule("mpq")->par("qlp");
    q[2] = getParentModule()->getSubmodule("lpq")->par("qlp");
    EV << "q["<<0<<"]= " << q[0] <<endl;
    EV << "q["<<1<<"]= " << q[1] <<endl;
    EV << "q["<<2<<"]= " << q[2] <<endl;

    if (msg == selfMsg){
        if( q[0]!=0){ // high priority queue is not empty
            cMessage *cmd = new cMessage("Hey 1");
            send(cmd,"txScheduling",0);
            q[0]--;
            getParentModule()->getSubmodule("hpq")->par("qlp") = q[0];
            EV << "now q["<<0<<"]= " << q[0] <<endl;
        }
        else if( q[1]!=0){ // medium priority queue is not empty
            cMessage *cmd = new cMessage("Hey 2");
            send(cmd,"txScheduling",1);
            q[1]--;
            getParentModule()->getSubmodule("mpq")->par("qlp") = q[1];
            EV << "now q["<<1<<"]= " << q[1] <<endl;
        }
        else if( q[2]!=0){ // low priority queue is not empty
            cMessage *cmd = new cMessage("Hey 3");
            send(cmd,"txScheduling",2);
            q[2]--;
            getParentModule()->getSubmodule("lpq")->par("qlp") = q[2];
            EV << "now q["<<2<<"]= " << q[2] <<endl;
        }
        else{
            EV << "All queues are empty" <<endl;
        }
       scheduleAt(simTime()+par("schedulingPeriod").doubleValue(), selfMsg);
    }
}

/*
 this:

void Scheduler::handleMessage(cMessage *msg)
{
    int q[NrQueues];


    for(int j=0;j<NrQueues; j++){
        q[j]= getParentModule()->getSubmodule("user",j)->getSubmodule("myqq")->par("qlp");
        EV << "q["<<j<<"]= " << q[j] <<endl;
    }
    int userWeights[NrQueues];
    if (msg == selfMsg){
        //finds out the length of each queue !!
        for(int i =0;i<NrQueues;i++){
            cMessage *cmd = new cMessage("cmd");
            //set parameter value, e.g., nr of blocks to be sent from the queue by user i
            send(cmd,"txScheduling",i);
        }
        scheduleAt(simTime()+par("schedulingPeriod").doubleValue(), selfMsg);

    }

    q[0] = getParentModule()->getSubmodule("hpq")->par("qlp");
    q[1] = getParentModule()->getSubmodule("mpq")->par("qlp");
    q[2] = getParentModule()->getSubmodule("lpq")->par("qlp");
}
*/

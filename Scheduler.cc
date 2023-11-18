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
    NrQueues = par("gateSize").intValue();
    NrOfChannels = 10;//read from omnetpp.ini
    selfMsg = new cMessage("selfMsg");
       scheduleAt(simTime(), selfMsg);
}

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

    /*
    q[0] = getParentModule()->getSubmodule("hpq")->par("qlp");
    q[1] = getParentModule()->getSubmodule("mpq")->par("qlp");
    q[2] = getParentModule()->getSubmodule("lpq")->par("qlp");
    */

}

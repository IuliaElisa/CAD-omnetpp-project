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
    NrUsers = par("gateSize").intValue();
    selfMsg = new cMessage("selfMsg");
       scheduleAt(simTime(), selfMsg);

    lastServedTime = new double[NrUsers];
    userWeights = new int[NrUsers];

    for (int i = 0; i < NrUsers; i++) {
        lastServedTime[i] = simTime().dbl();
        userWeights[i] = i + 1; // For example
    }
}

void Scheduler::handleMessage(cMessage *msg)
{
    int q[NrQueues];
    int userWeights[NrQueues];

    for(int j=0;j<NrQueues; j++){
        q[j]= getParentModule()->getSubmodule("user",j)->getSubmodule("myqq")->par("qlp");
        userWeights[j] = q[j]; // Set the weight of each user to the length of their queue
        EV << "q["<<j<<"]= " << q[j] <<endl;
    }

    if (msg == selfMsg){
        int maxScoreUser = 0;
        double maxScore = 0;

        for(int i = 0; i < NrQueues; i++){
            double elapsed = simTime().dbl() - lastServedTime[i];
            double score = elapsed * userWeights[i];

            if (score > maxScore) {
                maxScore = score;
                maxScoreUser = i;
            }
        }

        cMessage *cmd = new cMessage("cmd");
        send(cmd,"txScheduling",maxScoreUser);
        lastServedTime[maxScoreUser] = simTime().dbl();

        scheduleAt(simTime()+par("schedulingPeriod").doubleValue(), selfMsg);
    }
}

/*
Should be this: 

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

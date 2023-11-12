// Buffer.cc
#include <omnetpp.h>
using namespace omnetpp;

class Buffer : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Buffer);

void Buffer::initialize()
{
    // Schedule first transmission
    scheduleAt(simTime(), new cMessage("transmit"));
}

void Buffer::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "transmit") == 0) {
        // Transmit packet if buffer is not empty
        if (!gate("in")->isEmpty()) {
            cMessage *packet = pop();
            send(packet, "out");
        }

        // Schedule next transmission
        scheduleAt(simTime() + 1.0 / par("R").doubleValue(), msg);
    }
    else {
        // Buffer incoming packet
        push(msg);
    }
}
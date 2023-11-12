
// TokenBucket.cc
#include <omnetpp.h>
using namespace omnetpp;

class TokenBucket : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(TokenBucket);

void TokenBucket::initialize()
{
    // Schedule first token addition
    scheduleAt(simTime(), new cMessage("addToken"));
}

void TokenBucket::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "addToken") == 0) {
        // Add token to bucket
        par("tokens").setLongValue(par("tokens").longValue() + 1);

        // Schedule next token addition
        scheduleAt(simTime() + 1.0 / par("R").doubleValue(), msg);
    }
    else {
        // Check if packet complies to the agreed transfer rate
        if (par("tokens").longValue() > 0) {
            // Packet complies, decrement token count
            par("tokens").setLongValue(par("tokens").longValue() - 1);
        }
        else {
            // Packet is in excess, mark accordingly
            msg->setKind(1);
        }

        // Forward packet
        send(msg, "out");
    }
}
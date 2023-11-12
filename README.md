# CAD-omnetpp-project

This model includes a data generator, a buffer, and a token bucket system. The data generator generates IP packets at a certain rate, the buffer buffers the IP packets and transmits them at a certain rate R, and the token bucket system decides for every newly arrived IP packet if the packet complies to the agreed transfer rate or if it is in excess.

(First Commit) is a basic model and does not include more advanced features like different probability distribution functions for the data generator, handling of full buffers, or multiple users. You would need to extend this model to include these features.

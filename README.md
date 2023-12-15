# CAD-omnetpp-project

This project implements a scheduling model for an IP packets scheduler placed on a DiffServ node in Omnetpp-5.6.2.

## Overview

The goal of this project is to simulate a scheduling system for IP packets based on a DiffServ (Differentiated Services) node in OMNeT++. The simulation model consists of users generating IP packets, a scheduler managing packet queues based on priority, and a sink module collecting statistics.

## Requirements

The detailed requirements for the simulation model can be found on the [Computer Aided Design course page](http://staff.cs.upt.ro/~todinca/) under the "Simulation Model" section. Here's a brief overview:

### Simulation Model Components

1. **Users:**
   - Users generate IP packets based on specific patterns.
   - Each user has a certain priority (e.g., LP, MP, HP).
   - Users can be organized as an array, and each generates IP packets independently.

2. **Scheduler:**
   - The scheduler is part of the same module as the queues.
   - Queues are categorized by priority class (LP, MP, HP).
   - The scheduler implements a scheduling algorithm to determine which queue will send data.
   - Packet sending time is determined by the length of the packet divided by the line rate.

3. **Sink:**
   - Represents the destination of the data.
   - Deletes OMNeT++ messages representing data packets upon arrival.
   - Collects statistics for analysis (e.g., packet count, mean, minimum, and maximum delay).

### Basic Requirements

- Implement the described simulation model.
- The scheduling algorithm can be a simple round-robin or a basic priority queueing algorithm.

### More Advanced Requirements

- **Priority Queueing:**
  - Lower priority queues are served only if higher priority queues are empty.

- **Weighted Round Robin:**
  - An auction system determines the next user to be served.
  - Consider introducing weights to improve the algorithm, where users with higher weights are served more often.


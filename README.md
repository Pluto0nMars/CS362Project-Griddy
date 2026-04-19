# Griddy

**A three-node distributed power grid simulator build with Arduino's**

Griddy is a simualted small scale electrical grid using 3 independent Arduino nodes: Producer, Consumer, and Distributor/master. The nodes communicate using I2C, allowing for dynamic load balancing, variable generation and consumption. The goal was to learn more about the process that many CS majors forget to consider: power generation. 

### Project Overview

- **Producer Node**: Simulates different energy sources (Solar, Wind, Geothermal, Nuclear). A potentiometer controls generation level — the brighter the 5 LEDs and the faster the fan spins, the more power is being produced. Two buttons let you cycle through energy source types. Random disruptions mimicking real world events(weather, faults, wars, etc.) can suddenly reduce output.

- **Consumer Node**: Represents various types of electricity demand (homes, neighborhoods, factories, AI datacenters). Users adjust demand via potentiometer and can trigger different load types. During shortages, the Distributor can automatically shed lower-priority loads.

- **Distributor Node** (Master): The "brain" of the grid. It monitors and handles supply and demand, detects imbalances, sends load-shedding commands, and introduces realistic challenges to the system.


### Features

- Real-time I2C communication between the three nodes
- Custom message protocol for status updates and commands
- Visual generation and comsumption feedback
- Simulated random events and disruptions for realism
- Dynamic load shedding when the grid is under stress
- Easy debugging via Serial Monitor on each node

### Hardware
link to hardware.md - shows hardware and wiring guide. documentation basically


### Getting Started
link to gettingStarted.md

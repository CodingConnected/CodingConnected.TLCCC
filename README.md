# TLC-CC
Traffic Light Controller C Collection

A simple framework in C, to ease development of traffic-dependent software for traffic controllers. 

The library implements the so-called CVN-C interface: https://cvn.nl/?page_id=304.
This is a Dutch interface, describing the way traffic controller software shall exchange data with an actual traffic controller.
Implementation of this interface enables easy use of the framework in actual (Dutch) traffic controllers. 
Note: there is a new version of the CVN (5.0) which is not yet implemented in the library.

## Usage
Please refer to the test application for an example on how to build a working application with the library.
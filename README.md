# lekplats
Just my personal playground for experimenting things

### Overview

There are currently four small libraries, tested by an application and a bunch of unit tests:

* basics: common data types and utilities
* algorithms: at the moment just a basic implementation of k-means clustering for 2D datasets
* synthdata: generates synthetic datasets to test algorithms
* visualization: utilities to visualize the input and output of algorithms

The `do_it.sh` script is here to help building, testing and running everything from scratch.

### Dependencies & tools

Only tested on macOS High Sierra, but should work fairly easily on other Unix systems, with the following tools and frameworks:

* Qt5 (5.10)
* CppUTest (3.8)
* Ninja (1.7.2)
* CMake (3.11)
* CppCheck (1.83)
* Cloc (1.76)

### Possible future improvements

* Generalize the problems from 2D to nD
* Restructure the project to properly separate the libraries in the file system (and properly handle their installation)
* Improve the visualization tool to handle arbitrarily located datasets
* Try visualizing each iteration of the algorithm
* Better way to select the initialization method of the algorithm
* Implement other clustering methods
* Do some benchmarking to compare them
* Make things like CppCheck, Cloc or Doxygen optional in the script
* Write more tests!

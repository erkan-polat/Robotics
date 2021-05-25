# Home Service Robot
This document enumerates the packages used for Mapping, Localization and Navigation for this project.

## Mapping
SLAM: It is a solution to problem where we need to estimate both location features(landmarks) and Map(Environment) around the robot. This has to be done simultaneously. Gives approximate robot position and landmark features around it. 

## Localization
**AMCL Package**
AMCL is a probabilistic localization system for a robot which implements adaptive Monte Carlo localization approach while using a particle filter to track the pose of the robot against a known map.


## Navigation
**ROS Navigation Stack**
Using this package, we can creates a path for the robot based on Dijkstra's algorithm while avoiding obstacle along the way.



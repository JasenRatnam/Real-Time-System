# COEN 320 Project
COEN 320 Vehicle Sensor Monitor Project - Fall 2020

## Objective
Implementation of a smart system for real-time monitoring and diagnostic of a vehicle’s health.
In real-time monitor vehicle components.

## Description
The end-product of our project shall contain the core features below.
This is a project developed in the scope of the COEN 320 course at Concordia university. 
The project will allow its user to monitor the different sensors of a vehicle in real time.
Due to the COVID-19 situation, we will use a datasheet given to us for the sensor data instead of OBD-II data.

## Core Features
* The software shall allow the user to monitor the vehicle sensor data
* One real-time, periodic thread for each variable of interest
  * Full Consumption
  * Engine Speed (RPM)
  * Engine Coolant Temperature 
  * Current Gear
  * Transmission Oil Temperature
  * Vehicle Speed
  * Acceleration Speed Longitudinal
  * Indication of break switch
* One real-time thread that will be in charge of updating displayed information to the driver. 

## Team Members
- Evan Lamenta 27240007
- Karthikan Jeyabalan 40032932
- Jasen Ratnam 40094237

## Tools and Technologies
- Languages:
  - C++
- Technology:
  - QNX IDE

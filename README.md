# Pulse-Related-Cocktail-Dispenser
This repository contains the Arduino code I wrote for the first project of the CMU graduate class called "Making Things Interactive" (description [here](https://courses.ideate.cmu.edu/48-739/s2017/)).

## Description

For this project, I created a cocktail dispenser that mapped the amount of alcohol which was poured to the standard deviation of the heartbeat of the person during the day.

In the "ValveControlThroughSD" folder lies an Arduino code uploaded to the Arduino within the cocktail dispenser.

### Details

At this moment, I assume that there is an input device (that I haven't built yet) which records the Heart pulse of the person every 30 seconds between 9 am and 9 pm and then

So far, I have used data that I have online. I used the 1440 first values of data from MIT found in the two first links of [this website](http://ecg.mit.edu/time-series/).

# CardioCocktail
For the CMU graduate class ["Making Things Interactive"](https://courses.ideate.cmu.edu/48-739/s2017/?p=108) of Spring 2017, I created a cocktail dispenser where the amount of stress you got during the day determines the amount of alcohol you will get in your cocktail. Forget today and get a drink!

This repository documents the project. It contains the Arduino code I wrote, the images and videos documenting my work, and a description of the project in this very README file.

This work has been done individually, over the course of a week.

## Current state

<p align="center"><img src="http://i.imgur.com/SqRst9F.jpg" width="500"></p>

[![CardioCocktail](http://i.imgur.com/Oey9nLW.jpg)](https://vimeo.com/204309175 "CardioCocktail - Click to Watch!")

<p align="center"><img src="https://raw.githubusercontent.com/Bierro/CardioCocktail/master/Process%20Pics/Process3.gif" width="500"></p>

## About

### Idea

The scope of this class project was very broad: we had to design and build a machine that creates a physical output when given user input.

After some thoughts about what I wished to accomplish here, I decided I wanted for this project to deal with the notion of stress awareness: ways to implicitly tell a user that they should relax more next time or ways for a system to acknowledge that they went through a tough day and tell them to relax now that it is over.

Making cocktails had then different advantages:
* It required a lot of fabrication which was a skill I wanted to acquire
* Alcohol can be associated with relief after a tough day
* It seemed feasible over the course of a week

I then decided to map the stress someone got during a day with the amount of alcohol my machine would make in

Regarding the input, I came

### Input

At this moment, I assume that there is an input device (that I haven't built yet) which records the Heart pulse of the person every 30 seconds between 9 am and 9 pm and then logs this data into an SD Card. There could be different ways to do so (smartwatches, sensors...) but what I would like to do is have an Arduino (with a data logging shield and an SD Card) connected to a heart pulse sensor that the user would during the day.

So far, I have used data that I have found online. I used the 1440 first values (number of values we would get if the input device was built) of data entries found in the two first links of [this MIT website](http://ecg.mit.edu/time-series/).

On the SD Card I used, I then created a set of text files where heart pulse data are stored. I imagine the organization of the files working as such:
* When the input is stored on the SD card, it is stored with the name "LastData.txt".
* When another set of entries overrides the "LastData.txt", the previous file is stored under the name "HeartData_mth_day_year".
* On top of this can be stored some sample files as "Sample.txt" files for debugging purpose.

The text files I used follow the current template:

* ArduinoHeartData //Name of the file
* 2017 //Year of the recording
* 2 //Month of the recording
* 13 //Day of the recording
* 91.4634 //1st Heart pulse data. 8:00:00 AM
* 91.4634 //2st data. 8:00:30
* .
* .
* .
* 98.228 //1440th and last data

### Code

On the machine I created, I augmented an Arduino with a data logging shield which allows to read and write data onto an SD Card and to use timestamps. I then used this Arduino to open 2 solenoid valves during a certain amount of time (based on the heart data pulled - more details below). The opening and closing of these valves then makes the rum and the coke flow for a computed amount of time, resulting in the desired cocktail.

On this Arduino, I run a code which:
* Pulls the last heart data from the SD Card
* Calculate the standard deviation of this data (if lastData file is not there, a sample file is selected, and if none of them are present or if the card is not inserted, then a default deviation is used)
* The deviation computed is linearly converted into a percentage of rum in the drink
* Based on the global parameters of the experience (flows of liquids, desired volume of cocktail...), I then compute the amount of time each solenoid valve should open to let the liquid flow.

### Output and Fabrication

Process for fabrication parts can be found in the GIF on top of this file. The pictures are also stored in the "Process Pics" folder of this repository.

3 storeys

The circuit itself. 9Volts, I made a hole at the back

### Next Steps

Bought a caulking gun.

Play with the parameters for right value of flow etc...

Close the box.

drink

Create the input device

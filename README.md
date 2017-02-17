# CardioCocktail
Forget today and get a drink!

For the CMU graduate class ["Making Things Interactive"](https://courses.ideate.cmu.edu/48-739/s2017/?p=108) of Spring 2017, I created a cocktail dispenser where the amount of stress you got during the day determines the amount of alcohol you will get in your cocktail.

This repository documents the project. It contains the Arduino code I wrote, the images and videos documenting my work, and a description of the project in this very README file.

This work has been done individually, over the course of a week.

## Current state

<p align="center"><img src="http://i.imgur.com/SqRst9F.jpg" width="500"></p>

[![CardioCocktail](http://i.imgur.com/Oey9nLW.jpg)](https://vimeo.com/204309175 "CardioCocktail - Click to Watch!")

<p align="center"><img src="https://raw.githubusercontent.com/Bierro/CardioCocktail/master/Process%20Pics/Process3.gif" width="500"></p>

## About

### Idea

The scope of this class project was very broad: we had to design and build a machine that creates a physical output when given user input.

After some thoughts about what I wished to accomplish here, I decided I wanted this project to deal with the notion of stress awareness: ways to implicitly tell a user that they should relax more next time or ways for a system to acknowledge that they went through a tough day and tell them to relax now that it is over.

A cocktail machine had then different advantages:
* It required a lot of fabrication which was a skill I wanted to acquire
* Alcohol can be associated with relief after a tough day
* It seemed feasible over the course of a week

I then decided to map the stress someone got during a day with the amount of alcohol my machine would put in a cocktail.

Regarding input, I first thought about a friend of mine who fidgets a lot with her ring when she is nervous. My first prototype was a glove with a photocell which would register how much the ring was taken on and off and played with during the day.

<p align="center"><img src="/Process Pics/Glove.jpeg" width="500"></p>

However I realized that this system was designed for one specific type of person, that it was not easy to wear at all and that the there were some limitations to using a photocell as the amount of light someone is subject to throughout a day can vary a lot.

I then decided to move on to an input more common to everyone: heart pulse. On a stressful day, the heartrate of someone fluctuates a lot more than on a regular day. The standard deviation of someone's heart rate then seemed an appropriate measure of the stress of a day.

### Input

At this moment, I assume that there is an input device (that I haven't built yet) which records the Heart pulse of the person every 30 seconds between 9 am and 9 pm and then logs this data into an SD Card. There could be different ways to do so (smartwatches, sensors...) but what I would like to do is have an Arduino (with a data logging shield and an SD Card) connected to a heart pulse sensor that the user would wear during the day.

So far, I have used data that I have found online. I used the 1440 first values (12 x 60 x 2 = number of values we would get if the input device was built) of data entries found in the two first links of [this MIT website](http://ecg.mit.edu/time-series/).

On the SD Card I used, I then created a set of text files where heart pulse data are stored. The organization of the created files works as such:
* When input is stored on the SD card, it is stored on a text file with the name "LastData.txt".
* When another set of entries overrides "LastData.txt", the latter is stored under the name "HeartData_mth_day_year".
* On top of this can be stored some sample files such as "Sample.txt" files for debugging purpose.

The text files I used follow the current template:

* ArduinoHeartData //Name of the file
* 2017 //Year of the recording
* 2 //Month of the recording
* 13 //Day of the recording
* 91.4634 //1st Heart pulse data. 9:00:00 AM
* 91.4634 //2st data. 9:00:30
* .
* .
* .
* 98.228 //1440th and last data. 8:55:30 PM

### Code

On the machine I created, I augmented an Arduino with a data logging shield which allows to read and write data onto an SD Card and to use timestamps. I used this Arduino to open 2 solenoid valves during a certain amount of time (based on the heart data pulled - more details below). The opening and closing of these valves makes rum and coke flow for a computed amount of time, resulting in the desired cocktail.

On this Arduino, I run a code which:
* Pulls the last heart data from the SD Card
* Calculate the standard deviation of this data (if lastData file is not there, a sample file is selected, and if none of them are present or if the card is not inserted, then a default deviation is used)
* The deviation computed is linearly converted into a percentage of rum in the drink
* Based on the global parameters of the experience (flows of liquids, desired volume of cocktail...), I compute the amount of time each solenoid valve should open to let the liquid flow and have them open.

### Fabrication & electronics

For my machine I imagined a box with three different floors:
* On the top one lie the electronics of the machine. The major components of it are two solenoid valves which control whether we let the rum and coke flow. More details about the circuit can be found in the next section
* The second floor makes the two tubes convert into a funnel
* The bottom floor will be the only one which can be seen by the user. It has a circle engraved to put a glass, and we see the bottom of the funnel so that we know that liquid is going to flow though it.

A big challenge of this system is to make sure that liquid will flow and that the system is caulked properly. I then had to find tube, tube connections, funnels... that matched the dimensions of the solenoid valves and the bottles I was using.

Regarding the structure of my machine, I laser cut a box (plans in svg were made with ["makercase" website](http://www.makercase.com/)) and I made a set of transformations to the structure:
* I laser cut the back of it in order to insert the SD card and plug the Arduino from the outside of the box
* I made a circular hole on the side to have allow the user to turn ON and OFF a switch from the outside
* I made holes in order to put two bottles facing down on top of the machine
* I engraved the bottom of the machine so that the user can know where to position its glass.

These laser cutting steps required some testing with the plywood I bought to make sure that I had the dimensions right.

Finally, I added shelves to the machine (using Zinc plated shelf braces bought at Home Depot and screws that I drilled) to create the different floors.

Process pictures for fabrication can be found in the GIF on top of this file. They are also stored in the "Process Pics" folder of this repository.

### Electronics

My circuit is made of 4 main parts:
* An Arduino with a data logging shield which is powered
directly through an outlet (so that we can use 9 Volts on the Vin pin)
* A simple circuit with a (red) LED and a switch which tells the Arduino if the user has set the switch to ON or OFF
* Two circuits with solenoid valves powered by 9V coming from the Vin pin and controlled by a N-channel MOSFET transistor connected to the Arduino. A (blue or yellow) LED also lights up when the Arduino tells the valve to open.

### Next Steps

I now need to make liquid flow in my machine but first of all, I need to make sure that everything is waterproof. I bought a bottle of silicone and a caulking gun so I should be able to do this in the next days.

Once this is dealt with, I will have to play with the parameters of my code to adjust the right values of liquid flows in the system.

I will then close the front of the machine with the last wooden piece of my box that I will have cut to reveal only the location where the glass should be put.

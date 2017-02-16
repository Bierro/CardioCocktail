# CardioCocktail
For the CMU graduate class ["Making Things Interactive"](https://courses.ideate.cmu.edu/48-739/s2017/?p=108) of Spring 2017, I created a cocktail dispenser where the amount of stress you got during the day determines the amount of alcohol you will get in your cocktail. Forget today and get a drink!

This repository documents the project. It contains the Arduino code I wrote, the images and videos documenting my work, and a description of the project in this very ReadMe file.

## Current state

![Output](http://i.imgur.com/SqRst9F.jpg =10x)

[![CardioCocktail](http://imgur.com/Oey9nLW)](https://vimeo.com/204309175 "CardioCocktail - Click to Watch!")

I thought

 I created a cocktail dispenser that mapped the amount of alcohol which was poured to the standard deviation of the heartbeat of the person during the day.

This work has been done individually, over the course of 2 weeks.

## About

### Idea

The scope of this class project was very broad: we had to design and build a machine that creates a physical output when given user input.

### Input

At this moment, I assume that there is an input device (that I haven't built yet) which records the Heart pulse of the person every 30 seconds between 9 am and 9 pm and then logs this data into an SD Card. There could be different ways to do so (smartwatches, sensors...) but what I would like to do is have a Arduino (with a data logging shield and an SD Card) and like it to a heart pulse sensor that the user would during the day.

So far, I have used data that I have found online. I used the 1440 first values of data entries found in the two first links of [this MIT website](http://ecg.mit.edu/time-series/).

On the SD Card I used can be then found a set of text files where the heart data are stored. When the input is stored on the SD card, it is stored with the name "LastData.txt". When another set of entries overrides is, the previous file is stored under the name "Data_mth_day_year".
On top of this can be stored some sample files as "Sample.txt" files for debugging purpose.

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

### Output and Fabrication

### Next Steps

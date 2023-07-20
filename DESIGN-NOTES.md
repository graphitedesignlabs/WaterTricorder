Design Notes
============

These are high level design notes for the Water Tricorder project, an easy to use water quality instrument. 

Why
---

Existing water quality devices either measure only a subset of possible toxins, or are designed for industrial use and are too expensive and unusable by laypersons. This device is intended for use by outdoor enthusiasts, people in rural communities, and in disaster zones where water quality is unknown, and detailed data can help with adhoc water treatment. 


Design Team
-----------

TBD

Advisors
--------

TBD

Design Principles
-----------------

**Opensource** - a public project for all. 

**Simplicity** - simple enough that all components can be taken apart, examined, understood, and
repaired by people with high school educations.

**Affordability** - it shouldn't cost more than $100.

**Usability** - it should be simple enough that people without a high school
education can reliably use the instrument.

**Responsiveness** - it should not take more than 10 seconds to provide
a reading.

**Reliability** - it has one job: to answer the question, "can I drink this water?" If
the reliability of the system changes over time, then some reliable warning sensor should be built-in (a timer?) and maintenance should be easy for anyone without a high school degree.

**Attractiveness** - it should look awesome.

Primary Systems
---------------

**Optical Sensor** - a simple digital microscope to capture images of microorganisms.

**Spectrometer** - a small and simple spectrometer that captures inorganic data.

**CPU** - a small system for for processing sensor data and relaying it by bluetooth 
to user interfaces, such as [Arduino Nano 33 BLE](https://store.arduino.cc/products/arduino-nano-33-ble-sense).

**Software** - machine learning systems that can classify the sensor input from the
microscope and/or spectrometer and classify the type and density of toxic
components in the water, such as [Tensorflow Lite](https://www.tensorflow.org/lite/microcontrollers).

**Power** - it should be as low power as possible, and operate only briefly to take a reading, display results, and transfer data. Ideally solar with no need for battery charging. 

**Enclosure** - it should look awesome.


Optical Sensor
--------------

The optical sensor should be a portable microscope of just enough quality that
it can feed a machine learning system sufficiently good images for the ML to
recognize bacteriological pathogens (are these the right terms?). Low power
microscopes can even use a cellphone camera and a fitted lens, while middle 
or high power would require more sophisticated optics. Both system may require
backlighting.


Spectrometer
------------

A spectrometer design that could follow [Public Lab's DIY spectrometer](https://publiclab.org/wiki/spectrometry) design,
perhaps miniaturized.


Enclosure
---------

Consider the tricorder design. Play up the utopic Star Trek connection, either
as a superstructure over a cellphone or a wireless tricorder scanner puck. It
should have some superfluous led awesomeness so people who see this 
will ask "what is that?"

![image](https://trekcentral-net.cdn.ampproject.org/i/s/trekcentral.net/wp-content/uploads/2022/11/915416-1501x1536.png)

Consider inviting participation from indigenous communities in co-designing this. 

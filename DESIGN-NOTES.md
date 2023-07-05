WaterTricorder Design Notes
===========================


Design Team
-----------

TDB

Advisors
--------

TDB

Design Principles
-----------------

**Opensource:** A public project for all. 

**Simplicity:** Simple enough that all components can be taken apart, examined, understood, and
repaired by people with high school educations.

**Affordability:** It shouldn't cost more than $100.

**Usability:** It should be simple enough that people without a high school
education can reliably use the instrument.

**Responsiveness:** It should not take more than 10 seconds to provide and
a reading.

**Reliability:** It has one job: to answer the question, "can I drink this water?" If
the reliability of the system changes over time, then some reliable warning sensor should be built-in (a timer?) and maintenance should be easy for anyone without a high school degree.

**Attractiveness:** It should look awesome.

Primary Systems
---------------

**Optical Sensor** - a small and simple microscope that captures organism data

**Spectrometer** - a small and simple spectrometer that captures inorganic data

**CPU** - a small system for for processing sensor data and relaying it by bluetooth 
to user interfaces.

**Software** - machine learning systems that can classify the sensor input from the
microscope and/or spectrometer and classify the type and density of toxic
components in the water.

**Power** - it should be as low power as possible, and operate only briefly to take a reading and transfer data. Ideally solar with no need for battery charging. 

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

A spectrometer design that could follow Public Labs' DIY spectrometer design,
perhaps miniaturized.


Enclosure
---------

Consider the tricorder design. Play up the utopic Star Trek connection, either
as a superstructure over a cellphone or a wireless tricorder scanner puck. It
should have some superfluous led awesomeness so no one can see this and not want
to ask "what is that?"



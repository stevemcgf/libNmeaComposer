# libNmeaComposer

This library is a C++ implementation of a NMEA Sentence Composer, Track Binary and AIS Binary Encoder.

## Description

This library allows to compose supported NMEA sentences and encode binary data inside VDM, VDO and TTD messages. Example usage available in the test code. **test.cpp**.

## Motivation

I didn't find a comprehensive and straight forward library to compose NMEA sentences and encode AIS data. This library is part of a larger project currently in use on many ships.

## Installation

If you use CMake you can simple add this directory to your project and refer to it using **target_link_libraries**. You can also compile then copy the static library and include directory.

## API Reference

The code has doxygen documentation can be generated using "make doc.NmeaComposer"

## License

GNU LESSER GENERAL PUBLIC LICENSE Version 3, 29 June 2007

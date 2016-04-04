## AWS SDK for ESP8266 and Arduino-compatible devices <span clear="right">

<img src="https://cloud.githubusercontent.com/assets/6751621/12034320/94eb4d4a-ae2f-11e5-9a52-8ad3431fda68.png" alt="Glorious ESP8266" title="Glorious ESP8266" align="right" />

[![forthebadge](http://forthebadge.com/images/badges/powered-by-electricity.svg)](http://forthebadge.com) [![forthebadge](http://forthebadge.com/images/badges/uses-badges.svg)](http://forthebadge.com)

The purpose of this fork of the experimental [aws-sdk-arduino](https://github.com/awslabs/aws-sdk-arduino) repository is to add support for the **Espressif ESP8266** microcontroller [with the Arduino IDE](https://github.com/esp8266/Arduino) and maintain the common source while (if possible) trying not to break the support for the other Arduino based boards.

### Folder Structure (/src)

    * /common contains all the common source code
    * /esp8266 contains Espressif ESP8266 device-specific implementations
    * /sparkcore contains Spark IO Core device-specific implementations
    * /edison contains Intel Edison device-specfic implementations
    * /galileo contains Intel Galileo device-specific implementations
    * /mediatek contains MediaTek LinkIt One device-specific implementations


Depending on the device that you are using, simply copy the device-specific implementations (e.g. `/esp8266`) to the `common` directory so you can test out your samples using Arduino IDE.

### Getting Started with ESP8266

Getting the sample working has the following steps: setting up the DynamoDB table, importing the SDK and copying over the sample, configuring the `keys.cpp` file, and setting up the hardware. These steps are outlined for the ESP8266's sample, you can find more instructions for the other boards on the [original repository](https://github.com/awslabs/aws-sdk-arduino).

![esp8266-wiring](https://github.com/daniele-salvagni/aws-sdk-esp8266/blob/master/docs/wiring.png)

<sub>*Quick reminder of the wiring diagram for this module (ESP-01 version), note that GPIO0 needs to be shorted to ground and restarted to flash a new Firmware. The module needs to be powered by an external 3.3v supply as most of the serial adapters won't provide enough current.*</sub>


#### Step 1: Setting up the DynamoDB Table

You will need to set up a DynamoDB table with the same name, hash key, and range key as in the sample you are using. These values are defined as constants in the sample, i.e. `HASH_KEY_NAME` and `TABLE_NAME`. 

You can follow the steps below to get the tables set up with the right values:

* Log into the [AWS Console](http://console.aws.amazon.com/) and navigate to **DynamoDB**.
* Click on the "Create Table" button.
* Enter `ESP8266AWSDemo` as the *Table Name*, `id` as the primary *Partition Key*, and `timest` as the primary *Sort Key*. Be sure to mark *id* as *String* and *timest* as *Number*.
* Just one *Read Capacity Unit* and one *Write Capacity Unit* will be more than enough for this demo. Press create with these values.
* After the table has finished creating you are good to go, your ESP will take care about populating it.


#### Step 2: Importing SDK and Copying Sample

Make an `AWSArduinoSDK` directory in the Arduino IDE's libraries directory (`~/Arduino/libraries/AWSArduinoSDK`).

Move all of the files from the SDK's `src/common` and `src/esp8266` directories into the `AWSArduinoSDK` directory you just created, then create a new sketch with the Arduino IDE and copy and paste the sample code into it.


#### Step 3: Creating `keys.h` and `keys.cpp`

You will need to create and add `keys.h` and `keys.cpp` into the `AWSArduinoSDK` directory you made. Alternatively, if you want to use different access keys for every sketch you make, just put them inside your current sketch folder. These files define the `awsKeyID` and `awsSecKey` values used by the sketch, the files may be structured as following:

```
// keys.h
#ifndef KEYS_H_
#define KEYS_H_

extern const char* awsKeyID;  // Declare these variables to 
extern const char* awsSecKey; // be accessible by the sketch

#endif
```

```
// keys.cpp
#include "keys.h"

const char* awsKeyID = "YOUR AWS KEY ID HERE";
const char* awsSecKey = "YOUR AWS SECRET KEY HERE";
```

*Do not share your AWS keys with anyone, it is reccomended to create a dedicated user with restricted permissions, do not use your root account. If you accidentally push your keys online disable them immediatly from the [AWS IAM console](https://console.aws.amazon.com/iam/home)*


#### Step 4: Setting up Hardware

The ESP8266 sample uses only a "virtual sensor" (i.e. numbers generated randomly), so it is only necessary to give power to the module without adding extra components.

### Supported Services

| Service Name                             | Status                | API Version |
| :--------------------------------------- | :-------------------- | :---------- |
| Amazon DynamoDB                          | Complete              | 2012-08-10  |
| Amazon Kinesis \*                        | Complete              | 2013-12-02  |
| Amazon Simple Notification Service       | Only Publish          | 2010-03-31  |

<sub>\* *The code for creating, serializing, and deserializing Kinesis input and output objects is included, but the devices that the experimental SDK has been tested on do not have readily available HTTPS support. This code has been included so it can be used by those who want to do further experimenting with Kinesis and HTTPS.*</sub>

----------

###### Disclaimer

This fork is not affiliated in any way with Amazon Web Services (AWS), Arduino or Espressif which are registered trademarks of their respective holders.

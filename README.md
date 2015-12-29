## AWS SDK for ESP8266 and Arduino-compatible devices <span clear="right">

<img src="https://cloud.githubusercontent.com/assets/6751621/12034320/94eb4d4a-ae2f-11e5-9a52-8ad3431fda68.png" alt="Glorious ESP8266" title="Glorious ESP8266" align="right" />

[![forthebadge](http://forthebadge.com/images/badges/powered-by-electricity.svg)](http://forthebadge.com) [![forthebadge](http://forthebadge.com/images/badges/uses-badges.svg)](http://forthebadge.com)

This fork of the experimental [aws-sdk-arduino](https://github.com/awslabs/aws-sdk-arduino) repository is aimed to add support for the Espressif ESP8266 microcontroller [with the Arduino IDE](https://github.com/esp8266/Arduino) while also fixing and mantaining the common source without breaking the support for the other boards.

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

*Quick remainder of the wiring diagram for this module (ESP-01 version), note that GPIO0 needs to be shorted to ground and restarted to flash a new Firmware. The module needs to be powered by an external 3.3v supply.*

#### Step 1: Setting up the DynamoDB Table

You will need to set up a DynamoDB table with the same name, hash key, and range key as in the sample you are using. These values are defined as constants in the sample, i.e. `HASH_KEY_NAME` and `TABLE_NAME`. 

You can follow the steps below to get the tables set up with the right values:

* Log into the [AWS Console](http://console.aws.amazon.com/) and navigate to **DynamoDB**.
* Click on the "Create Table" button.
* Enter **ESP8266AWSDemo** as the *Table Name*, **id** as the primary *Partition Key*, and **timest** as the primary *Sort Key*. Be sure to mark *id* as *String* and *timest* as *Number*.
* Just one *Read Capacity Unit* and one *Write Capacity Unit* will be more than enough for this demo. Press create with these values.
* After the table has finished creating you are good to go, your ESP will take care about populating it.

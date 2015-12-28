# AWS SDK for ESP8266 and Arduino-compatible devices

This fork of the experimental [aws-sdk-arduino](https://github.com/awslabs/aws-sdk-arduino) repository is aimed to add support for the Espressif ESP8266 microcontroller [with the Arduino IDE](https://github.com/esp8266/Arduino) while also fixing and mantaining the common source without altering the support for the other boards.

## Folder Structure

	* /common contains all the common source code
  * /esp8266 contains Espressif ESP8266 device-specific implementations
	* /sparkcore contains Spark IO Core device-specific implementations
	* /edison contains Intel Edison device-specfic implementations
	* /galileo contains Intel Galileo device-specific implementations
  * /mediatek contains MediaTek LinkIt One device-specific implementations


Depending on the device that you are using, simply copy the device-specific implementations to the `common` directory so you can test out your samples using Arduino IDE.

## Getting Started with ESP8266

Trying the samples is a good way to get started with using the SDK.

Getting the samples working has the following steps: setting up the DynamoDB table, importing the SDK and copying over the sample, creating the `keys.h` and `keys.cpp` files, and setting up the hardware. These steps are outlined for the samples for the ESP8266, you can find instructions for the other boards on the [original repository](https://github.com/awslabs/aws-sdk-arduino).

### Step 1: Setting up the DynamoDB Table

For either device you will need to set up a DynamoDB table with the same name, hash key, and range key as in the sample you are using. These values are defined as constants in the sample, i.e. `HASH_KEY_NAME` and `TABLE_NAME`. 

You can follow the steps below to get the tables set up with the right values:

* Log into the [AWS Console](http://console.aws.amazon.com/) and navigate to DynamoDB.
* Click on the "Create Table" button.
* Enter "AWSArduinoSDKDemo" as the *Table Name*, "DemoName" as the *Hash Attribute Name*, and "id" as the *Range Attribute Name*. Be sure to mark *DemoName* as *String* and *id* as *Number*.
* For this example, we won't add indexes, so just press continue on the *Add Indexes (optional)* page.
* Just one *Read Capacity Unit* and one *Write Capacity Unit* will be enough for this demo. Press continue with these values.
* Uncheck *Use Basic Alarms* and continue again.
* Check that the information is correct on the *Review* page, then create the table!
* After the table has finished creating, double click on it to explore it. Here you should press the *New Item* button and create an item with the following values:
  * "DemoName": *String*, "Colors"
  * "id": *Number*, "1"
  * "R", *Number* "255"
  * "G", *Number* "255"
  * "B", *Number* "255"

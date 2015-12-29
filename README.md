## AWS SDK for ESP8266 and Arduino-compatible devices

This fork of the experimental [aws-sdk-arduino](https://github.com/awslabs/aws-sdk-arduino) repository is aimed to add support for the Espressif ESP8266 microcontroller [with the Arduino IDE](https://github.com/esp8266/Arduino) while also fixing and mantaining the common source without altering the support for the other boards.

### Folder Structure (/src)

    * /common contains all the common source code
    * /esp8266 contains Espressif ESP8266 device-specific implementations
    * /sparkcore contains Spark IO Core device-specific implementations
    * /edison contains Intel Edison device-specfic implementations
    * /galileo contains Intel Galileo device-specific implementations
    * /mediatek contains MediaTek LinkIt One device-specific implementations


Depending on the device that you are using, simply copy the device-specific implementations to the `common` directory so you can test out your samples using Arduino IDE.

### Getting Started with ESP8266

Getting the sample working has the following steps: setting up the DynamoDB table, importing the SDK and copying over the sample, creating the `keys.h` and `keys.cpp` files, and setting up the hardware. These steps are outlined for the ESP8266's sample, you can find more instructions for the other boards on the [original repository](https://github.com/awslabs/aws-sdk-arduino).

![esp8266-wiring](https://github.com/daniele-salvagni/aws-sdk-esp8266/blob/master/docs/wiring.png)

*Wiring diagram for the ESP-01 module, note that GPIO0 needs to be shorted to ground and restarted to flash a new Firmware. The module needs to be powered by an external 3.3v supply.*

#### Step 1: Setting up the DynamoDB Table

You will need to set up a DynamoDB table with the same name, hash key, and range key as in the sample you are using. These values are defined as constants in the sample, i.e. `HASH_KEY_NAME` and `TABLE_NAME`. 

You can follow the steps below to get the tables set up with the right values:

* Log into the [AWS Console](http://console.aws.amazon.com/) and navigate to **DynamoDB**.
* Click on the "Create Table" button.
* Enter "AWSArduinoSDKDemo" as the *Table Name*, "DemoName" as the primary *Partition Key*, and "id" as the primary *Sort Key*. Be sure to mark *DemoName* as *String* and *id* as *Number*.
* Just one *Read Capacity Unit* and one *Write Capacity Unit* will be more than enough for this demo. Press create with these values.
* After the table has finished creating, click on it and go to the *Items* tab to explore it. Here you should press the *Create Item* button and create an item with the following values. To add the *R*, *G* and *B* fields click on the plus symbol, then *Append* and select *Number*:
  * "DemoName": *String*, "Colors"
  * "id": *Number*, "1"
  * "R", *Number* "255"
  * "G", *Number* "255"
  * "B", *Number* "255"

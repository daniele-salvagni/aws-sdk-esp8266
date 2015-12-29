// keys.cpp
#include "keys.h"

/* Do not share your AWS keys with anyone, it is reccomended to create a dedicated user with restricted permissions, do not use your root account.
If you accidentally push your keys online disable them immediatly from the AWS IAM console (https://console.aws.amazon.com/iam/home) */

// AWS access keys
const char* awsKeyID = "xxxxxxxxxxxxxxxx"; // REPLACE with your access key id
const char* awsSecKey = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; // REPLACE with your secret access key

// Common AWS constants
const char* AWS_REGION = "eu-west-1";  // REPLACE with your region
const char* AWS_ENDPOINT = "amazonaws.com";

// Init and connect Esp8266 WiFi to local wlan
char* ssid = "myssid"; // REPLACE with your network SSID (name)
char* pass = "mypass"; // REPLACE with your network password (use for WPA, or use as key for WEP)

// Constants describing DynamoDB table and values being used
const char* TABLE_NAME = "ESP8266AWSDemo";
const char* HASH_KEY_NAME = "id";
const char* HASH_KEY_VALUE = "ESP01"; // Our sensor ID, to be REPLACED in case of multiple sensors.
const char* RANGE_KEY_NAME = "time";

/* This sample uses PutItem on a DynamoDB table to save the state of a virtual
 * temperature sensor.
 *
 * For this demo to work you must have keys.h/.ccp files that contain your AWS
 * access keys and define "awsSecKey" and "awsKeyID", a DynamoDB table with the
 * name defined by the constant TABLE_NAME with hash and range keys as defined
 * by constants HASH_KEY_NAME/RANGE_KEY_NAME. */

#include <ESP8266WiFi.h>

#include "Esp8266AWSImplementations.h"
#include "AmazonDynamoDBClient.h"
#include "AWSFoundationalTypes.h"
#include "keys.h"


/* Contants describing DynamoDB table and values being used. */
static const char* TABLE_NAME = "ESP8266AWSDemo";
static const char* HASH_KEY_NAME = "id";
static const char* RANGE_KEY_NAME = "timest";

/* Our sensor ID, to be changed in case of multiple sensors. */
static const char* HASH_KEY_VALUE = "1";

/* Constants for connecting to DynamoDB. */
static const char* AWS_REGION = "eu-west-1";
static const char* AWS_ENDPOINT = "amazonaws.com";

/* Temperature reading. */
int reading;

/* Parameters for WiFi connection. */
const char* pSSID = "myssid";
const char* pPassword = "mypassword";


Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;

AmazonDynamoDBClient ddbClient;

/* Reused objects. */
GetItemInput getItemInput;
PutItemInput putItemInput;
AttributeValue hashKey;
AttributeValue rangeKey;
ActionError actionError;


void setup() {
    /* Begin serial communication. */
    Serial.begin(115200);
    Serial.println();
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(pSSID);

    WiFi.hostname("ESP8266");

    // If pPassword is set the most secure supported mode will be automatically selected
    WiFi.begin(pSSID, pPassword);

    // Wait for WiFi connection
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println();

    /* Initialize ddbClient. */
    ddbClient.setAWSRegion(AWS_REGION);
    ddbClient.setAWSEndpoint(AWS_ENDPOINT);
    ddbClient.setAWSSecretKey(awsSecKey);
    ddbClient.setAWSKeyID(awsKeyID);
    ddbClient.setHttpClient(&httpClient);
    ddbClient.setDateTimeProvider(&dateTimeProvider);
}

void putTemp(int temp) {

    /* Create an Item. */
    char numberBuffer[4];
    AttributeValue id;
    id.setS(HASH_KEY_VALUE);
    AttributeValue timest;
    timest.setN(dateTimeProvider.getDateTime());

    /* Create an AttributeValue for 'temp', convert the number to a
     * string (AttributeValue object represents numbers as strings), and
     * use setN to apply that value to the AttributeValue. */
    AttributeValue tempAttributeValue;
    sprintf(numberBuffer, "%d", temp);
    tempAttributeValue.setN(numberBuffer);

    /* Create the Key-value pairs and make an array of them. */
    MinimalKeyValuePair < MinimalString, AttributeValue
            > att1(HASH_KEY_NAME, id);
    MinimalKeyValuePair < MinimalString, AttributeValue
            > att2(RANGE_KEY_NAME, timest);
    MinimalKeyValuePair < MinimalString, AttributeValue
            > att3("temp", tempAttributeValue);
    MinimalKeyValuePair<MinimalString, AttributeValue> itemArray[] = { att1,
            att2, att3 };

    /* Set values for putItemInput. */
    putItemInput.setItem(MinimalMap < AttributeValue > (itemArray, 3));
    putItemInput.setTableName(TABLE_NAME);

    /* Perform putItem and check for errors. */
    PutItemOutput putItemOutput = ddbClient.putItem(putItemInput,
            actionError);
    switch (actionError) {
    case NONE_ACTIONERROR:
        Serial.println("PutItem succeeded!");
        break;
    case INVALID_REQUEST_ACTIONERROR:
        Serial.print("ERROR: Invalid request");
        Serial.println(putItemOutput.getErrorMessage().getCStr());
        break;
    case MISSING_REQUIRED_ARGS_ACTIONERROR:
        Serial.println(
                "ERROR: Required arguments were not set for PutItemInput");
        break;
    case RESPONSE_PARSING_ACTIONERROR:
        Serial.println("ERROR: Problem parsing http response of PutItem");
        break;
    case CONNECTION_ACTIONERROR:
        Serial.println("ERROR: Connection problem");
        break;
    }
     /* wait to not double-record */
    delay(750);
  
}

void loop() {
    reading = random(20, 30);
    Serial.print("Temperature = ");
    Serial.println(reading);
    putTemp(reading);
    
    delay(2000);
}

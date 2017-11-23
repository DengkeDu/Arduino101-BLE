/*
 * Copyright (c) 2016 Intel Corporation.  All rights reserved.
 * See the bottom of this file for the license terms.
 */

#include <CurieBLE.h>

const int ledPin = 13; // set ledPin to use on-board LED
const int forward = 2;
const int left = 4;
const int back = 7;
const int right = 8;
const int ledStop = 10;



char result[4];

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // create service

// create switch characteristic and allow remote device to read and write
BLECharacteristic switchChar("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 4);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // use the LED on pin 13 as an output
  
  pinMode(forward, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(back,OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(ledStop, OUTPUT);

  // begin initialization
  BLE.begin();

  // set the local name peripheral advertises
  BLE.setLocalName("LEDCB");
  // set the UUID for the service this peripheral advertises
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchChar);

  // add service
  BLE.addService(ledService);

  // assign event handlers for connected, disconnected to peripheral
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // assign event handlers for characteristic
  switchChar.setEventHandler(BLEWritten, switchCharacteristicWritten);
  // set an initial value for the characteristic
  const unsigned char control[4] = {'0','0','0','0'};
  switchChar.setValue(control,4);

  // start advertising
  BLE.advertise();

  Serial.println(("Bluetooth device active, waiting for connections..."));
}

void loop() {
  // poll for BLE events
  BLE.poll();
}

void blePeripheralConnectHandler(BLEDevice central) {
  // central connected event handler
  digitalWrite(ledPin,HIGH);
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
}

void switchCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  // central wrote new value to characteristic, update LED
  Serial.print("Characteristic event, written: ");
  Serial.println((char*)switchChar.value());
  strncpy(result, (char *)switchChar.value(),4);
  Serial.println(result);

  instruct(result);
}

void instruct(char *instruction)
{
  if(instruction[0]=='f' && instruction[1]=='0')
  {
  digitalWrite(forward,HIGH);
  }
  else if(instruction[0]=='f' && instruction[1]=='1')
  {
    digitalWrite(forward,LOW);
  }
  else if(instruction[0]=='l' && instruction[1]=='0')
  {
  digitalWrite(left,HIGH);
  }
  else if(instruction[0]=='l' && instruction[1]=='1') 
  {
    digitalWrite(left,LOW);
  }
  else if(instruction[0]=='b' && instruction[1]=='0')
  {
  digitalWrite(back,HIGH);
  }
  else if (instruction[0]=='b' && instruction[1]=='1')
  {
      digitalWrite(back,LOW);
  }
  else if(instruction[0]=='r' && instruction[1]=='0')
  {
  digitalWrite(right,HIGH);
  }
  else if(instruction[0]=='r' && instruction[1]=='1')
  {
      digitalWrite(right,LOW);
  }
  else if(instruction[0]=='s' && instruction[1]=='0')
  {
  digitalWrite(ledStop,HIGH);
  }
  else if(instruction[0]=='s' && instruction[1]=='1')
  {
    digitalWrite(ledStop,LOW);
  }
}
/*
  Copyright (c) 2016 Intel Corporation. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-
  1301 USA
*/

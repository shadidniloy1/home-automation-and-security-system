#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>

int scanTime = 5; // scan for 5 seconds
BLEScan* pBLEScan;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing BLE...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);

  Serial.println("BLE scan ready!");
}

void loop() {
  Serial.println("Scanning for BLE devices...");
  BLEScanResults* results = pBLEScan->start(scanTime, false); // pointer fix
  int count = results->getCount();
  Serial.print("Devices found: ");
  Serial.println(count);

  for (int i = 0; i < count; i++) {
    BLEAdvertisedDevice device = results->getDevice(i);
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(device.getName().c_str());
    Serial.print(" (");
    Serial.print(device.getAddress().toString().c_str());
    Serial.println(")");
  }

  delay(5000); // wait 5 sec before next scan
}

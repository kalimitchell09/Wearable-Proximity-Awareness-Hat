/*

* Wearable Proximity Awareness Hat (WPAH)
* Author: Kali Mitchell
* Description:
* This prototype uses a VL53L1X Time-of-Flight (ToF) sensor and an ESP32
* microcontroller to detect nearby obstacles. When an object is detected
* within a specified distance threshold, a vibration motor is activated
* to provide haptic feedback to the user.
* Hardware:
* ESP32 Development Board
* VL53L1X ToF Distance Sensor
* Vibration Motor
* ULN2003 Driver Module
        */

#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;

// ===== SYSTEM CONFIGURATION =====
const int MOTOR_PIN = 25;          // ULN2003 motor driver input
const int MOTOR_THRESHOLD = 200;   // Distance threshold for haptic feedback (mm)

void setup() {
Serial.begin(115200);
delay(2000);

// Initialize I2C communication
Wire.begin(21, 22);
Wire.setClock(10000);

// Configure vibration motor output
pinMode(MOTOR_PIN, OUTPUT);
digitalWrite(MOTOR_PIN, LOW);

Serial.println(”=== WPAH Distance Detection Test ===”);

// Initialize VL53L1X sensor
sensor.setTimeout(1000);

if (!sensor.init()) {
Serial.println(“ERROR: VL53L1X initialization failed.”);
while (1) delay(10);
}

// Begin continuous distance measurements
sensor.startContinuous(100);

Serial.println(“Distance monitoring started.”);
}

void loop() {

// Read distance measurement from sensor
uint16_t distance = sensor.read();

if (sensor.timeoutOccurred()) {

// Disable motor if sensor communication is lost
Serial.println("Sensor timeout detected.");
digitalWrite(MOTOR_PIN, LOW);

} else {

// Display measured distance in Serial Monitor
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" mm");
// Activate haptic feedback when an obstacle
// is detected within the threshold distance
if (distance < MOTOR_THRESHOLD) {
  digitalWrite(MOTOR_PIN, HIGH);
} else {
  digitalWrite(MOTOR_PIN, LOW);
}

}

delay(200);
}

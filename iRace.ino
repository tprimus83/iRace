
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
sensors_event_t last;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  Serial.println("");
  delay(100);
  sensors_event_t g, temp;
  mpu.getEvent(&last, &g, &temp);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  /**Serial.print("gyro X: ");
  Serial.print(a.gyro.x);
  Serial.print(", Y: ");
  Serial.print(a.gyro.y);
  Serial.print(", Z: ");
  Serial.print(a.gyro.z);
  Serial.println(" m/s^2");**/
  float diff = 0.02;
  /**Serial.println("Max DELTA: " + 
    String(
    abs(a.gyro.x - last.gyro.x) +
    abs(a.gyro.y - last.gyro.y) +
    abs(a.gyro.z - last.gyro.z)
    )
  );**/
  if ((abs(a.gyro.x - last.gyro.x)/** +
    abs(a.gyro.y - last.gyro.y) +
    abs(a.gyro.z - last.gyro.z)**/) > diff
  ) {
    Serial.print("gyro X: ");
    Serial.print(a.gyro.x);
    Serial.print("->");
    Serial.print(last.gyro.x);
    /**Serial.print(", Y: ");
    Serial.print(a.gyro.y);
    Serial.print("->");
    Serial.print(last.gyro.y);
    Serial.print(", Z: ");
    Serial.print(a.gyro.z);
    Serial.print("->");
    Serial.print(last.gyro.z);**/
    Serial.println(" MOVED: " + String(a.gyro.x - last.gyro.x));  
  } else {
    //Serial.println(" STOP");  
  }
  last = a;
  delay(10);
}
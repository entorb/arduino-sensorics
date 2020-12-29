/*
Class for reading BME680 Sensor: Temp, Humidity, Pressure, Air-Quality

Based on bsec library usage example BME680_basic.ino

AQI: Air Quality Index
>=  0: Good
> 050: Moderate
> 100: Unhealthy for Sensitive Groups
> 150: Unhealthy
> 200: Very Unhealthy
> 300: Hazardous

IAQ-Accuracy
0: sensor restarted or sensor stabilizing (5 min in LP-Mode or 20min in ULP-Mode)
1: unstable
2: calibrating
3: is calibrated

Good German Guide: http://steinlaus.de/stinkt-das-hier-teil-1-mit-dem-bosch-bme680/
In order to use the pre-compiled lib by Bosch, the following setting is required
in AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.4\platform.txt
1,; modify existing code to

# BoschSensortec BME680
# from https://github.com/BoschSensortec/BSEC-Arduino-library#installation-and-getting-started
# These can be overridden in platform.local.txt
compiler.c.extra_flags=
compiler.c.elf.extra_flags=
#compiler.c.elf.extra_flags=-v
compiler.cpp.extra_flags=
compiler.S.extra_flags=
compiler.ar.extra_flags=
compiler.elf2hex.extra_flags=
compiler.libraries.ldflags=

and in section
## Combine gc-sections, archives, and objects
modify this line:
recipe.c.combine.pattern="{compiler.path}{compiler.c.elf.cmd}" {compiler.c.elf.flags} {compiler.c.elf.extra_flags} -Wl,--start-group {object_files} "{archive_file_path}" {compiler.c.elf.libs} -Wl,--end-group -Wl,-EL -o "{build.path}/{build.project_name}.elf"
to
recipe.c.combine.pattern="{compiler.path}{compiler.c.elf.cmd}" {compiler.c.elf.flags} {compiler.c.elf.extra_flags} -Wl,--start-group {object_files} "{archive_file_path}" {compiler.c.elf.libs} {compiler.libraries.ldflags} -Wl,--end-group -Wl,-EL -o "{build.path}/{build.project_name}.elf"
*/

#include "Arduino.h"
#include "TM_Device_Class.h"
#include "TM_BME680_Class.h"

#include "bsec.h"

TM_BME680_Class::TM_BME680_Class(const bool this_verbose) : TM_Sensor_Device_Class("BME680", this_verbose)
{
}

void TM_BME680_Class::init()
{
  TM_Sensor_Device_Class::init();
  Wire.begin();
  iaqSensor.begin(BME680_I2C_ADDR_PRIMARY, Wire);
  if (verbose)
  {
    output = "\nBSEC library version " + String(iaqSensor.version.major) + "." + String(iaqSensor.version.minor) + "." + String(iaqSensor.version.major_bugfix) + "." + String(iaqSensor.version.minor_bugfix);
    Serial.println(output);
  }
  checkIaqSensorStatus();
  iaqSensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
  checkIaqSensorStatus();
}

float *TM_BME680_Class::read()
{
  // unsigned long time_trigger = millis();
  if (iaqSensor.run())
  { // If new data is available
    // output = String(time_trigger);
    data[0] = iaqSensor.rawTemperature;
    data[1] = iaqSensor.temperature;
    data[2] = iaqSensor.rawHumidity;
    data[3] = iaqSensor.humidity;
    data[4] = iaqSensor.pressure / 100; // Pa -> hPa
    data[5] = iaqSensor.gasResistance;
    data[6] = iaqSensor.iaq;
    data[7] = iaqSensor.iaqAccuracy;
    data[8] = iaqSensor.staticIaq;
    data[9] = iaqSensor.co2Equivalent;
    data[10] = iaqSensor.breathVocEquivalent;
  }
  else
  {
    checkIaqSensorStatus();
  }
  if (verbose)
  {
    TM_Device_Class::printDeviceName();
    Serial.print("Temperature = ");
    Serial.print(data[0]);
    Serial.print(" / ");
    Serial.print(data[1]);
    Serial.println(" °C");
    TM_Device_Class::printDeviceName();
    Serial.print("Humidity = ");
    Serial.print(data[2]);
    Serial.print(" / ");
    Serial.print(data[3]);
    Serial.println(" %");
    TM_Device_Class::printDeviceName();
    Serial.print("Pressure = ");
    Serial.print(data[4]);
    Serial.println(" hPa");
    TM_Device_Class::printDeviceName();
    Serial.print("gasResistance = ");
    Serial.print(data[5]);
    Serial.println(" Ohm");
    TM_Device_Class::printDeviceName();
    Serial.print("IAQ = ");
    Serial.println(data[6]);
    TM_Device_Class::printDeviceName();
    Serial.print("IAQ accuracy  = ");
    Serial.println(data[7]);
    TM_Device_Class::printDeviceName();
    Serial.print("Static IAQ = ");
    Serial.println(data[8]);
    TM_Device_Class::printDeviceName();
    Serial.print("CO2 equivalent = ");
    Serial.println(data[9]);
    TM_Device_Class::printDeviceName();
    Serial.print("breath VOC equivalent = ");
    Serial.println(data[10]);
  }
  return (float *)&data;
}

void TM_BME680_Class::checkIaqSensorStatus(void)
{
  if (iaqSensor.status != BSEC_OK)
  {
    if (iaqSensor.status < BSEC_OK)
    {
      output = "BSEC error code : " + String(iaqSensor.status);
      Serial.println(output);
      //      for (;;)
      //        errLeds(); /* Halt in case of failure */
    }
    else
    {
      output = "BSEC warning code : " + String(iaqSensor.status);
      Serial.println(output);
    }
  }

  if (iaqSensor.bme680Status != BME680_OK)
  {
    if (iaqSensor.bme680Status < BME680_OK)
    {
      output = "BME680 error code : " + String(iaqSensor.bme680Status);
      Serial.println(output);
      //      for (;;)
      //        errLeds(); /* Halt in case of failure */
    }
    else
    {
      output = "BME680 warning code : " + String(iaqSensor.bme680Status);
      Serial.println(output);
    }
  }
}

// void TM_BME680_Class::errLeds(void)
// {
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(LED_BUILTIN, HIGH);
//   delay(100);
//   digitalWrite(LED_BUILTIN, LOW);
//   delay(100);
// }
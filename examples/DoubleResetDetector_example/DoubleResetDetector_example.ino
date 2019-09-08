#include <SPIFFS.h>
#include "DoubleResetDetector.h"


// Number of seconds after reset during which a 
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 3

DoubleResetDetector drd(DRD_TIMEOUT);

bool fsMounted = false;

// The Double Reset Detector uses the SPIFFS.
// If you also wish to use SPIFFS in your code,
// then you can inform the Double Reset Detector
// that it has been mounted.
void initFS()
{
  Serial.println("Mounting FS...");

  fsMounted = SPIFFS.begin(true);
  if (fsMounted) {
    Serial.println("Mounted file system");
    drd.detectDoubleReset(fsMounted);

    // use SPIFFS in your own code here
    
  } else {
    Serial.println("Failed to mount FS");
  }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("DoubleResetDetector Example Program");
  Serial.println("-----------------------------------");

  initFS();

  if (drd.doubleResetDetected()) {
    Serial.println("Double Reset Detected");
    digitalWrite(LED_BUILTIN, HIGH);
    
  } else {
    Serial.println("No Double Reset Detected");
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void loop()
{
  // Call the double reset detector loop method every so often,
  // so that it can recognise when the timeout expires.
  // You can also call drd.stop() when you wish to no longer
  // consider the next reset as a double reset.
  drd.loop();
}

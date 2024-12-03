#include "TM1637.h" 
#include "Ultrasonic.h"

/* Macro Define */
#define GREEN_LED         6              /* Pin for green LED (SLOW alert) */
#define RED_LED           10              /* Pin for red LED (STOP alert) */
#define BUZZER_PIN        38              /* Pin for buzzer */
#define ULTRASONIC_PIN    36              /* Pin of the Ultrasonic Ranger */

/* Global Variables */
Ultrasonic ultrasonic(ULTRASONIC_PIN);    /* Ultrasonic Ranger object */
int distance = 0;                          /* Variable to store the distance to obstacles in front */

/* the setup() method runs once, when the sketch starts */
void setup() 
{
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    
    digitalWrite(GREEN_LED, LOW);  // Ensure LEDs and buzzer are off initially
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);

}

/* the loop() method runs over and over again */
void loop() 
{
    distance = ultrasonic.MeasureInCentimeters();   /* Read the value from the sensor */

    if (distance < 15) {       // Only act within 15 centimeters
        if (distance <= 5) {                    // STOP alert (5 centimeters or less)
            digitalWrite(GREEN_LED, LOW);         // Turn off SLOW alert
            digitalWrite(RED_LED, HIGH);          // Turn on STOP alert
            digitalWrite(BUZZER_PIN, HIGH);       // Turn on buzzer
        } 
        else {                                  // SLOW alert (5-15 centimeters)
            digitalWrite(GREEN_LED, HIGH);        // Turn on SLOW alert
            digitalWrite(RED_LED, LOW);           // Turn off STOP alert
            digitalWrite(BUZZER_PIN, LOW);        // Turn off buzzer
        }
    } else {                                   
        // No pedestrians detected within 15 centimeters - turn off alerts
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, LOW);
        digitalWrite(BUZZER_PIN, LOW);
    }

    delay(5); // Short delay to avoid rapid switching
}

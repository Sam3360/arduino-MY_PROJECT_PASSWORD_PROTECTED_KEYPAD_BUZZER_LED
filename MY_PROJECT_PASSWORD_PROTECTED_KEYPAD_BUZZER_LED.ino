#include <Keypad.h>

// Define the keypad layout
const byte ROW_NUM    = 4; // Four rows
const byte COL_NUM    = 4; // Four columns
char keys[ROW_NUM][COL_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; // Rows are connected to pins 9, 8, 7, 6
byte pin_columns[COL_NUM] = {5, 4, 3, 2}; // Columns are connected to pins 5, 4, 3, 2

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_columns, ROW_NUM, COL_NUM );

const int greenLedPin = 13;  // Green LED connected to pin 13 (correct password)
const int redLedPin = 12;    // Red LED connected to pin 12 (incorrect password)
const int buzzerPin = 11;    // Buzzer connected to pin 11 (incorrect password)

String password = "2580";  // The correct password
String inputPassword = ""; // Store user input password

void setup() {
  pinMode(greenLedPin, OUTPUT);  // Set Green LED pin as output
  pinMode(redLedPin, OUTPUT);    // Set Red LED pin as output
  pinMode(buzzerPin, OUTPUT);    // Set Buzzer pin as output
  digitalWrite(greenLedPin, LOW);  // Turn off the Green LED initially
  digitalWrite(redLedPin, LOW);    // Turn off the Red LED initially
  digitalWrite(buzzerPin, LOW);    // Turn off the Buzzer initially
  Serial.begin(9600); // Start serial monitor 
}

void loop() {
  char key = keypad.getKey();  // Get the key pressed

  if (key) { // If a key is pressed
    Serial.println(key); // Print the key pressed 
    inputPassword += key; // Add the key to the input password string

    // Check if the length of the input is greater than the password length
    if (inputPassword.length() > password.length()) {
      inputPassword = inputPassword.substring(1); // Remove the first character
    }

    // Check if the input password matches the correct password
    if (inputPassword == password) {
      digitalWrite(greenLedPin, HIGH);  // Turn on the Green LED
      digitalWrite(redLedPin, LOW);     // Turn off the Red LED
      digitalWrite(buzzerPin, LOW);     // Turn off the Buzzer
      delay(2000);  // Keep the Green LED on for 2 seconds
      digitalWrite(greenLedPin, LOW);   // Turn off the Green LED
      inputPassword = ""; // Reset the input
    }

    // If the password is incorrect, give feedback with red LED and buzzer
    else if (inputPassword.length() == password.length()) {
      digitalWrite(redLedPin, HIGH);  // Turn on the Red LED
      digitalWrite(greenLedPin, LOW); // Turn off the Green LED
      digitalWrite(buzzerPin, HIGH);  // Turn on the Buzzer
      delay(500); // Wait for half a second
      digitalWrite(buzzerPin, LOW);   // Turn off the Buzzer
      delay(500); // Wait for a brief moment before resetting
      digitalWrite(redLedPin, LOW);   // Turn off the Red LED
      inputPassword = ""; // Reset the input
    }
  }
}
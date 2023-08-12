
int LEDS[] = {8,9, 10 ,11,12,13};
int BUTTONS[]= {5,2,6,4,3};

int TOTAL_LEDS;
int TOTAL_BUTTONS;

int CURRENT_LED_PIN;
int CURRENT_BUTTON_PIN;

unsigned long START_TIME = 0;
float ELAPSED_TIME = 0;

void setup() {
  Serial.begin(9600);
  
  // Calculate count of leds and buttons
  TOTAL_LEDS = sizeof(LEDS)/sizeof(LEDS[0]);
  TOTAL_BUTTONS = sizeof(BUTTONS)/sizeof(BUTTONS[0]);

  // Set leds pin mode to output
  for(int i=0;i<TOTAL_LEDS;i++){
    pinMode(LEDS[i] , OUTPUT);
  }

  // Set buttons pin mode to input
  for(int i=0;i<TOTAL_BUTTONS;i++){
    pinMode(BUTTONS[i] , INPUT);
  }
}

void loop() {
  
  if( START_TIME == 0 ){ // Determine there is no active game round
    // Print a message for user whenever a new round started
    Serial.println("Are you ready?");
    delay(500);
    Serial.println("Go");

    // Apply random delay between 1 to 4 seconds
    delay( random(1000,4000) );

    // Select a random led pin and get the related button pin
    CURRENT_LED_PIN = select_random_led();
    CURRENT_BUTTON_PIN = select_related_button(CURRENT_LED_PIN);

    // Set the selected led on
    digitalWrite(CURRENT_LED_PIN ,HIGH);

    // Store start time of current round
    START_TIME = millis();
  }

  if(!digitalRead(CURRENT_BUTTON_PIN)){ // If true, determine the related button is pressed
    // Store the end time of the current tound
    ELAPSED_TIME = millis() - START_TIME;

    // Set selected led off
    digitalWrite(CURRENT_LED_PIN ,LOW);

    // Print elapsed time of current round
    Serial.print("Elapsed time: ");
    Serial.print(ELAPSED_TIME/1000,3);
    Serial.println("s.");

    // Reset the round
    START_TIME = 0;

    // Apply one second delay before new round begin
    delay(1000);
  }
  
}

int select_random_led(){
  return LEDS[ random( 0, TOTAL_LEDS ) ];
}

int select_related_button(int led){
  for( int i=0; i < TOTAL_LEDS; i++){
    if(LEDS[i] == led){
      return BUTTONS[i];
    }
  }
}

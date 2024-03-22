/*Task 1: Blink LED
├── Pin: led1 (Output)
└── Timing: Various intervals

Task 2: Measure Frequency of Signal 1
├── Pin: t2_freq (Input)
└── Range: 333 Hz to 1000 Hz

Task 3: Measure Frequency of Signal 2
├── Pin: t3_freq (Input)
└── Range: 500 Hz to 1000 Hz

Task 4: Potentiometer Reading and Error LED
├── Pin: pot_t4 (Input)
├── Pin: error_led (Output)
└── Condition: Turn on error LED if value > maxAnalogIn / 2

Task 5: Print Frequencies
├── Task 2 Frequency (Serial Output)
└── Task 3 Frequency (Serial Output)

Task 6: Debounced Button and LED Toggle
├── Pin: buttonPin (Input)
├── Pin: ledPin (Output)
└── Semaphore: xButtonSemaphore

Task 7: LED Toggle using Semaphore
├── Pin: ledPin (Output)
└── Semaphore: xButtonSemaphore (Input)

Timer: outputTimerCallback
└── Interval: 4 ms

*/


#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>


int task1_led=34; //output port for LED of task 1 
int freq_T2=35;//input port from signal generator to measure task-2 frequency
int freq_T3=32;//input port from signal geneerator to measure task-3 frequency
int pott_4=33;//input port from potentiometer to show analog frequency
int Led_error=25;//output port to blink the led for error from potentiometer
const int buttone_t6 = 2;
const int led_t6 = 4;


SemaphoreHandle_t xButtonSemaphore;// Function prototypes

void Task1(void *Param);
void Task2(void *Param);
void Task3(void *Param);
void Task4(void *Param);
void Task5(void *Param);
void Task6(void *Param);
void Task7(void *Param);

// Timer function
void outputTimerCallback(TimerHandle_t xTimer) {

}



void setup(void) {
  xButtonSemaphore = xSemaphoreCreateBinary();
  pinMode(task1_led, OUTPUT); // set pin 34 as output for Task 1
  pinMode(freq_T2, INPUT); // set pin 35 as input for Task 2
  pinMode(freq_T3, INPUT); // set pin 32 as input for Task 3
  pinMode(pott_4, INPUT); // set pin 33 as input for Task 4
  pinMode(Led_error, OUTPUT); //Led pin output for Task 4
  pinMode(buttone_t6, INPUT_PULLUP);//Button pin input for Task 6
  pinMode(led_t6, OUTPUT);//LED pin output for Task6
  // Initialize readings array with 0's
  Serial.begin(9600);

  // Task creation
  xTaskCreate(Task1, "Task1", 1024, NULL, 1, NULL);
  xTaskCreate(Task2, "Task2", 1024, NULL, 1, NULL);
  xTaskCreate(Task3, "Task3", 1024, NULL, 1, NULL);
  xTaskCreate(Task4, "Task4", 1024, NULL, 1, NULL);
  xTaskCreate(Task5, "Task5", 1024, NULL, 1, NULL);
  xTaskCreate(Task6, "Task6", 1024, NULL, 1, NULL);
  xTaskCreate(Task7, "Task7", 1024, NULL, 1, NULL);

  // Timer creation
  TimerHandle_t outputTimer = xTimerCreate("OutputTimer", pdMS_TO_TICKS(4), pdTRUE, (void *)0, outputTimerCallback);
  xTimerStart(outputTimer, 0);
}

void loop() 
{
}


void Task1(void *Param) 
{
  for (;;){
  digitalWrite(task1_led, HIGH); // set pin 2 high for 200us
  delayMicroseconds(200);
  digitalWrite(task1_led, LOW); // set pin 2 low for 50us
  delayMicroseconds(50);
  digitalWrite(task1_led, HIGH); // set pin 2 high for 30us
  delayMicroseconds(30);
  digitalWrite(task1_led, LOW); // set pin 2 low for remaining period
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}


void Task2(void *Param) 
{
  for (;;){
  #define SAMPLES 10 // number of samples to take
  int count = 0;
  for (int i = 0; i < SAMPLES; i++) 
  {
    count += pulseIn(freq_T2, HIGH); // measure the pulse width of the input signal
  }
  count = count*2;
  float frequency = 1000000.0 / (count / SAMPLES); // calculate frequency in Hz
  frequency = constrain(frequency, 333, 1000); // bound frequency between 333 and 1000 Hz
  //Serial.println(frequency); // output frequency value to serial port
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
} 

void Task3(void *Param)
{
  for (;;){
  #define SAMPLES 8 // number of samples to take
  int count2 = 0;
  for (int i = 0; i < SAMPLES; i++) {
    count2 += pulseIn(freq_T3, HIGH); // measure the pulse width of the input signal
  }
 count2 = count2*2;
  float frequency2 = 1000000.0 / (count2 / SAMPLES); // calculate frequency in Hz
  frequency2 = constrain(frequency2, 500, 1000); // bound frequency between 500 and 1000 Hz
  //int scaled_frequency2 = map(frequency2, 500, 1000, 0, 99); // scale frequency between 0 and 99
  //Serial.println("Frequency_2:"); // output frequency value to serial port
  //Serial.println(frequency2); // output frequency value to serial port
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
} 

void Task4(void *Param)
{
  for (;;){
  const int maxAnalogIn = 1023;
  const int numReadings = 4;
  int readings[numReadings];
  int index = 0;
  int total = 0;
  int filteredValue = 0;
  for (int i = 0; i < numReadings; i++) 
  {
  readings[i] = 0;
  }
  
  // Read  the analog input value
  int analogValue = analogRead(pott_4);
  // Subtract the oldest reading from the total
  total -= readings[index];
  // Add the new reading to the total
  total += analogValue;
  // Store the new reading in the readings array
  readings[index] = analogValue;
  // Increment the index
  index++;
  // Wrap the index if it exceeds the number of readings
  if (index >= numReadings)
   {
    index = 0;
  }
  // Compute the filtered value as the average of the readings
  filteredValue = total / numReadings;
  // If the filtered value is greater than half of the maximum range, turn on the LED
  if (filteredValue > maxAnalogIn / 2) {
    digitalWrite(Led_error, HIGH);
    //Serial.println("error led HIGH");
 
  } else {
    digitalWrite(Led_error, LOW);
    //Serial.println("error led LOW");

  }
  // Send the filtered value to the serial port
  //Serial.println(filteredValue);
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void Task5(void *Param) 
{
  for (;;){
  int task2Freq = 0;
  int task3Freq = 0;
    // Measure the frequency of Task 2 signal
  task2Freq = pulseIn(freq_T2, HIGH, 20000) == 0 ? 0 : 1000000 / pulseIn(freq_T2, HIGH, 20000);
  // Scale and bound the frequency between to 0-99
  task2Freq = map(freq_T2, 333, 1000, 0, 99);
  // Measure the frequency of Task 3 signal
  task3Freq = pulseIn(freq_T3, HIGH, 8000) == 0 ? 0 : 1000000 / pulseIn(freq_T2, HIGH, 8000);
  // Scale and bound the frequency value between 0-99
  task3Freq = map(freq_T3, 500, 1000, 0, 99);
  // Send the frequency values to the serial port
  Serial.println(task2Freq);//To print frequency of given waveform of Task2
  Serial.println(task3Freq);//To print frequency of given waveform of Task3
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void Task6(void *Param)
{
  int buttonState = digitalRead(buttone_t6); //read button state
  int lastButtonState = buttonState;       // intialize button state 0
  unsigned long lastDebounceTime = 0;       // intialize button debounce time 0
  const unsigned long debounceTime = 50;      // debounce time for button

  for (;;) {
    int reading = digitalRead(buttone_t6);      //read button state

    if (reading != lastButtonState) {          //check button state
      lastDebounceTime = millis();             // check last debounce time
    }

    if ((millis() - lastDebounceTime) > debounceTime) {  // check last debounce time
      if (reading != buttonState) {
        buttonState = reading;

        if (buttonState == LOW) {    //if button  pressed task 7 in queue
          digitalWrite(led_t6, !digitalRead(led_t6));
          xSemaphoreGive(xButtonSemaphore);
        }
      }
    }

    lastButtonState = reading;
    vTaskDelay(pdMS_TO_TICKS(10));
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void Task7(void *Param)
{
  bool ledState = false;

  for (;;) {
    if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY) == pdTRUE)  //semaphore receive when button pressed 
     {
      ledState = !ledState;
      digitalWrite(led_t6, ledState ? HIGH : LOW);   //led high if button high , led low if button low
    }
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}
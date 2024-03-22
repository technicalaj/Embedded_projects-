# Rtos 

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

# Rtos 

**1. Problem**
Your program needs to satisfy the same functional and real-time requirements, i.e.
it needs to perform the same (hard RT) tasks at the same rates.
In addition, your program should satisfy the following additional requirements:
1. Monitor one digital input - to be connected to a pushbutton. Make sure the input is
debounced. The frequency at which your program monitor this digital input is left to your
choice.
2. Control a LED. The state of the LED should be toggled by the pushbutton.
Your program needs to use FreeRTOS (so you can use any number of FreeRTOS tasks, timers,
queues, semaphores, etc.). It is your choice whether you implement the required tasks using actual
FreeRTOS tasks or callback functions called by FreeRTOS software timers, or a combination of the
two approaches.
In particular, your program needs to:
 Monitor the digital input and control the LED from two independent tasks.
 Use an event queue to enable the communication between those two tasks, i.e. when the
pushbutton is pressed the monitor digital input task will queue an event, which needs to be
received and acted upon by the control LED task.
 Use a global structure (struct), to store the frequencies measured by Task #2 and Task #3
(from Assignment #2) and printed to the serial port by Task #5 (also from assignment 2).
Access to this structure must be adequately protected, using FreeRTOS’ semaphore(s).
 Use any other FreeRTOS constructs you consider useful for your program.

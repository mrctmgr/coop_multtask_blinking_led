# Cooperative Multitasking adjustable led on/off period with Serial Communication

 Two tasks run in Main. These tasks do not block each other.
 
 -The first task will turn the specified led on and off
 
 -The second task will echo the data from the UART over the same port. It will work with UART interrupt and its settings can be changed. default bound rate is 115200 8N1
 
 -When we send the "start" string from the UART, the echo task restart and the led will continue to work with the previous led on/off periods.
 
 -When we send the "stop" string from UART, the echo task end and the led blink at 1 second period.
 
 -If we write "ledon=500" from UART, the led on time will be 500 ms.
 
 -If we write "ledoff=500" from UART, the led off time will be 500 ms.

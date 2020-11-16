# avr-server-switch
Servo-motor controller: open/close gates by servo 

# The task description
A greenhouse ventilation cooler is located under the gates which are controlled by a servo motor. The greenhouse termostat can set/clear the cool start signal (1 bit TTL signal). So the task is to convert the boolean signal to the servo control signal.

## Input
Boolean signal (TTL)

## Output
0: servo minimal angle signal
1: servo maximum angle signal


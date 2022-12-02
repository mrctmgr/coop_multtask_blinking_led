#define led 13                  //define led 
String str;                     //define command string
bool echo_status = false;       //declare echo status initially false
bool led_status = 0;            //led status High or Low initially Low

/*Declaring the led on/off time initially 1sec and temp variables hold the value that before taking stop command*/
unsigned int    led_onTime = 1000; 
unsigned int    led_offTime = 1000;
unsigned int    temp_onTime = 1000;
unsigned int    temp_offTime = 1000;

unsigned long old_time = 0; //To calculate elapsed time of led blinking
unsigned long new_time;

void    blink_led(void)   //teh control of blinking led function
{
    new_time = millis(); //hold the elapsed time while the board energized

    if (new_time - old_time > led_offTime && !led_status) //if the off time duration is reached nad the led status is LOW
    {
        old_time = new_time; //defined period begining time
        led_status = 1;     //switching status
    }
    if (new_time - old_time > led_onTime && led_status)  //if the on time duration is reached and the led status is HIGH
    {
        old_time = new_time;
        led_status = 0;
    }
    digitalWrite(led, led_status);  //the led turns on or off
}

void    serialMessage(void)     //make the command string function
{
    str.remove(0);              //firstly, clean the command string
    while (Serial.available())  //check serial communication availability
    {
        char c = Serial.read();  //defiend a char
        if (c == '\n')           //if the char new line exit the loop 
            break;
        str += c;                //hold the income char
        delay(3);
    }
}

void    adj_led(void)           //adjust the led's on/off time function
{
    serialMessage();            //call the serial message function and command string
    if (str.length() > 0)       //if command string length greater than 0
    {
        if (str.indexOf("start") >= 0 && str.length() == 6) //if command is start and command str include just start
        {
            echo_status = true;                             //echo mode on
            led_onTime = temp_onTime;                       //set adjustable values of led on/off time 
            led_offTime = temp_offTime;
        }
        if (str.indexOf("stop") >= 0 && str.length() == 5)  //if command is stop and command str include just stop
        {
            echo_status = false;                            //echo mode off
            temp_onTime = led_onTime;                       //hold adjustable last values of led on/off time
            temp_offTime = led_offTime;
            led_onTime = 1000;                              //in this mode blinking led 1sec
            led_offTime = 1000;
        }
        if (str.indexOf("ledon") >= 0)                      //if command is ledon 
        {
            int i = str.indexOf('=');                       //find the index of equal mark
            String s = "";                                  //new string to hold the timing value
            for (i++; i < str.length(); i++)                //add after the equal mark values to new string
                s += str[i];
            if (str.length() - s.length() == 6 && echo_status) //check the string include ledon=value and echo mode on
                led_onTime = s.toInt();                        //set new led on value
        }
        if (str.indexOf("ledoff") >= 0)
        {
            int i = str.indexOf('=');
            String s = "";
            for (i++; i < str.length(); i++)
                s += str[i];
            if (str.length() - s.length() == 7 && echo_status) 
                led_offTime = s.toInt();
        }
        if (echo_status)                                    //if in the echo mode print
            Serial.println(str);
        str = "";                                           //clear string
    }
}

void    setup(void)             
{
    pinMode(led, OUTPUT);       //define led as an output
    Serial.begin(115200);       //set the bound rate 
}

void    loop(void)
{
    blink_led();                //task 1
    adj_led();                  //task 2
}
/*
This is a fully automatic security system!
System is meant to be started at 10 P.M.

The  scale for the following code in terms of time is
1 milisecond in code = 10 seconds in real life
(e.g 10 hrs = 36000 seconds = 3600 miliseconds in code)

NOTE: some of the variables I assigned aren't really needed but
      I made variables so I can explain them 
      (e.g if1, elseIf1, etc)
*/

int trigPin = 8; //pins for the 
int echoPin = 7; //ultrasonic distance sensor

int buzzer = 4; //pin for the piezo

int led = 2;    //led that lights up when somethings too close
                //and is synced with ultrasonic distance sensor
                //(put this led in the foyer)

int ledTWO = 1; //led that stays lit throughout the day to make
                //house look occupied (put this led in a room 
                //that's close to the front of the house)


/*
NOTE: For all the variables where I used "unsigned long", it's 
      because "int" can only store uptil 32768, or ~33 seconds.
      
      I had to create the next 4 variables so I could change 
      their values every 24 hrs (8640) for ledTWO to work.
*/

unsigned long x = 0;  
/*variable that starts out at 0 but increases by 8640 everytime
24 hrs are complete, it's one piece in making the code for ledTWO
basically reset each day.
*/

unsigned long zero = 0;
/*variable storing time of 10 P.M the night before, this variable
  may seem unnecessary but when I ran my code without making 0
  the minimum value, it malfunctioned*/

unsigned long thirtySixHundred = 3600;
//variable storing time of 8 A.M (when ledTWO turns on)

unsigned long eightySixHundredFourty = 8640;
//variable storing time of 10 P.M (when ledTWO turns off)


int distanceLED = 40;  //measurement in inches for how close 
                       //something can come before led and piezo
                       //are activated


long duration;         // 2 variables for the
float distanceInch;    //ultrasonic distance sensor


void setup() {              //code that's run once
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
/*echo pin is input because unlike the rest of the pins here, 
it receives information.(how long it took for an inaudible 
sound wave to reflect off of a surface and return back)*/
  
pinMode(buzzer, OUTPUT);
pinMode(led, OUTPUT);
pinMode(ledTWO, OUTPUT); 
}


void loop() {   //code that keeps looping
  
unsigned long currentMillis = millis(); 
//sets timer, (I used the millis function for the timer and not 
//delay because delay stops the whole code)

  
digitalWrite(trigPin, LOW);          //Code 
delayMicroseconds(2);                //to make
digitalWrite(trigPin, HIGH);         //the
delayMicroseconds(10);               //ultrasonic
digitalWrite(trigPin, LOW);          //distance

duration = pulseIn(echoPin, HIGH);   //sensor

distanceInch = duration * 0.0133 /2; //work

  
int nightCode = currentMillis > zero && currentMillis < thirtySixHundred;
//nightCode is the variable that stores all time throughout the
//5 days where the user is asleep (10 P.M - 8 A.M OR 0 - 3600)  
  
int dayCode = currentMillis > thirtySixHundred && currentMillis < eightySixHundredFourty;
//dayCode is the variable that stores all time where the user 
//is awake(8 A.M - 10 P.M OR 3600 - 8640)

  
//the following 4 variables go over the 4 possibilities there are
  
int if1 = (distanceLED > distanceInch) && nightCode;
// "if1" variable controls what to do if an object is too close
// and it's from 10 P.M - 8 A.M (night)
  
int elseIf1 = (distanceLED < distanceInch) && nightCode;
//"elseIf1" variable controls what to do if an object is out of
//range and it's from 10 P.M - 8 A.M (night)
  
int elseIf2 = (distanceLED < distanceInch) && dayCode;
//"elseIf2" variable controls what to do if an object is out of
//range and it's from 8 A.M - 10 P.M (day)
   
int elseIf3 = (distanceLED > distanceInch) && dayCode;
//"elseIf3" variable controls what to do if an object is too 
//close and it's from 8 A.M - 10 P.M (day)
 
  
    if(if1) //see what "if1" does on line 101
    {                                                 
      digitalWrite(led, HIGH);      
      digitalWrite(ledTWO, LOW);

      delay(1);    //so code doesn't lag or crash
      tone(buzzer, 315);          
      delay(150);                                
      tone(buzzer, 433);                
      delay(150);  
      tone(buzzer, 315);          
      delay(150);                                
      tone(buzzer, 433);                
      delay(150);
    }


    else if(elseIf1) //see what "elseIf1" does on line 105
    {
      digitalWrite(led, LOW);
      digitalWrite(ledTWO, LOW);
      noTone(buzzer); // function to make buzzer quiet 
    }


    else if(elseIf2) //see what "elseIf2" does on line 109
    {
      digitalWrite(led, LOW);
      digitalWrite(ledTWO, HIGH);
      noTone(buzzer);
    }


    else if(elseIf3) //see what "elseIf3" does on line 113
    {
      digitalWrite(led, HIGH);
      digitalWrite(ledTWO, HIGH);

      delay(1);
      tone(buzzer, 315);          
      delay(150);                                
      tone(buzzer, 433);                
      delay(150);  
      tone(buzzer, 315);          
      delay(150);                                
      tone(buzzer, 433);                
      delay(150);
    }

  if(currentMillis > (x + 8640)) //if timer is greater than the
                                 //last saved multiple of 8640
                                 //(this code is for ledTWO)
  {
    zero += 8640;                    
    thirtySixHundred += 8640;         
    eightySixHundredFourty += 8640;   
    x += 8640;

    /*everytime the timer reaches a multiple of 8640, this makes 
    it reset in a way by increasing the value of all the other 
    variables by 8640 in order to make ledTWO work.
    (e.g if timer = 20640, the closest previous multiple of 8640
    is 17280, meaning right now the time is 20640 - 17280 = 3360.
    Following the scale I chose, that would be 9h 20m from the 
    starting time (10 P.M), making it 7:20 A.M.
    Since this is before 8 A.M, that means ledTWO will be off.)*/
  }                           
}

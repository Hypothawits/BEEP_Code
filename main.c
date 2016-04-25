
int i;                 //For general use
int range = 700;       // The range of frequencys to output
int offset = 200;      // The min frequency to output (not hard limit)
int MidHz = (offset + (offset+700))/2;    //the middle frequency
int toneHz;            //The final frequency outputed 

String stringprint;    //String to print
String X_string;       //The Average x value read from sensor  
float Xavg;            //The Average x value read from sensor

float Level;           //The initial reading from the sensor, taken as "level" 
double SensorS = 0.33; // the sensitivity of the sensor (estimate)

boolean Button_Press;
boolean Level_Set;

void setup() {
  Serial.begin(9600);
  pinMode(10,INPUT); 
}

void loop() {
  //check if button pressed
  Button_Press = digitalRead(10);
  if (Button_Press == true){
    //Check if the reference level has been set
    if (Level_Set == false){
      Level = ReadSensor();  //set the reference level
      Level_Set = true;
    }
    
    Xavg = ReadSensor();
    if ((Xavg <= Level*1.02)&&(Xavg >=Level*0.98)){
        PlayTone(Xavg);
        delay (150);
    }
      
    
    StringCreate();   
    Serial.println(stringprint);
    
    PlayTone(Xavg);
    delay (200);
   }
   else{
     Level_Set = false;
   }
}

float ReadSensor (){
  // Takes 400 reading of the x value (pin A0) and returns the average
  float result;
  for (i=0;i<401;i+=1){
    result += analogRead(A0)*(5.0/1023.0);
  }
  result = result/400;
  return result;
}

void StringCreate(){
  //creates and string to display the average x value from sensor in serial
  stringprint = String(" ");
  X_string = String(Xavg, DEC);
  
  stringprint += "x Value: ";
  stringprint += X_string;
}

void PlayTone(float value){
  toneHz = ((value - Level)*(90/SensorS)*(range/180) + MidHz);
  Serial.println(toneHz);
  tone(9,toneHz, 100);
}

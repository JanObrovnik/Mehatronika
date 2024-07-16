//-----Hardware-------------
//User button
#define BTN 9
//RGB LED
#define LED_R 7
#define LED_G 10
#define LED_B 4
//Ambient Light Sensor
#define LX_A 1
#define LX_B 3
#define LX_OUT 0
//I2C
#define SDA 5
#define SCL 6
//UART
#define RX 20
#define TX 21
//--------------------------

//-----Global variables-----
const int led_R_channel = 0;
const int led_G_channel = 1;
const int led_B_channel = 2;
const int pwm_frequency = 5000;//Hz
const int pwm_resolution = 12;//bit

//--------Variables---------
bool lock = false; // gumb spremeni v stikalo
bool hold = false; // preveri ali se gumb drzi ali ne
short time_hold = 0; // preveri koliko casa se gumb drzi
short time_release = 0; // preveri koliko casa je gumb sprescen
short count = 0; // steje klike (pravo stevilo je +1)
short brightness = 16; // svetlost lucke
short light = 0; // stopnja okoliske osvetljave
//--------------------------


//---------Gumb BTN---------
int btn(){
  return !digitalRead(BTN);
}

//-----------LED------------
void rgb(int R, int G, int B){
  ledcWrite(led_R_channel, R);
  ledcWrite(led_G_channel, G);
  ledcWrite(led_B_channel, B);
}

//-----Svetlobni senzor-----
int lx(int mode){
  switch(mode){
    case 0:
      pinMode(LX_A,INPUT);
      pinMode(LX_B,INPUT);
    break;
    case 1:
      pinMode(LX_A,INPUT);
      pinMode(LX_B,OUTPUT);
      digitalWrite(LX_B, LOW);
    break;
    case 2:
      pinMode(LX_A,OUTPUT);
      digitalWrite(LX_A, LOW);
      pinMode(LX_B,INPUT);
    break;
    default:
      pinMode(LX_A,INPUT);
      pinMode(LX_B,INPUT);
  }

  return analogRead(LX_OUT);
}


void setup() {
  pinMode(BTN,INPUT);

  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);

  ledcSetup(led_R_channel, pwm_frequency, pwm_resolution);
  ledcAttachPin(LED_R, led_R_channel);
  ledcWrite(led_R_channel, 200);

  ledcSetup(led_G_channel, pwm_frequency, pwm_resolution);
  ledcAttachPin(LED_G, led_G_channel);
  ledcWrite(led_G_channel, 100);

  ledcSetup(led_B_channel, pwm_frequency, pwm_resolution);
  ledcAttachPin(LED_B, led_B_channel);
  ledcWrite(led_B_channel, 0);

  pinMode(LX_A,INPUT);
  pinMode(LX_B,INPUT);
  pinMode(LX_OUT,INPUT);

  pinMode(RX,OUTPUT);
  digitalWrite(RX,LOW);

  Serial.begin(9600);
  delay(1000);
  Serial.println("Erasmus+\nGEMS\nAmethyst\nv0.0\n\n");
}

void loop() {
  delay(100);

  if(btn()){

    if(time_hold == 0 && time_release <= 6) {
      count++;
    }

    time_hold++;
    time_release = 0;

    if(time_hold > 68) {brightness = 0; rgb(brightness,brightness,brightness);}
    else if(time_hold > 60) {brightness = 6; rgb(brightness,brightness,brightness);}
    else if(time_hold > 52) {brightness = 16; rgb(brightness,brightness,brightness);}
    else if(time_hold > 44) {brightness = 51; rgb(brightness,brightness,brightness);}
    else if(time_hold > 36) {brightness = 102; rgb(brightness,brightness,brightness);}
    else if(time_hold > 28) {brightness = 153; rgb(brightness,brightness,brightness);}
    else if(time_hold > 20) {brightness = 204; rgb(brightness,brightness,brightness);}
    else if(time_hold > 12) {brightness = 255; rgb(brightness,brightness,brightness); count = 0;}

    if(hold == false) {

      if(lock == true) {
        lock = false;
      }
      else if(lock == false) {
        rgb(0,0,brightness);
        lock = true;
        digitalWrite(RX,HIGH);
      }
      hold = true;
    }
  }

  else {
    hold = false;
    time_hold = 0;
    time_release++;

    if(time_release > 100) time_release = 20;
    else if(time_release > 6) {
      if (count == 2) {light = 0; rgb(16,0,8); delay(2000);}
      else if (count == 3) {light = 1; rgb(120,0,60); delay(2000);}
      else if (count == 4) {light = 2; rgb(250,0,125); delay(2000);}
      count = 0;
    }

    if(lock == true) {
      rgb(0,0,brightness);
      digitalWrite(RX,HIGH);
    }
    else if(lx(light) < (800/(light+1))){
      rgb(brightness,0,0);
      digitalWrite(RX,HIGH);
    }
    else{
      rgb(0,brightness,0);
      digitalWrite(RX,LOW);
    }
  }
}
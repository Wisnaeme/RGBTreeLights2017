// Source location \\adam\U_DRIVE\_BACKED_UP\_Documents\Electronics\XmasTree
#include <FastLED.h>
#define NUM_LEDS 102
#define DATA_PIN 6
CRGB leds[NUM_LEDS];
void setup() {
  Serial.begin(9600);
  Serial.println("Boot");
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  //  SetRandomLight;
  SetAllOff();
  delay(10); //Delay before getting going.
  BootUp();
  randomSeed(analogRead(0) + analogRead(1) + analogRead(2) + analogRead(3) + analogRead(4) + analogRead(5) + analogRead(6));
}



void loop() {
  // put your main code here, to run repeatedly:
  SingleDrift();
  FastLED.show();
  //delay(random(50));

}


void FadeAll(int x)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].subtractFromRGB(x);
  }
}


void SetRandomLight() {
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].r = random(128);
    leds[i].g = random(128);
    leds[i].b = random(128);
    Serial.println(i);
  }
}

void SetAllOff()
{
  Serial.println("Blanking all.");
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = 0x000000;
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;

    //Serial.println(i);
  }
  FastLED.show();

}


void SingleDrift() {
  int mini = 5;
  int maxi = 255;
  FastLED.setBrightness(maxi);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (leds[i].r > 64) leds[i].r = leds[i].r - 8;
    if (leds[i].g > 64) leds[i].g = leds[i].g - 8;
    if (leds[i].b > 64) leds[i].b = leds[i].b - 8;

    int rnd = random(10);
    if (rnd == 1 && leds[i].r >= 2) leds[i].r = leds[i].r - 1;
    if (rnd == 2 && leds[i].g >= 2) leds[i].g = leds[i].g - 1;
    if (rnd == 3 && leds[i].b >= 2) leds[i].b = leds[i].b - 1;
    if (rnd == 4) leds[i].fadeToBlackBy(2);
    if (rnd == 5) leds[i].g++;
    //if (rnd == 6 && leds[i].g < 240) leds[i].g = leds[i].g + 1;
    //if (rnd == 7 && leds[i].b < 240) leds[i].b = leds[i].b + 1;
    if (leds[i].g < 2) leds[i].g = 2;
  }


  int i = random(NUM_LEDS);
  Serial.println(i);
  if (leds[i].r + leds[i].g + leds[i].b > 10) return; //If the LED is still bright, do not change it.
  if (random(100) > 80)
  {
    //Choose a colour
    int r = random(20);
    switch (r)
    {

      case 99:
        for (i = 0; i < NUM_LEDS; i++)
        {
          int x = leds[i].r;
          leds[i].r = leds[i].b;
          leds[i].b = x;
        }

      case 1:
      case 2:
      case 3:
        leds[i] = CRGB::Red;
        break;
      case 4:
      case 5:
      case 6:
        leds[i] = CRGB::Green;
        break;
      case 7:
        leds[i] = CRGB::Blue;
        break;
      case 8:
        leds[i].r = random(128, 255);
        leds[i].g = random(128, 255);
        leds[i].b = random(128, 255);
      case 9:
        leds[i] = CRGB::Yellow;
        break;
      case 10:
        leds[i] = CRGB::Crimson;
        break;
      case 12:
        leds[i] = CRGB::Aqua;
        break;
      case 13:
        leds[i] = CRGB::BlueViolet;
        break;
      case 14:
        leds[i] = CRGB::MidnightBlue;
        break;
      case 15:
        leds[i].setRGB( 255, 255, 255);
        break;

    }
  }

}

void BootUp()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].b = map(i, 0, NUM_LEDS, 0, 255);
    leds[i].r = map(i, NUM_LEDS, 0, 0, 255);
  }
  for (int pc = 0; pc < 100; pc++)
  {
    FastLED.setBrightness(pc);
    FastLED.show();
    delay(3);
  }
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = -leds[i];
    FastLED.show();
    delay(10);
  }

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].setRGB( 0, 10, 0);

    FastLED.show();
    delay(10);
  }


}


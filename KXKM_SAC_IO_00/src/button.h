unsigned long lock_count = 0;
uint8_t pr = 0;
uint8_t bt = 0;
#define BT_T 100
int sensorValue = 0;
int som_Value = 0;
int Moy_sensor = 0;

void check_button () {

  if (Moy_sensor > BT_T) {
    Moy_sensor = 0;
    som_Value = 0;
  }
  int sen_Value = analogRead(35);

  if (sen_Value > 1) {
    som_Value += sen_Value;
    Moy_sensor += 1;
  } else {
    som_Value = 0;
    Moy_sensor = 0;
  }

  if (Moy_sensor != 0) {
    sensorValue =  som_Value / Moy_sensor;
  } else {
    sensorValue = 0;
  }

#ifdef DEBUG_calibre_btn
  Serial.print("sen_Value = ");
  Serial.print(sen_Value);
  Serial.print(" // sensorValue = ");
  Serial.print(sensorValue);
  Serial.print(" // pr = ");
  Serial.print(pr);
  Serial.print("  // bt = ");
  Serial.print(bt);
  Serial.print("  // Moy_sensor = ");
  Serial.print(Moy_sensor);
  Serial.print("  // som_Value = ");
  Serial.println(som_Value);
#endif



  if (sensorValue < 200) {
    pr = 0; // relache btn
  } 
  else if (sensorValue > 410 && sensorValue < 450) {
    if (lock_count == 0) lock_count = millis();
    if (millis() - lock_count > 2000) {
      lock = !lock;
      ledBlack();
      lock_count = 0;
      
#ifdef DEBUG
      if (lock) Serial.println("locked in manual");
      else Serial.println("unlocked to artnet");
#endif
    }
    pr = 2; bt = 34;// bt3 4
    for (int i = NUM_LEDS_PER_STRIP_max  ; i < NUM_LEDS_PER_STRIP_max + 2 ; i++) {
      if (lock) {
        strands[1]->pixels[i] = pixelFromRGB(80, 80, 80);
      }
      else  strands[1]->pixels[i] = pixelFromRGB(0, 0, 0);
#ifdef DEBUG_btn
      Serial.println("/////bt3 4");
#endif
    }//for i
  }

  if (lock && pr == 0 && bt == 0) {
    if (sensorValue > 1650 && sensorValue < 1700) {
      pr = 1; bt = 1; // bt1
    } else if (sensorValue > 910 && sensorValue < 1000) {
      pr = 1; bt = 2; // bt2
    } else if (sensorValue > 500 && sensorValue < 600) {
      pr = 1; bt = 3; // bt3
    }  else if (sensorValue > 290 && sensorValue < 390) {
      pr = 1; bt = 4; //bt4
    }
  }// pr !=1

  if (pr == 1) {
    if (sensorValue > 1590 && sensorValue < 1610) {
      pr = 2; bt = 12;// bt1 2
      for (int i = NUM_LEDS_PER_STRIP_max  ; i < NUM_LEDS_PER_STRIP_max + 2 ; i++) {
        strands[1]->pixels[i] = pixelFromRGB(40, 40, 0);
#ifdef DEBUG_btn
        Serial.println("/////bt1 2");
#endif
      }//for i
    } else if (sensorValue > 1460 && sensorValue < 1490) {
      pr = 2; bt = 13;// bt1 3
      for (int i = NUM_LEDS_PER_STRIP_max  ; i < NUM_LEDS_PER_STRIP_max + 2 ; i++) {
        strands[1]->pixels[i] = pixelFromRGB(40, 0, 40);
#ifdef DEBUG_btn
        Serial.println("/////bt1 3");
#endif
      }//for i
    } else if (sensorValue > 1170 && sensorValue < 1200) {
      pr = 2; bt = 14;// bt1 4
      for (int i = NUM_LEDS_PER_STRIP_max  ; i < NUM_LEDS_PER_STRIP_max + 2 ; i++) {
        strands[1]->pixels[i] = pixelFromRGB(80, 40,  0);
#ifdef DEBUG_btn
        Serial.println("/////bt1 4");
#endif
      }//for i
    } else if (sensorValue > 840 && sensorValue < 870) {
      pr = 2; bt = 23;// bt2 3
      for (int i = NUM_LEDS_PER_STRIP_max  ; i < NUM_LEDS_PER_STRIP_max + 2 ; i++) {
        strands[1]->pixels[i] = pixelFromRGB(0, 40, 40);
#ifdef DEBUG_btn
        Serial.println("/////bt2 3");
#endif
      }//for i
    } else if (sensorValue > 640 && sensorValue < 680) {
      pr = 2; bt = 24;// bt2 4
      for (int i = NUM_LEDS_PER_STRIP_max  ; i < NUM_LEDS_PER_STRIP_max + 2 ; i++) {
        strands[1]->pixels[i] = pixelFromRGB(80, 80, 0);
#ifdef DEBUG_btn
        Serial.println("/////bt2 4");
#endif
      }// for i
    }// else if
  }// pr > 1

  if (lock && pr == 0 && bt != 0) {
    if (bt == 1) {
      manu_frame(3);
#ifdef DEBUG_btn
      Serial.println("/////bt1");
#endif
      for (int i = NUM_LEDS_PER_STRIP_max  ; i < NUM_LEDS_PER_STRIP_max + 2 ; i++) {
        strands[1]->pixels[i] = pixelFromRGB(40, 0, 0);
      }//for i
    } else if (bt == 2) {
      manu_frame(4);
#ifdef DEBUG_btn
      Serial.println("/////bt2");
#endif
      for (int i = NUM_LEDS_PER_STRIP_max  ; i < NUM_LEDS_PER_STRIP_max + 2 ; i++) {
        strands[1]->pixels[i] = pixelFromRGB(0, 40, 0);
      }//for i
    } else if  (bt == 3) {
      manu_frame(5);
#ifdef DEBUG_btn
      Serial.println("/////bt3");
#endif
      for (int i = NUM_LEDS_PER_STRIP_max  ; i < NUM_LEDS_PER_STRIP_max + 2 ; i++) {
        strands[1]->pixels[i] = pixelFromRGB(0, 0, 40);
      }//for i
    } else if  (bt == 4) {
      manu_frame(2);
#ifdef DEBUG_btn
      Serial.println("/////bt4");
#endif
      for (int i = NUM_LEDS_PER_STRIP_max  ; i < NUM_LEDS_PER_STRIP_max + 2 ; i++) {
        strands[1]->pixels[i] = pixelFromRGB(40, 25, 0);
      }//for i
    }
    bt = 0;
  }//if (pr == 0 && bt != 0)
}// check_button
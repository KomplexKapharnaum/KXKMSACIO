#include <M5Stack.h>
#include <M5ez.h>

#define KEYBOARD_I2C_ADDR 0X08
#define KEYBOARD_INT 5

#include <K32.h> // https://github.com/KomplexKapharnaum/K32-lib
K32 *k32;

void setup()
{
#include <themes/dark.h>
  ez.begin();

  M5.Power.begin();
  M5.Speaker.mute();

  ez.screen.clear();

  ez.header.show("M5-Remote");
  ez.canvas.lmargin(10);
  ez.canvas.scroll(true);
  ez.canvas.font(&FreeSans9pt7b);
  ez.canvas.println("Hello world");

  //////////////////////////////////////// M5 Face Keyboard ////////////////////////////////
  Wire.begin();
  pinMode(KEYBOARD_INT, INPUT_PULLUP);

  //////////////////////////////////////// K32_lib ////////////////////////////////////
  k32 = new K32();

  /////////////////////////////////////////////// WIFI //////////////////////////////////////
  k32->init_wifi("M5-Remote");
  k32->wifi->staticIP("2.0.0.11", "2.0.0.1", "255.0.0.0");
  // k32->wifi->connect("kxkm24", NULL); //KXKM
  // k32->wifi->connect("mgr4g", NULL); //MGR
  k32->wifi->connect("riri_new", "B2az41opbn6397"); //Riri dev home

  /////////////////////////////////////// MQTT //////////////////////////////////////
  k32->init_mqtt({
      // .broker = "2.0.0.1",// Komplex
      .broker = "2.0.0.10", // Riri dev home
      // .broker = "192.168.43.100",//MGR
      .beatInterval = 0,  // heartbeat interval milliseconds (0 = disable)
      .beaconInterval = 0 // full beacon interval milliseconds (0 = disable)
  });
}

void loop()
{
  M5.update();

  // A/B/C Buttons
  //
  if (M5.BtnA.wasPressed() || M5.BtnA.isPressed())
  {
  };

  if (M5.BtnC.wasPressed() || M5.BtnC.isPressed())
  {
  };

  if (M5.BtnB.wasPressed())
  {
    ez.settings.menu();
  };

  // FACE
  //
  if (digitalRead(KEYBOARD_INT) == LOW)
  {
    Wire.requestFrom(KEYBOARD_I2C_ADDR, 1); // request 1 byte from keyboard
    while (Wire.available())
    {
      uint8_t key_val = Wire.read(); // receive a byte as character
      String msg((char)key_val);

      switch ((char)key_val)
      {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        k32->mqtt->publish("k32/all/leds/mem", msg.c_str(), 1);
        msg += "k32/all/leds/mem " + msg;
        break;

      case '.':
        k32->mqtt->publish("k32/all/leds/stop", nullptr, 1);
        msg += "k32/all/leds/stop";
        break;
      case '=':
        k32->mqtt->publish("k32/all/leds/master/fadeout", nullptr, 1);
        msg += "k32/all/leds/master/fadeout";
        break;
      case '-':
        k32->mqtt->publish("k32/all/leds/master/less", nullptr, 1);
        msg += "k32/all/leds/master/less";
        break;
      case '+':
        k32->mqtt->publish("k32/all/leds/master/more", nullptr, 1);
        msg += "k32/all/leds/master/more";
        break;

      case 'A':
        k32->mqtt->publish("/event/btn1");
        msg += "/event/btn1";
        break;
      case 'M':
        k32->mqtt->publish("/event/btn2");
        msg += "/event/btn2";
        break;
      case '%':
        k32->mqtt->publish("/event/btn3");
        msg += "/event/btn3";
        break;
      case '/':
        k32->mqtt->publish("/event/btn4");
        msg += "/event/btn4";
        break;
      }
      LOG(msg);
      ez.msgBox("M5 MQTT", msg, "", false);
    }
  }
}

#include <Hexapod_lib.h>

Hexapod hexapod;
Gamepad pad;
String command;
int angle_rotz = 0, dlugosc_kroku = 70, ilosc_odcinkow = 25, liczba_krokow = 1, delay_micros = 13, moves_without_line = 12;
float pos[3];
bool if_rotate_left = true;
int z = 0, y = 0, x = 0;
int test;
// siema
void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    hexapod.Setup();
    pad.setup();
}

void loop()
{
    pad.Get_PS2Dat(pad.PS2buf);
    delay(100);
    switch (pad.PS2buf[tab_arrows_start])
    {
    case up:
        // hexapod.walk(angle_rotz, dlugosc_kroku, ilosc_odcinkow, liczba_krokow, delay_micros, moves_without_line, true);
        // delay(1000);
        Serial.println("up");
        break;

    case down:
        Serial.println("down");
        break;

    case left:
        // hexapod.walk(-90, dlugosc_kroku, ilosc_odcinkow, liczba_krokow, delay_micros, moves_without_line, false);
        // delay(1000);
        Serial.println("left");
        break;

    case right:
        Serial.println("right");
        break;

    case start:
        Serial.println("start");
        break;

    default:
        // Serial.println("tab_arrows_start deafult");
        break;
    }
    switch (pad.PS2buf[tab_buttons_triggers])
    {
    case cross:
        Serial.println("cross");
        break;

    case circle:
        Serial.println("circle");
        break;

    case square:
        Serial.println("square");
        break;

    case triangle:
        Serial.println("triangle");
        break;
    default:
        // Serial.println("tab_buttons_triggers deafult");
        break;
    }
}
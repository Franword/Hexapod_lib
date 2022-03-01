#include <Hexapod_lib.h>

Hexapod hexapod;
Gamepad pad;
String command;
int angle_rotz = 0, dlugosc_kroku = 70, ilosc_odcinkow = 25, liczba_krokow = 1, delay_micros = 13, moves_without_line = 12;
float pos[3];
bool if_rotate_left = true;
int z = 0, y = 0, x = 0;
bool enable = true;
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
        if (enable == true)
        {
            hexapod.walk(angle_rotz, dlugosc_kroku, ilosc_odcinkow, liczba_krokow, delay_micros, moves_without_line, true);
            Serial.println("up");
        }
        enable = false;
        break;

    case down:
        if (enable == true)
        {
            hexapod.walk(angle_rotz + 180, dlugosc_kroku, ilosc_odcinkow, liczba_krokow, delay_micros, moves_without_line, true);
            Serial.println("down");
        }
        enable = false;
        break;

    case left:

        if (enable == true)
        {
            hexapod.walk(-90, dlugosc_kroku, ilosc_odcinkow, liczba_krokow, delay_micros, moves_without_line, false);
            Serial.println("left");
        }
        enable = false;
        break;

    case right:
        if (enable == true)
        {
            hexapod.walk(90, dlugosc_kroku, ilosc_odcinkow, liczba_krokow, delay_micros, moves_without_line, false);
            Serial.println("right");
        }
        enable = false;
        break;

    case start:
        Serial.println("start");
        enable = true;
        break;

    default:
        // Serial.println("tab_arrows_start deafult");
        break;
    }
    switch (pad.PS2buf[tab_buttons_triggers])
    {
    case cross:
        if (enable == true)
        {
            Serial.println("cross");
        }
        enable = false;
        break;

    case circle:
        if (enable == true)
        {
            Serial.println("circle");
        }
        enable = false;
        break;

    case square:
        if (enable == true)
        {
            Serial.println("square");
        }
        enable = false;
        break;

    case triangle:
        if (enable == true)
        {
            Serial.println("triangle");
        }
        enable = false;
        break;
    default:
        // Serial.println("tab_buttons_triggers deafult");
        break;
    }
}
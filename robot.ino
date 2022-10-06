#include <Servo.h>

// Constants
const int TRIG = 10;
const int ECHO = 9;

// Fields
Servo myservo;
int pos = 0;
int tienL = 5;
int tienR = 7;
int luiL = 6;
int luiR = 4;

// Declare
void dithang();
void disangtrai(int goc);
void disangphai(int goc);
void diluitrai(int goc);
void diluiphai(int goc);
void dilui();
void diquaydau();
void dunglai();
int dokhoangcach();

/// @brief Main.
void setup()
{
    // init
    myservo.attach(3);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(tienR, OUTPUT);
    pinMode(tienL, OUTPUT);
    pinMode(luiL, OUTPUT);
    pinMode(luiR, OUTPUT);
    digitalWrite(tienR, LOW);
    digitalWrite(tienL, LOW);
    digitalWrite(luiL, LOW);
    digitalWrite(luiR, LOW);
    myservo.write(90);
    delay(1000);
    int kcmaxt = 0;
    int kcmidt = 0;
    // run
    while (1)
    {
        int i;
        int gd;
        int kc;
        int gdmax = 0;
        int gdmid = 0;
        int gdmin = 0;
        int kcmax = 0;
        int kc90 = 500;
        int kc810[21];
        // scan
        for (gd = 90; gd >= 15; gd--)
        {
            myservo.write(gd);
            delay(10);
        }
        // re-scan
        for (gd = 15; gd <= 165; gd++)
        {
            myservo.write(gd);
            delay(10);
            kc = dokhoangcach();
            // check sort
            if (kc < 10)
            {
                gdmin = gd;
            }
            else if (kc < 30)
            {
                gdmid = gd;
            }
            else if (kc > kcmax)
            {
                kcmax = kc;
                gdmax = gd;
            }
            // check front
            if (gd >= 80 && gd <= 100)
            {
                kc810[gd - 80] = dokhoangcach();
                if (kc810[gd - 80] == 0)
                {
                    kc810[gd - 80] = 500;
                }
                else if (kc810[gd - 80] < kc90)
                {
                    kc90 = kc810[gd - 80];
                }
            }
        }
        // check right
        for (gd = 165; gd >= 90; gd--)
        {
            myservo.write(gd);
            delay(10);
        }
        // move straight
        while (kc90 > 50 && gdmid < 15 && gdmin < 15)
        {
            // check go/back
            if (kc90 == kcmidt)
            {
                dilui();
            }
            else
            {
                dithang();
                kc90 = dokhoangcach();
            }
        }
        dunglai();
        // check move turn
        if (gdmin == 0)
        {
            // check dead end
            if (gdmid == 0)
            {
                // check go-turn
                if (gdmax < 80)
                {
                    disangphai(gdmax);
                }
                else
                {
                    disangtrai(gdmax);
                }
            }
            else if (gdmid < 80)
            {
                // check go-turn left
                if (gdmax < 80)
                {
                    diquaydau();
                }
                else
                {
                    disangtrai(gdmax);
                }
            }
            else if (gdmid > 100)
            {
                // check go-turn right
                if (gdmax < 80)
                {
                    disangphai(gdmax);
                }
                else
                {
                    diquaydau();
                }
            }
            else if (gdmax < 80)
            {
                disangphai(gdmax);
            }
            else if (gdmax > 100)
            {
                disangtrai(gdmax);
            }
            else
            {
                diquaydau();
            }
        }
        else
        {
            if (gdmin < 80)
            {
                diluiphai(gdmin);
            }
            else if (gdmin > 100)
            {
                diluitrai(gdmin);
            }
            else
            {
                dilui();
            }
        }
        i = kcmax / 10;
        if (i == kcmaxt)
        {
            dilui();
        }
        else
        {
            kcmaxt = i;
        }
    }
}

/// @brief Loop.
void loop()
{
}

/// @brief Go on.
void dithang()
{
    digitalWrite(tienR, HIGH);
    digitalWrite(tienL, HIGH);
    analogWrite(tienL, 230);
}

/// @brief Go left.
/// @param goc Angle.
void disangtrai(int goc)
{
    int temp = abs(goc - 90) * 3;
    digitalWrite(tienL, HIGH);
    delay(temp);
    digitalWrite(tienL, LOW);
}

/// @brief Go right.
/// @param goc Angle.
void disangphai(int goc)
{
    int temp = abs(goc - 90) * 3;
    digitalWrite(tienR, HIGH);
    delay(temp);
    digitalWrite(tienR, LOW);
}

/// @brief Back left.
/// @param goc Angle.
void diluitrai(int goc)
{
    int temp = abs(goc - 90) * 5;
    digitalWrite(luiL, HIGH);
    delay(temp);
    digitalWrite(luiL, LOW);
}

/// @brief Back right.
/// @param goc Angle.
void diluiphai(int goc)
{
    int temp = abs(goc - 90) * 5;
    digitalWrite(luiR, HIGH);
    delay(temp);
    digitalWrite(luiR, LOW);
}

/// @brief Back.
void dilui()
{
    digitalWrite(luiL, HIGH);
    digitalWrite(luiR, HIGH);
    delay(500);
    digitalWrite(luiL, LOW);
    digitalWrite(luiR, LOW);
}

/// @brief Turning.
void diquaydau()
{
    digitalWrite(tienR, HIGH);
    digitalWrite(luiR, HIGH);
    delay(300);
    digitalWrite(tienR, LOW);
    digitalWrite(luiR, LOW);
}

/// @brief Stop.
void dunglai()
{
    digitalWrite(tienR, LOW);
    digitalWrite(tienL, LOW);
    digitalWrite(luiL, LOW);
    digitalWrite(luiR, LOW);
}

/// @brief Measure distance.
/// @return Distance.
int dokhoangcach()
{
    int kc;
    long tg;
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    tg = pulseIn(ECHO, HIGH, 3600000);
    kc = int(tg / 2 / 29.412);
    return kc;
}
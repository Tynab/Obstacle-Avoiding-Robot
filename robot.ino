#include <Servo.h>

Servo myservo;
int pos = 0;
const int trig = 10;
const int echo = 9;
int tien1 = 7;
int tien2 = 5;
int lui1 = 6;
int lui2 = 4;

void dithang();
void disangtrai(int goc);
void disangphai(int goc);
void diluitrai(int goc);
void diluiphai(int goc);
void dilui();
void diquaydau();
void dunglai();
int dokhoangcach();

void setup()
{
    myservo.attach(3);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(tien1, OUTPUT);
    pinMode(tien2, OUTPUT);
    pinMode(lui1, OUTPUT);
    pinMode(lui2, OUTPUT);
    digitalWrite(tien1, LOW);
    digitalWrite(tien2, LOW);
    digitalWrite(lui1, LOW);
    digitalWrite(lui2, LOW);
    myservo.write(90);
    delay(1000);
    int kcmaxt = 0, kcmidt = 0;
    while (1)
    {
        int khoangcach, gd, i, gdmax = 0, gdmid = 0, gdmin = 0, kcmax = 0, kc810[21], kc90 = 500;
        for (gd = 90; gd >= 15; gd--)
        {
            myservo.write(gd);
            delay(10);
        }
        for (gd = 15; gd <= 165; gd++)
        {
            myservo.write(gd);
            delay(10);
            khoangcach = dokhoangcach();
            if (khoangcach < 10)
                gdmin = gd;
            else
            {
                if (khoangcach < 30)
                    gdmid = gd;
                else
                {
                    if (khoangcach > kcmax)
                    {
                        kcmax = khoangcach;
                        gdmax = gd;
                    }
                }
            }
            if (gd >= 80 && gd <= 100)
            {
                kc810[gd - 80] = dokhoangcach();
                if (kc810[gd - 80] == 0)
                    kc810[gd - 80] = 500;
                else
                {
                    if (kc810[gd - 80] < kc90)
                        kc90 = kc810[gd - 80];
                }
            }
        }
        for (gd = 165; gd >= 90; gd--)
        {
            myservo.write(gd);
            delay(10);
        }
        while (kc90 > 50 && gdmid < 15 && gdmin < 15)
        {
            if (kc90 == kcmidt)
                dilui();
            else
            {
                dithang();
                kc90 = dokhoangcach();
            }
        }
        dunglai();
        if (gdmin == 0)
        {
            if (gdmid == 0)
            {
                if (gdmax < 80)
                    disangphai(gdmax);
                else
                    disangtrai(gdmax);
            }
            else
            {
                if (gdmid < 80)
                {
                    if (gdmax < 80)
                        diquaydau();
                    else
                        disangtrai(gdmax);
                }
                else
                {
                    if (gdmid > 100)
                    {
                        if (gdmax < 80)
                            disangphai(gdmax);
                        else
                            diquaydau();
                    }
                    else
                    {
                        if (gdmax < 80)
                            disangphai(gdmax);
                        else
                        {
                            if (gdmax > 100)
                                disangtrai(gdmax);
                            else
                                diquaydau();
                        }
                    }
                }
            }
        }
        else
        {
            if (gdmin < 80)
                diluiphai(gdmin);
            else
            {
                if (gdmin > 100)
                    diluitrai(gdmin);
                else
                    dilui();
            }
        }
        i = kcmax / 10;
        if (i == kcmaxt)
            dilui();
        else
            kcmaxt = i;
    }
}

void loop()
{
}

void dithang()
{
    digitalWrite(tien1, HIGH);
    digitalWrite(tien2, HIGH);
    analogWrite(tien2, 230);
}

void disangtrai(int goc)
{
    int temp = abs(goc - 90) * 3;
    digitalWrite(tien2, HIGH);
    delay(temp);
    digitalWrite(tien2, LOW);
}

void disangphai(int goc)
{
    int temp = abs(goc - 90) * 3;
    digitalWrite(tien1, HIGH);
    delay(temp);
    digitalWrite(tien1, LOW);
}

void diluitrai(int goc)
{
    int temp = abs(goc - 90) * 5;
    digitalWrite(lui1, HIGH);
    delay(temp);
    digitalWrite(lui1, LOW);
}

void diluiphai(int goc)
{
    int temp = abs(goc - 90) * 5;
    digitalWrite(lui2, HIGH);
    delay(temp);
    digitalWrite(lui2, LOW);
}

void dilui()
{
    digitalWrite(lui1, HIGH);
    digitalWrite(lui2, HIGH);
    delay(500);
    digitalWrite(lui1, LOW);
    digitalWrite(lui2, LOW);
}

void diquaydau()
{
    digitalWrite(tien1, HIGH);
    digitalWrite(lui2, HIGH);
    delay(300);
    digitalWrite(tien1, LOW);
    digitalWrite(lui2, LOW);
}

void dunglai()
{
    digitalWrite(tien1, LOW);
    digitalWrite(tien2, LOW);
    digitalWrite(lui1, LOW);
    digitalWrite(lui2, LOW);
}

int dokhoangcach()
{
    long tg;
    int kc;
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    tg = pulseIn(echo, HIGH, 3600000);
    kc = int(tg / 2 / 29.412);
    return kc;
}
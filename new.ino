#include <WiFi.h>
#include <Servo.h>

WiFiClient client;
WiFiServer server(80);

Servo myServo;

int ledPins[] = {13, 33, 32, 25, 26, 27, 14, 12};

void breathingEffect()
{
    for (int brightness = 0; brightness <= 255; brightness++)
    {
        for (int i = 0; i < 8; i++)
        {
            analogWrite(ledPins[i], brightness);
        }
        delay(5);
    }
    delay(500);

    for (int brightness = 255; brightness >= 0; brightness--)
    {
        for (int i = 0; i < 8; i++)
        {
            analogWrite(ledPins[i], brightness);
        }
        delay(5);
    }
    delay(500);
}

void randomFlickerEffect()
{
    for (int i = 0; i < 8; i++)
    {
        int flicker = random(50, 255);
        analogWrite(ledPins[i], flicker);
        delay(random(10, 50));
    }
}

void chaseEffect()
{
    for (int i = 0; i < 8; i++)
    {
        analogWrite(ledPins[i], 255);
        delay(50);
        analogWrite(ledPins[i], 0);
    }
    delay(200);
}

void randomFlashingEffect()
{
    for (int i = 0; i < 8; i++)
    {
        int flash = random(0, 2);
        if (flash == 0)
        {
            analogWrite(ledPins[i], LOW);
        }
        else
        {
            analogWrite(ledPins[i], HIGH);
        }
        delay(random(50, 100));
    }
}

void quickSequentialEffect()
{
    for (int i = 0; i < 8; i++)
    {
        analogWrite(ledPins[i], 255);
        delay(random(10, 30));
        analogWrite(ledPins[i], 0);
    }
    delay(100);
}

void fastBlinkEffect()
{
    for (int i = 0; i < 8; i++)
    {
        int color = random(0, 3);
        if (color == 0)
        {
            analogWrite(ledPins[i], random(50, 255));
        }
        else if (color == 1)
        {
            analogWrite(ledPins[i], random(50, 255));
        }
        else
        {
            analogWrite(ledPins[i], random(50, 255));
        }
        delay(random(10, 50));
        analogWrite(ledPins[i], 0);
        delay(random(10, 50));
    }
}

void colorShiftEffect()
{
    for (int i = 0; i < 8; i++)
    {
        int color = random(0, 3);
        if (color == 0)
        {
            analogWrite(ledPins[i], random(50, 255));
        }
        else if (color == 1)
        {
            analogWrite(ledPins[i], random(50, 255));
        }
        else
        {
            analogWrite(ledPins[i], random(50, 255));
        }
    }
    delay(100);
}

void setup()
{
    Serial.begin(9600);

    const char *ssid = "ESP32_AP";
    const char *password = "12345678";
    WiFi.softAP(ssid, password);

    Serial.println("Access Point started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    server.begin();

    for (int i = 0; i < 8; i++)
    {
        pinMode(ledPins[i], OUTPUT);
    }
    myServo.attach(18);
    myServo.write(100);
    delay(100);
}

void loop()
{
    client = server.available();
    if (client)
    {
        String request = client.readStringUntil('\n');
        Serial.println(request);
        request.trim();
        Serial.println(request);

        if (request == "GET /forward HTTP/1.1")
        {
            for (int angle = 100; angle >= 0; angle--)
            {
                myServo.write(angle);
                delay(15);
            }
        }
        if (request == "GET /reverse HTTP/1.1")
        {
            for (int angle = 0; angle <= 100; angle++)
            {
                myServo.write(angle);
                delay(15);
            }
        }
    }
    breathingEffect();
    randomFlickerEffect();
    chaseEffect();
    randomFlashingEffect();
    quickSequentialEffect();
    fastBlinkEffect();
    colorShiftEffect();
}
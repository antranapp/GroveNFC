#include "NFCClient.h"
#include "Grove_LCD_RGB_Backlight.h"

STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));

rgb_lcd lcd;

void callback(String tag);

NFCClientReadMessageHandler* readMessageHandler = callback;
NFCClient nfcClient(readMessageHandler);

void setup(void) {
    Serial.begin(9600);

    lcd.begin(16, 2);
    lcd.setRGB(100, 100, 100);
    lcd.print("hello, world!");

    nfcClient.start();
}

void loop(void) {
}

void callback(String tag) {
    lcd.setCursor(0,1);
    lcd.print(tag);
}

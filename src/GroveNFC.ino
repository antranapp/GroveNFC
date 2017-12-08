#include "PN532_I2C.h"
#include "PN532.h"
#include "NfcAdapter.h"
#include "Grove_LCD_RGB_Backlight.h"

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

rgb_lcd lcd;

void setup(void) {
    Serial.begin(115200);
    Serial.println("NDEF Reader");
    nfc.begin();

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    // Set up background backlight color
    lcd.setRGB(100, 100, 100);

    lcd.print("hello, world!");
}

void loop(void) {
    Serial.println("\nScan a NFC tag\n");
    if (nfc.tagPresent())
    {
        NfcTag tag = nfc.read();
        Serial.println("*** FOUND TAG ***");
        tag.print();
        lcd.setCursor(0,1);
        lcd.print(tag.getUidString());
    }
    delay(1000);
}

#include <Catalen.h>

#define APP_NAME    "Corpsewood Haunt Forest"
#define APP_VERSION "0.1"

#define ARDUINO_RX      10
#define ARDUINO_TX      11
#define PLAYLIST_LEN    3

Catalex player();

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        // Wait for hardware serial to become available
    }
    Serial.println("Starting Catalex module");
    // I don't know exactly how long it takes the Catalex hardware module to 
    // power up and become responsive over UART, so give it half a second (a lifetime
    // in uC years!) to sort itself out
    delay(500); // ms
    player.init(PLAYLIST_LEN, ARDUINO_RX, ARDUINO_TX);
    while (!player.ready()) {
        // Wait for acknowledgement that hardware module is ready
    }
    Serial.println(String(APP_NAME + ", " + APP_VERSION + " initialised"));
}

void loop() {
  // put your main code here, to run repeatedly:
}

void playClip()
{
    noInterrupts();
    if (player.ready()) {
        Serial.println("Playing audio sample");
        player.playRandom();
    } else {
        Serial.println("Error, Catalex player not ready");
    }
    interrupts();
}

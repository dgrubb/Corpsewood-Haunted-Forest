#include <Catalex.h>

#define APP_NAME    "Corpsewood Haunt Forest"
#define APP_VERSION "0.1"

#define CATALEX_ARDUINO_RX      5
#define CATALEX_ARDUINO_TX      6
#define CATALEX_PLAYLIST_LEN    5
#define CATALEX_INTERRUPT_PIN   2

#define DELAY_TIME              100 // ms

Catalex player;

typedef struct {
    uint8_t input;
    uint8_t output;
    uint8_t timeout; // in increments of 100ms. E.g., for 1 second, timeout = 10
    uint8_t count;
} pin_map_t;

pin_map_t IO_MAP[] = {
    { A0, 8,  10, 0},
    { A1, 9,  10, 0},
    { A2, 10, 10, 0},
    { A3, 11, 10, 0},
    {NULL, NULL, NULL}
};

void setup()
{
    int i;

    Serial.begin(9600);
    while (!Serial) {
        // Wait for hardware serial to become available
    }

    // Initialise I/O pin mapping
    Serial.println("Mapping I/O");
    i = 0;
    while (NULL != IO_MAP[i].input) {
        pinMode(IO_MAP[i].input, INPUT);
        pinMode(IO_MAP[i].output, OUTPUT);
        i++;
    }

    // Startup Catalex module
    Serial.println("Starting Catalex module");
    // I don't know exactly how long it takes the Catalex hardware module to 
    // power up and become responsive over UART, so give it half a second (a lifetime
    // in uC years!) to sort itself out
    delay(500); // ms
    player.init(CATALEX_PLAYLIST_LEN, CATALEX_ARDUINO_RX, CATALEX_ARDUINO_TX);
    while (!player.ready()) {
        // Wait for acknowledgement that hardware module is ready
    }
    // Attach an interrupt to trigger playback
    attachInterrupt(digitalPinToInterrupt(CATALEX_INTERRUPT_PIN), playClip, RISING);

    // Fin.
    Serial.println(String(APP_NAME) + ", " + APP_VERSION + " initialised");
}

void loop()
{
    readInputs();
    delay(DELAY_TIME);
    updateOutputs();
}

void readInputs()
{
    int i = 0;
    while (NULL != IO_MAP[i].input) {
        // If a timeout delay has been set then it doesn't matter what
        // state the relevant input pin is in, we can ignore it
        if (0 == IO_MAP[i].count) {
            if (digitalRead(IO_MAP[i].input)) {
                IO_MAP[i].count = IO_MAP[i].timeout;
                digitalWrite(IO_MAP[i].output, HIGH);
                Serial.println(String("Setting HIGH, pin: ") + IO_MAP[i].output);
            }
        }
        i++;
    }
}

void updateOutputs()
{
    int i = 0;
    int val = 0;
    while (NULL != IO_MAP[i].input) {
        if (1 == IO_MAP[i].count) {
            digitalWrite(IO_MAP[i].output, LOW);
        }
        if (0 != IO_MAP[i].count) {
            IO_MAP[i].count--;
        }
        i++;
    }
}

void playClip()
{
    noInterrupts();
    if (player.ready()) {
        Serial.println("Playing audio sample");
        //player.playRandom();
        player.play(1);
    } else {
        Serial.println("Error, Catalex player not ready");
    }
    interrupts();
}

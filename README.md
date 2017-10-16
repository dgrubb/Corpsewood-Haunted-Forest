# Corpsewood-Haunted-Forest

Arduino code for controlling props in a Halloween haunted forest display.

[Wolfe City Productions, LLC.](http://wolfecityproductions.com/corpsewood-haunted-forest)

The two main requirements for this project are:

1) That a PIR sensor can trigger playback of an audio sample on an mp3 playback device.
2) That a PIR sensor can trigger a mechnical relay to actuate a pneumatic device for a specified amount of time.

## Hardware

* Arduino Uno
* [Catalex YX5300 .mp3 player board](https://www.amazon.com/dp/B01JCI23JG/ref=asc_df_B01JCI23JG5203321/)
* [GEREE 4 relay module board](https://www.amazon.com/dp/B00PU1EUMI?psc=1)

## Implementation

1) On detection of a rising edge on a selected pin (PIR output) a command is sent via UART to the Catalex mp3 player board instructing it to play a randomly indexed audio clip.
2) On detection of a rising edge on a selected pin (PIR output) a digital output pin is set high and maintained until after a set timeout.

## Pin mapping:

Catalex module:
* Pin 2 [I]: Triggers an interrupt on rising edge which starts mp3 playback.
* Pin 5 [I]: Software serial RX pin (Arduino-side), connected to Catalex module's TX pin.
* Pin 6 [O]: Software serial TX pin (Arduino-side), connected to Catalex module's RX pin.

Digital pass-through:
* Pin A0 [I]: Drives pin 8 HIGH for set time after rising edge.
* Pin A1 [I]: Drives pin 9 HIGH for set time after rising edge.
* Pin A2 [I]: Drives pin 10 HIGH for set time after rising edge.
* Pin A3 [I]: Drives pin 11 HIGH for set time after rising edge.

* Pin 8 [O]: Goes HIGH for set time after rising edge on A0.
* Pin 9 [O]: Goes HIGH for set time after rising edge on A1.
* Pin 10 [O]: Goes HIGH for set time after rising edge on A2.
* Pin 11 [O]: Goes HIGH for set time after rising edge on A3.


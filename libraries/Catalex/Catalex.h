
#ifndef _CATALEX_H
#define _CATALEX_H

#include <SoftwareSerial.h>

class Catalex
{
    const max_volume = 0x30; // 100%
    const min_volume = 0x00; // 0%
    const sd_card_device = 0x0002;
    const default_device = sd_card_device;
    const default_volume = max_volume; // This goes all the way to 11
    public:
        namespace Cmd {
            const uint8_t next_song         = 0x01;
            const uint8_t prev_song         = 0x02;
            const uint8_t play_index        = 0x03;
            const uint8_t volume_up         = 0x04;
            const uint8_t volume_down       = 0x05;
            const uint8_t set_volume        = 0x06;
            const uint8_t single_cycle_play = 0x08;
            const uint8_t select_device     = 0x09;
            const uint8_t sleep_mode        = 0x0A;
            const uint8_t wake_up           = 0x0B;
            const uint8_t reset             = 0x0C;
            const uint8_t play              = 0x0D;
            const uint8_t pause             = 0x0E;
            const uint8_t play_folder       = 0x0F;
            const uint8_t stop              = 0x16;
            const uint8_t folder_cycle      = 0x17;
            const uint8_t shuffle_play      = 0x18;
            const uint8_t set_single_cycle  = 0x19;
            const uint8_t play_with_volume  = 0x22;
        }
        Catalex(uint16_t playlist_length, uint8_t rx, uint8_t tx);
        ~Catalex();
        bool play(uint16_t index);
        bool playRandom();
        bool setVolume(uint16_t volume);
    private:
        uint8_t m_rx;
        uint8_t m_tx;
        uint16_t m_volume;
        uint16_t m_device;
        uint16_t m_playlist_length;
        SoftwareSerial m_serial;
        bool selectDevice(uint16_t device);
        void sendCommand(const uint8_t command, uint16_t data);
};

#endif /* _CATALEX_H */


#ifndef _CATALEX_H
#define _CATALEX_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class Catalex
{
    public:
        const uint16_t max_volume = 0x0030; // 100%
        const uint16_t min_volume = 0x0000; // 0%
        const uint16_t sd_card_device = 0x0002;
        const uint16_t default_device = sd_card_device;
        const uint16_t default_volume = max_volume; // This goes all the way to 11

    class Cmd
    {
	public:
		static const uint8_t cmd_next_song         = 0x01;
		static const uint8_t cmd_prev_song         = 0x02;
		static const uint8_t cmd_play_index        = 0x03;
		static const uint8_t cmd_volume_up         = 0x04;
		static const uint8_t cmd_volume_down       = 0x05;
		static const uint8_t cmd_set_volume        = 0x06;
		static const uint8_t cmd_single_cycle_play = 0x08;
		static const uint8_t cmd_select_device     = 0x09;
		static const uint8_t cmd_sleep_mode        = 0x0A;
		static const uint8_t cmd_wake_up           = 0x0B;
		static const uint8_t cmd_reset             = 0x0C;
		static const uint8_t cmd_play              = 0x0D;
		static const uint8_t cmd_pause             = 0x0E;
		static const uint8_t cmd_play_folder       = 0x0F;
		static const uint8_t cmd_stop              = 0x16;
		static const uint8_t cmd_folder_cycle      = 0x17;
		static const uint8_t cmd_shuffle_play      = 0x18;
		static const uint8_t cmd_set_single_cycle  = 0x19;
		static const uint8_t cmd_play_with_volume  = 0x22;
    };

        Catalex(uint16_t playlist_length, uint8_t rx, uint8_t tx);
        Catalex();
        ~Catalex();
        bool init(uint16_t playlist_length, uint8_t rx, uint8_t tx);
        bool ready();
        bool play(uint16_t index);
        bool playRandom();
        bool setVolume(uint16_t volume);
    private:
        bool m_isInited;
        uint8_t m_rx;
        uint8_t m_tx;
        uint16_t m_volume;
        uint16_t m_device;
        uint16_t m_playlist_length;
        SoftwareSerial *m_serial;
        bool selectDevice(uint16_t device);
        void sendCommand(const uint8_t command, uint16_t data);
};

#endif /* _CATALEX_H */

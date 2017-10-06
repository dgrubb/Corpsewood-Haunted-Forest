#include "Catalex.h"

Catalex::Catalex(uint16_t playlist_length, uint8_t rx, uint8_t tx)
{
    randomSeed(analogRead(0));
    m_rx = rx;
    m_tx = tx;
    m_playlist_length = playlist_length;
    m_serial = SoftwareSerial(m_rx, m_tx);
    m_volume = default_volume;
    m_device = default_device;
    selectDevice(m_device);
    setVolume(m_volume);
}

Catalex::~Catalex()
{
    delete m_serial;
}

bool Catalex::play(uint16_t index)
{
    if (index < 0 || index > m_playlist_length) {
        return false;
    }
    sendCommand(Cmd::play_index, index);
    return true;
}

bool Catalex::playRandom()
{
    return play((uint16_t)random(0, m_playlist_length));
}

bool Catalex::setVolume(uint16_t volume)
{
    if (volume < min_volume) {
        m_volume = min_volume;
    } else if (volume > max_volume) {
        m_volume = max_volume;
    } else {
        m_volume = volume;
    }
    sendCommand(Cmd::set_volume, m_volume);
    return true;
}

bool Catalex::selectDevice(uint16_t device)
{
    // Catalex module only supports SD card as source device
    if (device != default_device) {
        return false;
    }
    m_device = device;
    sendCommand(Cmd::select_device, m_device);
    return true;
}

void Catalex::sendCommand(const uint8_t command, uint16_t data)
{
    delay(20);
    // Serial MP3 Player v1.0, page 5:
    // Command format:
    // 0x7F, fixed command prefix
    // 0xFF, version
    // 0xXX, command length (without starting and ending byte)
    // 0xXX, command (e.g., play, stop etc)
    // 0xXX, enable feedback
    // 0xXX, first data byte
    // 0xXX, second data byte
    // 0xEF, fixed command suffix
    uint8_t buf[8] = {0x7E, 0xFF, 0x06, 0x00, 0x00, 0x00, 0xEF};
    buf[3] = command;
    buf[4] = (uint8_t)(data >> 8);
    buf[5] = (uint8_t)(data);
    for (uint8_t i=0; i<8; i++) {
        m_serial.write(buf[i]);
    }
}


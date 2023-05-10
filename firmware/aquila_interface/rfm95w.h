/* Daniel Ciesla
LoRa rfm95w  chip
*/

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#define lora_frequency 868E6
#define packet_size 16
#define lora_cs 4
class RFM95W{
    public:
    bool lora_setup();
    int* lora_receive();
    void lora_transmit();
    int* lora_update();
    void lora_quality();
    uint8_t register_read();
    void register_write();
    uint8_t singleTransfer();
}

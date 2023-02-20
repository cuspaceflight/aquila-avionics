/* Daniel Ciesla
LoRa rfm95w  chip
*/

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#define lora_frequency 868E6
#define lora_packet_size 16

class RFM95W{
    public:
    void lora_setup();
    int* lora_receive();
    void lora_transmit();
    int* lora_update();
    void lora_quality();
    private:
}

/* Daniel Ciesla
LoRa rfm95w chip
*/

#include <rfm95w.h>

bool lora_setup(){
    if (!LoRa.begin(lora_frequency)) {
        Serial.println("LoRa failed");
        return false;
    }
    else {
        LoRa.receive();
        Serial.println("LoRa Started");
        LoRa.setPins(ss, -1, dio0);

        return true;
    }
    
}

int* RFM95W::lora_receive(){
    int current_packet_size = LoRa.parsePacket();
    Serial.println(current_packet_size);
    if (current_packet_size > 0) { 
        if (current_packet_size != lora_packet_size){
            Serial.print(" Packet Wrong Size ");
        }
        static uint8_t lora_array[lora_packet_size];
        uint8_t current_byte;
        for (i=0, i<lora_packet_size, i++){
            if (LoRa.available()) {
                current_byte = LoRa.read();
                lora_array[i] = current_byte;
                Serial.print(current_byte);
            }
            else {
                lora_array[i]=0;
            }
        }
        return lora_array;
    }
}

void RFM95W::lora_transmit(uint8_t* lora_array){
    LoRa.beginPacket();
    for (i=0, i<lora_packet_size, i++){
        LoRa.write(lora_array[i]);
    }
    LoRa.endPacket();
    Lora.receive();
}

int* RFM95W::lora_update(uint8_t* lora_transmit_pointer){
    uint8_t* lora_receive_pointer;
    lora_receive_pointer = lora_receive();
    lora_transmit(lora_transmit_pointer);
    return lora_receive_pointer;
}

void lora_quality(){
    Serial.println("RSSI: ");
    Serial.print(LoRa.packetRssi());     
    Serial.print("   SNR: ");
    Serial.print(LoRa.packetSnr());
    Serial.print("   Freq Error:");
    Serial.print(LoRa.packetFrequencyError());
}
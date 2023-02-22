/* Daniel Ciesla
20/02/2023
LoRa rfm95w chip

This Class interacts with the rfm95w LoRa chip, transmitting and receiving an array of uint8_t.
Inputs and Outputs are pointers to such arrays.
*/

#include <rfm95w.h>

//Attempt activation of LoRa, return true if success, false is fail
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

//Receive data, output as pointer to array of uint8_ts
int* RFM95W::lora_receive(){
    int current_packet_size = LoRa.parsePacket();
    Serial.println(current_packet_size);
    if (current_packet_size > 0) { 
        if (current_packet_size != packet_size){
            Serial.print(" Packet Wrong Size ");
        }
        static uint8_t lora_array[packet_size];
        uint8_t current_byte;
        for (i=0, i<packet_size, i++){
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
    else{
        uint8_t * lora_array = NULL;
        return lora_array 
    }
}

//Transmit data in array pointed to by input
void RFM95W::lora_transmit(uint8_t* lora_array){
    if (lora_array){
        LoRa.beginPacket();
        for (i=0, i<packet_size, i++){
            LoRa.write(lora_array[i]);
        }
        LoRa.endPacket();
        Lora.receive();
    }
}

//Receive and Transmit
int* RFM95W::lora_update(uint8_t* data_out = NULL){
    uint8_t* data_in;
    data_in = lora_receive();
    lora_transmit(data_out);
    return data_in;
}

//Print various radio signal quality indicators (might convert to output later)
void lora_quality(){
    Serial.println("RSSI: ");
    Serial.print(LoRa.packetRssi());     
    Serial.print("   SNR: ");
    Serial.print(LoRa.packetSnr());
    Serial.print("   Freq Error:");
    Serial.print(LoRa.packetFrequencyError());
}
import serial
import serial.tools.list_ports

print(list(serial.tools.list_ports.comports())[0])

ser = serial.Serial('COM5', timeout=0.01)


print(ser.name)

while (True):
    read = ser.readline().decode().strip()
    if (read != ''):
        print(read)
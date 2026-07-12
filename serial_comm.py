import serial
import time

PORT = "COM9"      # Your Arduino port
BAUD = 9600

arduino = serial.Serial(PORT, BAUD)
time.sleep(2)

print("Connected to Arduino")


def send_command(command):

    print(f"Sending: {command}")

    arduino.write(command.encode())
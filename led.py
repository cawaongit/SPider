from gpiozero import LED
from time import sleep

redLed = LED(2)
yellowLed = LED(3)
greenLed = LED(4)

while True:
    greenLed.off()
    redLed.on()
    sleep(1)
    redLed.off()
    yellowLed.on()
    sleep(1)
    yellowLed.off()
    greenLed.on()
    sleep(1)
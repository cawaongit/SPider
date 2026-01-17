from gpiozero.pins.pigpio import PiGPIOFactory
from gpiozero import Device, DistanceSensor, Servo
from time import sleep

# Device.pin_factory = PiGPIOFactory()

sensor = DistanceSensor(echo=5, trigger=6)

while True:
    print('Distance: ', sensor.distance * 100)
    sleep(1)
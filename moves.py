from gpiozero import Servo
import evdev

servo = Servo(17, min_pulse_width=0.5/1000, max_pulse_width=2.5/1000)

devices = [evdev.InputDevice(path) for path in evdev.list_devices()]
for device in devices:
  print(device.path, device.name, device.phys)

device = evdev.InputDevice('/dev/input/event5')

print(device)

servo.value = 0

for event in device.read_loop():
  if event.type == evdev.ecodes.EV_KEY:
    print(evdev.categorize(event))
  if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_X:
    print("Up")
    servo.value = 1
  if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_A:
    print("Down")
    servo.value = -1
  if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_MODE:
    exit()

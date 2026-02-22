from gpiozero import Servo
import evdev

servo = Servo(2, min_pulse_width=0.5/1000, max_pulse_width=2.5/1000)

#
# 

# 
# 

# 
# 

# 
# 

devices = [evdev.InputDevice(path) for path in evdev.list_devices()]
for device in devices:
  print(device.path, device.name, device.phys)

device = evdev.InputDevice('/dev/input/event5')

print(device)

print("Base")
servo.value = None

while True:
  for event in device.read_loop():
    if event.type == evdev.ecodes.EV_KEY:
      # print(evdev.categorize(event))

      # Up
      if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_X and event.value == 1:
        print("Up")
        servo.value = 1
      elif event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_X and event.value == 0:
        print("Idle")
        servo.value = None


      # Left
      if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_Y and event.value == 1:
        print("Left")
        servo.value = -1
      elif event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_Y and event.value == 0:
        print("Idle")
        servo.value = None


      # Right
      if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_B and event.value == 1:
        print("Right")
        servo.value = 1
      elif event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_B and event.value == 0:
        print("Idle")
        servo.value = None


      # Down
      if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_A and event.value == 1:
        print("Down")
        servo.value = -1
      elif event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_A and event.value == 0:
        print("Idle")
        servo.value = None

      # Shutdown
      if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_MODE:
        exit()

    # try:
      # while True:
        # pass
    # except KeyboardInterrupt:
      # print("Tst")
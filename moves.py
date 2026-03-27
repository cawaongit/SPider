from gpiozero import Servo
import evdev

class moves:
  # Front left leg
  servo0 = Servo(2, min_pulse_width=0.5/1000, max_pulse_width=2.5/1000)
  servo1 = Servo(3, min_pulse_width=0.5/1000, max_pulse_width=2.5/1000)

  # Front right leg
  servo2 = Servo(14, min_pulse_width=0.5/1000, max_pulse_width=2.5/1000)
  servo3 = Servo(15, min_pulse_width=0.5/1000, max_pulse_width=2.5/1000)

  # Back left leg
  servo4 = Servo(19, min_pulse_width=0.5/1000, max_pulse_width=2.5/1000)
  servo5 = Servo(26, min_pulse_width=0.5/1000, max_pulse_width=2.5/1000)
  
  # Back right leg
  servo6 = Servo(20, min_pulse_width=0.5/1000, max_pulse_width=2.5/1000)
  servo7 = Servo(21, min_pulse_width=0.5/1000, max_pulse_width=2.5/1000)

  devices = [evdev.InputDevice(path) for path in evdev.list_devices()]
  for device in devices:
    print(device.path, device.name, device.phys)

  device = evdev.InputDevice('/dev/input/event8')

  print(device)
  print("Base")

  servo0.value = None
  servo1.value = None

  servo2.value = None
  servo3.value = None

  servo4.value = None
  servo5.value = None

  servo6.value = None
  servo7.value = None

  while True:
    for event in device.read_loop():
      if event.type == evdev.ecodes.EV_KEY:
        # print(evdev.categorize(event))

        # Up
        if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_X and event.value == 1:
          print("Up")

          servo0.value = 0.5
          servo1.value = 0.5

          servo2.value = 0.5
          servo3.value = 0.5

          servo4.value = 0.5
          servo5.value = 0.5

          servo6.value = 0.5
          servo7.value = 0.5

        elif event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_X and event.value == 0:
          print("Idle")

          servo0.value = None
          servo1.value = None

          servo2.value = None
          servo3.value = None

          servo4.value = None
          servo5.value = None

          servo6.value = None
          servo7.value = None


        # Left
        if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_Y and event.value == 1:
          print("Left")

          servo0.value = -1
          servo1.value = -1

          servo2.value = -1
          servo3.value = -1

          servo4.value = -1
          servo5.value = -1

          servo6.value = -1
          servo7.value = -1

        elif event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_Y and event.value == 0:
          print("Idle")

          servo0.value = None
          servo1.value = None

          servo2.value = None
          servo3.value = None

          servo4.value = None
          servo5.value = None

          servo6.value = None
          servo7.value = None


        # Right
        if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_B and event.value == 1:
          print("Right")

          servo0.value = 1
          servo1.value = 1

          servo2.value = -1
          servo3.value = -1

          servo4.value = -1
          servo5.value = -1

          servo6.value = -1
          servo7.value = -1

        elif event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_B and event.value == 0:
          print("Idle")

          servo0.value = None
          servo1.value = None

          servo2.value = None
          servo3.value = None

          servo4.value = None
          servo5.value = None

          servo6.value = None
          servo7.value = None


        # Down
        if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_A and event.value == 1:
          print("Down")

          servo0.value = -1
          servo1.value = -1

          servo2.value = -1
          servo3.value = -1

          servo4.value = -1
          servo5.value = -1

          servo6.value = -1
          servo7.value = -1

        elif event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_A and event.value == 0:
          print("Idle")

          servo0.value = None
          servo1.value = None

          servo2.value = None
          servo3.value = None

          servo4.value = None
          servo5.value = None

          servo6.value = None
          servo7.value = None


          # Shutdown
        if event.type == evdev.ecodes.EV_KEY and event.code == evdev.ecodes.BTN_MODE:
          exit()

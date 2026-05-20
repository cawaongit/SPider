# Controller MAC address -> A4:53:85:B5:BD:85
# bluetoothctl pair A4:53:85:B5:BD:85
# bluetoothctl connect A4:53:85:B5:BD:85
cd build/
cmake .. && make && ./SPider /dev/input/event5

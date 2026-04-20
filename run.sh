# bluetoothctl pair A4:53:85:B5:BD:85
# bluetoothctl connect A4:53:85:B5:BD:85
# delay 5
cd build
cmake .. && make && ./spider /dev/input/event5

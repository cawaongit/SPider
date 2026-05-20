# OpenCV
sudo apt install libopencv-dev


# WiringPi
# sudo apt install git
# git clone https://github.com/WiringPi/WiringPi.git
# cd WiringPi

# build the package
# ./build debian
# mv debian-template/wiringpi_3.18_arm64.deb .

# install it
# sudo apt install ./wiringpi_3.18_arm64.deb

# remove repo
# cd ..
# rm -rf WiringPi/

sudo apt install wiringpi

# pca9685
git clone https://github.com/Reinbert/pca9685.git
cd pca9685/src

sudo make install

mv pca9685.o ../../lib/

cd ../../
rm -rf pca9685/

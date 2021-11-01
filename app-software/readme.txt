Компиляция для yocto poky-hardknott-25.0.2

. /opt/poky/3.3.2/environment-setup-cortexa5t2hf-vfp-poky-linux-gnueabi
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../common_modules/cmake_modules/oe-sdk_cross.cmake -DCMAKE_BUILD_TYPE=Debug ..
make

сборка на x86

mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=~/Qt5.14.0/5.14.0/gcc_64/lib/cmake/ ..
make

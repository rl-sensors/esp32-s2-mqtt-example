# ESP32-S2 MQTT

As of now (Nov 2021), the ESP32-__S2__ is not on PlatformIO and requires to download and use the latest toolchain (version 2.0).

For Arduino IDE it's described [here](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).

For platformIO, find the toolchain in the [JSON file](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json) from the __Installing using Boards Manager__ section.
Look for section `xtensa-esp32s2-elf-gcc` and download the toolchain for your platform.

Untar the file and copy the above JSON file inside and rename it to `package.json`.

Update the `platformio.ini` file to include:

    board_build.mcu = esp32s2
    platform_packages =
        toolchain-xtensa32s2@file:///home/bohm/install/xtensa-esp32s2-elf
        framework-arduinoespressif32@https://github.com/espressif/arduino-esp32.git#44c11981d2159565c551028f2498f65764607f74
        platformio/tool-esptoolpy @ ~1.30100

Basically, the toolchain-xtensa32s2 points to the dir with the downloaded toolchain.

The `framework-arduinoespressif32` section points to the github (the #44c11 is hash of version 2.0)
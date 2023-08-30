# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/josej/zephyrproject/modules/hal/espressif/components/bootloader/subproject"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/esp-idf/build/bootloader"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/esp-idf"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/esp-idf/tmp"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/esp-idf/src/EspIdfBootloader-stamp"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/esp-idf/src"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/esp-idf/src/EspIdfBootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/esp-idf/src/EspIdfBootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/esp-idf/src/EspIdfBootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()

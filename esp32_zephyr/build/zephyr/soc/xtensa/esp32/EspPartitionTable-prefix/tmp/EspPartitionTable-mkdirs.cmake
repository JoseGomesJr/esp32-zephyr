# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/josej/zephyrproject/modules/hal/espressif/components/partition_table"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/esp-idf/build"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/tmp"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/src/EspPartitionTable-stamp"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/src"
  "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/src/EspPartitionTable-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/src/EspPartitionTable-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/zephyr/soc/xtensa/esp32/EspPartitionTable-prefix/src/EspPartitionTable-stamp${cfgdir}") # cfgdir has leading slash
endif()

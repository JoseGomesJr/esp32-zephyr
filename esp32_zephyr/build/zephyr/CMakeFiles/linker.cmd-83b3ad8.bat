@echo off
cd /D C:\Users\josej\Documents\esp32-zephyr\esp32_zephyr\build\zephyr || (set FAIL_LINE=2& goto :ABORT)
C:\Users\josej\zephyr-sdk-0.16.0\xtensa-espressif_esp32_zephyr-elf\bin\xtensa-espressif_esp32_zephyr-elf-gcc.exe -x assembler-with-cpp -undef -MD -MF linker.cmd.dep -MT linker.cmd -D_LINKER -D_ASMLANGUAGE -imacros C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/zephyr/include/generated/autoconf.h -IC:/Users/josej/zephyrproject/zephyr/include -IC:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/zephyr/include/generated -IC:/Users/josej/zephyrproject/zephyr/soc/xtensa/esp32 -IC:/Users/josej/zephyrproject/zephyr/soc/xtensa/esp32/include -IC:/Users/josej/zephyrproject/zephyr/lib/libc/minimal/include -IC:/Users/josej/zephyrproject/zephyr/subsys/bluetooth -IC:/Users/josej/zephyrproject/zephyr/subsys/settings/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/include/bt -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/include/crypto -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../esp_shared/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../esp_shared/include/wifi -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../esp_shared/components/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/hal/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/hal/esp32/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/hal/platform_port/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_hw_support/include/soc -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_hw_support/port/esp32 -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_hw_support/port/esp32/private_include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_hw_support/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_common/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_pm/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_rom/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_rom/include/esp32/rom -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_rom/esp32/ld -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp32/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/soc/esp32/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/xtensa/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/xtensa/esp32/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/soc/include/soc -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/soc/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/soc/src/esp32/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/driver/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/driver/esp32/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_phy/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_phy/include/esp32 -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_phy/esp32/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_wifi/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/efuse/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/efuse/private_include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/efuse/esp32/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/efuse/esp32/private_include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_system/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_system/port/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_system/port/public_compat -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_wifi/esp32/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_timer/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_timer/private_include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_netif/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/esp_event/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/log/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/wpa_supplicant/esp_supplicant/src -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/wpa_supplicant/esp_supplicant/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/wpa_supplicant/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/wpa_supplicant/include/esp_supplicant -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/wpa_supplicant/port/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/wpa_supplicant/src -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/wpa_supplicant/src/crypto -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/wpa_supplicant/src/utils -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/wpa_supplicant/src/eap_peer -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/spi_flash/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/spi_flash/include/spi_flash -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/spi_flash/private_include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/bootloader_support/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/bootloader_support/include_bootloader -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/heap/include -IC:/Users/josej/zephyrproject/modules/hal/espressif/zephyr/esp32/../../components/mbedtls/port/include -IC:/Users/josej/zephyrproject/modules/crypto/tinycrypt/lib/include -D__GCC_LINKER_CMD__ -DLINKER_ZEPHYR_FINAL -E C:/Users/josej/zephyrproject/zephyr/soc/xtensa/esp32/linker.ld -P -o linker.cmd || (set FAIL_LINE=3& goto :ABORT)
"C:\Program Files\JetBrains\CLion 2022.1.3\bin\cmake\win\x64\bin\cmake.exe" -E cmake_transform_depfile Ninja gccdepfile C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr C:/Users/josej/zephyrproject/zephyr C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/zephyr C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/zephyr/linker.cmd.dep C:/Users/josej/Documents/esp32-zephyr/esp32_zephyr/build/CMakeFiles/d/c981d58c7efefca82d29783e0853dabf8dd98b80b944e9e1cfd33e41de151a06.d || (set FAIL_LINE=4& goto :ABORT)
goto :EOF

:ABORT
set ERROR_CODE=%ERRORLEVEL%
echo Batch file failed at line %FAIL_LINE% with errorcode %ERRORLEVEL%
exit /b %ERROR_CODE%
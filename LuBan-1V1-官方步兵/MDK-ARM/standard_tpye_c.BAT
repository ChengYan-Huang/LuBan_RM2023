SET PATH=D:\keil5\ARM\ARMCC\Bin;C:\Program Files\MySQL\mysql\bin;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;E:\python3.7\Scripts\;E:\python3.7\;C:\WINDOWS;C:\WINDOWS\system32;C:\WINDOWS\System32;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;E:\python3.7\Scripts;C:\ufgovApp\Camera\SZLT\;D:\ADB;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Users\huangchengyan\AppData\Local\Microsoft\WindowsApps;E:\CLion 2020.2.4\bin;D:\QT5.9\5.9\mingw53_32\bin;E:\opencv\build\bin;D:\QT5.9\Tools\mingw530_32\bin;E:\CMake\bin;E:\Microsoft VS Code\bin;C:\Users\huangchengyan\AppData\Local\Programs\Microsoft VS Code\bin;E:\opencv4.5.3\opencv\build\x64\vc15\bin;C:\Users\huangchengyan\AppData\Local\Microsoft\WindowsApps;E:\IntelliJ IDEA Educational Edition 2021.3.2\bin;E:\IntelliJ IDEA Educational Edition 2021.3.2\JDK\bin;
SET CPU_TYPE=STM32F407IGHx
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=standard_tpye_c
SET CPU_CLOCK=0x0A037A00
"D:\keil5\ARM\ARMCC\Bin\ArmAsm" --Via "standard_tpye_c\startup_stm32f407xx._ia"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\main.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\gpio.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\adc.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\can.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\crc.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\dma.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\freertos.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\i2c.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\rng.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\rtc.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\spi.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\tim.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmCC" --Via "standard_tpye_c\usart.__i"
"D:\keil5\ARM\ARMCC\Bin\ArmLink" --Via "standard_tpye_c\standard_tpye_c.lnp"
"D:\keil5\ARM\ARMCC\Bin\fromelf.exe" "standard_tpye_c\standard_tpye_c.axf" --i32combined --output "standard_tpye_c\standard_tpye_c.hex"

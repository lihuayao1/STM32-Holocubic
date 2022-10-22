ARM MPL Libaries -

All libaries compiled using GCC NONE-ARM-EABI 4.9.3 compiler options

1. M0, M0+ Options -

arm-none-eabi-gcc-4.9.3 -DEMPL -DUSE_DMP -DMPU9150 -DREMOVE_LOGGING -DMPL_LOG_NDEBUG=1 -I"C:\eclipseWS\libmplmpu\mpl" -I"C:\eclipseWS\libmplmpu\mllite" -I"C:\eclipseWS\libmplmpu\driver\msp430\bsp\USB_API\USB_Common" -I"C:\eclipseWS\libmplmpu\driver\include" -O2 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mcpu=cortex-m0 -mthumb -g -gdwarf-2

2. M3 Compilers Options -

arm-none-eabi-gcc-4.9.3 -DEMPL -DUSE_DMP -DMPU9150 -DREMOVE_LOGGING -DMPL_LOG_NDEBUG=1 -I"C:\eclipseWS\libmplmpu\mpl" -I"C:\eclipseWS\libmplmpu\mllite" -I"C:\eclipseWS\libmplmpu\driver\msp430\bsp\USB_API\USB_Common" -I"C:\eclipseWS\libmplmpu\driver\include" -O2 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mcpu=cortex-m3 -mthumb -g -gdwarf-2

4. M4 Compiler Options -

arm-none-eabi-gcc-4.9.3 -DEMPL -DUSE_DMP -DMPU9150 -DREMOVE_LOGGING -DMPL_LOG_NDEBUG=1 -I"C:\eclipseWS\libmplmpu\mpl" -I"C:\eclipseWS\libmplmpu\mllite" -I"C:\eclipseWS\libmplmpu\driver\msp430\bsp\USB_API\USB_Common" -I"C:\eclipseWS\libmplmpu\driver\include" -O2 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g -gdwarf-2

arm-none-eabi-gcc-4.9.3 -DEMPL -DUSE_DMP -DMPU9150 -DREMOVE_LOGGING -DMPL_LOG_NDEBUG=1 -I"C:\eclipseWS\libmplmpu\mpl" -I"C:\eclipseWS\libmplmpu\mllite" -I"C:\eclipseWS\libmplmpu\driver\msp430\bsp\USB_API\USB_Common" -I"C:\eclipseWS\libmplmpu\driver\include" -O2 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -g -gdwarf-2

arm-none-eabi-gcc-4.9.3 -DEMPL -DUSE_DMP -DMPU9150 -DREMOVE_LOGGING -DMPL_LOG_NDEBUG=1 -I"C:\eclipseWS\libmplmpu\mpl" -I"C:\eclipseWS\libmplmpu\mllite" -I"C:\eclipseWS\libmplmpu\driver\msp430\bsp\USB_API\USB_Common" -I"C:\eclipseWS\libmplmpu\driver\include" -O2 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mcpu=cortex-m4 -mthumb -g -gdwarf-2
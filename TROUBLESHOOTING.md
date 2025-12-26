# Troubleshooting Guide

## Common Issues and Solutions

### Build Issues

#### Error: "Platform Manager: Installing espressif32 - HTTPClientError"

**Cause**: Network connectivity issue or PlatformIO cache problem

**Solutions**:
1. Check internet connection
2. Try again - temporary network issues are common
3. Clear PlatformIO cache:
   ```bash
   rm -rf ~/.platformio
   pio run
   ```
4. Use different network (corporate firewalls may block)

#### Error: "Library not found"

**Cause**: Library download failed

**Solution**:
```bash
pio lib install
pio run
```

#### Error: "Compilation failed"

**Cause**: Syntax error or missing dependencies

**Solutions**:
1. Check error message for specific file/line
2. Ensure all files from repository are present
3. Clean and rebuild:
   ```bash
   pio run --target clean
   pio run
   ```

### Upload Issues

#### Error: "Could not open port /dev/ttyUSB0"

**Cause**: Permission issue or device not detected

**Solutions (Linux)**:
```bash
# Add user to dialout group
sudo usermod -a -G dialout $USER
# Log out and back in

# Or use sudo (not recommended for regular use)
sudo pio run --target upload
```

**Solutions (Mac)**:
- Install CH340 or CP2102 driver
- Try different USB port

**Solutions (Windows)**:
- Install USB-to-Serial drivers
- Check Device Manager for COM port

#### Error: "Failed to connect to ESP32"

**Cause**: Device not in bootloader mode

**Solution**:
1. Hold BOOT button on device
2. Press and release RESET button  
3. Release BOOT button
4. Try upload again immediately

#### Upload starts but fails partway

**Solutions**:
1. Try slower upload speed in platformio.ini:
   ```ini
   upload_speed = 115200
   ```
2. Use better quality USB cable
3. Connect directly to computer (not through USB hub)

### Display Issues

#### Display is blank/black

**Possible Causes**:
1. Backlight not enabled
2. Wrong pin configuration
3. Display not initialized properly

**Solutions**:
1. Check TFT_BL pin (GPIO 15) is set HIGH
2. Verify pin definitions in config.h match hardware
3. Check User_Setup.h settings
4. Verify TFT_eSPI library is installed correctly
5. Check serial output for initialization errors

#### Display shows garbage/noise

**Cause**: Wrong display driver or SPI configuration

**Solutions**:
1. Verify ST7789 driver is selected in User_Setup.h
2. Check SPI pins match hardware
3. Try different SPI frequency (lower = more stable):
   ```cpp
   #define SPI_FREQUENCY 20000000  // 20MHz instead of 40MHz
   ```

#### Display is rotated wrong

**Solution**: Change rotation in display.cpp:
```cpp
tft.setRotation(0);  // Try 0, 1, 2, or 3
```

#### Touch/Buttons not working

**Cause**: Wrong GPIO assignments

**Solutions**:
1. Verify button pins in config.h
2. Check if buttons need external pull-ups
3. Test with multimeter or oscilloscope
4. Try inverting logic (HIGH vs LOW)

### RF Module Issues

#### CC1101 initialization failed

**Possible Causes**:
1. Wrong SPI pins
2. CC1101 not powered
3. Damaged CC1101 module

**Solutions**:
1. Verify CC1101 pin definitions in config.h
2. Check SPI connections with multimeter
3. Measure voltage on CC1101 VCC pin (should be 3.3V)
4. Check continuity of SPI lines
5. Verify CS pin is correct

#### Cannot capture signals

**Possible Causes**:
1. No antenna connected
2. Wrong frequency
3. Signal too weak
4. GDO0 pin not configured

**Solutions**:
1. Connect appropriate antenna (length matters!)
   - 315MHz: ~23.8cm wire
   - 433MHz: ~17.3cm wire
   - 868MHz: ~8.6cm wire
   - 915MHz: ~8.2cm wire
2. Verify frequency matches transmitter
3. Move closer to signal source
4. Check GDO0 pin configuration

#### Replay doesn't work

**Possible Causes**:
1. Device uses rolling codes
2. Wrong frequency
3. Insufficient transmission power
4. No antenna

**Solutions**:
1. Verify device uses fixed codes (test with original remote)
2. Double-check frequency
3. Increase PA power in rf_module.cpp:
   ```cpp
   ELECHOUSE_cc1101.setPA(12);  // Max power
   ```
4. Use better antenna
5. Try replaying multiple times

#### Frequency scan shows nothing

**Cause**: Normal - depends on RF environment

**Solutions**:
- Test in area with known RF devices
- Trigger device (press remote) during scan
- Lower RSSI threshold in rf_module.cpp:
  ```cpp
  if (rssi > -100) {  // More sensitive
  ```

### Storage Issues

#### "SPIFFS Mount Failed"

**Cause**: Flash filesystem not formatted or corrupted

**Solutions**:
1. Format SPIFFS:
   - Use Settings -> Format Storage
   - Or reflash with "Erase Flash" option
2. Check partition table configuration

#### Cannot save signals

**Possible Causes**:
1. Storage full
2. Filesystem corrupted
3. No write permissions

**Solutions**:
1. Delete old signals
2. Format storage
3. Check available space in serial output

#### Saved signals corrupted

**Cause**: Power loss during write or filesystem corruption

**Solutions**:
1. Format storage
2. Capture signals again
3. Ensure stable power supply

### Power Issues

#### Device keeps resetting

**Possible Causes**:
1. Insufficient power supply
2. Brownout during RF transmission
3. Software crash

**Solutions**:
1. Use quality USB power supply (>500mA)
2. Charge battery fully
3. Check serial output for crash logs
4. Add decoupling capacitors if custom hardware

#### Battery drains quickly

**Solutions**:
1. Lower display backlight
2. Reduce RF transmission power
3. Add sleep mode (future feature)
4. Check for short circuits

### Serial Monitor Issues

#### No output in serial monitor

**Solutions**:
1. Verify baud rate (115200)
2. Check USB cable supports data
3. Select correct COM port
4. Enable USB CDC in platformio.ini:
   ```ini
   -DARDUINO_USB_CDC_ON_BOOT=1
   ```

#### Garbled serial output

**Cause**: Wrong baud rate

**Solution**: Set monitor to 115200 baud

## Hardware Debugging

### Check SPI Bus

The CC1101 and display share the SPI bus:
- MOSI: GPIO 11
- MISO: GPIO 13  
- SCK: GPIO 12

Use multimeter to check continuity:
1. Power off device
2. Check each pin from ESP32 to CC1101
3. Check each pin from ESP32 to display
4. Look for shorts between signals

### Check Chip Select Lines

Each SPI device has unique CS pin:
- CC1101 CS: GPIO 10
- Display CS: GPIO 9

Verify with oscilloscope or logic analyzer:
- CS should be LOW when device is active
- Only one CS LOW at a time

### Antenna Testing

Calculate proper antenna length:
```
Length (cm) = 7500 / Frequency (MHz) / 4
```

Examples:
- 433 MHz: 17.3 cm
- 868 MHz: 8.6 cm

Use wire antenna or proper helical/PCB antenna.

## Getting Help

If you're still stuck:

1. **Check Serial Output**: Most issues report errors
2. **Enable Debug**: Set CORE_DEBUG_LEVEL=5 in platformio.ini
3. **GitHub Issues**: Search existing issues or create new one
4. **Provide Details**:
   - Exact error message
   - Serial output
   - Hardware variant
   - Steps to reproduce

## Known Limitations

1. **Rolling Codes**: Cannot replay KeeLoq, HCS, or other rolling codes
2. **Encrypted Protocols**: Cannot decode/replay encrypted signals
3. **Complex Modulations**: Limited support for FSK/MSK
4. **Long Signals**: Buffer limited to 1024 transitions
5. **Real-time Analysis**: No protocol decoding (yet)

## Future Features

Planned improvements:
- Protocol identification
- Custom signal naming
- Frequency hopping
- Signal analysis tools
- Sub-GHz spectrum analyzer
- Remote control via WiFi
- Signal library sharing

## Resources

- **CC1101 Datasheet**: Texas Instruments CC1101 documentation
- **ESP32-S3 Datasheet**: Espressif documentation
- **TFT_eSPI Library**: https://github.com/Bodmer/TFT_eSPI
- **RF Signal Analysis**: RTL-SDR for signal visualization
- **PlatformIO Docs**: https://docs.platformio.org

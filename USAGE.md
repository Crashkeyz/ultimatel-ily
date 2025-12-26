# Usage Guide

## Getting Started

After flashing the firmware, the device will boot and display the splash screen showing "Ultimatel-ily" and the version number. After 2 seconds, the main menu will appear.

## Navigation

The firmware uses a simple menu-based interface controlled by three buttons:

- **UP Button**: Navigate up in menus
- **DOWN Button**: Navigate down in menus  
- **SELECT Button**: Confirm selection / Execute action

## Main Menu Options

### 1. Capture Signal

Captures RF signals from the environment.

**Steps:**
1. Select "Capture Signal" from the main menu
2. The device enters listening mode on the default frequency (433.92 MHz)
3. The display shows "Listening..."
4. Activate the RF device you want to capture (press your remote, etc.)
5. When a signal is detected, the display shows "Signal detected!"
6. The signal is automatically captured and analyzed
7. Signal details are displayed (frequency, timing count, etc.)
8. Press SELECT within 5 seconds to save the signal
9. The signal is saved with a timestamp-based filename
10. Return to main menu

**Tips:**
- Keep the antenna close to the transmitter for best results
- Multiple rapid presses may be needed for some protocols
- If capture fails, try again - timing is important

### 2. Replay Signal

Transmits a previously saved signal.

**Steps:**
1. Select "Replay Signal" from the main menu
2. If signals are saved, the saved signals list appears
3. Use UP/DOWN to navigate through saved signals
4. Press SELECT to transmit the selected signal
5. The display shows "Transmitting..."
6. The signal is replayed with original timing and frequency
7. "Transmitted!" confirmation appears
8. Return to main menu

**Notes:**
- Ensure you have permission to transmit on the frequency
- Keep antenna clear for best transmission range
- Some protocols may require multiple transmissions

### 3. Frequency Scan

Scans common RF frequencies for activity.

**Steps:**
1. Select "Frequency Scan" from the main menu
2. The device scans through preset frequencies:
   - 315 MHz
   - 433.92 MHz
   - 868 MHz
   - 915 MHz
3. For each frequency, the display shows:
   - Current frequency
   - RSSI (signal strength) if detected
4. Scan takes approximately 2-3 seconds
5. Press SELECT to cancel scan early
6. Return to main menu when complete

**Use Cases:**
- Identify which frequency a device uses
- Check for RF activity in an area
- Validate antenna performance

### 4. Saved Signals

Browse and manage your saved RF signals.

**Steps:**
1. Select "Saved Signals" from the main menu
2. List of saved signals appears
3. Use UP/DOWN to browse
4. Press SELECT to view details or transmit
5. Press SELECT again to return to main menu

**Management:**
- Signals are stored in internal SPIFFS filesystem
- Each signal includes frequency, timing, and metadata
- Filenames are timestamp-based by default
- Up to 50 signals can be stored (depending on complexity)

### 5. Settings

Configure device settings.

**Available Settings:**
- **Backlight**: Adjust display brightness
- **Default Freq**: Set default capture frequency
- **Modulation**: Change modulation type
- **Format Storage**: Erase all saved signals

**Note:** Settings functionality is in development and will be expanded in future versions.

### 6. Info

Display firmware and device information.

**Information Shown:**
- Firmware name and version
- Supported frequencies
- Device capabilities
- Credit information

## Advanced Usage

### Understanding Signal Capture

The firmware captures signals by recording the timing of RF transitions:
- High/Low state changes
- Duration of each state
- Total pattern length

This "timing-based" capture works well for:
- Simple fixed-code remotes
- ASK/OOK modulated signals
- Weather station sensors
- Wireless doorbells
- Many garage door openers

### Modulation Types

The CC1101 supports multiple modulation schemes:

- **ASK/OOK** (Amplitude Shift Keying / On-Off Keying)
  - Most common for simple remotes
  - Easy to capture and replay
  - Default mode

- **2-FSK** (2-level Frequency Shift Keying)
  - Used by some wireless sensors
  - More complex than ASK

- **GFSK** (Gaussian Frequency Shift Keying)
  - Used in more sophisticated devices
  - Better noise immunity

### Frequency Bands

Common frequency allocations:
- **315 MHz**: Popular in North America for remotes
- **433.92 MHz**: ISM band, worldwide use, most common
- **868 MHz**: European ISM band
- **915 MHz**: North American ISM band

**Legal Note:** Always verify local regulations before transmitting!

### Troubleshooting

**Signal not capturing:**
- Ensure antenna is connected
- Move closer to the transmitter
- Try capturing multiple times
- Check frequency matches the transmitter

**Replay doesn't work:**
- Verify correct frequency
- Ensure antenna is connected
- Try replaying multiple times
- Some devices use rolling codes (not supported)

**Display issues:**
- Check backlight setting
- Verify power supply
- Reset device

**Storage issues:**
- Check available space in Info menu
- Format storage if corrupted
- Signals may become corrupted if power lost during save

## Tips and Best Practices

1. **Antenna is Critical**: Always use a proper antenna tuned to your frequency
2. **Start Simple**: Test with simple devices first (basic remotes)
3. **Multiple Captures**: Capture the same signal 2-3 times to ensure accuracy
4. **Name Your Signals**: Future versions will support custom naming
5. **Legal Compliance**: Only analyze and replay your own devices
6. **Battery Life**: Lower backlight brightness to extend battery life
7. **Range**: Transmission range varies by frequency and antenna (typically 10-50m)

## Serial Console

For debugging and advanced monitoring, connect via USB and use a serial terminal:

```bash
# Linux/Mac
screen /dev/ttyUSB0 115200

# PlatformIO
pio device monitor
```

Serial output includes:
- Initialization status
- Signal capture details
- Transmission confirmations
- Error messages
- Debug information

## Safety and Legal Considerations

⚠️ **IMPORTANT WARNINGS:**

1. **Legal Compliance**: 
   - Only use on frequencies legal in your jurisdiction
   - Obtain permission before analyzing/transmitting signals
   - Never interfere with emergency services, aircraft, or critical communications

2. **Ethical Use**:
   - Only analyze and replay signals from devices you own
   - Do not use to gain unauthorized access
   - Respect privacy and property rights

3. **Technical Limitations**:
   - Rolling code systems (modern car keys, secure garage doors) are NOT supported
   - Encrypted protocols cannot be replayed
   - This tool is for education and research only

4. **Responsibility**:
   - User is solely responsible for compliance with laws
   - Authors assume no liability for misuse
   - Use at your own risk

## Support and Updates

- **GitHub**: https://github.com/Crashkeyz/ultimatel-ily
- **Issues**: Report bugs via GitHub Issues
- **Updates**: Check GitHub for firmware updates

## Credits

This firmware is built on excellent open-source libraries:
- TFT_eSPI by Bodmer
- SmartRC-CC1101 by LSatan
- ArduinoJson by Benoit Blanchon
- ESP32 Arduino Core by Espressif

Hardware by LilyGO - T-Embed CC1101

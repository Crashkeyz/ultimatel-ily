# Build Instructions

## Prerequisites

1. **Install PlatformIO**
   - Install [Visual Studio Code](https://code.visualstudio.com/)
   - Install the PlatformIO IDE extension from the VSCode marketplace
   - Alternatively, install PlatformIO Core CLI

2. **Hardware Requirements**
   - LilyGO T-Embed CC1101 board
   - USB-C cable for programming and power
   - Antenna (optional but recommended for better range)

## Building the Firmware

### Using Visual Studio Code + PlatformIO

1. Open the project folder in VSCode:
   ```bash
   cd ultimatel-ily
   code .
   ```

2. PlatformIO will automatically detect the project and install dependencies

3. Click the Build button (checkmark icon) in the PlatformIO toolbar
   - Or use: `Ctrl+Alt+B` (Windows/Linux) / `Cmd+Alt+B` (Mac)
   - Or run: `pio run` in the terminal

4. Wait for the build to complete. First build will take longer as it downloads libraries.

### Using PlatformIO CLI

1. Navigate to the project directory:
   ```bash
   cd ultimatel-ily
   ```

2. Build the firmware:
   ```bash
   platformio run
   ```

3. The compiled firmware will be in `.pio/build/lilygo-t-embed-cc1101/`

## Flashing the Firmware

### Automatic Upload

1. Connect your T-Embed to your computer via USB-C

2. The board should appear as a serial device:
   - Linux: `/dev/ttyUSB0` or `/dev/ttyACM0`
   - Mac: `/dev/cu.usbserial-*`
   - Windows: `COM3`, `COM4`, etc.

3. Upload the firmware:
   - VSCode: Click the Upload button (arrow icon) in PlatformIO toolbar
   - CLI: `platformio run --target upload`

4. Wait for the upload to complete

### Manual Upload (if automatic fails)

1. Put the ESP32-S3 into download mode:
   - Hold the BOOT button
   - Press and release the RESET button
   - Release the BOOT button

2. Run the upload command again

### Troubleshooting Upload Issues

**Device not detected:**
- Install USB-to-Serial drivers (usually CP210x or CH340)
- Try a different USB cable (some cables are power-only)
- Check if the device appears in device manager/system

**Permission denied (Linux):**
```bash
sudo usermod -a -G dialout $USER
# Log out and back in
```

**Upload fails:**
- Try putting the board in download mode manually
- Reduce upload speed in platformio.ini: `upload_speed = 115200`
- Check USB cable quality

## Monitoring Serial Output

To view debug output and logs:

### Using PlatformIO

```bash
platformio device monitor
```

Or click the Serial Monitor icon in VSCode

### Using Other Tools

```bash
# Linux/Mac
screen /dev/ttyUSB0 115200

# Or use minicom
minicom -D /dev/ttyUSB0 -b 115200
```

On Windows, use PuTTY or Tera Term.

## Customizing the Build

### Changing Pin Assignments

Edit `include/config.h` to modify pin definitions:

```cpp
#define CC1101_CS_PIN 10
#define TFT_CS_PIN 9
// etc.
```

### Adjusting Display Settings

Edit `include/User_Setup.h` for display-specific settings.

### Modifying Build Flags

Edit `platformio.ini` to change compiler flags or add features:

```ini
build_flags = 
    -DCORE_DEBUG_LEVEL=5  ; More verbose logging
    -DBOARD_HAS_PSRAM
```

## Build Artifacts

After a successful build, you'll find:

- **firmware.bin** - The main firmware binary
- **firmware.elf** - ELF file with debug symbols
- **partitions.bin** - Partition table

These are located in `.pio/build/lilygo-t-embed-cc1101/`

## Clean Build

To clean all build artifacts and start fresh:

```bash
platformio run --target clean
```

## Dependencies

The build system will automatically download:
- ESP32 Arduino framework
- TFT_eSPI library
- CC1101 driver library
- ArduinoJson library

First build may take 5-10 minutes depending on your internet connection.

## Verification

After flashing:

1. The display should show the splash screen
2. Serial output should show initialization messages
3. Main menu should appear after ~2 seconds
4. Device should be ready for use

If the display doesn't work, check:
- TFT pin definitions
- Display backlight (GPIO 15)
- SPI connections

If the RF module doesn't work:
- Check CC1101 pin definitions
- Verify SPI bus configuration
- Check antenna connection

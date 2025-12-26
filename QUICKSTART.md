# Quick Start Guide

## Getting Your Device Running in 5 Minutes

### Step 1: Install PlatformIO (2 minutes)

**Option A: VSCode (Recommended)**
1. Install [Visual Studio Code](https://code.visualstudio.com/)
2. Open VSCode
3. Go to Extensions (Ctrl+Shift+X)
4. Search for "PlatformIO IDE"
5. Click Install

**Option B: CLI**
```bash
pip install -U platformio
```

### Step 2: Get the Firmware (1 minute)

```bash
git clone https://github.com/Crashkeyz/ultimatel-ily.git
cd ultimatel-ily
```

### Step 3: Build & Flash (2 minutes)

```bash
# Connect your T-Embed via USB-C
pio run --target upload

# Watch it work
pio device monitor
```

Done! Your device should now show the main menu.

## First Use

### Basic Operations

**Navigation:**
- UP button: Move up in menus
- DOWN button: Move down in menus
- SELECT button: Choose/confirm

**Capturing Your First Signal:**
1. Select "Capture Signal" from main menu
2. Press your remote/device button
3. Wait for "Signal detected!"
4. Press SELECT to save
5. Done!

**Replaying a Signal:**
1. Select "Replay Signal"
2. Choose your saved signal
3. Press SELECT to transmit
4. Watch it work!

## Common Commands

```bash
# Build firmware
pio run

# Upload to device
pio run --target upload

# Monitor serial output
pio device monitor

# Clean build
pio run --target clean

# Build for release
pio run --environment release
```

## Quick Troubleshooting

| Problem | Quick Fix |
|---------|-----------|
| Can't upload | Hold BOOT, press RESET, release BOOT |
| Display blank | Check backlight GPIO 15 |
| No signals | Check antenna is connected |
| Won't compile | Run `pio lib install` |

## What's What

### Main Files

- **`src/main.cpp`** - Main program
- **`include/config.h`** - Pin definitions & settings
- **`platformio.ini`** - Build configuration

### Key Directories

- **`src/`** - Source code
- **`include/`** - Header files
- **`examples/`** - Example signals
- **`.pio/`** - Build output (auto-generated)

### Documentation

- **README.md** - Project overview
- **BUILD.md** - Detailed build instructions
- **USAGE.md** - How to use the device
- **TROUBLESHOOTING.md** - Fix common issues
- **FAQ.md** - Frequently asked questions
- **HARDWARE.md** - Hardware details
- **CONTRIBUTING.md** - How to contribute

## Quick Config Changes

### Change Default Frequency

Edit `include/config.h`:
```cpp
#define FREQ_433MHZ 433.92  // Change this value
```

### Adjust Display Brightness

In `src/main.cpp`, change:
```cpp
display.setBacklight(255);  // 0-255
```

### Modify Button Pins

Edit `include/config.h`:
```cpp
#define BUTTON_UP 0      // Change GPIO
#define BUTTON_DOWN 1    // Change GPIO
#define BUTTON_SELECT 2  // Change GPIO
```

## Legal Reminder

⚠️ **Use Responsibly**
- Only analyze your own devices
- Follow local RF regulations
- Don't interfere with others' systems
- Be ethical and legal

## Need More Help?

- **Detailed Instructions**: See BUILD.md
- **Usage Help**: See USAGE.md
- **Problems**: See TROUBLESHOOTING.md
- **Questions**: See FAQ.md
- **Issues**: https://github.com/Crashkeyz/ultimatel-ily/issues

## Next Steps

Once you have it working:
1. Read USAGE.md for detailed feature explanations
2. Try capturing different types of signals
3. Experiment with frequency scanning
4. Learn about RF protocols (examples/SIGNALS.md)
5. Contribute improvements!

## Tips for Success

✅ **Do This:**
- Use a proper antenna
- Start with simple remotes
- Read the documentation
- Test in a safe environment
- Keep firmware updated

❌ **Avoid This:**
- Transmitting without antenna
- Using on devices you don't own
- Ignoring warnings
- Skipping documentation
- Expecting it to break security

## Antenna Quick Reference

| Frequency | Wire Length |
|-----------|-------------|
| 315 MHz   | 23.8 cm     |
| 433 MHz   | 17.3 cm     |
| 868 MHz   | 8.6 cm      |
| 915 MHz   | 8.2 cm      |

Simple wire antennas work great for testing!

## Getting Help

1. Check FAQ.md first
2. Search existing GitHub issues
3. Read relevant documentation
4. Create new issue with details
5. Be patient and polite

## Supporting the Project

- ⭐ Star the repo on GitHub
- 🐛 Report bugs you find
- 📝 Improve documentation
- 💻 Contribute code
- 🗣️ Tell others about it

---

**Happy RF exploring! 📡**

Remember: With great power comes great responsibility. Use this tool ethically and legally.

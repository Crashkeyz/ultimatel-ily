# Ultimatel-ily

A fully functional multi-protocol RF firmware for the LilyGO T-Embed CC1101 device. This firmware turns your T-Embed into a powerful "skeleton key" tool for analyzing, capturing, and replaying RF signals across multiple frequencies.

## ⚠️ NEW: Advanced RF Security Research Features

**Version 1.1+** includes advanced educational tools for RF security research:

- **Rolling Code Analyzer**: Study and understand rolling code security systems
- **Signal Intelligence**: Advanced protocol identification and signal analysis  
- **Advanced Transmission**: Sophisticated transmission patterns for testing
- **RF Research Tools**: Educational demonstrations (disabled by default)

**📚 Complete Documentation**: See [ADVANCED_FEATURES.md](ADVANCED_FEATURES.md)
**⚖️ Legal Notice**: Read [LEGAL_DISCLAIMER.md](LEGAL_DISCLAIMER.md) before using advanced features

These features are for **EDUCATIONAL AND AUTHORIZED RESEARCH ONLY**. Misuse is illegal and can result in severe penalties.

## Features

### Basic Features
- **Multi-Frequency Support**: 315MHz, 433.92MHz, 868MHz, 915MHz
- **Signal Capture**: Capture RF signals with timing analysis
- **Signal Replay**: Transmit captured signals
- **Frequency Scanner**: Scan for active RF signals
- **Signal Storage**: Save and load captured signals to/from SPIFFS
- **TFT Display Interface**: Easy-to-use menu system
- **Multiple Modulation Types**: ASK/OOK, 2FSK, 4FSK, MSK, GFSK

### Advanced Research Features (v1.1+)

**⚠️ EDUCATIONAL AND AUTHORIZED USE ONLY ⚠️**

- **Rolling Code Analysis**: Study rolling code security systems (KeeLoq, HCS)
- **Signal Intelligence**: Advanced protocol identification and analysis
- **Advanced Transmission**: Sophisticated transmission testing capabilities
- **RF Research Tools**: Educational demonstrations of RF vulnerabilities

**Documentation**:
- [ADVANCED_FEATURES.md](ADVANCED_FEATURES.md) - Complete feature documentation
- [ROLLING_CODES.md](ROLLING_CODES.md) - Educational guide to rolling codes
- [RF_SECURITY.md](RF_SECURITY.md) - RF security research best practices
- [LEGAL_DISCLAIMER.md](LEGAL_DISCLAIMER.md) - Important legal information

## Hardware

This firmware is designed for the LilyGO T-Embed CC1101 which includes:
- ESP32-S3 microcontroller
- CC1101 sub-GHz transceiver
- ST7789 170x320 TFT display
- Battery management
- Programmable buttons

### Pin Configuration

**CC1101 Radio:**
- GDO0: GPIO 4
- GDO2: GPIO 5
- SCK: GPIO 12
- MISO: GPIO 13
- MOSI: GPIO 11
- CS: GPIO 10

**TFT Display:**
- CS: GPIO 9
- DC: GPIO 8
- RST: GPIO 14
- BL: GPIO 15
- MOSI: GPIO 11 (shared with CC1101)
- SCLK: GPIO 12 (shared with CC1101)

## Installation

### Prerequisites

- [PlatformIO](https://platformio.org/) installed (VSCode extension recommended)
- USB-C cable for programming
- LilyGO T-Embed CC1101 board

### Building and Flashing

1. Clone this repository:
```bash
git clone https://github.com/Crashkeyz/ultimatel-ily.git
cd ultimatel-ily
```

2. Open the project in PlatformIO (VSCode):
```bash
code .
```

3. Build the firmware:
```bash
pio run
```

4. Connect your T-Embed via USB-C and flash:
```bash
pio run --target upload
```

5. Monitor serial output (optional):
```bash
pio device monitor
```

## Usage

### Main Menu

Navigate using the UP/DOWN buttons and select with the SELECT button:

1. **Capture Signal** - Listen for and capture RF signals
2. **Replay Signal** - Transmit a saved signal
3. **Frequency Scan** - Scan for active frequencies
4. **Saved Signals** - Browse and manage saved signals
5. **Settings** - Configure device settings
6. **Info** - View firmware information
7. **🔬 Advanced Research** ⚠️ - Advanced RF security research features (Educational use only)

### Capturing Signals

1. Select "Capture Signal" from the main menu
2. The device will listen on the default frequency (433.92 MHz)
3. When a signal is detected, it will be captured automatically
4. Press SELECT to save the captured signal

### Replaying Signals

1. Select "Replay Signal" or "Saved Signals"
2. Navigate to the signal you want to transmit
3. Press SELECT to transmit the signal

### Frequency Scanning

1. Select "Frequency Scan"
2. The device will scan through common frequencies
3. Active frequencies will be displayed with RSSI values

## Supported Protocols

The firmware can capture and replay various RF protocols including:
- Fixed code remotes (garage doors, gates)
- Simple ASK/OOK devices
- Weather stations
- Wireless sensors
- Remote controls
- And many more...

**Note**: This firmware is for educational and research purposes. Rolling code systems with encryption are not supported by design.

## Development

### Project Structure

```
ultimatel-ily/
├── include/           # Header files
│   ├── config.h      # Hardware configuration
│   ├── display.h     # Display interface
│   ├── rf_module.h   # RF radio interface
│   ├── rf_signal.h   # Signal structures
│   └── storage.h     # File system interface
├── src/              # Source files
│   ├── main.cpp      # Main firmware
│   ├── display.cpp   # Display implementation
│   ├── rf_module.cpp # RF implementation
│   └── storage.cpp   # Storage implementation
├── platformio.ini    # PlatformIO configuration
└── README.md         # This file
```

### Libraries Used

- **TFT_eSPI** - Display driver
- **SmartRC-CC1101-Driver-Lib** - CC1101 radio driver
- **ArduinoJson** - JSON serialization for storage
- **SPIFFS** - File system

## Legal Disclaimer

⚠️ **IMPORTANT**: This tool is for educational and research purposes only.

### Legal Uses
✅ Analyzing and testing **your own devices**
✅ Educational learning about RF systems
✅ Authorized security research with permission
✅ Professional penetration testing under contract

### Illegal Uses
❌ Accessing systems you don't own or control
❌ RF jamming or interference (FEDERAL CRIME)
❌ Bypassing security without authorization
❌ Intercepting private communications

### Regulations
- **Always operate within legal frequency bands** for your region
- **Obtain proper authorization** before analyzing or transmitting RF signals
- **Do not interfere** with wireless communications
- **FCC Part 15 regulations** apply in USA (penalties up to $112,500/day)
- **Be aware of local laws** and regulations regarding RF devices

### Advanced Features Warning

Version 1.1+ includes advanced RF security research features. **Read [LEGAL_DISCLAIMER.md](LEGAL_DISCLAIMER.md) before using them.**

These features are for EDUCATIONAL purposes only. Misuse can result in:
- Criminal prosecution
- Heavy fines
- Equipment seizure
- Imprisonment

**You assume ALL legal responsibility for your actions.**

## Disclaimer

THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY. The developers:
- Accept NO liability for misuse
- Do NOT endorse illegal activities  
- Provide tools for EDUCATIONAL purposes only
- WILL cooperate with law enforcement

**Use responsibly. Use legally. Use ethically.**

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues.

## License

This project is open source. Please use responsibly and ethically.

## Acknowledgments

- LilyGO for the T-Embed hardware
- The open-source community for the excellent libraries
- RF security researchers for protocol documentation

## Support

For issues, questions, or suggestions, please open an issue on GitHub.

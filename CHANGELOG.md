# Changelog

All notable changes to the Ultimatel-ily firmware will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2024-12-26

### Added - Initial Release

#### Core Functionality
- Complete firmware implementation for LilyGO T-Embed CC1101
- Multi-frequency RF signal capture (315, 433, 868, 915 MHz)
- Signal replay functionality
- Frequency scanner
- Menu-based UI system
- SPIFFS storage for saved signals
- TFT display support with ST7789 driver

#### RF Features
- CC1101 radio module integration
- ASK/OOK modulation support
- Timing-based signal capture (up to 1024 transitions)
- Configurable transmission power
- Multiple modulation type support (ASK/OOK, 2FSK, GFSK, MSK)
- RSSI (signal strength) monitoring

#### User Interface
- Main menu with 6 options
- Capture mode with visual feedback
- Replay mode with signal selection
- Frequency scan display
- Saved signals browser
- Settings menu
- Info screen
- Status bar for feedback
- PWM-controlled backlight

#### Storage System
- JSON-based signal storage
- Save/load/delete signal operations
- Signal metadata (frequency, timing, timestamp)
- Storage management (format, space checking)
- File system organization

#### Documentation
- Comprehensive README with features and installation
- Detailed BUILD.md with step-by-step instructions
- USAGE.md with complete user guide
- TROUBLESHOOTING.md for common issues
- FAQ.md answering common questions
- HARDWARE.md with technical specifications
- CONTRIBUTING.md for developers
- QUICKSTART.md for fast setup
- Examples and signal documentation
- Legal disclaimers and responsible use guidelines

#### Development
- PlatformIO project configuration
- Modular code architecture
- Header/implementation file separation
- Configurable pin definitions
- Build optimization
- Serial debugging support

### Project Structure
```
ultimatel-ily/
├── src/                  # Source implementations
├── include/              # Header files
├── examples/             # Example signals
├── platformio.ini        # Build configuration
└── docs/                 # Documentation
```

### Dependencies
- TFT_eSPI ^2.5.43
- SmartRC-CC1101-Driver-Lib ^2.5.7
- ArduinoJson ^6.21.3
- ESP32 Arduino Framework

### Known Limitations
- Rolling code protocols not supported (by design)
- Encrypted signals cannot be decoded
- Signal buffer limited to 1024 transitions
- No protocol identification (yet)
- Basic button input only

### Security
- No backdoors or exploits
- Educational/research focus
- Responsible disclosure policy
- Legal warnings and disclaimers

## [Unreleased] - Future Plans

### Planned Features
- [ ] Protocol identification and decoding
- [ ] Custom signal naming UI
- [ ] WiFi configuration interface
- [ ] Web-based control panel
- [ ] Sleep mode for battery optimization
- [ ] Over-the-air (OTA) updates
- [ ] Signal analysis and comparison
- [ ] Spectrum analyzer visualization
- [ ] Signal quality metrics
- [ ] Frequency hopping support
- [ ] Sub-GHz spectrum scanner
- [ ] Cloud signal library
- [ ] Multi-language support
- [ ] Signal statistics and logging

### Planned Improvements
- [ ] Enhanced protocol support (FSK variants)
- [ ] Better signal filtering and noise reduction
- [ ] Advanced capture modes
- [ ] Signal editing capabilities
- [ ] Improved battery life
- [ ] Enhanced UI/UX
- [ ] More comprehensive error handling
- [ ] Performance optimizations
- [ ] Additional modulation types

### Under Consideration
- Remote control via WiFi/Bluetooth
- Mobile app companion
- Desktop software for signal analysis
- Hardware revision support
- Custom board variants
- Community signal database

## Version History

### Version Numbering

- **Major.Minor.Patch** (e.g., 1.0.0)
- **Major**: Breaking changes, major features
- **Minor**: New features, backwards compatible
- **Patch**: Bug fixes, minor improvements

### Release Schedule

- Major releases: When significant features complete
- Minor releases: Monthly (if features ready)
- Patch releases: As needed for critical bugs

## How to Upgrade

### Firmware Update Process

1. **Backup your signals** (export if possible)
2. **Download latest release** from GitHub
3. **Build and flash** new firmware
4. **Verify functionality** after update
5. **Restore signals** if needed

### Breaking Changes

When breaking changes occur:
- They will be clearly documented
- Migration guides will be provided
- Backwards compatibility maintained when possible
- Old signal files should remain compatible

## Contributing to Changelog

When contributing, update this file:
- Add entry under [Unreleased]
- Use categories: Added, Changed, Deprecated, Removed, Fixed, Security
- Link to issues/PRs
- Credit contributors

## Questions About Versions?

- Check GitHub releases for downloads
- Read release notes for details
- See FAQ for upgrade questions
- Create issue if problems occur

---

**Note**: This is the initial release. More updates coming soon!

For the latest version, always check: https://github.com/Crashkeyz/ultimatel-ily/releases

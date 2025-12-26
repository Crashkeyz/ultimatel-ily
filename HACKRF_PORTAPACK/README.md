# HackRF One + PortaPack H4M - Drone Detection & Personal Recall System

## ⚠️ LEGAL DISCLAIMER - READ FIRST ⚠️

**CRITICAL LEGAL INFORMATION:**

### ✅ LEGAL USES:
- **Receiving/monitoring any frequency (passive detection)** - Always legal
- **Transmitting to YOUR OWN drones** - Legal when compliant with regulations
- **Educational and research purposes** - Within legal boundaries
- **Testing YOUR OWN equipment** - In appropriate environments

### ❌ ILLEGAL USES:
- **Jamming or interfering with drones you don't own** - FEDERAL CRIME
- **Transmitting on unauthorized frequencies** - FCC violation
- **Controlling aircraft/drones you don't own** - Criminal offense
- **Creating interference to licensed services** - Heavy fines + prosecution

**Penalties for illegal use:** Fines up to $10,000+ per violation, equipment seizure, criminal charges, possible imprisonment.

**BY USING THIS PACKAGE, YOU AGREE:** You are solely responsible for legal compliance. The authors accept NO liability for misuse.

---

## Overview

This comprehensive SD card package provides:

1. **Drone Detection System (Receive-Only - Always Legal)**
   - Multi-band frequency scanning (433 MHz to 5.8 GHz)
   - Real-time RSSI monitoring and alerts
   - Signal pattern identification
   - Activity logging with timestamps

2. **Personal Drone Recall Framework (YOUR Equipment ONLY)**
   - Template configurations for common protocols (FrSky, FlySky, ELRS, Crossfire)
   - Signal capture and analysis tools
   - Replay system for YOUR drone's control signals
   - Safety-focused testing procedures

3. **Educational Resources**
   - Comprehensive guides and documentation
   - RF protocol analysis tools
   - Legal compliance information
   - Safety procedures

## Hardware Requirements

### Required:
- **HackRF One** - Software Defined Radio (1 MHz - 6 GHz)
- **PortaPack H4M** - Standalone interface with display and controls
- **MicroSD Card** - 8GB+ recommended, Class 10 or better
- **Antenna Kit** - Appropriate antennas for target frequencies:
  - 433 MHz antenna (UHF)
  - 915 MHz antenna (UHF)
  - 1.2 GHz antenna
  - 2.4 GHz antenna (WiFi/Bluetooth type)
  - 5.8 GHz antenna (WiFi/FPV type)

### Optional:
- External battery pack (HackRF can drain batteries quickly)
- Tripod for stable positioning
- Directional antennas for improved range/direction finding
- GPS module for location logging

## Firmware Requirements

- **PortaPack Mayhem** firmware (recommended) - Latest version
- Alternatively: **PortaPack Havoc** firmware
- HackRF firmware 2018.01.1 or later

Firmware updates available at:
- Mayhem: https://github.com/eried/portapack-mayhem
- Havoc: https://github.com/furrtek/portapack-havoc

## Quick Start

### 1. SD Card Preparation (5 minutes)

```bash
# Format SD card as FAT32
# Copy entire SDCARD directory contents to SD card root

SDCARD/
├── FREQMAN/       # Frequency scanner configurations
├── SETTINGS/      # Configuration files
├── CAPTURES/      # Your signal captures (initially empty)
└── REPLAYS/       # Your replay files (initially empty)
```

### 2. Installation

1. Power off HackRF and PortaPack
2. Insert prepared microSD card into PortaPack
3. Power on device
4. PortaPack should boot to main menu

### 3. First Use - Drone Detection (100% Legal)

**Start Scanning in 5 Steps:**

1. From main menu: **Select "Freqman"**
2. Choose a frequency file:
   - `DRONE_SCAN_ALL.TXT` - Quick multi-band scan (recommended first try)
   - `DRONE_SCAN_2G4.TXT` - 2.4 GHz (most common consumer drones)
   - `DRONE_SCAN_5G8.TXT` - 5.8 GHz (FPV video links)
3. Set RSSI threshold: `-70 dBm` (good starting point)
4. Press **START** to begin scanning
5. Watch for signal activity - audio/visual alerts will trigger on detection

**What you'll see:**
- Real-time RSSI readings
- Frequency where signal detected
- Signal strength indicator
- Alert when drone activity found

See **DETECTION_GUIDE.md** for detailed instructions.

### 4. Personal Recall Setup (YOUR Drones ONLY)

⚠️ **This is for YOUR OWN equipment only. Using on others' drones is ILLEGAL.**

**Setup Overview:**
1. Read **LEGAL.md** completely
2. Follow **PERSONAL_RECALL_SETUP.md** step-by-step
3. Capture YOUR drone's control signals
4. Create customized replay files
5. Test in safe, controlled environment
6. Verify legal compliance

**This is NOT plug-and-play** - requires customization with YOUR specific drone's signals.

## Feature Set

### Drone Detection (Passive - Always Legal)

#### Frequency Coverage:
- **433 MHz ISM Band** - RC control signals
  - 40 channels (433.05 - 434.00 MHz)
  - Optimal for: Generic RC, some toys
  
- **915 MHz ISM Band** - RC control and telemetry
  - 26 channels (902 - 928 MHz)  
  - Optimal for: Long-range systems, telemetry
  
- **1.2 GHz Band** - Analog FPV video
  - 15 channels (1.2 - 1.32 GHz)
  - Optimal for: Long-range FPV video
  
- **2.4 GHz ISM Band** - DJI, WiFi, most consumer drones
  - 50 channels (2.4 - 2.48 GHz)
  - Optimal for: Consumer drones, WiFi control
  
- **5.8 GHz Band** - FPV video downlinks
  - 48 channels across A/B/E/F/R bands
  - Optimal for: Racing drones, FPV video
  
- **GPS L1 (1575.42 MHz)** - GPS monitoring (receive only!)
  - 7 channels around GPS L1 center
  - Optimal for: Detecting GPS jamming attempts

#### Detection Features:
- Real-time RSSI monitoring
- Audio alerts (configurable tones per band)
- Visual alerts (LED, screen flash)
- Activity logging with timestamps
- Pattern recognition helpers
- Multi-band simultaneous scanning
- Battery-efficient scanning modes
- Waterfall display
- Signal strength history

### Personal Recall System (YOUR Equipment ONLY)

#### Supported Protocols (Templates):
- **FrSky D16** - 16 channel frequency hopping (2.4 GHz)
- **FlySky AFHDS/AFHDS2A** - FlySky protocols (2.4 GHz)
- **ExpressLRS (ELRS)** - High-speed digital (900 MHz / 2.4 GHz)
- **TBS Crossfire** - Long-range (868/915 MHz)
- **Generic PPM/PWM** - Standard RC protocols
- **DSM2/DSMX** - Spektrum protocols

#### Recall Features:
- Signal capture from YOUR transmitter
- Signal analysis and protocol identification
- Replay configuration for YOUR drone
- Return-to-home (RTH) command templates
- Failsafe trigger configurations
- Emergency recall sequences
- Range testing tools
- Safe testing modes (reduced power)

## Directory Structure

```
HACKRF_PORTAPACK/
├── README.md (this file)
├── DETECTION_GUIDE.md
├── PERSONAL_RECALL_SETUP.md
├── LEGAL.md
├── QUICK_START.md
└── SDCARD/
    ├── FREQMAN/
    │   ├── DRONE_SCAN_433.TXT        # 433 MHz RC scanning
    │   ├── DRONE_SCAN_915.TXT        # 915 MHz RC/telemetry scanning
    │   ├── DRONE_SCAN_1G2.TXT        # 1.2 GHz FPV scanning
    │   ├── DRONE_SCAN_2G4.TXT        # 2.4 GHz control scanning
    │   ├── DRONE_SCAN_5G8.TXT        # 5.8 GHz FPV scanning
    │   ├── DRONE_SCAN_GPS.TXT        # GPS L1 monitoring
    │   ├── DRONE_SCAN_ALL.TXT        # Multi-band quick scan
    │   ├── PERSONAL_FRSKY_D16.TXT    # FrSky template
    │   ├── PERSONAL_FLYSKY.TXT       # FlySky template
    │   ├── PERSONAL_ELRS.TXT         # ELRS template
    │   └── PERSONAL_CROSSFIRE.TXT    # Crossfire template
    ├── SETTINGS/
    │   ├── drone_detect_config.txt   # Detection configuration
    │   ├── alert_settings.txt        # Alert configuration
    │   └── personal_recall_template.txt  # Recall template config
    ├── CAPTURES/
    │   └── README_CAPTURES.TXT       # Capture instructions
    └── REPLAYS/
        └── README_REPLAYS.TXT        # Replay instructions
```

## Safety Features

### Detection Mode Safety:
- Passive reception only (no transmission)
- Configurable RSSI thresholds
- Battery monitoring
- Thermal management tips
- Power-saving modes

### Transmission Mode Safety (Personal Recall):
- Mandatory confirmation before transmit
- Automatic transmission timeout
- Maximum duration limits
- Safe test mode (reduced power)
- Emergency stop capability
- Requires explicit user configuration

## Documentation

### Quick Reference:
- **QUICK_START.md** - 5-minute setup guide
- **README.md** (this file) - Overview and features

### Detection System:
- **DETECTION_GUIDE.md** - Complete drone detection guide
  - Scanner configuration
  - RSSI interpretation
  - Alert setup
  - Logging and analysis
  - Battery-efficient operation
  - Multi-band strategies

### Personal Recall System:
- **PERSONAL_RECALL_SETUP.md** - Personal drone recall setup
  - Signal capture procedures
  - Protocol identification
  - Creating replay files
  - Protocol-specific guides
  - Testing procedures
  - Troubleshooting

### Legal & Safety:
- **LEGAL.md** - Complete legal information
  - FCC Part 15 compliance
  - International regulations
  - Legal vs illegal use
  - Safety warnings
  - Liability disclaimer

## Common Use Cases

### 1. Drone Detection at Event/Property
✅ **Legal** - Passive monitoring only
- Load `DRONE_SCAN_ALL.TXT`
- Set RSSI threshold
- Enable audio alerts
- Monitor for activity
- Log detections for records

### 2. FPV Frequency Coordination
✅ **Legal** - Receive-only scanning
- Load `DRONE_SCAN_5G8.TXT`
- Identify occupied channels
- Find clear frequency for your use
- Coordinate with other pilots

### 3. Personal Drone Emergency Recall
⚠️ **Legal ONLY for YOUR drone**
- Pre-capture YOUR drone's signals
- Create tested replay file
- Emergency: Load replay file
- Transmit RTH command to YOUR drone
- Monitor drone response

### 4. RC Equipment Testing
✅ **Legal** - YOUR equipment testing
- Capture YOUR transmitter output
- Analyze frequency accuracy
- Check signal strength
- Verify failsafe behavior

## Troubleshooting

### No Signals Detected
- Check antenna connection
- Verify correct frequency file loaded
- Lower RSSI threshold (-80 or -90 dBm)
- Increase RF/IF/BB gain settings
- Ensure drone activity in area

### SD Card Not Reading
- Verify FAT32 format
- Check card compatibility (Class 10 recommended)
- Try different microSD card
- Ensure proper directory structure

### Weak Signal Strength
- Use appropriate antenna for frequency
- Check antenna connection
- Increase gain settings
- Get closer to signal source
- Check for interference

### HackRF Not Detected
- Check USB cable connection
- Verify PortaPack is properly seated
- Update HackRF firmware
- Try different USB port/cable
- Check battery power level

### Replay Not Working (Personal Recall)
- Verify capture quality
- Check frequency accuracy
- Ensure correct sample rate
- Test with increased TX gain (verify legal limits!)
- Recapture signal with better parameters
- Verify drone is in range and powered

## Battery Life Tips

HackRF One is power-hungry. To maximize battery:
- Use high-capacity external battery (10,000+ mAh)
- Enable battery saver mode in settings
- Reduce screen brightness
- Disable waterfall when not needed
- Use narrower scan ranges
- Power off when not in use
- Monitor thermal levels

## Antenna Selection Guide

| Frequency | Antenna Type | Connector | Notes |
|-----------|--------------|-----------|-------|
| 433 MHz | UHF stub/whip | SMA | 17.3 cm quarter-wave |
| 915 MHz | UHF stub/whip | SMA | 8.2 cm quarter-wave |
| 1.2 GHz | Dipole/patch | SMA | Directional for FPV |
| 2.4 GHz | WiFi rubber duck | SMA/RP-SMA | Common, effective |
| 5.8 GHz | FPV pagoda/patch | SMA/RP-SMA | Circular polarized |

**Multi-band antennas** (e.g., discone, wideband) work but with reduced performance.

## Advanced Features

### Signal Analysis:
- FFT spectrum analyzer
- Waterfall display
- Signal demodulation
- Protocol decoding helpers
- Timing analysis
- Modulation identification

### Custom Configurations:
- Create custom frequency lists
- Define custom protocols
- Set up automated scanning sequences
- Configure complex alerting rules
- Develop detection profiles

## Integration with ultimatel-ily Project

This HackRF/PortaPack package complements the main ultimatel-ily firmware project:

- **Main Project**: CC1101-based drone control (different hardware)
- **This Package**: HackRF-based detection and analysis (this hardware)
- **Relationship**: Both educational tools for drone RF systems
- **Cross-Reference**: Similar frequencies, different implementations

See main [ultimatel-ily README](../README.md) for CC1101 firmware details.

## FAQ

**Q: Can I use this to take down drones I don't own?**
A: **NO. That is ILLEGAL.** This package is for detection (legal) and controlling YOUR OWN drones only.

**Q: Is drone detection legal?**
A: **YES.** Receiving/monitoring radio signals is always legal. You're just listening, not transmitting.

**Q: What range can I expect for detection?**
A: Depends on many factors: antenna quality, frequency, drone power, environment. Typically:
- Strong signals: 1-2 km
- Weak signals: 100-500 m
- With directional antenna: 2-5 km+

**Q: Will this work with DJI drones?**
A: **Detection: YES** - Can detect DJI signals at 2.4/5.8 GHz
**Personal Recall: COMPLEX** - DJI uses encrypted protocols, very difficult to replay

**Q: Can I add my own frequencies?**
A: **YES!** Edit the .TXT files in FREQMAN directory following the format:
```
f=<frequency_hz>,m=<modulation>,bw=<bandwidth>,d=<description>
```

**Q: Is this package legal to download/possess?**
A: **YES.** Possessing this software/hardware is legal. Only MISUSE is illegal.

**Q: What about flying in restricted airspace?**
A: This package doesn't help with that. YOU are responsible for:
- Checking airspace restrictions
- Following FAA/local regulations
- Registering drones if required
- Obtaining necessary permissions

**Q: Can I sell this package or services using it?**
A: Check your local regulations. Generally:
- Selling educational packages: Usually OK
- Offering "drone defeat" services: Likely ILLEGAL
- RF testing services: May require FCC/local licenses

**Q: How do I report illegal drone activity?**
A: Contact:
- Local law enforcement
- FAA (in USA): 1-866-TELL-FAA
- Local aviation authority (other countries)
- Do NOT attempt to interfere yourself

## Contributing

Contributions welcome! Please ensure:
- Legal compliance in all examples
- Clear documentation
- Tested configurations
- Proper attribution
- Safety warnings where appropriate

## License

This educational package is provided as-is for legal use only.

See LEGAL.md for complete terms and conditions.

## Support

For issues, questions, or contributions:
- GitHub Issues: [ultimatel-ily repository](https://github.com/Crashkeyz/ultimatel-ily)
- Documentation: See included .md files
- Community: HackRF and PortaPack user forums

## Credits

- HackRF One hardware: Great Scott Gadgets
- PortaPack project: Jared Boone, Furrtek, Erwin Ried
- Frequency data: Community contributed
- Protocol information: Open source communities

## Version

Package Version: 1.0.0
Last Updated: 2024
Compatible: PortaPack Mayhem firmware

---

## Final Reminder

🛑 **RESPECT THE LAW** 🛑

This toolkit is powerful and educational. Use it responsibly:
- Detection: Always legal, go ahead!
- Transmission: Only to YOUR equipment, verify legal compliance
- Report suspicious drone activity to authorities
- Never interfere with others' equipment
- Be a responsible member of the RF community

**When in doubt, don't transmit. Detection alone is powerful and legal.**

---

**Next Steps:**
1. Read LEGAL.md thoroughly
2. Follow QUICK_START.md for setup
3. Try detection mode (safe and legal)
4. If needed, carefully follow PERSONAL_RECALL_SETUP.md
5. Always prioritize safety and legality

Happy (legal) drone monitoring! 🚁📡

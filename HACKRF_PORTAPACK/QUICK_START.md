# Quick Start Guide - HackRF PortaPack Drone Detection System

## ⚠️ 5-Second Legal Notice
**Detection = Legal ✅ | Jamming Others = Illegal ❌**
Use only for monitoring or YOUR OWN equipment.

---

## What You'll Need (5 minutes to gather)

✓ HackRF One with PortaPack H4M  
✓ MicroSD card (8GB+, FAT32 formatted)  
✓ Appropriate antenna(s) for target frequencies  
✓ USB cable or battery pack  
✓ Computer (for initial SD card setup)

---

## Setup Process

### Step 1: Format SD Card (2 minutes)

**Windows:**
```
1. Insert SD card
2. Right-click drive → Format
3. Choose: FAT32, Default allocation size
4. Click Start
```

**Mac:**
```
1. Insert SD card
2. Open Disk Utility
3. Select card → Erase
4. Format: MS-DOS (FAT)
5. Click Erase
```

**Linux:**
```bash
# Find device (usually /dev/sdX)
lsblk

# Format (replace sdX with your device)
sudo mkfs.vfat -F 32 /dev/sdX1
```

### Step 2: Copy Files to SD Card (1 minute)

```
1. Download/locate the HACKRF_PORTAPACK package
2. Copy entire SDCARD directory contents to SD card root
3. Verify structure:
   
   SD_CARD/
   ├── FREQMAN/
   ├── SETTINGS/
   ├── CAPTURES/
   └── REPLAYS/
   
4. Safely eject SD card
```

### Step 3: Install in PortaPack (1 minute)

```
1. Power OFF HackRF/PortaPack completely
2. Insert SD card into PortaPack slot (push until click)
3. Connect antenna for target frequency
4. Power ON device
5. Wait for boot (10-15 seconds)
```

### Step 4: Verify Installation (<1 minute)

```
1. From main menu, navigate to: Apps → File Manager
2. You should see: FREQMAN, SETTINGS, CAPTURES, REPLAYS folders
3. If not visible: reinsert SD card or reformat
```

---

## First Use: Drone Detection (5 minutes)

### Basic Detection Mode (100% Legal)

**Goal:** Detect if drones are active nearby

1. **Select Frequency Scanner:**
   - Main Menu → **"Receiver"** → **"Freqman"**
   - Or: Main Menu → **"Scanner"** (depends on firmware version)

2. **Choose Frequency File:**
   - First time: Select **`DRONE_SCAN_ALL.TXT`** (covers all bands)
   - For specific use:
     - `DRONE_SCAN_2G4.TXT` - Consumer drones (DJI, etc.)
     - `DRONE_SCAN_5G8.TXT` - FPV racing drones
     - `DRONE_SCAN_433.TXT` - RC toys, basic drones

3. **Configure Scanner:**
   - RSSI Threshold: **-70 dBm** (good starting point)
   - Squelch: **Enabled**
   - Audio Alert: **On** (you'll hear beeps when signals found)

4. **Set Gains:**
   - RF Gain: **14 dB** (increase if no signals detected)
   - IF Gain: **40 dB**
   - Baseband Gain: **32 dB**
   
5. **Start Scanning:**
   - Press **START** or **SELECT**
   - Watch display for signal activity
   - Listen for audio alerts

**What You'll See:**
- Frequency currently being scanned
- RSSI value (signal strength in dBm)
- Bar graph showing signal level
- Screen flash when signal detected
- Audio beep when signal crosses threshold

**What the Numbers Mean:**
- **-90 to -80 dBm**: Very weak signal, far away
- **-80 to -60 dBm**: Moderate signal, medium distance
- **-60 to -40 dBm**: Strong signal, nearby
- **-40 dBm and above**: Very strong signal, very close

---

## Testing Your Setup (2 minutes)

### Test with Known Signal

**Easy Test - Use Your Phone:**

1. Load **`DRONE_SCAN_2G4.TXT`** (WiFi/Bluetooth)
2. Start scanning
3. Enable WiFi hotspot on your phone
4. You should immediately detect signals at 2.4 GHz
5. HackRF should beep and show activity

**This confirms:**
✓ SD card is reading correctly  
✓ Antenna is connected  
✓ Scanner is working  
✓ Alerts are functional

### If No Signals Detected:

**Troubleshooting (in order):**
1. Check antenna is screwed on tight
2. Lower RSSI threshold to **-90 dBm**
3. Increase **RF Gain** to **30 dB**
4. Verify SD card file structure
5. Try different frequency file
6. Ensure antenna matches frequency (2.4 GHz antenna for 2.4 GHz signals)

---

## Common Button Mappings

**PortaPack H4M Controls:**
- **Encoder Wheel**: Navigate menus, adjust values
- **Encoder Press**: Select/confirm
- **Left Button**: Back/cancel
- **Right Button**: Options/menu
- **Up/Down**: Scroll (on some screens)

**In Scanner Mode:**
- **Encoder Wheel**: Adjust RSSI threshold
- **Left Button**: Pause/resume scanning
- **Right Button**: Access settings
- **Press Encoder**: Manual frequency entry

---

## Quick Command Reference

### Switch Between Modes:

**Detection → Analysis:**
1. Stop scanner
2. Return to main menu
3. Select **"Spectrum Analyzer"**
4. Enter frequency of interest

**Detection → Capture:**
1. Stop scanner
2. Go to **"Capture"** app
3. Set frequency
4. Press **Record** to capture

### Save a Detection Event:

1. When signal detected, note frequency
2. Go to main menu → **"File Manager"**
3. Navigate to **CAPTURES**
4. Note time and frequency in a log (manual for now)

---

## Safety Checklist

Before ANY transmission (personal recall ONLY):

- [ ] Read **LEGAL.md** completely
- [ ] Read **PERSONAL_RECALL_SETUP.md** completely
- [ ] This is MY drone that I personally own
- [ ] I have captured MY drone's signals
- [ ] I am in a safe, open area
- [ ] No other drones are nearby
- [ ] I have verified legal compliance
- [ ] I have a backup control method ready

**If ANY checkbox is unchecked, do NOT transmit.**

---

## Monitoring Scenarios

### Scenario 1: Home/Property Security
**Goal:** Detect drones near your property

```
1. Load: DRONE_SCAN_ALL.TXT
2. Set threshold: -70 dBm
3. Enable audio alerts
4. Position HackRF with clear view
5. Monitor periodically or continuously
6. Log any detections with timestamp
```

**Battery Life:** ~2-3 hours on 10,000 mAh power bank

### Scenario 2: Event Monitoring
**Goal:** Know if drones active at outdoor event

```
1. Load: DRONE_SCAN_2G4.TXT (most consumer drones)
2. Add: DRONE_SCAN_5G8.TXT scan after
3. Set threshold: -60 dBm (nearby drones only)
4. Enable visual alerts (discrete)
5. Carry HackRF, monitor periodically
```

**Battery Life:** ~1-2 hours active scanning

### Scenario 3: FPV Racing Coordination
**Goal:** Find free 5.8 GHz channel for FPV

```
1. Load: DRONE_SCAN_5G8.TXT
2. Set threshold: -75 dBm
3. Scan all channels
4. Identify occupied channels
5. Choose free channel for your use
6. Coordinate with other pilots
```

**Time:** 2-5 minutes per scan cycle

### Scenario 4: RF Learning
**Goal:** Understand drone RF protocols

```
1. Use YOUR drone/transmitter
2. Load appropriate frequency file
3. Power on transmitter
4. Observe signals in scanner
5. Note: frequency, strength, pattern
6. Switch to spectrum analyzer for detail
7. Capture signals for later analysis
```

**Educational Value:** High - learn real RF behavior

---

## Power Management

### Battery Life Estimates:

| Mode | Power Draw | 10,000 mAh Runtime |
|------|------------|-------------------|
| Scanning (screen on) | ~1.5W | 2-3 hours |
| Scanning (screen dim) | ~1.2W | 3-4 hours |
| Idle/menu | ~0.8W | 5-6 hours |
| Transmitting | ~2-3W | 1-2 hours |

### Extending Battery Life:

1. **Dim screen**: Settings → Display → Brightness → 25%
2. **Enable battery saver**: Settings → Power → Battery Saver
3. **Reduce scan speed**: Slower scan = less power
4. **Narrower frequency range**: Scan fewer channels
5. **Power off between uses**: Don't leave in idle
6. **Use efficient antennas**: Better signal = lower gain needed

---

## Emergency Procedures

### HackRF Overheating:
```
1. Power off immediately
2. Remove from case if enclosed
3. Allow to cool (5-10 minutes)
4. Reduce gain settings before restart
5. Ensure adequate ventilation
```

### Unexpected Behavior:
```
1. Press left button repeatedly (back to menu)
2. Power cycle device
3. Remove and reinsert SD card
4. Verify file integrity
5. Re-copy files if needed
```

### Lost Connection:
```
1. Check USB cable firmly connected
2. Try different USB port
3. Check battery charge level
4. Verify HackRF LED is on
5. Power cycle PortaPack
```

---

## Next Steps

### After You're Comfortable with Detection:

1. **Read Full Documentation:**
   - [DETECTION_GUIDE.md](DETECTION_GUIDE.md) - Deep dive into detection
   - [LEGAL.md](LEGAL.md) - Complete legal information

2. **Experiment with Settings:**
   - Try different frequency files
   - Adjust RSSI thresholds
   - Compare gain settings
   - Use spectrum analyzer mode

3. **Learn Signal Analysis:**
   - Capture signals from known sources
   - Analyze modulation types
   - Study protocol characteristics
   - Build understanding of RF behavior

4. **Only If Needed - Personal Recall:**
   - Read [PERSONAL_RECALL_SETUP.md](PERSONAL_RECALL_SETUP.md) completely
   - Only for YOUR drones
   - Follow all safety procedures
   - Test thoroughly in safe environment

---

## Quick Troubleshooting

| Problem | Quick Fix |
|---------|----------|
| No signals detected | Lower threshold to -90 dBm, increase RF gain |
| Too many false alerts | Raise threshold to -60 dBm, reduce gain |
| Scanner won't start | Check SD card inserted, verify file format |
| Screen frozen | Power cycle device |
| Battery drains fast | Dim screen, reduce scan range |
| Can't see SD files | Reformat as FAT32, copy files again |
| Weak signals | Check antenna, increase gain, get closer |
| No audio alerts | Check settings → audio → enable |

---

## Common Mistakes to Avoid

❌ **Wrong antenna for frequency**
✅ Use 2.4 GHz antenna for 2.4 GHz signals, etc.

❌ **Threshold too high**
✅ Start with -70 dBm, adjust based on results

❌ **SD card wrong format**
✅ Must be FAT32, not exFAT or NTFS

❌ **Files in wrong location**
✅ FREQMAN files must be in /FREQMAN/ folder

❌ **Expecting instant results**
✅ May take time to detect activity, be patient

❌ **Ignoring battery level**
✅ HackRF drains batteries fast, monitor level

❌ **Using on others' drones**
✅ ONLY for detection (legal) or YOUR equipment

---

## Getting Help

**Built-in Help:**
- Many apps have "?" or "Help" button
- Press and hold encoder for context help (some screens)

**Documentation:**
- Full guides in HACKRF_PORTAPACK directory
- README.md for overview
- Specific guides for each function

**Community Resources:**
- HackRF mailing list
- PortaPack GitHub discussions
- Reddit: r/hackrf, r/RTLSDR
- Discord: Various SDR communities

**Report Issues:**
- GitHub: ultimatel-ily repository
- Include: firmware version, what you tried, error messages

---

## Success Checklist

After this quick start, you should be able to:

- [ ] Format and prepare SD card
- [ ] Install files in correct structure
- [ ] Boot PortaPack with SD card
- [ ] Navigate to Freqman/Scanner mode
- [ ] Load a frequency file
- [ ] Start scanning
- [ ] Detect signals (tested with phone WiFi)
- [ ] Understand RSSI readings
- [ ] Adjust gain settings
- [ ] Use spectrum analyzer
- [ ] Navigate back to main menu

**If all checked: Congratulations! You're ready to explore more features.**

**If some unchecked: Review relevant sections above or see full documentation.**

---

## Time Investment Summary

- **Setup**: 5-10 minutes (one-time)
- **Learning basics**: 15-30 minutes
- **Comfortable detection**: 1-2 hours practice
- **Advanced features**: Ongoing learning
- **Personal recall**: Several hours + testing (if needed)

---

## Final Quick Tips

💡 **Start simple**: Use DRONE_SCAN_ALL.TXT first  
💡 **Test with known signals**: Your phone's WiFi hotspot  
💡 **Be patient**: Signal detection takes time  
💡 **Stay legal**: Detection is always OK, transmission only for YOUR equipment  
💡 **Read docs**: Full guides have much more detail  
💡 **Practice**: The more you use it, the better you'll understand  
💡 **Stay safe**: RF can be powerful, use responsibly  

---

**You're ready to start! Power on, load a frequency file, and begin monitoring.** 

**For detailed information, proceed to [DETECTION_GUIDE.md](DETECTION_GUIDE.md)**

**Remember: Detection = Always Legal ✅ | Have Fun! 📡🚁**

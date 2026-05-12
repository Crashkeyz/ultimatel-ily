# Comprehensive Drone Detection Guide

## Table of Contents
1. [Introduction](#introduction)
2. [Legal Status](#legal-status)
3. [Hardware Setup](#hardware-setup)
4. [Basic Detection](#basic-detection)
5. [Advanced Scanning](#advanced-scanning)
6. [RSSI Interpretation](#rssi-interpretation)
7. [Alert Configuration](#alert-configuration)
8. [Signal Analysis](#signal-analysis)
9. [Logging and Documentation](#logging-and-documentation)
10. [Multi-Band Strategies](#multi-band-strategies)
11. [Battery Optimization](#battery-optimization)
12. [Troubleshooting](#troubleshooting)

---

## Introduction

Drone detection using HackRF One and PortaPack H4M is 100% legal as it involves passive monitoring only - you're receiving signals, not transmitting. This guide covers everything from basic detection to advanced signal analysis.

### What You Can Detect:
- RC control signals (433/915 MHz, 2.4 GHz)
- FPV video downlinks (1.2 GHz, 5.8 GHz)
- Telemetry data streams
- GPS signals (monitoring only)
- WiFi-based drone control
- Digital drone protocols

### Detection Range:
Highly variable based on:
- **Antenna quality**: Better antenna = longer range
- **Frequency band**: Lower frequencies travel farther
- **Drone transmit power**: DJI @ 2.4 GHz stronger than toys
- **Environment**: Open field vs urban canyon
- **Interference**: Clean RF environment vs noisy
- **Gain settings**: Higher gain = better sensitivity

**Typical Ranges:**
- Consumer drones (DJI, etc.): 500m - 2km
- FPV racing drones: 300m - 1.5km
- Toy drones: 100m - 500m
- With directional antenna: 2x - 5x improvement

---

## Legal Status

### ✅ LEGAL: Receive-Only Monitoring

**You CAN legally:**
- Monitor any frequency (public airwaves)
- Record signal characteristics
- Analyze protocols
- Log drone activity
- Share technical findings
- Use for security awareness
- Educational purposes

**This is protected by:**
- First Amendment (USA) - Information gathering
- FCC Part 15 - General receiving not regulated
- Similar laws internationally

### ❌ What You CANNOT Do:

- Jam or interfere with signals
- Transmit on unauthorized frequencies
- Control drones you don't own
- Use information for criminal purposes
- Violate privacy laws with captured data

---

## Hardware Setup

### Antenna Selection

Different frequencies require different antennas for optimal detection:

#### 433 MHz Band:
- **Type**: UHF quarter-wave whip or dipole
- **Length**: ~17.3 cm for quarter-wave
- **Connector**: SMA male
- **Gain**: 2-5 dBi typical
- **Recommendation**: Generic 433 MHz antenna or build dipole

#### 915 MHz Band:
- **Type**: UHF quarter-wave whip
- **Length**: ~8.2 cm for quarter-wave
- **Connector**: SMA male
- **Gain**: 2-5 dBi
- **Recommendation**: 900 MHz ISM antenna

#### 1.2 GHz Band:
- **Type**: Dipole or patch antenna
- **Polarization**: Horizontal or circular
- **Gain**: 5-10 dBi
- **Recommendation**: 1.2 GHz FPV patch antenna

#### 2.4 GHz Band:
- **Type**: Rubber duck, dipole, or patch
- **Polarization**: Vertical (most common)
- **Gain**: 2-5 dBi
- **Recommendation**: WiFi antenna (very common and cheap)

#### 5.8 GHz Band:
- **Type**: Patch, pagoda, or cloverleaf
- **Polarization**: Circular (RHCP for most FPV)
- **Gain**: 3-8 dBi
- **Recommendation**: FPV pagoda or 5.8 GHz patch

#### Multi-Band Option:
- **Type**: Discone or wideband antenna
- **Coverage**: 25 MHz - 1.3 GHz (typical)
- **Gain**: Lower than dedicated antennas
- **Use Case**: Quick scanning without antenna changes
- **Trade-off**: Reduced sensitivity on all bands

### Physical Setup

**Positioning:**
1. **Height**: Higher is better (reduce ground clutter)
2. **Clear line of sight**: Minimize obstructions
3. **Away from interference**: Distance from WiFi routers, etc.
4. **Stable mounting**: Tripod or secure position
5. **Antenna orientation**: Vertical for most (match drone's polarization)

**Power:**
- Use quality USB cable (power loss in cheap cables)
- External battery: 10,000+ mAh recommended
- USB power supply: 2A minimum
- Monitor battery level regularly

---

## Basic Detection

### Method 1: Quick Scan (All Bands)

**Best for:** Rapid check if any drone activity present

```
1. Navigate to: Receiver → Freqman
2. Select: DRONE_SCAN_ALL.TXT
3. Settings:
   - RSSI Threshold: -70 dBm
   - Audio Alert: ON
   - Scan Speed: Medium
4. Gains:
   - RF: 14 dB
   - IF: 40 dB
   - BB: 32 dB
5. Start scanning
```

**Expected results in 5-10 minutes:**
- If drones present: Multiple alerts, consistent signals
- If no drones: Occasional false triggers from WiFi, etc.

### Method 2: Specific Band Scan

**Best for:** Focused detection of specific drone types

**Consumer Drones (DJI, etc.):**
```
File: DRONE_SCAN_2G4.TXT
Threshold: -65 dBm (strong signal expected)
Notes: Also catches WiFi - ignore home networks
```

**FPV Racing Drones:**
```
File: DRONE_SCAN_5G8.TXT
Threshold: -70 dBm
Notes: Video downlink, very characteristic
```

**Long-Range RC:**
```
File: DRONE_SCAN_915.TXT or DRONE_SCAN_433.TXT
Threshold: -75 dBm
Notes: Weaker signals, need more sensitivity
```

### Method 3: Continuous Monitoring

**Best for:** Security, event monitoring, long-term observation

```
1. Choose appropriate band(s)
2. Set conservative threshold: -75 dBm
3. Enable logging (if available)
4. Reduce screen brightness (battery saving)
5. Let run continuously
6. Check periodically for alerts
```

---

## Advanced Scanning

### Optimizing Scan Speed

**Fast Scan (50ms per channel):**
- Pros: Cover band quickly, good for mobile use
- Cons: Might miss brief signals
- Use: When walking/moving, quick checks

**Medium Scan (100-200ms per channel):**
- Pros: Balance of speed and sensitivity
- Cons: Takes longer to cycle through
- Use: General purpose, default recommendation

**Slow Scan (500ms+ per channel):**
- Pros: Catch brief signals, better sensitivity
- Cons: Slow to cover full band
- Use: Stationary monitoring, maximizing detection

### Gain Settings Deep Dive

HackRF has three gain stages:

#### RF Gain (0-14 dB)
- **Controls**: Front-end amplifier
- **Effect**: First-stage amplification
- **Recommendation**: Start at 14 dB, reduce if signals too strong
- **Note**: Most critical for weak signals

#### IF Gain (0-40 dB)
- **Controls**: Intermediate frequency amplifier
- **Effect**: Main amplification stage
- **Recommendation**: 32-40 dB for detection
- **Note**: Can increase for distant signals

#### Baseband Gain (0-62 dB)
- **Controls**: Final amplification before ADC
- **Effect**: Fine-tuning sensitivity
- **Recommendation**: 20-40 dB typically
- **Note**: High values increase noise floor

**Optimal Settings by Scenario:**

| Scenario | RF | IF | BB | Notes |
|----------|----|----|-----|-------|
| Close range (0-100m) | 0 | 20 | 20 | Prevent overload |
| Medium range (100-500m) | 14 | 32 | 32 | Balanced |
| Long range (500m+) | 14 | 40 | 40 | Maximum sensitivity |
| Urban/noisy | 8 | 32 | 24 | Reduce noise |
| Rural/quiet | 14 | 40 | 36 | Maximize sensitivity |

### Frequency Hopping Detection

Many modern drones use frequency hopping (e.g., FrSky, Crossfire, ELRS):

**Characteristics:**
- Rapid switching between channels
- Brief signal bursts (ms)
- Repeating pattern
- Multiple frequencies in sequence

**Detection Strategy:**
1. Slow down scan speed (catch brief signals)
2. Use wider bandwidth setting
3. Monitor multiple frequencies in range
4. Look for pattern in spectrum analyzer
5. Note: Will see multiple frequencies active

**Example: FrSky D16**
- Hops across 47 channels in 2.4 GHz
- ~9ms per hop
- Repeating sequence
- You'll see bursts on multiple channels

### Directional Finding

**With Standard Omni Antenna:**
- Walk in different directions
- Note signal strength changes
- Stronger = closer to that direction
- Crude but effective for general direction

**With Directional Antenna:**
- Rotate antenna (yagi, patch, etc.)
- Note maximum signal direction
- Take bearings from multiple locations
- Triangulate drone position
- Much more accurate (5-15° accuracy possible)

**Procedure:**
1. Detect drone signal
2. Note frequency
3. Switch to directional antenna
4. Rotate for maximum signal
5. Mark bearing/direction
6. Move to new location (100m+)
7. Repeat bearing measurement
8. Plot lines on map - intersection = drone location

---

## RSSI Interpretation

### Understanding RSSI Values

**RSSI = Received Signal Strength Indicator**
- Measured in dBm (decibels relative to 1 milliwatt)
- Negative values (e.g., -70 dBm)
- More negative = weaker signal
- Less negative = stronger signal

### RSSI Scale

```
 -40 dBm |████████████| VERY STRONG - Drone very close (0-20m)
         |             | Possibly on ground near you
         |
 -50 dBm |██████████  | STRONG - Drone nearby (20-100m)
         |             | Clear detection, good tracking
         |
 -60 dBm |████████    | GOOD - Medium distance (100-300m)
         |             | Reliable detection
         |
 -70 dBm |██████      | MODERATE - Far but detectable (300-1000m)
         |             | Good threshold for alerts
         |
 -80 dBm |████        | WEAK - Long range or low power (1000m+)
         |             | May be toy drone nearby or DJI far away
         |
 -90 dBm |██          | VERY WEAK - Extreme range or obstructed
         |             | Borderline detection, many false positives
         |
-100 dBm |            | NOISE FLOOR - Not a real signal
         |             | Just background RF noise
```

### Signal Strength Patterns

**Steady Strong Signal:**
- Likely hovering drone
- Or slowly moving
- Or ground-based control station

**Slowly Varying Signal:**
- Drone moving toward/away from you
- Normal flight pattern
- Track changes to estimate movement

**Rapidly Fluctuating:**
- Frequency hopping system
- Moving through obstruction
- Multipath fading
- Fast-moving drone

**Bursts/Intermittent:**
- Telemetry data (periodic)
- Frequency hopping (caught in scan)
- Drone far away (borderline range)
- Possible false positive

### Distance Estimation

**Very rough guide** (many variables affect this):

| RSSI | Distance (2.4 GHz consumer) | Distance (5.8 GHz FPV) |
|------|----------------------------|----------------------|
| -40 dBm | 0-20m | 0-10m |
| -50 dBm | 20-100m | 10-50m |
| -60 dBm | 100-300m | 50-200m |
| -70 dBm | 300-1000m | 200-500m |
| -80 dBm | 1000m+ | 500m+ |

**Variables that affect distance:**
- Drone transmit power
- Antenna gains (both sides)
- Obstructions (buildings, trees)
- Weather (rain attenuates)
- Frequency (lower travels farther)

---

## Alert Configuration

### Audio Alerts

**Configure in:** SETTINGS/alert_settings.txt

**Alert Tone Strategy:**

**Different tones for different bands:**
```
433 MHz: 800 Hz (low tone)
915 MHz: 1000 Hz (medium-low)
2.4 GHz: 1400 Hz (medium-high)
5.8 GHz: 1600 Hz (high tone)
GPS: 1800 Hz (very high, urgent)
```

**Why:** Instantly recognize which band detected without looking

**Alert Duration:**
- Short (100ms): Brief notification
- Medium (200ms): Standard (recommended)
- Long (500ms): Ensure you don't miss it

**Volume:**
- 50%: Indoor, close monitoring
- 75%: Outdoor, ambient noise (recommended)
- 100%: Noisy environment, maximum alert

### Visual Alerts

**LED/Screen Flash:**
- Red: High-priority detection (2.4/5.8 GHz)
- Yellow: Medium priority (1.2 GHz)
- Green: Low priority (433/915 MHz)
- Flashing: Active signal
- Solid: Signal locked

**On-Screen Information:**
- Display frequency detected
- Show RSSI value
- Show signal duration
- Time stamp
- Band/channel identifier

### Alert Conditions

**Threshold Settings:**

**Conservative (fewer false positives):**
```
RSSI Threshold: -60 dBm
Minimum Duration: 200ms
Cooldown: 5 seconds
```

**Balanced (recommended):**
```
RSSI Threshold: -70 dBm
Minimum Duration: 100ms
Cooldown: 2 seconds
```

**Aggressive (maximum sensitivity):**
```
RSSI Threshold: -80 dBm
Minimum Duration: 50ms
Cooldown: 1 second
```

**Pattern Matching:**
- Look for repeating signals
- Filter out one-off noise spikes
- Confirm with multiple detections
- Reduces false positives significantly

---

## Signal Analysis

### Using Spectrum Analyzer

After detecting a signal, analyze it:

```
1. Note frequency from scanner
2. Stop scanner
3. Go to: Spectrum Analyzer
4. Enter frequency (or range)
5. Set appropriate bandwidth
6. Observe signal characteristics
```

**What to Look For:**

**Continuous Carrier:**
- Steady tone
- Likely analog video or simple RC
- Common in 5.8 GHz FPV

**Bursting Signal:**
- Periodic pulses
- Digital telemetry or control
- Note burst rate and pattern

**Wideband Noise:**
- Spread across wide frequency range
- Digital spread-spectrum (ELRS, Crossfire)
- Or LoRa-based systems

**Multiple Carriers:**
- Frequency hopping visible
- Multiple simultaneous signals
- Multiple drones present

### Waterfall Display

**Enables:**
- Visual history of signal over time
- Identify patterns and timing
- See frequency hopping
- Differentiate signal types

**Colors indicate signal strength:**
- Blue/Black: Noise floor
- Green/Yellow: Moderate signal
- Orange/Red: Strong signal

**Patterns:**
- **Horizontal line**: Steady carrier (analog video)
- **Vertical bars**: Bursts (digital data)
- **Diagonal lines**: Frequency drift
- **Multiple bars**: Frequency hopping
- **Spread**: Wideband digital

### Modulation Identification

**AM (Amplitude Modulation):**
- Variable amplitude
- Common in older RC systems
- Simple detection

**FM (Frequency Modulation):**
- Constant amplitude, varies frequency
- Analog video links (1.2/5.8 GHz)
- Better noise immunity than AM

**GFSK (Gaussian FSK):**
- Digital modulation
- FrSky, FlySky protocols
- Smooth frequency transitions

**Spread Spectrum:**
- FHSS: Frequency Hopping (FrSky, Futaba)
- DSSS: Direct Sequence (some WiFi modes)
- Wide bandwidth, noise-like

**LoRa:**
- Chirp spread spectrum
- ELRS, Crossfire use this
- Distinctive "chirp" in waterfall
- Very long range

### Protocol Identification

**Clues to identify protocol:**

**FrSky D16/D8:**
- 2.4 GHz
- Frequency hopping (47 channels)
- ~9ms hop interval
- 1 MHz spacing

**FlySky AFHDS:**
- 2.4 GHz
- 16 channels
- ~5 MHz spacing
- Less complex hopping

**ExpressLRS:**
- 900 MHz or 2.4 GHz
- LoRa chirps in waterfall
- High packet rate (50-1000 Hz)
- Wideband

**Crossfire:**
- 868/915 MHz
- LoRa modulation
- Lower packet rate
- Very robust

**DJI:**
- 2.4 GHz and 5.8 GHz
- Proprietary protocols
- OcuSync: wideband, frequency agile
- Strong signals (high power)

**Analog Video:**
- 1.2 or 5.8 GHz
- FM modulation
- 6-8 MHz bandwidth
- Continuous carrier
- Sync pulses visible

---

## Logging and Documentation

### Manual Logging

Create log entries for detections:

```
Date/Time: 2024-12-26 14:35:22
Frequency: 2447 MHz
RSSI: -62 dBm
Duration: Continuous (5+ minutes)
Band: 2.4 GHz
Signal Type: Continuous, likely DJI
Location: [Your location]
Weather: Clear, light wind
Notes: Signal appeared suddenly, moved away gradually
```

### Automated Logging (if supported)

Some PortaPack versions support logging to CSV:

```
timestamp,frequency,rssi,duration,notes
2024-12-26T14:35:22,2447000000,-62,300,2.4G_continuous
2024-12-26T14:42:18,5843000000,-58,180,5.8G_FPV_video
```

### Data Analysis

**Look for patterns:**
- Time of day (when are drones active?)
- Day of week (weekends vs weekdays)
- Frequency bands used (consumer vs FPV)
- Signal strength trends (getting closer/farther)
- Duration (quick flyby vs loitering)

**Create detection profile:**
- Most common frequencies
- Typical signal strengths
- Peak activity times
- Common flight patterns

---

## Multi-Band Strategies

### Simultaneous Multi-Band

**Not possible with single HackRF** (can only tune one frequency at a time)

**But you can:**

**Sequential Scanning:**
1. Scan 2.4 GHz (most common) - 2 minutes
2. Quick scan 5.8 GHz - 1 minute
3. Quick scan 915 MHz - 1 minute
4. Back to 2.4 GHz
5. Repeat cycle

**Priority-Based:**
1. Start with DRONE_SCAN_ALL.TXT (hits all bands)
2. When detection, switch to specific band file
3. Monitor that band continuously
4. Resume all-band after signal lost

### Two-HackRF Setup

**If you have two HackRF devices:**

**HackRF #1:**
- Monitor 2.4 GHz (control)
- Continuous scanning
- Primary alert source

**HackRF #2:**
- Monitor 5.8 GHz (video)
- Continuous scanning
- Confirm detections

**Benefits:**
- True simultaneous multi-band
- Correlate control and video signals
- Better directional finding
- Redundancy

### Band Selection Strategy

**Choose based on your scenario:**

**General Security/Unknown Drones:**
- Start: DRONE_SCAN_ALL.TXT
- Reason: Don't know what to expect

**Consumer Drone Heavy Area:**
- Focus: 2.4 GHz (DRONE_SCAN_2G4.TXT)
- Reason: DJI and others use 2.4 GHz control

**FPV Racing Event:**
- Focus: 5.8 GHz (DRONE_SCAN_5G8.TXT)
- Reason: All FPV video here

**Rural Long-Range:**
- Check: 433/915 MHz first
- Then: 2.4 GHz
- Reason: Long-range systems use UHF

---

## Battery Optimization

### Power Consumption Breakdown

**HackRF One power usage:**
- Idle: ~0.5W
- Receiving: ~1.5W
- Transmitting: ~2.5W (not used in detection)
- PortaPack display: +0.3-0.5W

**Battery capacity vs runtime:**
- 10,000 mAh @ 5V = 50 Wh
- At 1.5W: ~33 hours theoretical
- Practical: ~20-25 hours (efficiency losses)

### Extending Battery Life

**Display Management:**
1. Reduce brightness: 25-50%
2. Disable waterfall (text mode only)
3. Shorter screen timeout
4. Black background (OLED screens)

**Scanning Optimization:**
1. Narrower frequency ranges
2. Slower scan rate (less processing)
3. Lower sample rates where possible
4. Disable logging (SD card writes)

**Gain Settings:**
1. Don't maximize unless needed
2. Lower gain = less power in amplifiers
3. Adjust based on actual signal strength
4. Start low, increase if needed

**Operational:**
1. Power off between monitoring sessions
2. Use airplane mode if PortaPack supports it
3. Pause scanning when not needed
4. Close unnecessary apps/features

**Battery Selection:**
- High-quality cells (Samsung, Panasonic)
- 2A+ output capability
- USB-C PD for fast charging
- 20,000+ mAh for all-day operation

### Battery Life Estimates

| Configuration | Runtime (10,000 mAh) |
|--------------|---------------------|
| Maximum power (bright screen, fast scan) | 2-3 hours |
| Standard operation | 4-6 hours |
| Optimized (dim screen, slow scan) | 8-12 hours |
| Minimal (pause between scans) | 15-20 hours |

---

## Troubleshooting

### No Signals Detected

**Checklist:**
1. ✓ Antenna connected and appropriate for frequency?
2. ✓ RSSI threshold not too high (-70 to -80 dBm)?
3. ✓ Gain settings adequate (RF: 14, IF: 40, BB: 32)?
4. ✓ Correct frequency file loaded?
5. ✓ Scanner actually running (not paused)?
6. ✓ Are drones actually present nearby?

**Tests:**
- Try scanning 2.4 GHz with phone WiFi hotspot on
- Should immediately detect WiFi signals
- If this works: Hardware OK, no drones nearby
- If this fails: Hardware/setup issue

### Too Many False Alerts

**Causes:**
- RSSI threshold too low (too sensitive)
- In RF-noisy environment (urban, near WiFi)
- Gain too high (amplifying noise)
- Wrong antenna (picking up everything)

**Solutions:**
1. Raise threshold: -60 dBm instead of -80
2. Reduce gain settings
3. Use narrower bandwidth
4. Enable pattern matching
5. Increase minimum duration
6. Add alert cooldown period

### Weak Signals Only

**Possible issues:**
- Antenna not matched to frequency
- Antenna not connected properly
- Gain settings too low
- Sample rate too low
- Interference/noise masking signals

**Solutions:**
1. Verify antenna: Right type? Tight connection?
2. Increase gains incrementally
3. Try different antenna orientation
4. Move to clearer RF environment
5. Check antenna SWR if possible

### Signal Detection Inconsistent

**Causes:**
- Drone frequency hopping (normal behavior)
- Drone at edge of range
- Obstructions blocking signal
- Interference from local sources
- Scan speed too fast

**Solutions:**
1. Slow down scan rate
2. Use narrower frequency range
3. Increase gain slightly
4. Note pattern: Periodic = likely frequency hopping
5. Switch to specific band, not all-band

### Device Overheating

**Symptoms:**
- HackRF/PortaPack hot to touch
- Performance degradation
- Unexpected shutdowns

**Solutions:**
1. Power off immediately if very hot
2. Remove from enclosure for better airflow
3. Reduce gain settings (less power)
4. Take breaks between scanning sessions
5. Add heatsinks to HackRF chips
6. Don't use in direct sunlight
7. Consider active cooling (small fan)

### SD Card Issues

**Problems:**
- Files not loading
- Can't save captures
- Corrupted data

**Solutions:**
1. Reformat as FAT32 (not exFAT or NTFS)
2. Use quality name-brand SD card
3. Class 10 or UHS-I rating
4. 8-32 GB size (don't oversize)
5. Check for fake/counterfeit cards
6. Try different SD card to isolate issue

### PortaPack Not Booting

**Checklist:**
1. HackRF powered? (LED on?)
2. PortaPack properly seated?
3. SD card inserted correctly?
4. Firmware compatible?
5. Battery charged?

**Recovery:**
1. Remove SD card, try boot
2. If boots: SD card or firmware issue
3. If doesn't boot: Hardware issue
4. Try different power source
5. Check USB cable quality
6. May need firmware reflash

---

## Advanced Topics

### Creating Custom Frequency Lists

Edit .TXT files in FREQMAN folder:

```
# Comment line
f=<frequency_hz>,m=<modulation>,bw=<bandwidth>,d=<description>

Example:
f=2450000000,m=AM,bw=1000000,d=Custom 2.45G
```

**Parameters:**
- `f=`: Frequency in Hz (e.g., 2450000000 = 2.45 GHz)
- `m=`: Modulation (AM, FM, WFM, NFM, USB, LSB)
- `bw=`: Bandwidth in Hz (e.g., 1000000 = 1 MHz)
- `d=`: Description (shown on screen)

### Integration with Other Tools

**Export data for analysis:**
- PortaPack captures → Import to GNU Radio
- RSSI logs → Excel/Python for plotting
- Waterfall screenshots → Image analysis

**Coordinate with:**
- FlightRadar24 (manned aircraft)
- Local drone registration databases
- ADS-B receivers (manned aircraft IFF)
- RF mapping software

### Building a Detection Station

**Fixed Installation:**
1. Permanent power supply
2. Multiple antennas (antenna switch)
3. Elevated mounting (roof, tower)
4. Weather protection
5. Remote access (VNC/SSH if supported)
6. Automated logging
7. Alert notifications (email, SMS)

**Requirements:**
- Dedicated HackRF/PortaPack
- Raspberry Pi or small computer (for automation)
- Network connectivity
- Power redundancy (UPS)

---

## Best Practices

### Detection Operations

**Do:**
- Document all detections
- Use appropriate equipment
- Respect others' privacy
- Report illegal drone activity to authorities
- Share technical findings with community
- Test equipment regularly

**Don't:**
- Interfere with detected drones (illegal!)
- Assume all signals are drones (verify)
- Ignore safety (terrain, weather)
- Use detection to facilitate illegal activity
- Share personal info about drone operators

### Equipment Care

- Store in dry environment
- Use protective case
- Keep antennas clean and undamaged
- Update firmware regularly
- Backup SD card contents
- Check connections before each use

### Continuous Improvement

- Keep logs of detections
- Review and analyze patterns
- Experiment with settings
- Learn from false positives
- Study drone protocols
- Join community forums
- Share knowledge

---

## Conclusion

Drone detection with HackRF/PortaPack is a powerful capability. This guide covers the essentials, but real expertise comes from practice. Start simple, experiment, document your findings, and continuously improve your technique.

**Remember:**
- Detection is always legal ✅
- Start with basic scanning
- Learn to interpret signals
- Document your observations
- Share knowledge responsibly
- Respect the law

**Next Steps:**
- Practice with different scenarios
- Build detection profiles for your area
- Experiment with antennas
- Analyze captured signals
- Contribute to community knowledge

For personal drone recall (YOUR equipment only), see PERSONAL_RECALL_SETUP.md.

For legal details, see LEGAL.md.

**Happy detecting! 📡🚁**

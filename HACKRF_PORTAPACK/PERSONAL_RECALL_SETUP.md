# Personal Drone Recall Setup Guide

## 🛑 CRITICAL WARNING - READ FIRST 🛑

### ⚠️ THIS GUIDE IS FOR YOUR OWN DRONES ONLY ⚠️

**ILLEGAL USE WARNING:**

Using these techniques on drones you DO NOT own is:
- **FEDERAL CRIME** in most countries
- Violation of FCC regulations (USA) and equivalent internationally
- Aircraft interference (serious criminal offense)
- Can result in: Heavy fines ($10,000+), equipment seizure, criminal prosecution, imprisonment

**LEGAL USE:**
- ✅ YOUR personally owned drone
- ✅ Drones you have explicit written permission to control
- ✅ Emergency recall of YOUR drone only
- ✅ Testing in controlled environment with YOUR equipment

**BY PROCEEDING, YOU ACKNOWLEDGE:**
- You will ONLY use this on YOUR OWN equipment
- You understand the legal consequences of misuse
- You accept FULL responsibility for your actions
- Authors/contributors have NO liability for your use

**If you plan to use this on drones you don't own: STOP NOW.**

---

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Understanding RF Control](#understanding-rf-control)
3. [Legal Compliance](#legal-compliance)
4. [Signal Capture Process](#signal-capture-process)
5. [Signal Analysis](#signal-analysis)
6. [Creating Recall Commands](#creating-recall-commands)
7. [Protocol-Specific Guides](#protocol-specific-guides)
8. [Testing Procedures](#testing-procedures)
9. [Troubleshooting](#troubleshooting)
10. [Safety Considerations](#safety-considerations)

---

## Prerequisites

### Required Knowledge

Before attempting this, you should understand:
- Basic RF principles (frequency, modulation, power)
- Your drone's control protocol
- Basic command-line or file editing
- Safety procedures for drone operation
- Local radio transmission regulations

**If you lack this knowledge:** Study first, then return to this guide.

### Required Equipment

**Essential:**
- HackRF One with PortaPack H4M
- Your drone (the one you want to recall)
- Your drone's transmitter/controller
- Appropriate antenna for drone's frequency
- Charged batteries for all equipment
- Notebook for documentation

**Highly Recommended:**
- Second antenna for simultaneous RX/TX testing
- Spectrum analyzer or SDR for verification
- Oscilloscope or logic analyzer (advanced analysis)
- RF power meter (verify legal limits)
- Faraday cage or RF shielded box (for bench testing)

**Safety Equipment:**
- Prop guards or remove props for testing
- Safety glasses
- Fire extinguisher (LiPo battery safety)
- First aid kit

### Legal Verification

**BEFORE proceeding, verify:**

✓ You OWN this drone (have receipt/proof)  
✓ Transmitting on this frequency is legal in your country  
✓ You have necessary licenses if required  
✓ You understand maximum legal power limits  
✓ You will test in legal location (not restricted airspace)  
✓ You have read all safety warnings

**If ANY box unchecked: STOP. Do not proceed.**

---

## Understanding RF Control

### How Drone Control Works

**Basic Control Signal:**
```
Transmitter → RF Signal → Drone Receiver → Flight Controller → Motors
```

**Components of Control Signal:**
1. **Carrier Frequency**: The RF channel (e.g., 2.45 GHz)
2. **Modulation**: How data is encoded (AM, FM, GFSK, LoRa)
3. **Protocol**: Data format (PPM, SBUS, FrSky, etc.)
4. **Binding**: Pairing between TX and RX (unique ID)
5. **Commands**: Stick positions, switches, modes

### Types of Control Signals

**Analog (Older Systems):**
- PPM (Pulse Position Modulation)
- PWM (Pulse Width Modulation)
- Simple to capture and replay
- Less secure
- Longer range typically

**Digital (Modern Systems):**
- FrSky (D8, D16, ACCESS)
- FlySky (AFHDS, AFHDS2A)
- Spektrum (DSM2, DSMX)
- ExpressLRS
- Crossfire
- More complex
- Often frequency hopping
- May have encryption

### Why Replay Can Be Difficult

**Challenges:**
- **Frequency Hopping**: Signal jumps between channels
- **Encryption**: Data is scrambled
- **Timing**: Precise timing required
- **Binding**: Unique pairing between TX/RX
- **Checksums**: Data validation
- **Rolling Codes**: Changes each transmission

**Easier Protocols:**
- Fixed frequency
- No encryption
- Simple modulation
- Examples: Basic FM, some PPM systems

**Harder Protocols:**
- Frequency hopping
- Encrypted
- Complex modulation
- Examples: FrSky ACCESS, DJI OcuSync, ELRS with binding phrase

---

## Legal Compliance

### Transmission Regulations

**United States (FCC):**
- Part 15 devices: No license required (low power, ISM bands)
- Maximum EIRP limits vary by band:
  - 433 MHz: 10 mW - 1W depending on application
  - 915 MHz: 1W (36 dBm) EIRP typical
  - 2.4 GHz: 1W (30 dBm) or 4W (36 dBm) with spread spectrum
  - 5.8 GHz: 1W (30 dBm) typical
- Must not cause harmful interference
- Must accept any interference received

**Europe (ETSI):**
- Similar ISM band rules
- 868 MHz common (instead of 915 MHz)
- Power limits generally lower than US
- CE certification requirements

**Other Countries:**
- Check local regulations
- May require amateur radio license
- Some countries prohibit certain frequencies
- Power limits vary significantly

**Your Responsibility:**
- Research YOUR country's rules
- Verify frequency is legal
- Measure your transmit power
- Stay within legal limits
- Document compliance

### Verification Steps

**Before first transmission:**

1. **Frequency Check:**
   - Is this frequency legal in my location?
   - Is it an ISM or licensed band?
   - Any restrictions on use?

2. **Power Check:**
   - Measure actual transmit power
   - Calculate EIRP (power + antenna gain - cable loss)
   - Verify under legal limit
   - Document measurements

3. **Location Check:**
   - Not in restricted airspace?
   - Not near airports, military bases?
   - Not near sensitive RF installations?
   - Safe for drone testing?

4. **Interference Check:**
   - Scan for other users on frequency
   - Coordinate if others present
   - Minimize transmission time
   - Have way to immediately stop

---

## Signal Capture Process

### Step 1: Prepare Equipment

**Setup:**
1. Charge all batteries (HackRF, drone, transmitter)
2. Connect appropriate antenna to HackRF
3. Insert SD card with adequate free space
4. Prepare notebook for documentation
5. Position equipment on stable surface

**Environment:**
- Indoors or RF-quiet location
- Away from WiFi routers, computers
- Minimize RF interference
- Comfortable working area
- Good lighting for notes

### Step 2: Identify Your Drone's Frequency

**Check Transmitter:**
- Look for label (e.g., "2.4 GHz", "5.8 GHz")
- Check user manual
- Common bands: 2.4 GHz, 868 MHz (EU), 915 MHz (US), 433 MHz

**If Unknown:**
1. Power on transmitter only (drone off)
2. Use HackRF in spectrum analyzer mode
3. Scan likely bands (2.4 GHz most common)
4. Watch for signals appearing when TX powered on
5. Note center frequency

**Document:**
- Transmitter model:
- Frequency band:
- Exact frequency (if found):
- Signal bandwidth observed:

### Step 3: Capture Control Signal

**PortaPack Capture Procedure:**

1. **Go to Capture App:**
   - Main Menu → Capture → Baseband Capture

2. **Configure Capture:**
   - Frequency: [Your drone's frequency]
   - Sample Rate: 2-4 MSPS (higher for wideband)
   - Format: Complex16 (.c16) recommended
   - Gain Settings:
     - RF: 14 dB
     - IF: 32 dB
     - BB: 24 dB (adjust based on signal strength)

3. **Prepare for Capture:**
   - Position transmitter near HackRF (0.5-2 meters)
   - Drone powered off or far away (don't want propeller spin!)
   - SD card ready

4. **Capture Sequence:**
   ```
   a. Start recording on HackRF
   b. Wait 2 seconds (get baseline)
   c. Power on transmitter
   d. Wait 2 seconds (capture binding/initialization)
   e. Perform desired command (e.g., RTH switch)
   f. Hold command for 3-5 seconds
   g. Wait 2 seconds (capture after)
   h. Stop recording
   ```

5. **Save Capture:**
   - Name descriptively: `my_drone_rth_capture.c16`
   - Note filename in documentation

**Document Capture:**
```
Capture Details:
- Filename: my_drone_rth_capture.c16
- Date/Time: 2024-12-26 15:30
- Frequency: 2450 MHz
- Sample Rate: 2 MSPS
- Duration: 10 seconds
- Command Performed: RTH switch activated
- Transmitter Battery: 12.4V (full)
- Notes: Clean capture, strong signal
```

### Step 4: Capture Multiple Scenarios

**Recommended Captures:**

1. **Binding Sequence** (if accessible)
   - Power sequence to bind TX to RX
   - May be needed for some protocols

2. **Idle/Baseline**
   - Transmitter on, no stick input
   - Reference signal

3. **Return to Home (RTH)**
   - Main emergency command
   - Primary use case

4. **Failsafe Trigger**
   - If transmitter has failsafe button
   - Alternative recall method

5. **Specific Mode Changes**
   - Switch to "Land" mode
   - Switch to "Position Hold" mode

6. **Different Commands** (optional)
   - Throttle changes
   - Directional commands
   - For analysis and understanding

---

## Signal Analysis

### Step 5: Analyze Captured Signals

**Transfer Files:**
1. Remove SD card from PortaPack
2. Insert in computer
3. Copy .c16 files to working directory
4. Keep originals safe (backup!)

**Analysis Tools:**

**Option 1: GNU Radio (Recommended)**
```bash
# Install GNU Radio if needed
sudo apt install gnuradio

# Create flowgraph to:
# - Read .c16 file
# - Demodulate (AM/FM/GFSK as appropriate)
# - Display spectrum
# - Save demodulated audio/data
```

**Option 2: Inspectrum**
```bash
# Install
sudo apt install inspectrum

# Open capture
inspectrum my_drone_rth_capture.c16

# Visual analysis:
# - See signal in time/frequency
# - Measure bandwidth
# - Identify modulation
# - Extract timing
```

**Option 3: URH (Universal Radio Hacker)**
```bash
# Install
pip3 install urh

# Or use GUI
urh

# Features:
# - Protocol analysis
# - Demodulation
# - Signal comparison
# - Automatic protocol discovery
```

### Identify Signal Characteristics

**Questions to Answer:**

1. **Modulation Type:**
   - AM, FM, FSK, GFSK, LoRa, other?
   - Use waterfall to identify

2. **Bandwidth:**
   - How wide is the signal?
   - Example: FrSky = ~1 MHz, LoRa = 250-500 kHz

3. **Frequency Hopping:**
   - Does frequency change?
   - How many channels?
   - What's the pattern?

4. **Data Rate:**
   - Symbols per second
   - Bit rate if digital

5. **Timing:**
   - Packet length
   - Packet interval
   - Burst characteristics

6. **Protocol Structure:**
   - Preamble
   - Sync word
   - Data payload
   - Checksum/CRC

**Document Findings:**
```
Signal Analysis Results:
- Modulation: GFSK
- Bandwidth: 1 MHz
- Center Frequency: 2450.5 MHz
- Data Rate: ~250 kbps estimated
- Frequency Hopping: No (or not detected)
- Packet Structure: [preamble][sync][data][crc]
- Timing: 10ms packets, 50 Hz rate
```

### Compare Captures

**Identify RTH Command:**
1. Compare "idle" vs "RTH active" captures
2. Look for differences in:
   - Packet content (data bits changed)
   - Frequency (if hopping differently)
   - Timing (faster/slower packets)
   - Specific bit patterns

**Example:**
```
Idle:     AA AA 55 12 34 00 00 00 [CRC]
RTH:      AA AA 55 12 34 01 00 00 [CRC]
                          ^^
                 Bit changed for RTH
```

**This gives you the exact command to replay!**

---

## Creating Recall Commands

### Step 6: Prepare Replay File

**Simple Replay (Fixed Frequency, No Hopping):**

1. **Trim Capture:**
   - Remove beginning/end noise
   - Keep only the actual command transmission
   - 1-2 seconds of clean signal

2. **Save as Replay File:**
   - Copy trimmed .c16 to: `/SDCARD/REPLAYS/`
   - Name clearly: `my_drone_rth_tested.c16`
   - Document in README_REPLAYS.TXT

**Complex Replay (Frequency Hopping):**

**Challenge:** Single frequency capture won't work

**Options:**

a. **Capture All Hop Frequencies:**
   - Wideband capture covering all channels
   - Very large file size
   - Replay entire sequence

b. **Identify Hop Pattern:**
   - Analyze hopping algorithm
   - Recreate hop sequence programmatically
   - Advanced, requires coding

c. **Use Single Frequency:**
   - Some protocols allow single-channel mode
   - Reduce TX to one frequency
   - Drone may still respond (if protocol allows)

d. **Modify Drone to Fixed Frequency:**
   - Reflash drone firmware (if possible)
   - Use fixed frequency mode
   - Safest for personal recall

### Step 7: Configure Replay in PortaPack

**Create FREQMAN Entry:**

Edit appropriate protocol template in `/SDCARD/FREQMAN/`:

Example: `PERSONAL_FRSKY_D16.TXT`
```
# Updated with MY drone's actual frequency
f=2450500000,m=AM,bw=1000000,d=My Drone RTH Frequency

# Replace template frequency with YOUR captured frequency
```

**Or Create Custom File:**
```
# Create: PERSONAL_MY_DRONE.TXT
f=2450500000,m=AM,bw=1000000,d=My Quad RTH
```

**Configure Settings:**

Edit: `/SDCARD/SETTINGS/personal_recall_template.txt`

```
protocol=my_drone
center_frequency=2450500000
modulation=GFSK
bandwidth=1000000
tx_gain=0          # Start LOW!
tx_power=0         # Start LOW!
```

---

## Protocol-Specific Guides

### FrSky D16 Setup

**Characteristics:**
- Frequency: 2400-2480 MHz
- Hopping: 47 channels
- Modulation: GFSK
- Binding: Required

**Capture Procedure:**
1. Bind transmitter to receiver (if not already)
2. Power on transmitter
3. **Capture binding sequence** (power cycle RX while recording)
4. Capture RTH command after binding
5. Note all 47 hop frequencies if possible

**Replay Strategy:**
- Replaying hopping sequence is complex
- Consider: Fixed frequency mode (if firmware allows)
- Or: Wideband capture/replay (large files)

**Testing:**
- Bench test with RX only (no drone powered)
- Verify RX LED responds
- Then test with drone (props off!)

### FlySky AFHDS/AFHDS2A Setup

**Characteristics:**
- Frequency: 2400-2480 MHz
- Hopping: 16 channels (AFHDS) or improved AFHDS2A
- Modulation: GFSK
- Binding: Required

**Capture Procedure:**
1. Bind TX to RX
2. Capture binding and normal operation
3. Identify hop pattern (simpler than FrSky)
4. Capture failsafe command

**Replay Strategy:**
- AFHDS2A has better error correction
- May respond to single-channel transmission
- Test with RX module disconnected from FC first

**Testing:**
- Use receiver bind LED as indicator
- Successful replay = LED changes state

### ExpressLRS (ELRS) Setup

**Characteristics:**
- Frequency: 900 MHz or 2.4 GHz variants
- Modulation: LoRa (chirp spread spectrum)
- Binding: Unique binding phrase
- Hopping: Yes, based on binding phrase

**Challenges:**
- LoRa is complex to replay
- Encrypted with binding phrase
- Frequency hopping based on phrase
- **Most difficult protocol to replay**

**Capture Procedure:**
1. Know your binding phrase
2. Capture wideband (LoRa bandwidth)
3. Identify chirp pattern in waterfall
4. Very challenging to replay accurately

**Recommendations:**
- ELRS is designed to resist replay attacks
- Consider using traditional transmitter as backup
- Replay may not be practical for emergency recall
- Use OTX lua script failsafe settings instead

### TBS Crossfire Setup

**Characteristics:**
- Frequency: 868 MHz (EU) or 915 MHz (US)
- Modulation: LoRa
- Binding: Required
- Long range, robust

**Challenges:**
- LoRa modulation complex
- Frequency hopping
- Error correction
- **Difficult to replay**

**Capture Procedure:**
1. Know your region (868 vs 915 MHz)
2. Capture wide bandwidth (LoRa needs it)
3. Identify chirp characteristics
4. Note any frequency changes

**Recommendations:**
- Crossfire has excellent failsafe features
- Use transmitter's built-in failsafe instead
- Replay not recommended for emergency use
- Better: Configure failsafe in transmitter

### DJI Drones (Consumer)

**Characteristics:**
- Frequency: 2.4 GHz and/or 5.8 GHz
- Protocol: Proprietary (Lightbridge, OcuSync)
- Encryption: Yes
- Frequency Agile: Changes based on interference

**Reality Check:**
- **DJI protocols are encrypted and proprietary**
- Replay is effectively impossible without keys
- Frequency hopping/agility defeats simple replay
- **Not a viable option for personal recall**

**Alternatives:**
- Use DJI app failsafe settings (RTH on signal loss)
- Use physical transmitter controls
- DJI has built-in emergency features
- Don't rely on RF replay for DJI

### Generic PPM/PWM (Simple RC)

**Characteristics:**
- Older, simpler systems
- Fixed frequency typically
- FM or AM modulation
- No encryption

**Advantages:**
- **Easiest to replay!**
- Fixed frequency
- Simple modulation
- No hopping or encryption

**Capture Procedure:**
1. Identify frequency (often 72 MHz, 27 MHz old systems, or 2.4 GHz newer)
2. Capture control signal
3. Identify stick position encoding
4. Very straightforward

**Replay Strategy:**
- Direct replay usually works
- May need to time pulses correctly
- Test thoroughly before aerial use

---

## Testing Procedures

### Phase 1: Bench Testing (CRITICAL)

**Setup:**
- Drone on bench, **PROPELLERS REMOVED**
- Or receiver only (disconnected from flight controller)
- All parties indoors or in RF shielded space
- Emergency power cutoff available

**Test 1: Receiver Response**
```
1. Power on drone (no props!) or receiver
2. Load replay file in PortaPack
3. Set TX gain to MINIMUM (0-5 dB)
4. Position HackRF 1 meter from drone
5. Transmit replay signal (short burst, <1 second)
6. Observe receiver LED
7. Check flight controller status (if connected)
```

**Success Indicators:**
- Receiver LED changes state
- Flight controller detects signal
- No actual motor commands (props off!)
- Repeatable behavior

**If No Response:**
- Increase TX gain incrementally (+3 dB)
- Verify frequency accuracy
- Check signal timing
- Review capture quality
- May need to recapture

**Test 2: Command Verification**
```
1. Connect flight controller to computer
2. Open configurator (Betaflight, etc.)
3. Watch receiver tab for commands
4. Replay signal
5. Verify correct command received
```

**Success Indicators:**
- Correct channel changes
- RTH function triggered
- Match expected behavior

### Phase 2: Controlled Environment Testing

**Setup:**
- Open field, no people nearby
- No other drones in air
- Good weather conditions
- Traditional transmitter as backup
- Spotter to assist

**Test 3: Tethered Test**
```
1. Attach drone to tether (rope/fishing line)
2. Limit altitude to 1-2 meters
3. Propellers: ON (secure tether first!)
4. Arm and hover (traditional transmitter)
5. Attempt replay RTH command
6. Observe response
7. Use traditional TX to land if issues
```

**Success Indicators:**
- Drone responds to replay command
- RTH mode activated
- Drone behavior matches traditional TX command
- No unexpected behavior

**Safety:**
- Spotter watching drone
- Tether prevents flyaway
- Traditional TX ready to take over
- Kill power if anything unexpected

**Test 4: Short-Range Free Flight**
```
1. Untethered, clear area
2. Hover at 2-3 meters altitude
3. Attempt replay RTH
4. Monitor drone response
5. Be ready with traditional TX backup
```

**Success Indicators:**
- Drone enters RTH mode
- Returns to home position
- Lands safely
- Repeatable behavior

### Phase 3: Operational Testing

**Only after successful Phase 1 & 2:**

**Test 5: Realistic Scenario**
```
1. Fly normally with traditional TX
2. Move to distance where replay needed (simulated emergency)
3. Attempt replay RTH
4. Verify effective recall
5. Document range, conditions, results
```

**Document Everything:**
```
Test Log:
- Date/Time:
- Test Phase:
- Conditions: (weather, RF environment)
- Distance from drone:
- TX power used:
- Result: (success/fail)
- Drone response:
- Time to RTH:
- Notes:
```

---

## Troubleshooting

### Replay Doesn't Work

**Check List:**

1. **Frequency Correct?**
   - Verify captured frequency matches replay
   - Use spectrum analyzer to check TX output
   - Tolerance: Within 10 kHz usually OK

2. **Modulation Correct?**
   - AM vs FM vs GFSK makes big difference
   - Check capture analysis
   - Try different modulation settings

3. **Timing Issues?**
   - Some protocols very timing-sensitive
   - May need exact packet timing
   - Compare capture timing to replay

4. **Frequency Hopping?**
   - If protocol hops, single frequency won't work
   - Need full hop sequence
   - Or modify to fixed frequency

5. **Signal Quality?**
   - Noisy capture won't replay well
   - Recapture in cleaner RF environment
   - Better antenna positioning

6. **TX Power Too Low?**
   - Incrementally increase
   - Measure actual output power
   - Stay within legal limits

7. **Binding Issue?**
   - RX not bound to your TX signal
   - May need to capture and replay binding
   - Or physically bind RX to your TX first

### Unexpected Drone Behavior

**If drone does something unexpected:**

1. **IMMEDIATELY:** Use traditional TX to take control
2. **Land drone safely**
3. **Power off replay TX**
4. **Analyze what happened**
5. **DO NOT retry until issue understood**

**Possible Causes:**
- Wrong command replayed
- Interference with other signals
- Partial command (corrupted)
- Flight controller misinterpretation
- Multiple sources of RF

**Resolution:**
- Review captures more carefully
- Verify exact command bytes
- Test more thoroughly in Phase 1
- May need different approach

### Legal/Interference Issues

**If you experience:**
- Interference to others
- Complaints from nearby users
- Equipment malfunctioning
- Unexpected regulatory contact

**Actions:**
1. **STOP transmitting immediately**
2. Verify frequency is legal
3. Measure transmit power
4. Ensure within legal limits
5. Document compliance
6. Consult with legal expert if needed

---

## Safety Considerations

### RF Safety

**Exposure Limits:**
- FCC guidelines for RF exposure
- Keep HackRF away from body when transmitting
- Don't transmit near people
- Especially careful with higher power levels

**Equipment Safety:**
- Don't exceed HackRF's ratings
- Monitor for overheating
- Use appropriate antennas
- Check SWR (Standing Wave Ratio)

### Drone Safety

**Pre-Flight:**
- Check drone condition
- Verify GPS lock
- Set failsafe properly
- Know RTH altitude
- Clear return path

**During Testing:**
- Spotter present
- Emergency procedures ready
- Traditional TX as backup
- Clear area of people
- Good weather conditions

**Emergency Procedures:**

**If Replay Causes Flyaway:**
1. Traditional TX: Try to regain control
2. If that fails: Let failsafe engage (signal loss)
3. Note last direction/altitude
4. Do NOT attempt further replay
5. Report as necessary

**If Drone Becomes Unresponsive:**
1. Stop all transmissions
2. Let failsafe engage (usually lands or RTH)
3. Do not attempt takeoff again until issue resolved
4. Analyze logs

### Legal Safety

**Protecting Yourself:**
- Document that drone is yours (receipt, serial number)
- Document all testing procedures
- Measure and record transmit power
- Verify legal compliance in writing
- Consider consulting lawyer for high-risk scenarios

**If Questioned:**
- Be cooperative
- Provide documentation
- Explain educational purpose
- Demonstrate ownership
- Don't admit to illegal activity

---

## Advanced Topics

### Creating Automated Recall

**Goal:** Button press = immediate RTH

**Approach:**
1. Store validated replay file on SD card
2. Create quick-access shortcut in PortaPack
3. Map to physical button if possible
4. Pre-configure frequency and power

**Implementation:**
- Save replay file: `/SDCARD/REPLAYS/EMERGENCY_RTH.c16`
- Create FREQMAN entry for quick load
- Test extensively before relying on it

### Multi-Drone Management

**If you have multiple drones:**

**Challenge:** Each drone has unique binding

**Solution:**
1. Capture signals for EACH drone separately
2. Label clearly: `drone1_rth.c16`, `drone2_rth.c16`
3. Create FREQMAN entry for each
4. Select correct one before use

**Safety:** Easy to confuse drones, double-check!

### Range Extension

**To maximize recall range:**

**Antenna Improvement:**
- Directional antenna (yagi, patch)
- Higher gain = longer range
- But: Must point at drone

**Power Increase:**
- Increase TX gain carefully
- Verify legal limits
- Measure actual EIRP
- Don't exceed regulations

**Environmental:**
- Higher ground position
- Line of sight
- Away from interference
- Good weather (rain attenuates)

**Realistic Ranges:**
- With stock setup: 100-500m
- With directional antenna: 500m-2km
- With high gain + power: 2-5km
- Limited by legal power and antenna

---

## Conclusion

Personal drone recall using HackRF/PortaPack is **technically possible** but comes with significant challenges:

**Difficulty by Protocol:**
- ✅ **Easy:** Simple FM/AM systems, PPM, no hopping
- ⚠️ **Medium:** FrSky, FlySky (fixed frequency mode)
- ❌ **Hard:** ELRS, Crossfire, DJI (encryption/hopping)

**Recommendations:**

1. **Primary Method:** Use traditional transmitter
   - Most reliable
   - Always legal (your drone)
   - Instant response

2. **Secondary Method:** Configure failsafe
   - Automatic on signal loss
   - No special equipment needed
   - Very reliable

3. **Tertiary Method:** HackRF replay
   - Emergency backup only
   - After extensive testing
   - When traditional TX fails
   - Simple protocols only

**Final Warnings:**

⚠️ **ONLY use on YOUR drones**
⚠️ **Test extensively before relying on it**
⚠️ **Traditional TX is more reliable**
⚠️ **Legal compliance is YOUR responsibility**
⚠️ **Safety first, always**

**If in doubt:**
- Use traditional transmitter
- Use built-in failsafe
- Don't rely on untested replay

---

## Resources

**Learn More:**
- Your drone's user manual
- Protocol documentation (if available)
- SDR communities (r/RTLSDR, r/hackrf)
- RC forums for your specific drone

**Tools:**
- GNU Radio: https://www.gnuradio.org/
- Universal Radio Hacker: https://github.com/jopohl/urh
- Inspectrum: https://github.com/miek/inspectrum

**Legal Resources:**
- FCC Part 15 Rules: https://www.fcc.gov/general/radio-frequency-safety-0
- Your country's radio regulations authority

---

**Remember: Legal, safe, and responsible use only. Detection is always legal - transmission only to YOUR equipment. When in doubt, use your regular transmitter.** 📡🚁

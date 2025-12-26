# Example Signal Captures

This directory contains example signal files that can be used for testing and reference.

## Signal Format

Signals are stored as JSON files with the following structure:

```json
{
  "frequency": 433.92,
  "modulation": 0,
  "captureTime": 1234567890,
  "name": "example_signal",
  "timings": [200, 400, 200, 800, 200, 400, ...],
  "rawData": [0, 1, 0, 1, ...]
}
```

### Fields

- **frequency**: Transmission frequency in MHz
- **modulation**: Modulation type (0=ASK/OOK, 1=2FSK, 2=4FSK, etc.)
- **captureTime**: Unix timestamp of capture
- **name**: Human-readable signal name
- **timings**: Array of pulse durations in microseconds
- **rawData**: Optional raw byte data

## Example Signals

### 1. Simple Fixed Code Remote (433.92 MHz)

Common garage door or gate remote with fixed code transmission.

**Characteristics:**
- Frequency: 433.92 MHz
- Modulation: ASK/OOK
- Protocol: Simple fixed code
- Bit duration: ~400-500 μs
- Repeat: Typically 3-5 times

**Pattern Example:**
```
Preamble: 9000 μs high
Bit 0: 400 μs high, 800 μs low
Bit 1: 800 μs high, 400 μs low
Gap: 9000 μs low
```

**Sample Timing Sequence:**
```
[9000, 400, 800, 800, 400, 400, 800, 800, 400, ...]
```

### 2. Weather Station (915 MHz)

Wireless weather station transmitting temperature and humidity.

**Characteristics:**
- Frequency: 915 MHz (North America) or 868 MHz (Europe)
- Modulation: ASK/OOK or 2FSK
- Update rate: Every 30-60 seconds
- Manchester encoding common
- CRC for error detection

**Pattern Example:**
```
Sync: 4000 μs pulse
Data bits: Manchester encoded
- 0: 500 μs high, 500 μs low
- 1: 500 μs low, 500 μs high
```

### 3. Wireless Doorbell (433 MHz)

Simple wireless doorbell button.

**Characteristics:**
- Frequency: 433 MHz
- Modulation: ASK/OOK
- Very simple protocol
- Short transmission (100-200ms)
- Button press triggered

**Pattern Example:**
```
[1000, 1000, 1000, 400, 400, 1000, 1000, 400, ...]
Repeated 5-10 times per button press
```

### 4. Tire Pressure Monitor (315 MHz)

TPMS sensor commonly used in vehicles (for educational reference only).

**Characteristics:**
- Frequency: 315 MHz (North America) or 433 MHz (Europe)
- Modulation: FSK
- Contains: Pressure, Temperature, Battery, ID
- Encrypted or proprietary protocols

**Note**: Many TPMS systems use proprietary protocols. This is for analysis only.

### 5. Remote Control Socket (433 MHz)

Wireless power outlet remote control.

**Characteristics:**
- Frequency: 433.92 MHz
- Modulation: ASK/OOK
- Protocol: Often PT2262 or similar
- Tri-state encoding possible
- Includes device ID and command

**Common Protocols:**
- **PT2262**: Tri-state encoding (0, 1, F)
- **EV1527**: Standard binary encoding
- **HT6P20B**: Similar to PT2262

## Creating Custom Signals

### Manual Signal Creation

You can create custom signals programmatically:

```cpp
RFSignal customSignal;
customSignal.frequency = 433.92;
customSignal.modulation = MOD_ASK_OOK;
customSignal.name = "Custom Test";

// Simple pattern: 1ms high, 1ms low, repeated
for(int i = 0; i < 10; i++) {
    customSignal.timings.push_back(1000);  // 1ms high
    customSignal.timings.push_back(1000);  // 1ms low
}

// Save the signal
storage.saveSignal(customSignal, "custom_test");
```

### Signal Analysis

To analyze captured signals:

1. **Count the timings**: Determine bit patterns
2. **Look for repeats**: Signals often repeat 3-5 times
3. **Find preamble**: Usually longer pulse at start
4. **Identify bits**: Look for short/long patterns
5. **Check for sync gaps**: Long gaps between transmissions

### Protocol Identification

Common protocol characteristics:

**Princeton (PT2262/EV1527)**:
- Sync: ~31x pulse width
- Short: 1x pulse
- Long: 3x pulse

**Learning Code (EV1527)**:
- 24 bits typically
- Fixed timing ratios
- No encryption

**HCS (KeeLoq)** - NOT SUPPORTED:
- 66-bit transmission
- Rolling code
- Encrypted
- Cannot be replayed

## Testing Signals

### Verifying Signal Quality

Good signal capture indicators:
- Clean timing transitions
- Repeatable pattern
- Similar to known protocols
- No excessive noise

Poor signal indicators:
- Erratic timings
- Single short capture
- Wildly varying durations
- Mostly very short pulses

### Testing Replay

To test if a signal will replay well:

1. Capture the same signal multiple times
2. Compare timing patterns
3. Look for consistency
4. Test replay in safe environment
5. Verify with original transmitter nearby

## Legal Considerations

⚠️ **Important**: All example signals are for educational purposes only.

**Allowed**:
- Analyzing your own devices
- Testing with your own remotes
- Research in controlled environment
- Learning about RF protocols

**NOT Allowed**:
- Replaying signals to devices you don't own
- Interfering with others' equipment
- Accessing systems without authorization
- Commercial use without proper licensing

## Contributing Examples

To contribute example signals:

1. Capture clear, clean signals
2. Document the source device
3. Specify frequency and modulation
4. Test replay functionality
5. Submit via pull request
6. Include legal disclaimer

## Additional Resources

- **RF Protocol Database**: Various online resources
- **Universal Radio Hacker**: Software for protocol analysis
- **RTL-SDR**: Visualize RF signals
- **Sigrok/PulseView**: Logic analyzer software
- **CC1101 Datasheet**: Technical reference

## Troubleshooting Examples

### Signal Won't Replay

Possible issues:
1. Captured during interference
2. Rolling code device (not supported)
3. Wrong frequency
4. Incomplete capture

### Signal Too Long

Solutions:
1. Capture just one repeat
2. Filter noise
3. Increase buffer size in firmware
4. Use more sophisticated capture

### Signal Too Short

Solutions:
1. Capture multiple transmissions
2. Hold button longer
3. Reduce noise threshold
4. Improve antenna position

## File Organization

Organize your signals:
```
/signals/
  /remotes/
    garage_door_main.json
    gate_remote.json
  /sensors/
    weather_station.json
    door_sensor.json
  /test/
    test_pattern_1.json
    calibration.json
```

While the firmware uses flat storage, you can organize offline backups this way.

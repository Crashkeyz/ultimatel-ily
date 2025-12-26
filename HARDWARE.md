# Hardware Information

## LilyGO T-Embed CC1101 Specifications

### Microcontroller
- **Chip**: ESP32-S3-WROOM-1
- **CPU**: Dual-core Xtensa LX7
- **Clock**: Up to 240 MHz
- **Flash**: 16MB (typically)
- **PSRAM**: 8MB (typically)
- **WiFi**: 802.11 b/g/n
- **Bluetooth**: BLE 5.0

### RF Transceiver
- **Chip**: Texas Instruments CC1101
- **Frequency Range**: 300-348 MHz, 387-464 MHz, 779-928 MHz
- **Modulation**: ASK/OOK, 2-FSK, 4-FSK, GFSK, MSK
- **Data Rate**: 0.6 to 600 kBaud
- **TX Power**: Up to +12 dBm (configurable)
- **RX Sensitivity**: -110 dBm (typical at 1.2 kBaud)
- **Interface**: SPI

### Display
- **Type**: TFT LCD
- **Driver**: ST7789
- **Resolution**: 170 x 320 pixels
- **Colors**: 65K (RGB565)
- **Interface**: SPI
- **Backlight**: PWM-controlled LED

### Power
- **USB**: USB-C connector
- **Battery**: Built-in lithium battery (typical: 500-1000mAh)
- **Charging**: Integrated charge controller
- **Voltage**: 3.3V logic level

### Physical
- **Form Factor**: Compact handheld
- **Dimensions**: Approximately 50mm x 85mm x 10mm
- **Weight**: ~30g (without battery)
- **Case**: Plastic enclosure with integrated display

## Pin Mapping

### ESP32-S3 to CC1101
| ESP32-S3 GPIO | CC1101 Pin | Function |
|---------------|------------|----------|
| GPIO 4        | GDO0       | Data/Signal Output |
| GPIO 5        | GDO2       | Clock/Status Output |
| GPIO 10       | CSN        | Chip Select (Active Low) |
| GPIO 11       | SI (MOSI)  | SPI Data In |
| GPIO 12       | SCLK       | SPI Clock |
| GPIO 13       | SO (MISO)  | SPI Data Out |
| 3.3V          | VCC        | Power Supply |
| GND           | GND        | Ground |

### ESP32-S3 to Display (ST7789)
| ESP32-S3 GPIO | ST7789 Pin | Function |
|---------------|------------|----------|
| GPIO 8        | DC         | Data/Command Select |
| GPIO 9        | CS         | Chip Select |
| GPIO 11       | SDA (MOSI) | SPI Data |
| GPIO 12       | SCL (SCLK) | SPI Clock |
| GPIO 13       | (MISO)     | Not used |
| GPIO 14       | RST        | Reset |
| GPIO 15       | BL         | Backlight Control |
| 3.3V          | VCC        | Power Supply |
| GND           | GND        | Ground |

### Buttons (Typical Configuration)
| Button   | GPIO | Pull |
|----------|------|------|
| UP       | GPIO 0  | Internal Pull-up |
| DOWN     | GPIO 1  | Internal Pull-up |
| SELECT   | GPIO 2  | Internal Pull-up |

**Note**: Button GPIO assignments may vary by hardware revision. Verify with your specific board.

## SPI Bus Configuration

The CC1101 and ST7789 display share the same SPI bus (HSPI):
- **MOSI**: GPIO 11 (shared)
- **MISO**: GPIO 13 (shared)
- **SCLK**: GPIO 12 (shared)
- **CC1101 CS**: GPIO 10 (dedicated)
- **Display CS**: GPIO 9 (dedicated)

This configuration allows both devices to coexist on the same SPI bus, with chip select lines controlling which device is active.

## Antenna Recommendations

### Quarter-Wave Wire Antennas

For optimal performance, use quarter-wavelength wire antennas:

| Frequency | Length (λ/4) | Length (cm) | Length (inches) |
|-----------|--------------|-------------|-----------------|
| 315 MHz   | λ/4          | ~23.8 cm    | ~9.4"          |
| 433 MHz   | λ/4          | ~17.3 cm    | ~6.8"          |
| 868 MHz   | λ/4          | ~8.6 cm     | ~3.4"          |
| 915 MHz   | λ/4          | ~8.2 cm     | ~3.2"          |

### Antenna Types

1. **Simple Wire Antenna**
   - Most basic: cut wire to quarter-wavelength
   - Orientation matters (vertical typically best)
   - Good for testing and prototyping

2. **Helical/Spring Antenna**
   - More compact than wire
   - Better omnidirectional pattern
   - Available commercially for specific frequencies

3. **PCB Antenna**
   - Integrated into device PCB
   - Compact but may have lower gain
   - Convenient for portable use

### Antenna Connection

The CC1101 module typically has:
- **U.FL/IPEX connector**: For external antennas
- **Built-in PCB antenna**: May be present (check your module)

Always ensure an antenna is connected before transmitting to avoid damaging the RF amplifier.

## Power Consumption

Typical current draw:
- **Idle**: ~50-80 mA
- **Display Active**: ~100-150 mA
- **RX Mode**: ~150-200 mA
- **TX Mode (max power)**: ~250-350 mA
- **Sleep Mode**: Not yet implemented (~10 mA when added)

Battery life depends on usage patterns:
- Continuous RX: 3-5 hours
- Intermittent use: 6-10 hours
- With sleep mode: 12-24 hours (future feature)

## Frequency Bands and Regulations

### ISM Bands (Industrial, Scientific, Medical)

These are unlicensed bands but still have regulations:

| Region | Frequency | Band | Max Power | Notes |
|--------|-----------|------|-----------|-------|
| North America | 315 MHz | ISM | 100 mW | Common for remotes |
| Worldwide | 433.05-434.79 MHz | ISM | 10 mW (EU) / 100 mW (US) | Most popular |
| Europe | 868.0-868.6 MHz | SRD | 25 mW | European devices |
| North America | 902-928 MHz | ISM | 1W (with restrictions) | WiFi, ZigBee |

**Important**: 
- Regulations vary by country and region
- Power limits are strictly enforced
- Some frequencies require licensing
- Duty cycle restrictions may apply
- Always verify local regulations before transmitting

### Recommended Operating Frequencies

For best compatibility and legal compliance:
- **433.92 MHz**: Worldwide ISM band (most compatible)
- **868.35 MHz**: European devices
- **315.0 MHz**: North American remotes (older)
- **915.0 MHz**: North American devices (newer)

## Hardware Modifications

### Adding External Antenna

If your board has a U.FL connector:
1. Purchase appropriate frequency antenna with U.FL connector
2. Connect carefully (connectors are fragile)
3. Secure cable to prevent stress on connector

### Improving Display Visibility

To adjust backlight:
```cpp
display.setBacklight(255);  // 0-255, 255 = brightest
```

Hardware dimming:
- Add resistor in series with backlight LED
- Use PWM control (already implemented in firmware)

### Battery Upgrades

To use larger battery:
1. Check polarity (+ and -)
2. Verify voltage (3.7V lithium)
3. Ensure charge controller supports capacity
4. Consider physical space

**Warning**: Lithium batteries can be dangerous if mishandled. Use appropriate charging and protection circuits.

## Troubleshooting Hardware

### Testing CC1101

Basic SPI communication test:
1. Check CS line toggles when transmitting
2. Verify MOSI/MISO have activity
3. Measure voltage: VCC should be 3.3V
4. Check continuity of all connections

### Testing Display

1. Check backlight: GPIO 15 should be HIGH
2. Verify CS line toggles during updates
3. Check D/C line changes during operation
4. Measure SPI clock frequency (~40 MHz)

### Common Hardware Issues

1. **No RF transmission**: Check antenna connection
2. **Display not working**: Verify VCC is 3.3V, not 5V
3. **Short battery life**: Lower backlight, reduce TX power
4. **Overheating**: Reduce TX power, improve ventilation
5. **Random resets**: Power supply issue, add capacitors

## Schematic References

For detailed schematics:
- Official LilyGO GitHub: https://github.com/Xinyuan-LilyGO
- CC1101 Datasheet: Texas Instruments
- ESP32-S3 Datasheet: Espressif Systems
- ST7789 Datasheet: Sitronix

## Safety Considerations

### Electrical Safety
- Use proper ESD precautions
- Don't short battery terminals
- Use appropriate power supply (5V USB)
- Don't modify circuitry without understanding

### RF Safety
- CC1101 output is low power (~12 dBm max)
- Generally safe at typical operating distances
- Follow antenna manufacturer guidelines
- Don't operate continuously at max power

### Battery Safety
- Use protection circuit
- Don't over-discharge (<3.0V)
- Don't over-charge (>4.2V)
- Don't puncture or crush
- Dispose of properly

## Warranty and Support

- Check with LilyGO for hardware warranty
- Community support via GitHub
- No official support for modified hardware
- Use at your own risk

## Purchasing Information

Official sources:
- **LilyGO Official Store**: AliExpress, Amazon
- **Authorized Resellers**: Various electronics distributors

Ensure you're getting authentic hardware:
- Look for LilyGO branding
- Check seller reviews
- Verify CE/FCC markings if required
- Compare with official product photos

## Accessories

Recommended accessories:
- **Case**: Protect hardware during use
- **Antennas**: Various frequencies and types
- **USB-C Cable**: For programming and power
- **Battery**: Spare or higher capacity
- **SD Card**: For future firmware storage expansion

# Frequently Asked Questions (FAQ)

## General Questions

### What is Ultimatel-ily?

Ultimatel-ily is open-source firmware for the LilyGO T-Embed CC1101 that transforms it into a multi-protocol RF analysis and replay tool. It can capture, analyze, store, and replay RF signals across multiple frequency bands.

### What can I do with it?

- Analyze RF signals from remotes, sensors, and other devices
- Capture and replay fixed-code RF signals
- Scan for active RF frequencies
- Learn about RF protocols and wireless communication
- Test and debug your own RF projects

### What can't I do with it?

- Break rolling code security systems (modern car keys, secure garage doors)
- Decrypt encrypted communications
- Jam or interfere with signals (illegal and not implemented)
- Access systems you don't own or have permission to use

### Is this legal?

The firmware itself is legal. However, transmitting RF signals is regulated in all countries. You must:
- Only analyze/transmit signals from your own devices
- Comply with local RF regulations
- Stay within allowed frequency bands and power levels
- Obtain proper authorization for any testing

**Always check your local laws before use.**

## Hardware Questions

### Where can I buy the LilyGO T-Embed CC1101?

- LilyGO official store on AliExpress
- Amazon (various sellers)
- Electronic component distributors
- Maker/hobbyist shops

Typical price range: $30-50 USD

### Do I need an antenna?

**Yes!** An antenna is critical for:
- Receiving signals (poor reception without it)
- Transmitting signals (required - don't transmit without antenna!)
- Protecting the RF amplifier from damage

The board may include a PCB antenna, but an external antenna usually works better.

### What kind of antenna do I need?

For best results:
- **433 MHz**: 17.3 cm wire or helical antenna
- **315 MHz**: 23.8 cm wire or helical antenna
- **868 MHz**: 8.6 cm wire or helical antenna
- **915 MHz**: 8.2 cm wire or helical antenna

Simple wire antennas work well. Commercial helical antennas offer better omnidirectional coverage.

### Can I use this with other ESP32 boards?

Not directly. The firmware is configured specifically for the T-Embed CC1101 pinout and peripherals. However, you could adapt it for:
- Other ESP32-S3 boards
- Custom hardware with CC1101
- Different display configurations

You'll need to modify pin definitions in `config.h`.

### How long does the battery last?

Depends on usage:
- Continuous RX: 3-5 hours
- Intermittent use: 6-10 hours
- With sleep mode (future): 12-24 hours

Lower display brightness to extend battery life.

## Firmware Questions

### How do I install the firmware?

See [BUILD.md](BUILD.md) for detailed instructions:
1. Install PlatformIO
2. Clone this repository
3. Build with `pio run`
4. Upload with `pio run --target upload`

### Does it work on Arduino IDE?

Not officially supported, but possible:
1. Install required libraries manually
2. Configure board settings
3. Copy source files
4. Build and upload

PlatformIO is strongly recommended.

### Can I update the firmware via WiFi?

Not currently implemented. Future versions may include OTA (Over-The-Air) updates.

### How do I restore to factory settings?

Current method:
1. Reflash the firmware
2. Use "Format Storage" in Settings menu

This will erase all saved signals.

## Usage Questions

### Why isn't my signal capturing?

Common reasons:
1. **No antenna**: Connect proper antenna
2. **Wrong frequency**: Set correct frequency for your device
3. **Too far away**: Move closer to transmitter
4. **Weak signal**: Try multiple captures
5. **Interference**: Move away from other RF sources

### Why doesn't replay work?

Possible issues:
1. **Rolling code**: Device uses encrypted rolling codes (not supported)
2. **Wrong frequency**: Double-check frequency setting
3. **No antenna**: Ensure antenna connected
4. **Low power**: Increase TX power in settings
5. **Incomplete capture**: Signal wasn't fully captured

### What are rolling codes and why don't they work?

Rolling codes (KeeLoq, HCS, etc.) are security systems where the code changes with each use. Simply replaying the signal doesn't work because the receiver expects a new code. These systems are designed to prevent replay attacks and the firmware intentionally doesn't support breaking them.

### How do I know what frequency to use?

Common frequencies by device type:
- **Old garage remotes**: 300-400 MHz
- **Modern remotes**: 433 MHz (worldwide) or 315 MHz (North America)
- **Weather stations**: 433 MHz or 915 MHz
- **Wireless sensors**: 433 MHz or 868 MHz
- **Car remotes**: Usually rolling code, 315 or 433 MHz

Use the frequency scan feature to find active frequencies.

### Can I capture multiple signals at once?

No, the firmware captures one signal at a time. To work with multiple signals:
1. Capture first signal
2. Save it
3. Capture next signal
4. Save it
5. Repeat as needed

### How many signals can I save?

Depends on:
- Signal complexity (number of timings)
- Available SPIFFS space (typically a few MB)
- Typically: 20-50 signals

Use "Format Storage" to clear space if full.

### What does RSSI mean?

RSSI (Received Signal Strength Indicator) measures signal strength in dBm:
- **-50 dBm**: Very strong signal
- **-70 dBm**: Good signal
- **-90 dBm**: Weak signal
- **-110 dBm**: Very weak signal (detection threshold)

### Can I name my signals?

Currently, signals are auto-named with timestamps. Custom naming will be added in a future update. For now, you can:
1. Keep notes separately
2. Edit JSON files manually
3. Wait for UI update

## Technical Questions

### What protocols are supported?

The firmware can capture and replay:
- ASK/OOK modulated signals (most common)
- Simple fixed-code protocols
- Weather station protocols
- Wireless sensor protocols
- Simple remotes and controls

Currently focusing on timing-based capture, which works for most simple protocols.

### What's the maximum signal length?

Current limit: 1024 timing transitions

This is sufficient for most signals, which typically have 50-200 transitions. Very long or complex signals may be truncated.

### Can I export signals?

Yes! Signals are stored as JSON files in SPIFFS. In the future, you'll be able to:
- Export via WiFi
- Share via USB
- Upload to cloud
- Import from others

### How accurate is the capture?

Timing accuracy:
- Sample rate: ~10 microseconds
- Sufficient for most protocols
- May not work for very high-speed protocols

Good enough for typical 433 MHz devices.

### Can I modify the code?

Yes! The firmware is open source (MIT License). You can:
- Modify for your needs
- Add new features
- Fix bugs
- Share improvements

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

### Does it support [specific protocol]?

The firmware uses timing-based capture, which works for:
- ✅ Princeton (PT2262)
- ✅ EV1527
- ✅ HT6P20B
- ✅ Simple fixed codes
- ✅ Weather stations (simple)
- ❌ KeeLoq (rolling code)
- ❌ Encrypted protocols
- ❌ Complex FSK protocols

## Troubleshooting

### Display is blank

1. Check backlight (GPIO 15)
2. Verify power supply
3. Reset device
4. Check for serial output errors
5. See [TROUBLESHOOTING.md](TROUBLESHOOTING.md)

### RF not working

1. Verify CC1101 initialization in serial output
2. Check antenna connection
3. Verify SPI connections
4. Try different frequency
5. Check for "CC1101 initialized" message

### Cannot upload firmware

1. Put ESP32 in bootloader mode (hold BOOT, press RESET)
2. Check USB cable (must support data)
3. Verify correct COM port
4. Try slower upload speed
5. Install USB drivers if needed

### Device keeps resetting

1. Check power supply (need stable 5V, >500mA)
2. Charge battery fully
3. Check serial output for crash logs
4. Verify no short circuits

## Future Features

### What's planned for future versions?

Roadmap includes:
- Protocol identification
- Signal analysis and comparison
- Custom signal naming via UI
- WiFi configuration interface
- Web-based control
- Sleep mode for battery life
- Spectrum analyzer view
- Signal quality metrics
- Over-the-air updates
- Cloud signal library

### When will feature X be added?

This is an open-source community project. Features are added when contributors have time and interest. You can:
- Request features via GitHub Issues
- Contribute code yourself
- Sponsor development
- Help with testing

### Can I request a feature?

Yes! Open an issue on GitHub with:
- Clear description
- Use cases
- Why it's useful
- Whether you can help implement

## Legal and Ethical

### Is this a hacking tool?

No. It's an educational RF analysis tool. Like any tool, it can be used responsibly or irresponsibly. The choice is yours, along with the legal responsibility.

### Can I use this for penetration testing?

Only with proper authorization:
- Written permission from system owner
- Within scope of engagement
- Compliant with local laws
- As part of legitimate security testing

**Never** use without explicit permission.

### What if I accidentally captured something I shouldn't?

1. Delete the signal immediately
2. Don't replay it
3. Don't share it
4. Be more careful in the future

### Is it illegal to just receive/analyze signals?

Laws vary by jurisdiction. Generally:
- **Receiving**: Usually legal (passive)
- **Analyzing**: Usually legal (educational)
- **Transmitting**: Regulated (requires compliance)
- **Accessing systems**: Illegal without permission

**Check your local laws.**

### Someone is misusing this tool. What should I do?

1. Don't be a vigilante
2. Report to appropriate authorities
3. Don't engage directly
4. Let law enforcement handle it

## Support

### Where can I get help?

- **Documentation**: Check README, USAGE, TROUBLESHOOTING
- **GitHub Issues**: Search existing issues
- **New Issue**: Create detailed issue report
- **Community**: Help others and learn together

### How can I support the project?

- **Use it**: Try the firmware and provide feedback
- **Report bugs**: Help improve stability
- **Contribute code**: Add features or fix bugs
- **Write documentation**: Help others learn
- **Share responsibly**: Tell others about the project
- **Star the repo**: Show your support on GitHub

### I found a bug. What now?

1. Check if it's already reported
2. Gather details (version, steps to reproduce, logs)
3. Create GitHub issue with details
4. Be patient while it's investigated
5. Test fixes when available

### Can I get commercial support?

Currently, there's no official commercial support. The project is community-driven. For commercial use, consider:
- Hiring a developer familiar with the project
- Contributing funding for specific features
- Providing sponsorship to maintainers

## Advanced Research Features

### What are the advanced research features?

Version 1.1+ includes educational tools for RF security research:
- **Rolling Code Analyzer**: Study rolling code systems
- **Signal Intelligence**: Advanced protocol identification
- **Advanced TX**: Sophisticated transmission testing
- **RF Research Tools**: Educational demonstrations (disabled by default)

See [ADVANCED_FEATURES.md](ADVANCED_FEATURES.md) for complete documentation.

### Are these features legal to use?

The features themselves are legal, but **HOW you use them matters**:

✅ **Legal uses**:
- Analyzing your own devices
- Authorized security research
- Educational learning
- Professional penetration testing (with permission)

❌ **Illegal uses**:
- Accessing systems you don't own
- RF jamming or interference
- Bypassing security without permission
- Violating FCC regulations

**Always read [LEGAL_DISCLAIMER.md](LEGAL_DISCLAIMER.md) before using advanced features.**

### Can I break rolling codes with this?

**No.** The rolling code analyzer is educational only. It teaches:
- How rolling codes work
- Why simple replay doesn't work
- Protocol structures
- Cryptographic principles

Modern rolling codes (KeeLoq, HCS) use encryption that cannot be broken with these tools. The analyzer demonstrates WHY they're secure.

See [ROLLING_CODES.md](ROLLING_CODES.md) for detailed explanation.

### Is the RF jamming feature real?

**No.** The RF research tools provide **educational demonstrations only**. The actual harmful functionality is disabled for safety and legal compliance.

These features teach about:
- RF vulnerabilities (theoretical)
- Why jamming is dangerous
- Defensive countermeasures
- Legal consequences

**Real jamming is a federal crime with severe penalties.**

### How do I enable advanced features?

1. Navigate to main menu
2. Select "7. Advanced Research"
3. Read and accept legal warning
4. Choose desired feature

Some features require activation in `config.h`:
```cpp
#define ENABLE_ROLLING_CODE_ANALYSIS 1
#define ENABLE_SIGNAL_INTELLIGENCE 1
#define ENABLE_ADVANCED_TX 1
#define ENABLE_RF_RESEARCH 0  // Disabled by default
```

### What safety features are included?

Multiple safety mechanisms:
- **Emergency stop button** (GPIO_NUM_0)
- **Transmission duration limits** (5 seconds default)
- **Automatic timeouts** (5 minutes for research mode)
- **Feature flags** (enable/disable at compile time)
- **Usage logging** (audit trail)
- **Legal warnings** (must accept before use)

### Can I use these for penetration testing?

**Only with proper authorization**:
- Written permission from system owner
- Clear scope definition
- Professional contract or engagement letter
- Compliance with all laws
- Liability insurance recommended

See [RF_SECURITY.md](RF_SECURITY.md) for responsible research guidelines.

### What if I accidentally do something illegal?

**Immediately**:
1. Stop the activity
2. Document what occurred
3. Consult legal counsel
4. Consider voluntary disclosure
5. Don't attempt to cover it up

**Prevention is better**:
- Read documentation thoroughly
- Get authorization before testing
- When in doubt, don't do it
- Consult legal counsel proactively

### Where can I learn more about RF security?

**Documentation**:
- [ADVANCED_FEATURES.md](ADVANCED_FEATURES.md) - Feature documentation
- [ROLLING_CODES.md](ROLLING_CODES.md) - Rolling code explanation
- [RF_SECURITY.md](RF_SECURITY.md) - Security research guide
- [LEGAL_DISCLAIMER.md](LEGAL_DISCLAIMER.md) - Legal warnings

**External Resources**:
- Academic papers on RF security
- DEFCON/Black Hat conference talks
- Security research blogs
- Professional training courses

### How can I contribute to RF security research?

**Responsibly**:
- ✅ Learn the fundamentals
- ✅ Practice on your own devices
- ✅ Share knowledge ethically
- ✅ Follow responsible disclosure
- ✅ Contribute to open source
- ✅ Help improve security for everyone

**Not this way**:
- ❌ Attacking others' systems
- ❌ Publishing weaponized exploits
- ❌ Enabling script kiddies
- ❌ Seeking fame through harm
- ❌ Violating ethical standards

### What's the difference between gray hat and black hat?

**White Hat** (Ethical):
- Authorized testing only
- Responsible disclosure
- Follows laws and ethics
- Improves security

**Gray Hat** (Questionable):
- Unauthorized testing "for good"
- Public disclosure without coordination
- Legal gray areas
- Mixed motivations

**Black Hat** (Criminal):
- Malicious intent
- Unauthorized access
- Criminal activity
- Causes harm

**Always be white hat. It's the only legally and ethically defensible position.**

### Can I use this for my security research thesis?

Yes, with caveats:
- Get IRB/ethics committee approval
- Use only authorized test equipment
- Follow academic integrity standards
- Coordinate with advisor
- Document methodology carefully
- Consider responsible disclosure implications

The firmware can be excellent for educational research on:
- Protocol analysis
- RF security mechanisms
- Cryptographic implementations
- Security system design

### What should I do if I discover a vulnerability?

**Follow responsible disclosure**:

1. **Don't exploit it** beyond proof-of-concept
2. **Document thoroughly** (methodology, impact)
3. **Contact vendor** through security contact
4. **Give time to fix** (typically 90 days)
5. **Coordinate disclosure** date
6. **Publish responsibly** with remediation guidance

See detailed process in [RF_SECURITY.md](RF_SECURITY.md).

## Responsible Disclosure

### How do I report a vulnerability I found?

1. **Gather information**:
   - Affected product/version
   - Vulnerability details
   - Proof of concept (if safe)
   - Impact assessment

2. **Contact vendor**:
   - Use security@ email or security portal
   - Request secure communication
   - Provide summary (not full details initially)
   - Propose disclosure timeline

3. **Work together**:
   - Provide additional info as needed
   - Test proposed fixes
   - Coordinate public disclosure
   - Credit appropriately

4. **Public disclosure**:
   - After fix is available
   - Or after reasonable timeline (90+ days)
   - Include remediation guidance
   - Be professional and factual

### What if a vendor doesn't respond?

**Try escalation**:
- Alternative contacts (security team, executives)
- CERT/CC or national CERT
- Industry organizations
- Public notification (last resort)

**Timeline**:
- 7 days: Initial response expected
- 30 days: Acknowledgment and plan
- 90 days: Fix or disclosure
- 120 days: Extended timeline for complex fixes

### Should I disclose publicly even without a fix?

**Consider carefully**:

**Yes if**:
- Active exploitation occurring
- Critical infrastructure at risk
- Vendor unresponsive after reasonable time
- Public interest outweighs risks

**No if**:
- Vendor working on fix in good faith
- More time likely to result in solution
- Disclosure would cause disproportionate harm
- Legal restrictions apply

**When in doubt, consult CERT/CC or similar coordination center.**

## Still Have Questions?

If your question isn't answered here:
1. Check other documentation files
2. Search GitHub Issues
3. Create a new issue with your question
4. Be specific and provide context

We're here to help! 🚀

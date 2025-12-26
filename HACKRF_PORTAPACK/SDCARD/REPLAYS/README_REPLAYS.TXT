# REPLAYS Directory
# Store replay-ready signals for YOUR OWN drones

## Purpose
This directory stores processed signal files ready for replay transmission to YOUR OWN drones.

## ⚠️ CRITICAL LEGAL WARNING ⚠️
**TRANSMITTING TO DRONES YOU DON'T OWN IS ILLEGAL**

This is not just unethical - it violates:
- FCC regulations (USA)
- Equivalent regulations in other countries
- Criminal laws against interference with aircraft
- Telecommunications laws

Penalties can include:
- Heavy fines ($10,000+ per violation)
- Criminal charges
- Confiscation of equipment
- Imprisonment in severe cases

## Legal Use
You may ONLY replay signals to:
✅ YOUR OWN drone that you personally own
✅ Drones you have explicit written permission to control
✅ In controlled test environments you have authorization for

## Replay File Guidelines

### File Naming
Use clear, descriptive names:
- `my_mavic_rth.c16` - DJI Mavic return to home
- `my_quad_land.c16` - Landing command
- `my_race_drone_disarm.c16` - Disarm command
- `emergency_recall.c16` - Emergency recall sequence

### Required Documentation
Create a .txt file alongside each replay file with:
```
Filename: my_mavic_rth.c16
Drone: DJI Mavic 2 Pro (Serial: XXXXX)
Owner: [Your Name]
Frequency: 2450 MHz
Sample Rate: 2 MSPS
Purpose: Emergency return to home
Tested: Yes, 2023-12-25
Safety Range: 500m max
Notes: Triggers RTH at current altitude
```

### Replay File Formats
- `.c16` - Complex 16-bit (most common)
- `.c8` - Complex 8-bit (smaller files)
- `.wav` - WAV format for compatible signals

## Safety Checklist Before Replay

Before transmitting ANY signal:
- [ ] Confirm this is YOUR drone
- [ ] Verify no other drones nearby
- [ ] Check you're in legal frequency band
- [ ] Ensure safe environment (open area, no people)
- [ ] Have line of sight to drone
- [ ] Weather is suitable for flight/recall
- [ ] Battery sufficient for recall operation
- [ ] Emergency landing area identified
- [ ] No restricted airspace
- [ ] Spotter present (recommended)

## Testing Procedure

1. **Bench Test First**
   - Test with drone powered but props removed
   - Verify correct response
   - Start with minimal TX power

2. **Safe Environment Test**
   - Open field, no obstacles
   - Tethered drone (if possible)
   - Short range initially
   - Gradually increase distance

3. **Operational Use**
   - Only after successful tests
   - Always have backup control method
   - Keep traditional controller ready
   - Monitor drone behavior

## PortaPack Replay Operation

To replay a signal on PortaPack:
1. Go to Replay App
2. Select your replay file
3. Verify frequency and settings
4. Set appropriate TX gain (start low!)
5. Confirm safety checklist
6. Press to transmit
7. Monitor drone response

## Troubleshooting

**Replay doesn't work:**
- Verify capture quality (clean signal)
- Check frequency accuracy
- Ensure sufficient TX power (but stay legal!)
- Verify timing is correct
- Try recapturing signal

**Unexpected behavior:**
- STOP immediately
- Use regular controller
- Land drone safely
- Review capture and settings
- May need to recapture with better parameters

## Emergency Procedures

If replay causes unexpected behavior:
1. STOP transmitting immediately
2. Switch to regular controller
3. Command immediate landing or hover
4. Clear the area
5. Do NOT attempt replay again until issue resolved

## File Management

- Keep only tested, working replays
- Delete failed attempts
- Update documentation regularly
- Back up working replays
- Note any changes to drone firmware/settings

## Related Resources

- PERSONAL_RECALL_SETUP.md - How to create replay files
- DETECTION_GUIDE.md - Understanding signals
- LEGAL.md - Complete legal information

Remember: With great power comes great responsibility. Use this technology legally and ethically.

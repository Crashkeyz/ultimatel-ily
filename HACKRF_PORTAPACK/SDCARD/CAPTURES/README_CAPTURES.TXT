# CAPTURES Directory
# Store your captured drone signals here

## Purpose
This directory is for storing captured RF signals from YOUR OWN drones only.

## Legal Notice
⚠️ **WARNING: FOR YOUR OWN EQUIPMENT ONLY** ⚠️

It is LEGAL to:
- Capture signals from YOUR OWN drone
- Record YOUR OWN transmitter's control signals
- Analyze YOUR OWN equipment's RF patterns

It is ILLEGAL to:
- Capture and replay signals from drones you don't own
- Record others' control signals with intent to interfere
- Use captured signals to control equipment you don't own

## File Naming Convention
Use descriptive names for your captures:
- `my_drone_rth_2023-12-25.c16` - Return to home signal
- `my_quad_failsafe.c16` - Failsafe trigger
- `my_tx_binding.c16` - Binding sequence
- `range_test_capture.c16` - Range test signals

## Capture Format
HackRF/PortaPack typically saves in these formats:
- `.c16` - Complex 16-bit samples (int16_t I/Q pairs)
- `.c8` - Complex 8-bit samples
- `.wav` - WAV format for audio-band signals

## Capture Settings to Record
When saving a capture, also document:
1. Center frequency
2. Sample rate
3. Gain settings (IF, BB, RF)
4. Bandwidth
5. Date and time
6. Drone model and transmitter type
7. Purpose of capture (RTH, failsafe, etc.)

## Storage Management
- Captures can be large files (MB to GB)
- Use appropriate sample rates for your protocol
- Delete old captures when no longer needed
- Keep your SD card organized

## Next Steps
After capturing signals from YOUR drone:
1. Analyze them using PortaPack's analyzer tools
2. Identify the exact frequencies and timing
3. Create replay files in the REPLAYS directory
4. Test in a safe, controlled environment
5. Document your settings

See PERSONAL_RECALL_SETUP.md for detailed capture procedures.

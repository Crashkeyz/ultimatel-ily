# Rolling Code Systems - Educational Guide

**Understanding RF Security Through Rolling Codes**

This document provides an educational explanation of rolling code systems, how they work, why they're secure, and what security researchers should understand about them.

## Table of Contents

1. [Introduction](#introduction)
2. [The Problem with Fixed Codes](#the-problem-with-fixed-codes)
3. [How Rolling Codes Work](#how-rolling-codes-work)
4. [Common Rolling Code Protocols](#common-rolling-code-protocols)
5. [Security Analysis](#security-analysis)
6. [Why Replay Attacks Don't Work](#why-replay-attacks-dont-work)
7. [Research and Educational Value](#research-and-educational-value)

## Introduction

Rolling codes (also called hopping codes or dynamic codes) are a cryptographic security mechanism used in modern RF access control systems like:

- Car remote keyless entry (RKE)
- Garage door openers (post-1990s)
- Home security systems
- Industrial access control
- Modern alarm systems

### Purpose

Rolling codes prevent **replay attacks** - a simple but effective attack where an attacker captures an RF transmission and replays it later to gain unauthorized access.

## The Problem with Fixed Codes

### Fixed Code Systems

Early RF remote systems used **fixed codes** - a static identifier transmitted every time:

```
Remote: "Hey, I'm remote #12345"
Receiver: "I recognize #12345, opening door"
```

### The Vulnerability

Anyone with an RF receiver can:
1. Capture the transmission
2. Replay it later
3. Gain unauthorized access

This is trivial to exploit and why fixed codes are insecure for access control.

### Historical Context

- **Pre-1990**: Most systems used fixed codes
- **1990s**: Rolling codes introduced
- **Today**: Rolling codes standard for security-critical applications

## How Rolling Codes Work

### Basic Principle

Instead of sending the same code every time, rolling code systems generate a **new code for each transmission**:

```
Button Press #1: Code A
Button Press #2: Code B
Button Press #3: Code C
(Each code is used only once)
```

### Synchronization

The transmitter and receiver stay synchronized using:

1. **Shared Secret Key**: Known only to paired devices
2. **Counter**: Increments with each use
3. **Encryption Algorithm**: Generates unique codes

### Typical Flow

```
Transmitter Side:
1. User presses button
2. Counter increments: N → N+1
3. Encrypt(Secret_Key, Counter, Serial_Number) → Code
4. Transmit Code

Receiver Side:
1. Receive Code
2. Decrypt(Code) → Counter, Serial_Number
3. Verify Serial_Number matches
4. Check Counter > Last_Seen_Counter
5. If valid: Grant access, update Last_Seen_Counter
```

### Synchronization Window

Receivers typically accept codes within a window:
- Current counter: N
- Accept range: N to N+256 (typical)
- Prevents desynchronization from accidental button presses

## Common Rolling Code Protocols

### 1. KeeLoq

**Developer**: Microchip Technology
**Introduced**: 1980s
**Use**: Automotive, garage doors, security systems

**Characteristics**:
- 64-bit block cipher
- 32-bit encrypted payload
- 28-bit serial number
- Counter-based
- Proprietary algorithm (reverse-engineered)

**Packet Structure**:
```
| Encrypted (32 bits)        | Serial Number (28 bits) | Function (4 bits) |
| Counter (16) | Discrim (4) | Button/Seed (12)        | 28-bit ID          | Buttons   |
```

**Security Status**:
- Original implementation had vulnerabilities
- Modern variants more secure
- Still widely used
- Considered adequate for most applications

### 2. HCS (High-Security Code Hopping)

**Developer**: Microchip Technology
**Family**: HCS200, HCS300, HCS301, etc.

**Improvements over basic KeeLoq**:
- Enhanced encryption
- Better counter management
- Anti-scan features
- Seed diversity

**Applications**:
- Automotive keyless entry
- Secure access control
- High-value targets

### 3. Hitag

**Developer**: NXP Semiconductors (formerly Philips)
**Use**: Automotive immobilizers, access control

**Variants**:
- Hitag1 (obsolete, broken)
- Hitag2 (widely used, some vulnerabilities)
- Hitag3/AES (current, secure)

**Note**: Hitag typically operates at 125 kHz (LF), not sub-GHz

### 4. Modern Implementations

**Current Best Practices**:
- AES-128 encryption (automotive)
- Challenge-response authentication
- Time-based codes
- Multi-factor authentication
- Secure element storage

## Security Analysis

### Strengths

1. **Prevents Simple Replay**:
   - Each code valid only once
   - Old codes rejected
   - Attacker can't reuse captured transmission

2. **Counter Verification**:
   - Codes must be sequential
   - Large jumps may be rejected
   - Prevents brute force of counter space

3. **Encryption**:
   - Secret key never transmitted
   - Code appears random without key
   - Difficult to predict next code

4. **Serial Number Binding**:
   - Code tied to specific transmitter
   - Can't use code from different device

### Weaknesses and Attacks

#### 1. Code Grabbing Attack

**Concept**: Capture code before legitimate receiver

```
Scenario:
1. User presses button
2. Attacker captures code (blocks legitimate reception)
3. Legitimate receiver never sees code
4. Attacker can use code once
```

**Mitigation**:
- Limited by range
- Code expires quickly
- Requires precise timing
- User notices access doesn't work

#### 2. Replay and Resync Attack

**Concept**: Force desynchronization, replay old code

**Mitigation**:
- Resync procedures secured
- Limited acceptance window
- Multiple verifications

#### 3. Cryptanalysis

**KeeLoq Example**:
- Algorithm reverse-engineered
- Slide attacks demonstrated
- Takes significant time/resources
- Not practical for casual attacks

**Modern Protocols**:
- Use standard algorithms (AES)
- Extensively peer-reviewed
- No known practical breaks

#### 4. Side-Channel Attacks

**Power Analysis**:
- Measure power consumption during encryption
- Can reveal secret key
- Requires physical access
- Complex analysis

**Timing Attacks**:
- Analyze encryption timing
- Reveal key bits
- Hardware countermeasures exist

### Security Considerations

**For Manufacturers**:
- Use proven encryption (AES)
- Implement proper counter management
- Secure key generation and storage
- Regular security audits
- Stay current with research

**For Users**:
- Keep firmware updated
- Use additional security (two-factor)
- Monitor for unusual activity
- Don't assume RF alone is sufficient

## Why Replay Attacks Don't Work

### Simple Replay

```
❌ DOESN'T WORK:
1. Capture transmission: Code_N
2. Replay Code_N later
3. Receiver: "Code_N already used, rejected"
```

### Why the Analyzer Can't Predict

**Common Misconception**: "If I capture enough codes, I can predict the next one"

**Reality**:
```
Captured Codes: [Code_1, Code_2, Code_3, ...]

Without Secret Key:
- Codes appear random
- No discernible pattern
- Counter value encrypted
- Prediction impossible

With Secret Key (not transmitted):
- Could generate valid codes
- But that's called "having the key"
- Not breaking the system
```

### Cryptographic Security

Rolling codes rely on **computational security**:
- Breaking encryption takes more time/resources than value gained
- Modern algorithms (AES-128) secure against brute force
- 2^128 possible keys = computational infeasible

## Research and Educational Value

### What Researchers Can Learn

1. **Protocol Analysis**:
   - Packet structure
   - Timing characteristics
   - Modulation schemes
   - Error handling

2. **Implementation Flaws**:
   - Weak random number generators
   - Poor key management
   - Timing vulnerabilities
   - Side channels

3. **System Design**:
   - How to implement security
   - Common pitfalls
   - Best practices
   - Defense in depth

### Responsible Research

**Ethical Guidelines**:
- ✅ Study your own devices
- ✅ Analyze publicly documented protocols
- ✅ Contribute to security knowledge
- ✅ Responsible disclosure of vulnerabilities
- ❌ Don't attack others' systems
- ❌ Don't enable unauthorized access
- ❌ Don't publish full exploits without responsible disclosure

### Educational Goals

The rolling code analyzer in this firmware teaches:

1. **Why Simple Replay Doesn't Work**:
   - Hands-on demonstration
   - See codes change each time
   - Understand counter progression

2. **Protocol Identification**:
   - Recognize different systems
   - Understand packet structures
   - Analyze timing patterns

3. **Cryptographic Principles**:
   - Entropy in encrypted data
   - Importance of secret keys
   - Counter-based security

4. **Security Design**:
   - How proper security works
   - Why old systems were vulnerable
   - Modern improvements

### Using the Analyzer Ethically

**Good Uses**:
- Analyze YOUR OWN remote controls
- Learn protocol structures
- Understand why rolling codes work
- Educational demonstrations
- Security research on authorized systems

**Bad Uses**:
- ❌ Attempting to break others' systems
- ❌ Attacking vehicles or buildings
- ❌ Unauthorized access attempts
- ❌ Malicious research

## Advanced Topics

### Counter Management

**Challenges**:
- Accidental button presses (counter advances)
- Battery replacement (counter reset?)
- Multiple transmitters (same counter space?)

**Solutions**:
- Wide acceptance window
- Resynchronization procedures
- Separate counter spaces per transmitter

### Key Diversification

**Problem**: Factory master key compromise

**Solution**:
- Unique key per device
- Derived from master + serial number
- Master key not stored in devices

### Anti-Scan Features

**Jam Detection**:
- Monitor for interference
- Delay acceptance during jamming
- Alert user to attacks

**Code Freshness**:
- Timestamp-based expiration
- Very short validity window
- Prevents code grabbing

### Future Developments

**Trends**:
- Move to smartphone-based access
- Bluetooth Low Energy (BLE)
- Ultra-Wideband (UWB) for cars
- Biometric integration
- Continuous authentication

## Conclusion

Rolling codes represent an important evolution in RF security:

1. **Effective Against Simple Attacks**: Prevent replay attacks that plagued fixed codes
2. **Not Perfect**: Vulnerabilities exist, especially in older implementations
3. **Constantly Evolving**: New protocols address discovered weaknesses
4. **Educational Value**: Excellent example of practical cryptography

### Key Takeaways

- **Fixed codes are insecure** for access control
- **Rolling codes use encryption and counters** to prevent replay
- **Modern implementations are secure** when properly designed
- **Research helps improve security** for everyone
- **Ethical research is essential** to progress

### For Security Researchers

Study rolling codes to:
- Understand real-world cryptographic implementations
- Learn about security system design
- Identify and responsibly disclose vulnerabilities
- Contribute to safer systems for everyone

**Always remember**: The goal of security research is to make systems more secure, not to enable attacks.

## References

### Academic Papers

- "Cryptanalysis of the KeeLoq Block Cipher" (2008)
- "Gone in 360 Seconds: Hijacking with Hitag2" (2012)
- Various automotive security conferences

### Standards

- ISO 14443 (Contactless cards)
- SAE J2945 (V2X security)

### Further Reading

- [RF_SECURITY.md](RF_SECURITY.md) - General RF security guide
- [ADVANCED_FEATURES.md](ADVANCED_FEATURES.md) - Using the analyzer

---

**Remember**: This knowledge is powerful. Use it to learn, to teach, and to make systems more secure - never to harm others or bypass security without authorization. 🔒

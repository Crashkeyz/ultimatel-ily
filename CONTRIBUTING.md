# Contributing to Ultimatel-ily

Thank you for your interest in contributing to Ultimatel-ily! This document provides guidelines and instructions for contributing to the project.

## Code of Conduct

### Our Standards

- Be respectful and inclusive
- Focus on constructive feedback
- Prioritize ethical and legal use
- Help others learn and grow
- Accept responsibility for your contributions

### Responsible Disclosure

If you discover security vulnerabilities or potential misuse scenarios:
1. Do NOT publicly disclose
2. Contact maintainers privately
3. Allow time for assessment and fixes
4. Follow coordinated disclosure practices

## How to Contribute

### Reporting Bugs

Before creating a bug report:
1. Check existing issues
2. Verify you're using the latest version
3. Test with default configuration
4. Gather relevant information

Include in your bug report:
- Firmware version
- Hardware revision
- Steps to reproduce
- Expected vs actual behavior
- Serial output logs
- Any error messages

### Suggesting Features

Feature requests should:
- Align with project goals
- Be technically feasible
- Consider legal/ethical implications
- Include clear use cases
- Respect existing architecture

### Pull Requests

#### Before You Start

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/your-feature-name`
3. **Discuss major changes**: Open an issue first for big changes

#### Development Guidelines

**Code Style:**
- Follow existing code style
- Use meaningful variable names
- Comment complex logic
- Keep functions focused and small
- Avoid unnecessary dependencies

**C++ Best Practices:**
```cpp
// Good: Clear naming, const correctness
void RFModule::setFrequency(const float freq) {
    if (freq < MIN_FREQ || freq > MAX_FREQ) {
        return;
    }
    currentFrequency = freq;
}

// Avoid: Unclear naming, missing validation
void RFModule::sf(float f) {
    x = f;
}
```

**Memory Management:**
- Use RAII principles
- Avoid memory leaks
- Be mindful of ESP32 limitations
- Test with large signals

**Error Handling:**
- Check return values
- Log errors appropriately
- Fail gracefully
- Provide useful error messages

#### Testing Your Changes

1. **Build successfully**: `pio run`
2. **Test on hardware**: If possible
3. **Check serial output**: Look for errors
4. **Test edge cases**: Not just happy path
5. **Verify no regression**: Existing features still work

#### Documentation

Update documentation for:
- New features
- Changed behavior
- New dependencies
- Configuration changes
- Breaking changes

#### Commit Messages

Use clear, descriptive commit messages:

```
Add frequency hopping support

- Implement frequency hopping algorithm
- Add configuration options
- Update display to show current frequency
- Add documentation to USAGE.md

Fixes #123
```

Format:
- First line: Short summary (50 chars max)
- Blank line
- Detailed description if needed
- Reference issues/PRs

#### Pull Request Process

1. **Update documentation**: README, USAGE, etc.
2. **Add examples**: If applicable
3. **Test thoroughly**: On actual hardware if possible
4. **Request review**: Wait for maintainer feedback
5. **Address comments**: Respond to review feedback
6. **Squash commits**: If requested

## Development Setup

### Prerequisites

- PlatformIO installed
- Git configured
- Text editor or IDE (VSCode recommended)
- LilyGO T-Embed CC1101 (for hardware testing)

### Initial Setup

```bash
# Clone your fork
git clone https://github.com/YOUR-USERNAME/ultimatel-ily.git
cd ultimatel-ily

# Add upstream remote
git remote add upstream https://github.com/Crashkeyz/ultimatel-ily.git

# Create feature branch
git checkout -b feature/my-feature
```

### Building

```bash
# Build firmware
pio run

# Upload to device
pio run --target upload

# Monitor output
pio device monitor
```

### Testing Changes

```bash
# Clean build
pio run --target clean
pio run

# Check for warnings
pio run 2>&1 | grep -i warning
```

## Project Structure

Understanding the codebase:

```
ultimatel-ily/
├── include/              # Header files
│   ├── config.h         # Configuration constants
│   ├── rf_module.h      # RF interface
│   ├── display.h        # Display interface
│   ├── storage.h        # Storage interface
│   └── rf_signal.h      # Signal structures
├── src/                 # Implementation files
│   ├── main.cpp         # Main firmware
│   ├── rf_module.cpp    # RF implementation
│   ├── display.cpp      # Display implementation
│   └── storage.cpp      # Storage implementation
├── examples/            # Example signals and docs
├── docs/                # Additional documentation
└── platformio.ini       # Build configuration
```

## Areas for Contribution

### High Priority

- Protocol decoding and identification
- Signal quality analysis
- Battery life optimization
- Additional modulation types
- Frequency hopping support

### Medium Priority

- WiFi configuration interface
- Web-based control panel
- Signal library/database
- Custom signal naming UI
- Sleep mode implementation

### Low Priority

- Visual signal analysis
- Spectrum analyzer view
- Statistics and logging
- Firmware update mechanism
- Multi-language support

### Documentation

- Usage examples
- Video tutorials
- Hardware modification guides
- Protocol documentation
- Troubleshooting expansion

## Legal and Ethical Guidelines

### What to Contribute

✅ **Acceptable:**
- Protocol analysis tools
- Educational features
- Safety improvements
- Documentation
- Bug fixes
- Performance enhancements
- UI improvements

❌ **Not Acceptable:**
- Rolling code attacks
- Encryption breaking
- Jamming capabilities
- Automated scanning tools
- Features for unauthorized access
- Anything explicitly illegal

### Responsible Development

When adding features:
1. Consider potential misuse
2. Add appropriate warnings
3. Document legal considerations
4. Implement safety checks
5. Follow responsible disclosure

## Review Process

### What We Look For

- **Functionality**: Does it work as intended?
- **Code Quality**: Is it well-written and maintainable?
- **Documentation**: Is it properly documented?
- **Testing**: Has it been adequately tested?
- **Ethics**: Does it promote responsible use?
- **Performance**: Is it efficient?

### Timeline

- Initial review: Within 1 week
- Feedback provided: As needed
- Final approval: After all concerns addressed

## Communication

### Channels

- **GitHub Issues**: Bug reports, feature requests
- **Pull Requests**: Code contributions
- **Discussions**: General questions and ideas

### Response Time

- Maintainers aim to respond within 1 week
- Complex issues may take longer
- Be patient and respectful

## Recognition

Contributors will be:
- Listed in CONTRIBUTORS.md
- Mentioned in release notes
- Credited in relevant documentation

## License

By contributing, you agree that your contributions will be licensed under the MIT License (see LICENSE file).

You also affirm that:
- You own the copyright to your contributions OR
- You have permission to contribute the code
- Your contributions don't violate any third-party rights

## Questions?

If you have questions about contributing:
1. Check existing documentation
2. Search closed issues
3. Ask in a new issue
4. Be specific about your question

## Thank You!

Your contributions help make Ultimatel-ily better for everyone. Whether you're fixing typos, reporting bugs, or adding features, every contribution is valuable.

Happy coding! 🚀

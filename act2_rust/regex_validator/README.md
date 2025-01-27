# Regex Validator

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Technical Details](#technical-details)
- [Project Structure](#project-structure)
- [Contributing](#contributing)

## Overview

Regex Validator is a modern, user-friendly graphical application built in Rust that enables real-time testing and validation of regular expressions. It provides an intuitive interface for developers and users to experiment with regex patterns and test them against multiple input strings simultaneously.

## Features

### Core Functionality
- ✨ Real-time regex pattern validation
- 🔄 Immediate feedback on pattern matching
- 📝 Multiple test string support
- 🎨 Clean, modern GUI interface
- 🎯 Preset regex patterns for common use cases

### User Interface Components
- **Pattern Input Panel**: Real-time validation with error messages
- **Test String Area**: Add/remove test strings with instant feedback
- **Preset Patterns**: Quick access to common regex patterns
- **Visual Feedback**: Color-coded results and status indicators

## Installation

### Prerequisites
- Rust toolchain (1.56 or later)
- Cargo package manager
- OpenGL compatible graphics drivers

### Build from Source
```bash
# Clone the repository
git clone https://github.com/yourusername/regex-validator.git
cd regex-validator

# Build the project
cargo build --release

# Run the application
cargo run --release
```

### System Requirements
- **OS**: Windows 10+, macOS 10.13+, or Linux with X11/Wayland
- **Memory**: 50MB minimum
- **Graphics**: OpenGL 2.1+ capable GPU

## Usage

### Basic Operation
1. Launch the application
2. Enter a regex pattern in the top input field
3. Add test strings using the central input area
4. Observe real-time matching results

### Working with Patterns
```
# Example pattern for email validation
^[\w.-]+@([\w-]+\.)+[\w-]{2,4}$
```

### Preset Patterns
The application includes several built-in patterns:
- **Email**: `^[\w.-]+@([\w-]+\.)+[\w-]{2,4}$`
- **Phone (US)**: `^\+?1?\d{10}$`
- **URL**: `^https?://[\w\-\.]+(:\d+)?(/[\w/_\.\-]*)?$`

## Technical Details

### Architecture
The application is built using the following technology stack:
- **GUI Framework**: eframe/egui
- **Regex Engine**: Rust regex crate
- **Window Management**: Native window features

### Core Components
```rust
struct RegexApp {
    pattern: String,              // Current regex pattern
    test_strings: Vec<String>,    // List of strings to test
    compiled_regex: Result<Regex, regex::Error>, // Compiled regex pattern
    new_test_string: String,      // Input buffer for new test string
    presets: HashMap<String, String>, // Predefined regex patterns
}
```

### Visual Theme Constants
```rust
const ACCENT_COLOR: Color32 = Color32::from_rgb(70, 130, 180);
const SUCCESS_COLOR: Color32 = Color32::from_rgb(50, 205, 50);
const ERROR_COLOR: Color32 = Color32::from_rgb(220, 20, 60);
```

## Project Structure

```
src/
├── main.rs          # Application entry point
├── app.rs           # Main application logic
├── ui/              # UI components
│   ├── pattern.rs   # Pattern input panel
│   ├── testing.rs   # Test string panel
│   └── presets.rs   # Preset patterns panel
└── utils/           # Utility functions
```

### Key Components
- **Window Configuration**: 800x600 pixels default size
- **Top Panel**: Pattern input and validation
- **Right Panel**: Preset patterns (200px width)
- **Central Panel**: Test string management

## Contributing

### Getting Started
1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to your fork
5. Submit a Pull Request

### Code Style
- Follow Rust standard formatting guidelines
- Use `cargo fmt` before committing
- Run `cargo clippy` to catch common mistakes

### Testing
- Write unit tests for new features
- Ensure all tests pass: `cargo test`
- Include UI tests where applicable

### Commit Guidelines
- Use descriptive commit messages
- Reference issues in commits
- Keep commits focused and atomic

### Bug Reports
- Use the GitHub issue tracker
- Include steps to reproduce
- Provide system information
- Add screenshots if relevant

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- The Rust ecosystem and community
- The egui framework developers
- All contributors and users


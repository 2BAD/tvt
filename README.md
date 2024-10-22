# TVT Device SDK

[![NPM version](https://img.shields.io/npm/v/@2bad/tvt)](https://www.npmjs.com/package/@2bad/tvt)
[![License](https://img.shields.io/npm/l/@2bad/tvt)](https://opensource.org/license/MIT)
[![GitHub Build Status](https://img.shields.io/github/actions/workflow/status/2BAD/ryanair/build.yml)](https://github.com/2BAD/ryanair/actions/workflows/build.yml)
[![Code coverage](https://img.shields.io/codecov/c/github/2BAD/tvt)](https://codecov.io/gh/2BAD/ryanair)
[![Written in TypeScript](https://img.shields.io/github/languages/top/2BAD/tvt)](https://www.typescriptlang.org/)


A modern TypeScript SDK for TVT CCTV devices, providing a clean and type-safe interface for device management, monitoring, and control. This project is the result of extensive research and reverse engineering of TVT (Tongwei Video Technology) CCTV systems.

## 🌟 Features

- **Type-Safe API**: Full TypeScript support with comprehensive type definitions
- **Lazy Loading**: Efficient resource management with on-demand library loading
- **Error Handling**: Robust error handling with detailed error messages
- **Logging**: Built-in debug logging for easier troubleshooting
- **Documentation**: Extensive JSDoc documentation for all methods

## 📦 Installation

```bash
npm install tvt
```

## 🚀 Quick Start

```typescript
import { Device } from 'tvt'

// Create a new device instance
const device = new Device('192.168.1.100', 9008)

// Login to the device
device.login('admin', 'password')

// Get device information
const info = device.info
console.log(`Connected to ${info.deviceName}`)

// Capture a snapshot
device.saveSnapshot(0, '/path/to/snapshot.jpg')

// Clean up
device.dispose()
```

## 🔧 Core Features

### Device Management
- Device discovery
- Connection management
- Authentication
- Device information retrieval

### Security Features
- Alarm management
- Manual alarm triggering
- Event monitoring

### Media Operations
- Snapshot capture
- Live stream management
- Video recording

## 📚 API Reference

### Device Class

The main interface for interacting with TVT devices.

```typescript
class Device {
  constructor(ip: string, port?: number, settings?: Settings)
  login(user: string, pass: string): boolean
  logout(): boolean
  triggerAlarm(value: boolean): boolean
  saveSnapshot(channel: number, filePath: string): boolean
  // ... and more
}
```

See [API Documentation](source/lib/sdk.ts) for detailed method descriptions.

## 🛠️ Development

### Prerequisites

- Node.js 18 or higher
- Linux operating system

### Building from Source

```bash
git clone https://github.com/yourusername/tvt.git
cd tvt
npm install
npm run build
```

### Running Tests

```bash
npm test
```

## 📁 Project Structure

```
tvt/
├── bin/            # Precompiled SDK libraries
├── docs/           # Documentation and examples
├── proto/          # Protocol definitions and dissectors
└── source/         # TypeScript implementation
    ├── lib/        # Core SDK implementation
    ├── helpers/    # Utility functions
    └── types/      # TypeScript type definitions
```

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

### Development Guidelines

1. Follow TypeScript best practices
2. Include tests for new features
3. Update documentation as needed
4. Follow the existing code style

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## ⚠️ Disclaimer

This project is not officially associated with TVT Digital Technology Co., Ltd. It is an independent implementation based on research and reverse engineering. Use at your own risk.

## 🙏 Acknowledgments

- TVT Digital Technology for their CCTV systems
- The open-source community for various tools and libraries used in this project
- Contributors who have helped improve this SDK

## 📬 Support

- Create an issue for bug reports or feature requests

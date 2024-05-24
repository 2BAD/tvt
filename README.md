# TVT CCTV Research Repository

This repository is the result of extensive research, disassembling, and reverse engineering efforts focused on CCTV cameras produced by Tongwei Video Technology Co., Ltd. (TVT). Our aim is to document and facilitate a deep understanding and interaction with TVT CCTV systems, shedding light on proprietary technologies and protocols.

## Directory Structure

### `bin`

This directory contains precompiled SDK libraries needed for interfacing with TVT CCTV devices. These are essential for developing custom applications that can interact with TVT's proprietary protocols and device functionalities.

### `docs`

This directory holds comprehensive documentation provided by TVT. It includes:

- The original SDK manual
- Header files
- A variety of demo projects implemented in multiple programming languages
- These resources are invaluable for understanding the capabilities and proper usage of the TVT SDK.

### `proto`

In this directory, you will find the Wireshark dissector code for the proprietary network IPC protocol used by TVT devices. This dissector enables the analysis and debugging of network traffic to and from the CCTV cameras, making it easier to understand and reverse engineer the communication protocol.

### `source`

This directory contains a TypeScript implementation of a device client. The client interacts with the TVT devices by making calls to a shared library via Foreign Function Interface (FFI). This implementation serves as a practical example of how to build applications that can communicate with TVT CCTV devices using TypeScript.

## Getting Started

1. Clone the repository:

   ```bash
   git clone https://github.com/2BAD/tvt.git
   cd tvt
   npm install
   npm run build
   ```

2. Review the documentation in the `docs` directory to understand the SDK and its functionalities.
3. If you are looking to analyze network traffic, refer to the `proto` directory for the Wireshark dissector code. Follow the instructions within to integrate it into Wireshark.
4. To develop custom applications using the precompiled SDK, navigate to the `source` directory and explore the TypeScript client implementation. This can serve as a template or guide for your own projects.

## Contributing

We welcome contributions! If you find a bug or want to request a new feature, please open an issue. If you want to submit a bug fix or new feature, please open a pull request.

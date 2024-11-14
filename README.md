# Wi-Fi Sniffer for UPOD

## Project Overview

Wi-Fi Sniffer for UPOD is an IoT-based Wi-Fi network scanner using the ESP8266 microcontroller. The project scans for nearby Wi-Fi networks, categorizes devices based on signal strength, and uploads the results to the UPOD. It helps monitor the presence of people in a household, particularly for tracking whether elderly individuals are at home by detecting connected devices.

## Features

- **Wi-Fi Network Scanning**: Scans for nearby Wi-Fi networks and retrieves SSID and signal strength (RSSI).
- **Device Categorization**: Categorizes devices into high signal and low signal strength groups.
- **Presence Detection**: Estimates whether someone is at home based on the number of connected devices.
- **Upload to UPOD**: Uploads Wi-Fi scan results (including device count and details) to the UPOD.

## Installation

### Hardware Requirements

- ESP8266 Development Board (e.g., NodeMCU or Wemos D1 mini)
- Wi-Fi network (for connection and scanning)

### Software Requirements

- Arduino IDE or PlatformIO
- ESP8266 libraries installed
- UPOD set up with a working REST API.

### Environment Setup

1. Open Arduino IDE, go to `Tools` -> `Board`, and select the appropriate ESP8266 board (e.g., `NodeMCU 1.0`).
2. Install the `ESP8266` library. In Arduino IDE, go to `Tools` -> `Manage Libraries`, search for and install `ESP8266`.
3. Install the `WiFiClientSecure` and `ESP8266HTTPClient` libraries, which are necessary for handling HTTPS requests and Wi-Fi connections.

### Configuration

1. Open the code and update the following parameters:
   - `ssid`: Your Wi-Fi network name.
   - `password`: Your Wi-Fi password.
   - `wordpressHost`: Your UPOD system URL (e.g., `https://yourupodsite.com`).
   - `username`: The username for API access.
   - `app_password`: The application password for API authentication.

### Upload the Code

1. Upload the code to the ESP8266 development board.
2. Open the Serial Monitor and check for device connection and scanning status.

## Usage

Once uploaded, the ESP8266 will scan for nearby Wi-Fi networks and upload the scan results to the UPOD. The uploaded posts will contain the following details:

- **Wi-Fi Scan Results**: List of detected Wi-Fi networks with SSID and signal strength.
- **Device Count**: Estimated number of people in the house based on detected device count.

The post will automatically publish with the title `"Wi-Fi Sniffer"` and content containing the list of devices and the number of devices detected.

## Example Output

Example of the uploaded post content:

Title: Wi-Fi Sniffer

Content: Estimated number of people (High Signal): 2 High Signal Devices (Above -70 dBm): MAC: 98:2D:BA:40:C9:1F, Signal: -65 dBm MAC: 98:2D:BA:41:2E
, Signal: -54 dBm

Other Devices Detected: 3 Low Signal Devices (Below -70 dBm): MAC: 88:5A:92:20:A1:6F, Signal: -85 dBm MAC: 12:34:56:78:90
, Signal: -80 dBm ...


## License

This project is licensed under the [GNU General Public License v3.0 (GPL-3.0)](https://opensource.org/licenses/GPL-3.0). This allows for free use, modification, and distribution of the code, but any derivative works must also be licensed under the GPL-3.0 license.

## Contribution

If you have any suggestions for improvements or find any bugs, please feel free to open an Issue or submit a Pull Request. Thank you for contributing!

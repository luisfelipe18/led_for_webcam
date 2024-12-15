# ESP-01S LED Control 🔦

An IoT project that turns an ESP-01S into a LED controller with web interface and physical control. This repository implements a LED lamp to illuminate you when you have virtual meetings and your location does not have good lighting. The project requires an ESP-01S (ESP 8266)


## 🎥 Demo

[![ESP-01S LED Control Demo](https://img.youtube.com/vi/85AhwS4iVeg/0.jpg)](https://youtube.com/shorts/85AhwS4iVeg)

Click on the image above to watch the demo video!


## 🌟 Features

- Remote LED control through web interface
- Physical switch for manual control
- Blinking mode with adjustable frequency
- mDNS support for easy local access
- Responsive web interface
- Serial port status monitoring

## 📋 Prerequisites

### Hardware
- ESP-01S
- LED (connected to GPIO2)
- Push button (connected to GPIO0)
- 3.3V power supply
- USB programmer for ESP-01S

### Software
- Arduino IDE
- ESP8266 board for Arduino (ESP-01S)
- Required libraries:
  - ESP8266WiFi
  - ESP8266WebServer
  - ESP8266mDNS

## 🔧 Configuration

1. Clone this repository or download the code
2. Open the `.ino` file in Arduino IDE
3. Configure WiFi credentials:
   ```cpp
   const char* ssid = "YOUR-WIFI-SSID";
   const char* password = "YOUR-WIFI-PASSWORD";
   ```
4. Configure hostname if desired:
   ```cpp
   const char* hostname = "flashlight";
   ```

## 📌 Connections

- GPIO2 (PIN-4): LED (with appropriate resistor)
- GPIO0 (PIN-5): Push button (with pull-up)
- VCC (PIN-8): 3.3V
- GND (PIN-1): GND

## 🚀 Installation

1. Connect the ESP-01S to the USB programmer
2. Select "Generic ESP8266 Module" board in Arduino IDE
3. Configure the following parameters:
   - Flash Size: 1MB
   - Flash Mode: DIO
   - Flash Frequency: 40MHz
   - CPU Frequency: 80MHz
4. Upload the code

## 💻 Usage

### Web Access
1. The device will automatically connect to your WiFi network
2. Access through:
   - `http://flashlight.local` (if your device supports mDNS)
   - The IP address shown in the serial monitor

### Web Interface
- "Toggle LED" button: Turns the LED on/off
- "Toggle Blink" button: Activates/deactivates blinking mode
- Frequency control: Adjusts blinking speed (in Hz)

### Manual Control
- Press the physical button to toggle LED state

## 🔍 Monitoring
- IP address is displayed on the serial monitor every 10 seconds
- Serial port speed: 115200 baud

## 🛠️ Customization

You can modify the following constants according to your needs:
```cpp
const int LED_PIN = 2;      // LED pin
const int SWITCH_PIN = 0;   // Push button pin
const unsigned long IP_PRINT_INTERVAL = 10000; // IP printing interval
```

## 📄 License

This project is under the MIT License - see the LICENSE.md file for details

## ✨ Contributing

Contributions are welcome:
1. Fork the project
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

## 🐛 Issue Reporting

If you find any issues or have a suggestion, please open an issue in the repository.
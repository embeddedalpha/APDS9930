# APDS9930 Sensor Library

Welcome to the APDS9930 Sensor Library! This repository contains a comprehensive library for interfacing with the APDS9930 sensor, which combines ambient light sensing (ALS) and proximity detection capabilities. Designed for ease of use, this library enables quick integration of the APDS9930 sensor into your projects, providing accurate and reliable light and proximity measurements.

## Features

- **Ambient Light Sensing**: Measure ambient light intensity in lux with high precision.
- **Proximity Detection**: Detect the presence of nearby objects using IR LED and photodiode.
- **I2C Communication**: Simple communication with the sensor via the I2C interface.
- **Configurable Parameters**: Adjust ALS and proximity sensor settings to suit your application needs.
- **Interrupt Support**: Utilize interrupt pins for efficient and low-power sensing applications.
- **Example Code**: Easy-to-follow examples to help you get started quickly.


## Getting Started

### Prerequisites

- STM32F4x
- APDS9930 sensor module
- USB-to-UART Converter
- Jumper Cables

### Installation

1. Clone this repository to your local machine:
    ```bash
    git clone https://github.com/yourusername/APDS9930-Sensor-Library.git
    ```
2. Include the library in your project by adding the source files to your development environment.

### Example Projects

- **Ambient Light Logger**: Log ambient light levels to a Virtual Com Port. [Link](Example/Ambient%20Light%20Logger.c) 

- **Proximity-Based Device Activation**: Activate a device when an object is detected within a specified range.

- **Automatic Display Brightness**: Adjust display brightness based on ambient light conditions.

## Contributing

Contributions are welcome! Please fork this repository, create a new branch for your feature or bugfix, and submit a pull request. Make sure to follow the coding standards and include relevant tests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.

## Acknowledgements

Special thanks to the community and contributors who have helped improve this library.

## Contact

For support or inquiries, please open an issue on this repository or contact [kunalsalvius@example.com](mailto:kunalsalvius.email@example.com).

---

Feel free to explore the documentation and source code to better understand how to use the APDS9930 sensor in your projects. Happy coding!

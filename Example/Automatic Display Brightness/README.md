# Automatic Display Brightness

This project aims to dynamically adjust the brightness of a display based on ambient light conditions using the APDS9930 sensor. This ensures optimal screen visibility and power efficiency by adapting to the surrounding light environment.


## Introduction

The Automatic Display Brightness project utilizes the APDS9930 sensor to measure ambient light levels and adjust the display brightness accordingly. This is particularly useful in environments where lighting conditions change frequently, ensuring a comfortable viewing experience while conserving energy.

## Features

- **Real-time Ambient Light Measurement**: Continuously monitor ambient light intensity.
- **Dynamic Brightness Adjustment**: Automatically adjust display brightness based on light levels.
- **Configurable Parameters**: Customize light thresholds and brightness levels to suit your needs.
- **Efficient Power Usage**: Optimize display power consumption by adapting to environmental conditions.

## Hardware Requirements

- APDS9930 sensor module
- Display (e.g., LCD, OLED) Here LED is used
- STM32F40x MCU
- Connecting Wires

## Software Requirements

- STM32CubeIDE
- APDS9930 sensor library
- Drivers present in the repo

## Installation

 **Install the required libraries**:
    - APDS9930 sensor library
    - Display library compatible with your display module


## Usage

1. **Connect the hardware**:
    - Connect the APDS9930 sensor to your microcontroller via the I2C interface.
    - Connect your display to the microcontroller as per the display's requirements.

2. **Load the code**:
    - Open the `Automatic_Display_Brightness.c`.
    - Change the void `Automatic_Display_Brightness()` to `void main()`
    - Flash your microcontroller.

3. **Run the project**:
    - The microcontroller will start reading ambient light levels from the APDS9930 sensor.
    - The display brightness will be adjusted automatically based on the measured light intensity.



## Contributing

Contributions are welcome! To contribute:

1. Fork this repository.
2. Create a new branch for your feature or bugfix.
3. Commit your changes and push the branch to your fork.
4. Submit a pull request to this repository.

Please ensure your code follows the existing style and includes relevant tests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

For support or inquiries, please open an issue on this repository or contact [your.email@example.com](mailto:your.email@example.com).

---

We hope this project helps you create adaptive and energy-efficient display systems. Happy coding!
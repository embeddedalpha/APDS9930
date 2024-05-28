# Proximity-Based Device Activation

 This project demonstrates how to use the APDS9930 sensor to activate a device when an object is detected within a specified range. This can be applied to various use cases such as touchless controls, automated lighting, and security systems.



## Introduction

The Proximity-Based Device Activation project uses the APDS9930 sensor to detect the presence of nearby objects and trigger an activation signal. This project is ideal for implementing touchless interfaces, automatic door openers, and other applications where device activation is needed based on proximity detection.

## Features

- **Proximity Detection**: Detect objects within a specified range using the APDS9930 sensor.
- **Device Activation**: Trigger a device activation signal when an object is detected.
- **Configurable Range**: Set the detection range to suit your application.
- **Efficient Operation**: Low power consumption during standby and active detection modes.

## Hardware Requirements

- APDS9930 sensor module
- Device to be activated (here a VCOM prompt)
- STM32F4x MCU
- Jumper wires

## Software Requirements

- STM32CubeIDE (or your preferred development environment)
- APDS9930 sensor library

## Installation


 **Install the required libraries**:
    - APDS9930 sensor library

    You can install this library via the Arduino Library Manager or manually add it to your project.

## Usage

1. **Connect the hardware**:
    - Connect the APDS9930 sensor to your microcontroller via the I2C interface.
    - Connect the device to be activated to a digital output pin on the microcontroller.

2. **Load the code**:
    - Open the `Proximity_Based_Device_Activation.c`.
    - Change the `void Proximity_Based_Device_Activation()` to `void main()`
    - Flash your microcontroller.

3. **Run the project**:
    - The microcontroller will start reading proximity data from the APDS9930 sensor.
    - When an object is detected within the specified range, the device connected to the activation pin will be triggered.


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

We hope this project helps you create innovative and touchless control systems. Happy coding!
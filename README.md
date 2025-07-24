# 🎓 Embedded Systems Internship Portfolio: nRF52832 Projects
![C](https://img.shields.io/badge/Language-C-A8B9CC?style=for-the-badge&logo=c&logoColor=white)
![MCU](https://img.shields.io/badge/MCU-Nordic%20nRF52832-00A9CE?style=for-the-badge&logo=nordicsemiconductor&logoColor=white)
![BLE](https://img.shields.io/badge/Protocol-Bluetooth%20Low%20Energy-0082FC?style=for-the-badge&logo=bluetooth&logoColor=white)
![IDE](https://img.shields.io/badge/IDE-Segger%20Embedded%20Studio-1A1A1A?style=for-the-badge&logo=segger&logoColor=white)

This repository showcases the projects and skills I developed during my summer 2024 internship at **Zistpardazesh Nasir (Zistel)**, a knowledge-based company specializing in smart medical devices. The primary focus of the internship was hands-on embedded systems development using the **Nordic Semiconductor nRF52832 System-on-Chip (SoC)**.

## 💻 Core Technologies & Skills Acquired
* **MCU Programming**: Advanced C programming for embedded systems on the **ARM Cortex-M4** architecture.
* **Development Environment**: Proficient use of **Segger Embedded Studio** IDE and the **J-Link** debugger for programming and real-time debugging.
* **Nordic SDK**: In-depth work with the nRF5 SDK, including driver configuration and library usage.
* **Peripherals**: Hands-on experience with a wide range of MCU peripherals:
    * **GPIO** & **GPIOTE** (Interrupt-driven I/O)
    * **PWM** (Pulse Width Modulation) for analog-like control
    * **App Timer** & Hardware Timers
    * **UART**, **SPI**, and **I2C (TWI)** serial communication protocols
    * **SAADC** (Successive Approximation Analog-to-Digital Converter)
* **Wireless Communication**: Deep dive into the **Bluetooth Low Energy (BLE)** protocol stack, including GAP and GATT services.

---

## 🚀 Project Showcase
The internship followed a structured learning path, starting with basic peripheral control and culminating in a complete Bluetooth Low Energy application. The projects were developed on a custom PCB designed for Zistel's future ECG and blood pressure monitor products.

<details>
<summary>
  <strong>1. Foundational I/O and Control (GPIO, GPIOTE, PWM)</strong>
</summary>

This series of projects focused on mastering the control of general-purpose I/O.
* **RGB LED Control via GPIO**: Implemented a simple state machine to cycle through Red, Green, and Blue colors on an RGB LED by polling a push-button.
* **Interrupt-Driven Control with GPIOTE**: Advanced the previous project by using the GPIOTE peripheral to handle button presses via interrupts, eliminating the need for polling and improving power efficiency.
* **Brightness Control with PWM**: Implemented a fade effect for an LED by using the PWM peripheral. The duty cycle was adjusted within the button's interrupt handler to gradually increase or decrease the LED's brightness.
</details>

<details>
<summary>
  <strong>2. Debugging and Serial Communication (Logger, UART, SPI, I2C)</strong>
</summary>

These projects focused on data communication between the MCU and external devices or a host PC.
* **Segger RTT Logger**: Utilized the Segger J-Link's Real-Time Transfer (RTT) capability to print debug messages and variable states to a terminal, enabling efficient, non-intrusive debugging.
* **OLED Display Control (I2C)**: Interfaced with an SSD1306 OLED display using the I2C (TWI) protocol. Developed a custom library to display text and graphics, including the company and university logos.
* **Timer and UART Communication**: Created a real-time clock using the `app_timer` library and transmitted the elapsed time (minutes:seconds) to a PC via a USB-to-TTL (CP2102) adapter using the UART protocol. Also implemented receiving commands from the PC to control the onboard RGB LED.
* **SPI Peripheral Communication**: Implemented the SPI protocol to write to and read from an external device's register, demonstrating mastery of another key serial communication standard.
</details>

<details>
<summary>
  <strong>3. Analog Sensing (SAADC)</strong>
</summary>

This project involved interfacing with the analog world.
* **Analog Voltage Reading**: Configured the Successive Approximation Analog-to-Digital Converter (SAADC) to read an analog voltage from an input pin. The 10-bit digital result was then converted back to a voltage level and monitored in the debugger to verify its accuracy against a signal generator's output.
</details>

<details>
<summary>
  <strong>4. Capstone Project: Bluetooth Low Energy (BLE) Peripheral</strong>
</summary>

The culmination of the internship was an in-depth study of the BLE protocol and the development of a fully functional BLE peripheral device.
* **Deep Dive into BLE Theory**: The initial phase involved a comprehensive study of the entire BLE protocol stack, including the Physical Layer (PHY), Link Layer (LL), Host Controller Interface (HCI), L2CAP, and the crucial **Generic Access Profile (GAP)** and **Generic Attribute Profile (GATT)**.
* **BLE Peripheral Application**: Developed an application based on Nordic's LED Button Service (LBS) example. The key functionalities are:
    * The device **advertises** itself with a custom name (`Naghiloo_intern`).
    * A central device (e.g., a smartphone using the **nRF Connect** or **nRF Blinky** app) can scan for and **connect** to the device.
    * Once connected, the central can remotely turn an **LED** on or off by writing to a GATT characteristic.
    * When the onboard **button** is pressed, the device sends a **GATT Notification** to the central, updating its status in the app.
    * The device uses different LEDs to visually indicate its status (advertising, connected).
</details>

## 🙏 Acknowledgments
I would like to extend my sincere gratitude to my internship supervisor, **Dr. Hossein Hosseininejad**, the technical lead **Dr. Danial Katoozian**, and the entire engineering team at **Zistel** for their invaluable mentorship and support throughout this learning experience.

## ✍️ Author
* **Ali Naghiloo** (40010093)

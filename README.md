# Precision Measurement System: Comparative Analysis of Dual-Slope (ICL7107) and SAR (STM32F446RE) ADCs
Embedded systems project comparing Dual-Slope (ICL7107) and SAR (STM32F446RE) ADC architectures through analog circuit design, bare-metal firmware, and PCB development to evaluate accuracy, speed, noise immunity, and implementation complexity.

## Overview

Analog-to-Digital Converters (ADCs) play a critical role in embedded systems by converting analog signals into digital data for processing. Different ADC architectures offer unique advantages depending on application requirements such as speed, accuracy, and noise performance.

This project implements and compares two widely used ADC architectures: a Dual-Slope ADC using the ICL7107 and a 12-bit Successive Approximation Register (SAR) ADC integrated within the STM32F446RE microcontroller. Both systems were developed and tested to study their performance, implementation complexity, and suitability for precision voltage measurement applications




## Objectives

* Design and implement a precision voltage measurement system.
* Develop bare-metal firmware for the STM32F446RE using register-level programming.
* Design, test, and validate the analog measurement circuit based on the ICL7107.
* Design a custom PCB to improve reliability and measurement stability.
* Compare the performance of Dual-Slope (ICL7107) and SAR (STM32F446RE) ADC architectures in terms of accuracy, conversion speed, noise immunity, and implementation complexity.

## Features

* Bare-metal STM32F446RE programming
* Register-level ADC configuration
* UART-based voltage monitoring
* Analog signal conditioning
* Precision voltage measurement
* Serial communication through USART using PuTTY


## Hardware Components

* STM32F446RE Nucleo Board
* ICL7107 Dual-Slope ADC
* LM7805 Voltage Regulator
* Precision Resistors
* Capacitors
* Voltage Divider Network
* Seven Segment Display
* Custom PCB


## Software & Tools

* Embedded C
* STM32CubeIDE
* GitHub
* KiCad / EasyEDA


## System Architecture

The input voltage is simultaneously processed through two independent measurement paths. The first path uses the ICL7107 Dual-Slope ADC for precision analog measurement, while the second path scales the input voltage through a voltage divider before sampling it using the STM32F446RE's internal 12-bit SAR ADC. The measured data is processed by the microcontroller and transmitted over UART for monitoring and analysis.

## Working Principle

### Dual-Slope ADC (ICL7107)

The Dual-Slope ADC integrates the unknown input voltage for a fixed interval and then integrates a reference voltage of opposite polarity until the integrator output returns to zero. The measured discharge time is proportional to the input voltage, providing excellent noise rejection and high measurement stability.

### SAR ADC (STM32F446RE)

The STM32F446RE employs a 12-bit Successive Approximation Register (SAR) ADC that performs a binary search to determine the digital representation of the analog input voltage. This architecture enables fast conversion speeds while maintaining good accuracy for embedded applications.


## Hardware Design

The hardware consists of a regulated 5 V power supply, voltage divider network, analog conditioning circuitry, the ICL7107-based measurement circuit, and the STM32F446RE development board. The complete design was later implemented on a custom PCB to improve measurement stability and reduce parasitic effects.

## Firmware Implementation

The STM32 firmware was developed using Embedded C with direct register-level programming. The firmware initializes the ADC peripheral, continuously samples the input voltage, converts the digital value into its corresponding voltage, and transmits the results through USART for real-time monitoring.
## Performance Comparison

| Parameter            | ICL7107 (Dual-Slope) | STM32F446RE (SAR)        |
| -------------------- | -------------------- | ------------------------ |
| Conversion Method    | Dual-Slope           | Successive Approximation |
| Resolution           | 3½ Digit             | 12-bit                   |
| Conversion Speed     | Slow                 | Fast                     |
| Noise Immunity       | Excellent            | Moderate                 |
| Hardware Complexity  | High                 | Low                      |
| Embedded Integration | Limited              | Excellent                |


## Prototype Validation

Both ADC implementations were supplied with identical input voltages under the same operating conditions. Their outputs were compared using a calibrated digital multimeter as the reference instrument to evaluate measurement accuracy, conversion speed, and stability.

### Photos
### Complete Hardware Prototype
<img width="3852" height="3019" alt="IMG_9010" src="https://github.com/user-attachments/assets/310bd789-148a-4c7c-a5dd-d157f93f1e24" />

#### STM32 Side
<img width="4624" height="3213" alt="IMG_9038" src="https://github.com/user-attachments/assets/08c7c879-c37a-4829-b8a0-ebbe2a831005" />

#### Visible Result



<table>
<tr>

<td align="center" width="50%">

### Hardware Prototype

<img src="https://github.com/user-attachments/assets/e780d346-2a50-4fc3-a005-9f59933ff91e" width="95%">

<br>

**Figure 1.** Breadboard implementation of the ICL7107 voltage measurement system.

</td>

<td align="center" width="50%">

### Software Output

<img src="https://github.com/user-attachments/assets/57bbd210-3bf7-4027-b6e4-8763ccf24eec"
 width="95%">

<br>

**Figure 2.** Real-time voltage measurements transmitted over USART using PuTTY.

</td>

</tr>
</table>

The hardware prototype was tested using the same input voltage for both the ICL7107 Dual-Slope ADC and the STM32F446RE SAR ADC. The ICL7107 displays the measured voltage on the seven-segment display, while the STM32F446RE continuously transmits the measured voltage through USART to a PC terminal. 

### Schematics
<img width="1348" height="833" alt="Screenshot 2026-07-17 233228" src="https://github.com/user-attachments/assets/2acd0158-08b5-4bea-bf99-005f30f4c212" />


### PCB
<img width="672" height="610" alt="image" src="https://github.com/user-attachments/assets/8a714aba-d82f-4995-8b56-1ab010c849fe" />


## Results

The STM32F446RE-based SAR ADC demonstrated more stable measurements in the implemented prototype. The ICL7107 Dual-Slope ADC performance was influenced by breadboard parasitics, analog noise, and calibration limitations, resulting in larger measurement variations.

These observations emphasize the importance of hardware implementation quality when evaluating ADC architectures and provide practical insight into the trade-offs between precision analog and embedded digital measurement systems.

## Challenges

- Breadboard parasitic capacitance affected analog measurements.
- Stable negative voltage generation for the ICL7107 required multiple iterations.
- ADC calibration was necessary to improve measurement accuracy.

## References

* STM32F446RE Reference Manual
* STM32F446RE Datasheet
* ICL7107 Datasheet

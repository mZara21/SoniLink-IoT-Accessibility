# SoniLink: IoT Shield for Auditory Hypersensitivity 

![IoT](https://img.shields.io/badge/Domain-Internet_of_Things-007396?style=for-the-badge)
![HCI](https://img.shields.io/badge/UX%2FUI-Human--Computer_Interaction-8A2BE2?style=for-the-badge)
![Figma](https://img.shields.io/badge/Figma-F24E1E?style=for-the-badge&logo=figma&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)

**SoniLink** is a decentralized Body Area Network (BAN) IoT ecosystem designed to mitigate auditory hypersensitivity (hyperacusis) in children with Autism Spectrum Disorder (ASD). 

Unlike traditional passive noise-canceling headphones that completely isolate the child and cause social alienation, SoniLink acts as an "Invisible Sentinel". It fuses environmental acoustic monitoring with real-time biometric stress tracking to actively protect the user from unexpected auditory pain while promoting a strong sense of agency and internal locus of control.

## System Architecture

The hardware topology is designed for low latency, affordability, and asynchronous operation:

*   **The "Brain" (ANC Headphones):** The master node equipped with a Digital Signal Processor (DSP). It monitors external decibels (dB), maintains a 30-second audio ring-buffer, and executes the core decision logic.
*   **The Biometric Bracelet (Slave Node):** A low-cost wearable equipped with a BITalino module to track Heart Rate Variability (HRV) and Galvanic Skin Response (GSR). It features a coreless haptic vibration motor and a capacitive physical button].
*   **Parental Hub (Tablet/Smartphone):** A dual-profile platform (Parent/Child) that synchronizes with the hardware via Bluetooth Low Energy (BLE). It uses strict AES-128 encrypted Whitelisting protocols to reject unauthorized connections and ensure GDPR compliance.

## HCI & UX Design Principles

The user interface and interaction model were strictly tailored for neurodivergent profiles:

*   **Low Arousal Approach:** The UI avoids pure white backgrounds (which cause visual fatigue) and highly saturated colors. It uses serene blues (#005088) and emerald greens to stabilize the amygdala response, reducing cognitive load during panic.
*   **Agency vs. Automatic Override:** When a loud noise is detected, the bracelet provides a gentle haptic vibration, giving the child a 1.5-second "Agency Window" to manually press the button and activate the ANC shield. Total automation (Automatic Override) is only engaged as a safety net if extreme biometric stress is detected alongside motor paralysis.
*   **Gamification & Systematic Desensitization:** Includes a "Sound Laboratory" where the child uses large visual sliders to lower the volume of aversive sounds (depicted as cute monsters), earning virtual "Mystery Eggs" as a reward for building tolerance.
*   **Collective Intelligence:** Parents can listen to captured audio loops (e.g., a vacuum cleaner) and easily tag them. The system uses these tags to instantly generate therapeutic Multimedia Social Stories from a community-validated library.

## Prototyping & Testing

The project was validated through a hybrid simulation architecture:
*   **High-Fidelity Visual Prototype:** Developed in **Figma**, mapping the complete state machine and Low Arousal UI dynamics. Evaluated via AI-assisted Cognitive Walkthroughs.
*   **Low-Fidelity Hardware Proof of Concept:** Built with an **Arduino UNO (C++)**, utilizing sound sensors, a capacitive button, relays (to simulate haptic feedback), and an LED matrix to externalize the hidden algorithmic states and validate zero-latency sensor-motor interaction.

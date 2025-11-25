# ATOM (Atmega To Open Mapping)

**ATOM** is a specialized control software designed to bridge the gap between analog mixers and digital software.

Originally developed exclusively for **RMA devices (Redstudio Mixer Analog)**, ATOM is now free for anyone to use for both personal and commercial purposes. Starting with version 1.6, the core software is available to the public, allowing third-party developers and DIY enthusiasts to build their own custom mixers without needing to code their own control software from scratch.

## 🎛️ What is ATOM?
ATOM allows you to map physical hardware controls (faders, knobs, switches sending analog data) based on Atmega microcontrollers (like Arduino) to a single unified software interface. It then re-streams this data to various protocols, such as the Reaper API or MIDI.

It handles the communication "from what" and "to whom," letting you build any kind of mixer you want—from a single analog button that emulates a mixer function, to a complex setup with up to 10 individual mixers with individual outputs (more are supported, but stability is not guaranteed).

## 🚀 Release Channels & Compatibility
ATOM operates on a **Staggered Release Model**.

| Feature | RMA Owner (Official Hardware) | Public / DIY User |
| :--- | :--- | :--- |
| **Current Version** | 1.7.2.0 | 1.6.1.0 |
| **Updates** | Immediate | Delayed (Catch-up cycle) |
| **Firmware** | Official Proprietary Firmware | DIY / Third-party |
| **RMA Extra Features** | ✅ Supported | 🔒 Not supported |

**Note:** While public versions are currently a few steps behind the RMA user release, the roadmap aims to synchronize both versions in the near future.

## ✨ Key Features
* **Universal Mapping:** Flexible protocol to map custom DIY hardware inputs or virtual inputs (non-official firmware can create virtual analog sliders without physical hardware) to any supported output via the ATOM interface.
* **Universal Version Compatibility:** The software is designed to be compatible with newer or older firmware. Regardless of the software or firmware version you are working on, it is guaranteed to work seamlessly (excluding missing features). Updates are optional, even if tutorials and demo firmware are based on newer software versions.
* **Visual Feedback:** Real-time metering and state monitoring for your hardware.
* **DIY Friendly:** Includes "Demo Firmware" and a tutorial file to get your Atmega chip talking to ATOM quickly.
* **Dynamic:** The software dynamically re-adjusts to each connected device.
* **Profile Management:** Built-in profile manager for individual slots (if supported) and a global mapping profile (separate from settings) that is easy to save, load, and share with other PCs.
* **Background Friendly:** Supports running in the background with an overlay for monitoring. It is extremely lightweight (performance may vary based on hardware communication speed) and offers multiple "Performance vs. Quality" modes.
* **LoopMIDI Compatible:** Allows output as MIDI devices and with easy connection and auto-launch/auto-close for loopmidi users. 
  *(Note: loopMIDI is a separate software created by Tobias Erichsen. It is not included in ATOM and must be downloaded installed separately. This compatibility feature is provided as a convenience and may be removed in future versions if requested by the original creator.)*

## 🛠️ Getting Started (For DIY Users)
If you are building your own mixer, follow these steps to use ATOM:

1.  **Download the Software:** Check the [Releases] tab for the latest Public version.
2.  **Flash the Demo Firmware:** (For a quick trial) Navigate to the `/firmware/demo` folder.
3.  **Connect:** Plug your hardware in via USB/Serial.
4.  **Upload:** Upload the `.ino` file to your Atmega-compatible board (e.g., Arduino Uno) using the latest Arduino IDE.
5.  **Configure:** Launch ATOM. The software should recognize the Demo Firmware signature and allow basic mapping (Note: Demo firmware does not support saving profiles to the chip).

*Please check the `/firmware/demo/wiring/` folder for the wiring diagram required for the Demo Firmware.*

## 🔒 RMA Official Firmware Features
Certain advanced functions and deep-level hardware diagnostics are only available when using **RMA Official Firmware** (Official Hardware).

* **Firmware Optimizer:** Special deep-integration features specific to RMA firmware for better optimization of both hardware and PC resources.
* **Health Check:** Built-in slider health monitoring system that allows users to check signal integrity and know exactly when to change a slider module before it fails (Modular replacement only available on 'Fat' models).
* **High Speed Mode:** Enables a new optimized communication API with faster bandwidth for demanding setups with many sliders.
* **Noise Reduction & Filter:** Extends the usable lifespan of sliders and provides smoother data using multiple configuration types.

## 🤝 Contributing
We welcome feedback from the community! Feel free to share your creations and tag me at **@wolf33b** (Instagram). I will personally comment on your creation and highlight it!

If you find bugs in the release, please open an Issue.

* **Bug Reports:** Accepted. (Note: You may need to wait until the Public release syncs with the Dev release to see the fix).
* **Feature Requests:** Considered for implementation, but priority is given to RMA users.


## 📜 License
This software is licensed under the **RedWerewolf Studio Software License**.
It is free to use, free to distribute, and will **always** remain free for its core functionality.
*Please read the `LICENSE` file for full terms regarding tampering, redistribution, and attribution.*

---

# ATOM (Atmega To Open Mapping)

**ATOM** is a specialized control software designed to bridge the gap between analog mixer and digital software. 

Originally developed exclusively for the **RMA devices (Redstudio Mixer Analog)**, ATOM now free for anyone both personall and commercial use. Starting with version 1.6, the core software is now available to the public, allowing third-party developers and DIY enthusiasts to build their own custom mixers without needing to code their own control software from scratch.

## 🎛️ What is ATOM?

ATOM allows you to map physical hardware controls (faders, knobs, switches that send analog data) based on Atmega microcontrollers(like arduino) to a single unified software that re stream to many protocol like Reaper api or midi. It handles the communication from what and to who, letting you built any kind of mixer you want. a single analog. button that emulate a mixer. or straight up to 10 individual mixer with indiviual output(more are supported but not guarantee play nice)

## 🚀 Release Channels & Compatibility

ATOM operates on a **Staggered Release Model**. 

| Feature | RMA Owner (Official Hardware) | Public / DIY User |
| :--- | :--- | :--- |
| **Current Version** | 1.7.2.0 | 1.6.1.0 |
| **Updates** | Immediate | Delayed (Catch-up cycle) |
| **Firmware** | Official Proprietary Firmware | D.I.Y/ any Thirdparty |
| **RMA Premium Features** | ✅ Supported | 🔒 Not supported |

**Note:** While public versions are currently a few steps behind the  RMA user, the roadmap aims to synchronize both versions in the near future.

## ✨ Key Features
* **Universal Mapping:** flexible protocol to map custom DIY hardware inputs or virtual input(non official firmware can make virtual analog slider that doens't have physical slider) to any supported output via ATOM interface.
* **Universal Version forever:** Any Version are design to always compatible with newer or older firmware. no matter the software version or the firmware version you working on. it will guarantee to work seamlessly(exlude missing feature). update are basically optional even if tutorial and demo firmware based on newer software
* **Visual Feedback:** Real-time metering and state monitoring for your hardware .
* **DIY Friendly:** Includes a "Demo Firmware" and tutorial file to get your Atmega chip talking to ATOM quickly.
* **Dynamic:** Software will dyanamically re adjust to each devices.
* **Profile both hardware and software:** built in profile manager for each profile slot(if supported) and a mapping profile(seperate from setting) that easy to save, load and share to other pc
* **Background friendly:** support running on background with a overlay for monitoring and very lightweight(perfromance may vary based on how hardware communicated to software) with extra multiple performance to quality mode
* **Loopmidi compatible:** allow easy connect and auto lauch for loopmidi user(software need to be download seperately)


## 🛠️ Getting Started (For DIY Users)

If you are building your own mixer, follow these steps to use ATOM:

1.  **Download the Software:** Check the [Releases] tab for the latest Public version.
2.  for quick try of the software **Flash the Demo Firmware:** * Navigate to the `/firmware/demo` folder
3.  **Connect:** Plug your hardware via USB/Serial.
4.  Upload the `.ino` file to your Atmega compatible board via aruino uno(use latest version).
5.  **Configure:** Launch ATOM. The software should recognize the Demo Firmware signature and allow basic mapping(demo are not compatible with saving a profile).
*Please check the `/firmware/demo/wiring/` folder for the wiring diagram required for the Demo Firmware.*

## 🔒 RMA official Firmware Features
Certain functions and deep-level hardware diagnostics are only avaiable to the **RMA Official Firmware**.
* **Firmware Optimizer:** Special deeper integration features specific to RMA firmware(compatible firmware version needed). for better optimization on both hardware and PC resource
* **Health check:**built in slider health monitoring system to allow user check and know when to change slider module once gone bad than replace whole hardware(modular change only avaiable to Fat model)
* **High Speed mode:** Allow a new optimize communication api with Faster Bandwith for more demanding use with many slider
* **Noise Reduction & Noise Filter :** Allow smoother and longer usable lifespand of the slider with multiple configuration and type
## 🤝 Contributing
We welcome feedback from the community! Feel Free to share your creation and tag me at @wolf33b(instagram). i will personally comment your creation and hightlight it!. OR if you find bugs in the release, please open an Issue. 

* **Bug Reports:** Accepted. might requred you to wait until both release are sync before you see the fix
* **Feature Requests:** Consider to be implement, but priority is given to RMA user.


---

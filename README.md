# TimeBoard

**TimeBoard** is a Palm OS application designed to provide quick access to essential device information, optimized for **one-handed operation**.  
It combines a clean interface with multiple views focused on time, date, system status, and battery information.

## Features

TimeBoard offers five main views:

### 🧭 Overview
Displays essential information about your Palm device.  
Supports **one-handed navigation** using the hardware direction buttons.

### 🕰 Analog Clock
A full-screen analog clock showing:
- Current time  
- Date  
- Day of the week  

On color devices, the clock adapts its colors according to the selected theme.

### ⏱ Digital Clock
A full-screen digital clock with:
- Current time  
- Date  
- Day of the week  

Designed for maximum readability.

### 📅 Calendar
Shows detailed calendar information:
- Current date and month  
- Day number within the year  
- Current week number  
- Remaining days until the end of the year  

### 🔋 Battery
Provides detailed battery and system information:
- Charge percentage  
- Voltage  
- Estimated remaining usage time  
- Total device uptime  

## Compatibility

- Compatible with **Palm OS 3.5 and later**
- Designed to run on both **grayscale and color** Palm OS devices

## Downloads

TimeBoard can be downloaded from the following locations:

- 📦 **GitHub Releases**: download the latest `.prc` files from the  
  [`/Releases`](./Releases) folder in this repository
- 🌴 **PalmDB**: https://palmdb.net/app/timeboard

## Technology

- Developed using **[OrbForms Designer](https://github.com/OrbWorks/orbworks-archive)**

More features are planned for future releases!

---

## Changelog

### v1.1 — 04/06/2025
- 🎨 Themes: new background color picker for enhanced customization  
- 🖥 Implemented offscreen drawing buffers for better UX on older devices  
- ✏️ Updated text in some preference menus  
- 🧩 UI tweaks  
- 🐞 Bug fixes  

### v1.0 — 22/05/2025
- 🚀 Initial release  

---

## About

TimeBoard is part of an effort to preserve and enhance classic Palm OS applications while exploring modern UI ideas within the constraints of legacy hardware.

If you enjoy Palm OS software, clocks, or system utilities, I hope you enjoy using **TimeBoard**!

---

## NetClock prototype: Network Notes

This application retrieves the current date and time from a public HTTP API.

Due to the nature of legacy Palm OS networking stacks and modern internet routing,
the following behaviors are expected and handled gracefully:

- Some servers (e.g. worldtimeapi.org) may close the TCP connection with a reset (RST)
  after sending a complete HTTP response.
- In such cases, OrbForms may report error `4628 (netErrSocketClosedByRemote)` even
  though the response body was fully received.
- This application treats a valid JSON response as success even if the socket
  is closed abruptly after transmission.

### Emulators

- Palm OS Emulator (POSE) and real devices work as expected.
- [CloudPilotEmu](https://cloudpilot-emu.github.io/) versions prior to 1.5 contain a known bug in EOF handling that
  affects OrbForms-style character-by-character socket reads.
- This bug has been fixed and will be available starting with CloudPilotEmu 1.5.

### Reliability

If the primary time API is unreachable due to routing or regional issues,
the application may retry or fallback to alternative time sources in future versions.

# TimeBoard

**TimeBoard** is a Palm OS application designed to provide quick access to time, calendar, battery and device information, with an interface optimized for **one-handed operation**.

The project also includes the **TBTS Palm Client**, a companion application that allows compatible Palm OS devices to synchronize their system clock over the Internet using the **TimeBoard Time Service (TBTS)**.

---

## Features

TimeBoard offers five main views:

### 🧭 Overview

Displays essential information about your Palm device and provides access to the different TimeBoard views.

Supports **one-handed navigation** using the hardware direction buttons.

### 🕰 Analog Clock

A full-screen analog clock showing:

- Current time
- Date
- Day of the week

On color devices, the clock adapts its colors according to the selected theme.

### ⏱ Digital Clock

A full-screen digital clock showing:

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

Provides battery and system information:

- Charge percentage
- Voltage
- Estimated remaining usage time
- Total device uptime

---

## TBTS Palm Client

This repository also contains the **TBTS Palm Client**, a companion application for Palm OS that provides Internet time synchronization using the **TimeBoard Time Service**.

The client connects to the TBTS server using HTTP, retrieves the current Coordinated Universal Time (UTC), applies the GMT offset selected by the user, and updates the Palm system clock.

### Features

- Internet time synchronization
- User-selectable GMT offset
- Configurable connection retry attempts
- Connection status indication
- Network error handling
- HTTP `429 Too Many Requests` handling
- Server response validation
- API version detection
- TBTS service version detection
- Persistent storage of the last successfully reported API and service versions

The API and service version information is updated after each successful synchronization and remains available when the application is restarted.

---

## TimeBoard Time Service

**TimeBoard Time Service (TBTS)** is a lightweight Internet time service created specifically for TimeBoard and compatible Palm OS devices.

The production service is available at:

```text
http://tbts.coloraturip.com
```

The current UTC endpoint is:

```text
http://tbts.coloraturip.com/api/v1/utc
```

A successful response contains the current UTC date and time, Unix timestamp, API version and TBTS service version.

Example:

```json
{
    "utc_datetime": "2026-07-31T11:23:50Z",
    "unixtime": 1785497030 ,
    "api_version": "v1",
    "service_version": "1.0.2"
}
```

The values above are illustrative.

TBTS intentionally supports **plain HTTP** to maintain compatibility with legacy Palm OS devices that cannot reliably communicate using modern HTTPS/TLS protocols.

The TBTS server and API are maintained in a separate repository with their own documentation.

---

## From NetClock to TBTS

Internet time synchronization originally began as an experimental Palm OS application called **NetClock**.

NetClock was created to explore Internet connectivity and time synchronization using the networking capabilities available on legacy Palm OS devices.

Early versions communicated with public time APIs and helped identify compatibility challenges involving legacy TCP/IP stacks, HTTP behavior and modern Internet infrastructure.

These experiments demonstrated that Internet time synchronization was possible, but relying on third-party services introduced compatibility and long-term availability concerns.

This led to the creation of **TimeBoard Time Service**, a dedicated service designed specifically for legacy Palm OS clients.

The TBTS Palm Client evolved from those NetClock experiments and now communicates with the dedicated TBTS infrastructure.

---

## Networking

The TBTS Palm Client uses Palm OS networking capabilities through OrbForms to communicate with the service.

Communication uses:

- DNS resolution
- TCP sockets
- HTTP
- Lightweight JSON responses

The protocol is intentionally simple to preserve compatibility with legacy hardware and software.

An active Internet connection is required only when synchronizing the clock.

Depending on the Palm OS device, connectivity may be provided through Wi-Fi, a network adapter, modem, connected mobile phone or another supported networking method.

---

## Compatibility

TimeBoard is compatible with:

- **Palm OS 3.5 and later**
- Grayscale Palm OS devices
- Color Palm OS devices
- Palm OS Emulator (POSE)
- Compatible real Palm OS hardware

Internet time synchronization through the TBTS Palm Client additionally requires a working Palm OS network connection.

---

## Downloads

TimeBoard can be downloaded from:

- 📦 **Repository releases:** download the latest `.prc` files from the [`/Releases`](./Releases) folder
- 🌴 **PalmDB:** https://palmdb.net/app/timeboard

---

## Technology

The Palm OS applications are developed using **OrbForms Designer** and **OrbC**.

OrbForms archive:

https://github.com/OrbWorks/orbworks-archive

The TBTS server is developed and maintained separately using modern server technologies while exposing a deliberately simple HTTP interface for legacy Palm OS clients.

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

TimeBoard is part of an effort to preserve and extend the usefulness of classic Palm OS devices while exploring new possibilities within the constraints of legacy hardware.

TimeBoard provides clock, calendar, battery and device information, while the TBTS ecosystem adds optional Internet time synchronization through infrastructure designed specifically to remain accessible to legacy Palm OS devices.

More features are planned for future releases.
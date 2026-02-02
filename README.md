# 🤖 B5 Vac Bomber – Autonomous Cleaning Robot
> A custom-engineered, remote-controlled vacuum prototype built with Arduino and PVC fabrication.

![B5 Vac Bomber Side View](media/Side%20View.jpeg)

## 📖 About The Project
The **B5 Vac Bomber** is a 3rd Semester Digital Logic Design (DLD) capstone project. Unlike standard kits, this robot features a **hand-fabricated PVC body** designed for aerodynamic efficiency and a **dual-power architecture** to handle high-current loads.

### 🌟 Key Features
* **Custom Pneumatics:** PVC Intake Manifold designed to maximize suction pressure.
* **Dual-Power Isolation:** Separated logic (Arduino) and drive (Motor) power rails to prevent voltage sag during high-RPM operation.
* **Wireless Control:** Android-based remote navigation via Bluetooth (HC-05).

---

## ⚙️ Hardware Specifications
| Component | Function |
| :--- | :--- |
| **Arduino Uno** | Central Processing Unit (Logic Control) |
| **L293D Driver** | H-Bridge for DC Gear Motor Control |
| **HC-05** | Bluetooth Module for Serial Communication |
| **TT Gear Motors** | High-torque drivetrain |
| **Impeller Fan** | High-RPM DC motor for vacuum suction |
| **Li-Ion Pack** | High-current power source |

---

## ⚡ The "Power Isolation" Architecture
One of the biggest engineering challenges was **Voltage Drop**. The vacuum motor draws significant current on startup, which initially caused the microcontroller to reset.

**Our Solution:**
We implemented a split-power design:
1.  **Logic Circuit:** 9V separate supply for Arduino & Sensors.
2.  **Power Circuit:** High-discharge Li-ion bank strictly for the Suction Motor & Drive Train.
*(See `/schematics` folder for the wiring diagram)*

---

## 🚀 How to Run
1.  Clone the repo:
    ```bash
    git clone [https://github.com/hamzamir-uetp/ROBOT-VAC-CLEANER-DLD-Project-.git](https://github.com/hamzamir-uetp/ROBOT-VAC-CLEANER-DLD-Project-.git)
    ```
2.  Open `src/main.ino` in Arduino IDE.
3.  Install the required library (`AFMotor`).
4.  Connect Arduino via USB and Upload.
5.  Pair with HC-05 (Password: `1234`) via Bluetooth Terminal app.

---

## 👨‍💻 The Team
Built by Computer Systems Engineering Students @UET Peshawar:
* **Hamza Mir**
* **Samiullah**
* **Hashir Ali**

This project is open-source. Feel free to use the schematics for your own learning!

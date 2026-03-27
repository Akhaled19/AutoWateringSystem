# 🌱 Smart Plant Monitoring & Watering System

### A microcontroller-based system that monitors soil moisture in real time and automatically waters plants while providing visual feedback and remote control capabilities.


**This project uses an Arduino UNO R4 WiFi to:**

- Monitor soil moisture levels
- Automatically water plants when soil is dry
- Display plant “mood” using an onboard LED matrix
- Allow remote interaction (future phase with mobile app)

The system is designed to be adaptive, starting with default moisture ranges and allowing user adjustments over time.

### ⚙️ Features:
- Real-time soil moisture monitoring
- Automatic watering via relay-controlled pump
- Visual feedback using LED matrix (happy / neutral / sad)
- Hysteresis-based control to prevent pump oscillation
- Extensible design for app integration and plant-specific tuning

### 🧩 Components:

  **Hardware**
1. [Arduino UNO R4 WiFi](https://www.amazon.com/dp/B0C8V88Z9D?ref=ppx_yo2ov_dt_b_fed_asin_title) 
    - <sub>Microcontroller + onboard LED matrix for visual output</sub>
2. [Capacitive Soil Moisture Sensor](https://www.amazon.com/dp/B0BTHL6M19?ref=ppx_yo2ov_dt_b_fed_asin_title)
    - <sub> Measures soil moisture via dielectric permittivity </sub>
    - <sub> More durable than resistive sensors </sub>
3. [5V Relay Module (10A)](https://shorturl.at/hVTga)
    - <sub> Acts as a switch to control the water pump </sub>
    - <sub> Allows low-power Arduino signal to control higher current </sub>
4. [Water Pump](https://shorturl.at/JvW2j)
    - <sub>Used to irrigate the plant</sub>
    - <sub>Controlled through the relay</sub>
5. [12V Power Adapter](https://shorturl.at/JvW2j)
    - <sub>Provides stable power supply for the system</sub>
6. [MB102 Breadboard Power Supply Module (3.3V / 5V)](https://shorturl.at/9CFOi)
   - <sub>Provides regulated voltage directly to the breadboard</sub>
   - <sub>Simplifies power distribution across components</sub>
   - <sub>Reduces reliance on Arduino's onboard power rails</sub>
7. [Solderless Breadboard](https://shorturl.at/P7Mhg)
   - <sub>Used for prototyping and circuit connections</sub>
7. [USB-C Cable (Data + Power)](https://shorturl.at/4hoCK)
    - <sub>Connects Arduino to development machine</sub>
8. [Jumper Wires](https://shorturl.at/P7Mhg)
    - <sub>For circuit connections</sub>

  **Software**
1. Arduino IDE
2. C++ (Arduino framework)

### 🧠 System Design

**1. Moisture Interpretation**

The capacitive sensor outputs:
 ```
 High value → Dry soil
 Low value → Wet soil 
 ```

Values are mapped to a percentage:
 ```
 0%   → Very Dry
 100% → Fully Wet
 ```

**2. Control Logic**

**The system uses threshold-based logic with hysteresis:**

This prevents rapid toggling of the pump.
```
If moisture < dry threshold → pump turns ON
If moisture > wet threshold → pump turns OFF
```

**3. Visual Feedback**

The onboard LED matrix displays plant state: </br>
😊 Happy → Well-watered </br>
😐 Neutral → Acceptable range </br>
😢 Sad → Needs water </br>


### 🔄 Future Improvements
- Mobile app integration (React Native)
- Remote monitoring and control via WiFi
- Plant-specific moisture profiles
- Moisture history tracking and analytics
- Adaptive watering based on user feedback

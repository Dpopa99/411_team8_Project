* Group Member Names: David Popa | Jade Nguyen | Pushpesh Sharma | Shyamal Singh
* Course: ECE411 Fall 2022
* Date: Oct 13, 2022
* Revision: Version 1.0

# Problem Statement and Concept of Operations
Self defense is a necessity in our everyday lives. Whether you go on late night walks in downtown or spend your time in the rural side of town, you have to be prepared to defend yourself in a attack on your person. The stun gun in its mounted state creates a non-lethal electric shock used to stop an intruder from trespassing in an unauthorized area. The device is connected to an entrance door and upon activation of the device, any unauthorized operation of the door will send an electric shock from the device to the door thus immobilizing the assailant. Although they lack some advantages, such as the capacity to render an adversary helpless or a larger range, they are highly regarded for their ease of use and accessibility. The device is mounted, its size and weight make it portable and versatile. The overall product offers a sense of security and vigilance and should be marketed as such. The final marketing team should strongly consider any number of regulations as well as the variance in stand your ground laws within the U.S and internationally. 

# Market Analysis 
As a mounted device, it can be used by a vast number of customers such as small businesses owners, street food vendors, landlords, storage units owners, RV/Van campers, etc. to protect their belongings and themselves.
Over the development of the product, it can be marketed to bigger businesses, corporate offices, banks, armored vehicles, private security firms, as well as in home security companies. 

The competition can be felt through any of the manufacturers selling pre-installed security devices as well as products that offer multipurpose use such as the Ring Doorbell etc. Our product is in a completely different region as it targets a specific audience: the self-made individuals who are vigilant and don't hesitate to do what's necessary to protect what's theirs. 
	
In comparison to other security devices and their features, our device can be priced within the $40-$50 range. There are several key factors that affect this price and as our design and overall ideas develop, the price may be adjusted accordingly. Factors like the mounting apparatus, 3D printed casing, any user interfaces used, and the cost of internal parts such as the transformer, connectors, and the PCB will eventually determine the final price for our product. 

# Product Requirements
* Must be a rugged design for versatile use and placement.
* Must send a non-lethal electric shock.
* Must be marketed as a plug in device. 
* Must not overheat. (Check transformer behavior in various situations)
* Must be operated via a Door actuated sensor. 
* Should have the ability to be deactivated via remote or physical switch. 
* Should have LED indicators to dictate state of device (Armed or Disarmed)
* May have 3D printed enclosure for all components
* May have Display to show state of device (Active, Triggered, Inactive)

# System Architecture (Currently in Design)
![Option 1] https://github.com/Dpopa99/Stun-Gun/blob/1cf66b6ec34d4ff388a511120fdf6c6f7bfc1d21/Option%201.png
![Option 2] https://github.com/Dpopa99/Stun-Gun/blob/1cf66b6ec34d4ff388a511120fdf6c6f7bfc1d21/Option%202.png

# Design Specification
* Sensor: Door knob movement actuating motion sensor, metal contact to send electric shock
* Processor: ATMega328P microcontroller with Arduino IDE for processing motion sensor activity to send electric shock via transformer. Firmware used will be the Bootloader.  
* Actuator: High voltage transformer taking input voltage and sending converted voltage at variable frequency chosen shock apparatus. 
* Power: 9V wall adapter feeding a high voltage transformer 

# License
GNU General Public License v2.0
The GNU GPL is the most widely used free software license and has a strong copyleft requirement. When distributing derived works, the source code of the work must be made available under the same license. There are multiple variants of the GNU GPL, each with different requirements.

See Documentation file in this repository for all sources used for this project

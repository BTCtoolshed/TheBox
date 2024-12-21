# The Box
Cryptography and Bitcoin : Thermal printer + MCU in a standard waterproof box.
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/01.jpeg?raw=true)

# READ this whole page and all instructions before proceeding!!!
**Skill level : You need to be able to strip wires, solder and use a 3d printer.**

<br><br>
# Shopping List
* A. LilyGo t5 4.7 v2.3 ESP32-S3 (non touch version, available on Amazon)
* B. USB-C Data Cable for flashing (Not a regular charging cable! This is specifically a data cable.)
* C. Mini Rocker Switches (available on Amazon, I chose the Zupayipa)
* D. Push Button Switch (pick your favorite, must be momentary not latching)
* E. QR 204 58mm Thermal Printer (available on Amazon, I chose the Xixian)
* F. 30MM x 58MM Thermal Paper (available on Amazon, coreless is great)
* G. 2 USB-C chargeable 9v batteries (available on Amazon, I chose the KOOAQQ)
* H. 2 9V battery connectors (available on Amazon, I chose the VWEICYY)
* I. USB-hub with at least 2 ports (this will be your charger)
* J. Marine sealant, electrical tape
* K. Jumper wire for microcontrollers/small electronics (Adafruit spooled tinned wire is nice) and solder
* L. Apache 1800 Waterproof Case (Harbor Freight, comparable to Pelican 1150)
* *Optional: 2 SD Cards (smallest size in MB possible)
* You also need a computer with a USB port and with Arduino IDE installed

<br><br>
# PROGRAMMING THE MICROCONTROLLER

**1st installation option : Flashing Binary to the ESP32**<br>
*Warning : By using this option you are trusting I am not a malicious actor and that the software I used to compile this bin was not compromised!!!*
1) Download the "TheBox.bin" file from this github repository.<br>
2) You will need to install Python on your computer if it isn't already installed.<br>
3) Then you will need to install esptool (see here https://docs.espressif.com/projects/esptool/en/latest/esp32/installation.html)<br>
5) Plug in your USB data cable to your esp32 device and connect to your computer's USB.<br>
6) Identify the comms port (Windows example COM9) or device path (Linux/Mac example /dev/ttyUSB0) of your esp32. Google this if you don't know how.<br>
7) Open CMD (command prompt). Navigate to the folder in which you installed esptool.py <br>
8) Type: python esptool.py -p YOURCOMPORTorDEVICEPATH -b 460800 --before default_reset --after hard_reset --chip esp32  write_flash --flash_mode dio --flash_size detect --flash_freq 40m 0x10000 FULLPATHTOWHEREYOUDOWNLOADEDtheBINFILE <br>
9) Hit enter. <br>
10) Device should flash in under a minute and be ready for use. <br><br>

Example of an esp32 device connected via COM port 9: python esptool.py -p COM9 -b 460800 --before default_reset --after hard_reset --chip esp32  write_flash --flash_mode dio --flash_size detect --flash_freq 40m 0x10000 C:\Users\YourUser\Desktop\TheBox.bin

<br><br><br>
**2nd installation option : The way of pain in the Arduino IDE**
Read the .ino file appropriate for your Featherwing in the repository, especially the comments in the header. I do not have the time to support other boards or setups, unfortunately, other than the Adafruit ESP32 v2 Feather and eInk FeatherWing 2.9". If you are new to Arduino IDE, checkout https://randomnerdtutorials.com/ for ESP32 programming tutorials. You will need to know how to install new libraries and program an ESP32 for this project. Why am I not making this easier? You should have to read code in order to trust what you are doing when it comes to Hardware Wallets.

Make sure you also view Adafruit for basic instructions on installing libraries for the ThinkInk feather and/or Nano Thermal Printer. I do not follow Adafruit's power instructions on the thermal printer though, preferring a 1amp DC power source instead of a 2amp that would require a logic stepdown chip to prevent burning out the 3.3v ESP32 board. Instead you can use the 1amp power source but adjust certain settings in the libraries as noted in the .ino file and also plug the thermal printer in for 15 minutes or so to let it heat up before printing.

Thermal printing is great for setting up burner wallets - for tipping servers for example. This wallet will produce airgapped, truly random private bitcoin keys. Although ESP32s have a native function for generating true random numbers that has been evaluated by others as being truly random, I advise you to only use this for creating temporary use wallets. Bitcoin Core remains the gold standard in random key generation for bitcoin wallets.

In full transparency, this is where the private keys are generated. esp_random is a native function in ESP32:
![Randomization](https://github.com/BTCtoolshed/TippingWallet/blob/main/Photos/Random.png?raw=true)
![Randomization](https://github.com/BTCtoolshed/TippingWallet/blob/main/Photos/Random2.png?raw=true)

<br><br>
# HARDWARE ASSEMBLY

Wire for external battery<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/02.png?raw=true)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/03.png?raw=true)

Print the 3D Printed Dashboard file in this repo. I suggest printing 2 so you have some spare flat plastic you can use for this next step. Plastic weld to hold the microcontroller using the 3d printer filament. (FYI I suck at 3d print design, I included the source file in case you want to change it in Free Cad)<br>

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/09.jpeg?raw=true)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/04.jpeg?raw=true)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/05.jpeg?raw=true)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/06.jpeg?raw=true)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/10.gif?raw=true)

You will need to leave the corner unwelded that corresponds to the header on the MCU unit (the thing that looks like multiple holes in a black rectangle), insert the MCU into your welded brackets, then weld the final one in place.

Don't pay attention to the rest of the stuff in this picture, we haven't gotten to the wiring yet.
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/08.jpeg?raw=true)


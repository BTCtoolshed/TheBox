# The Box
Cryptography and Bitcoin : Thermal printer + MCU in a standard waterproof box.
* Bitcoin Wallet printer, including private phrase, Xpub, public address 1 and simple instructions on usage
* OTP one time pad printer, numeric or alpha (see NC Scout's Guerrilla's Guide to the Boafeng for instructions on how to use)
* Trigram printer (see NC Scout's Guerrilla's Guide to the Boafeng for instructions on how to use) This option uses a lot of paper. You will need 2 full rolls.
* Bitcoin Wallet qr code from screen
* Bitcoin Wallet PBST signer
* FOSS, airgapped, generic hardware, TRNG, stateless (no memory of keys kept in printer or MCU)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/01.jpeg?raw=true)

# READ this whole page and all instructions before proceeding!!!
**Skill level : You need to be able to strip wires, solder and use a 3d printer.**

<br><br>
# Shopping List
* A. LilyGo t5 4.7 v2.3 ESP32-S3 (non touch version, available on Amazon)
* B. MakerFocus 3.7v 300mAh battery (available on Amazon)
* C. USB-C Data Cable for flashing (Not a regular charging cable! This is specifically a data cable.)
* D. Mini Rocker Switches (available on Amazon, I chose the Zupayipa)
* E. Push Button Switch (pick your favorite, must be momentary not latching)
* F. QR 204 58mm Thermal Printer (available on Amazon, I chose the Xixian)
* G. 30MM x 58MM Thermal Paper (available on Amazon, coreless is great)
* H. 2 USB-C chargeable 9v batteries (available on Amazon, I chose the KOOAQQ)
* I. 2 9V battery connectors (available on Amazon, I chose the VWEICYY)
* J. USB-hub with at least 2 ports (this will be your charger)
* K. Marine sealant, electrical tape
* L. Jumper wire for microcontrollers/small electronics (Adafruit spooled tinned wire is nice) and solder
* M. Apache 1800 Waterproof Case (Harbor Freight, comparable to Pelican 1150)
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
8) Type: python esptool.py --chip esp32s3 --port YOURCOMPORTorDEVICEPATH --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size 16MB 0x0 FULLPATHTOWHEREYOUDOWNLOADEDtheBINFILE <br>
9) Hit enter. <br>
10) Device should flash in under a minute and be ready for use. <br><br>

<br><br><br>
**2nd installation option : The way of pain in the Arduino IDE**
Read the .ino file appropriate for your Featherwing in the repository, especially the comments in the header. I do not have the time to support other boards or setups, unfortunately, other than the Adafruit ESP32 v2 Feather and eInk FeatherWing 2.9". If you are new to Arduino IDE, checkout https://randomnerdtutorials.com/ for ESP32 programming tutorials. You will need to know how to install new libraries and program an ESP32 for this project. Why am I not making this easier? You should have to read code in order to trust what you are doing when it comes to Hardware Wallets.

Make sure you google basic instructions on installing libraries for the LilyGo T5 4.7 and Qr204 Thermal Printer. You can use Adafruit thermal printer library. There are special instructions in the ino file itself for an adjustment you need to make for the QR Code library. Also, you need to add two files to the LilyGo EPD library : trigrams.h and opensans12b.h ; view the PNG with the label **"MCU Settings.png"** to see where to put these files.

If you have issues flashing, check out the FAQ of LilyGo here https://github.com/Xinyuan-LilyGO/LilyGo-EPD47 (Point #7). You may have to uninstall and reinstall the device as well.

<br><br>
# TEST SOFTWARE
Before moving on to hardware assembly, try out the programmed unit. Use the button labeled "Sensor" to navigate. Press 1 time for quote change. Press 4 times quickly for hidden menu, wait until the screen has stopped loading. Press 1 time to navigate, wait until the screen has stopped loading. Double-click to select an option, wait until the screen has stopped loading. I would suggest playing with the "no print" wallet to test.

<br><br>
# NOTES ON RANDOMIZATION AND SECURITY
Thermal printing is great for setting up burner wallets - for tipping servers for example. This wallet will produce airgapped, truly random private bitcoin keys. Although ESP32s have a native function for generating true random numbers that has been evaluated by others as being truly random, I advise you to only use this for creating temporary use wallets. Bitcoin Core remains the gold standard in random key generation for bitcoin wallets.

In full transparency, this is where the private keys are generated. esp_random is a native function in ESP32:
![Randomization](https://github.com/BTCtoolshed/TippingWallet/blob/main/Photos/Random.png?raw=true)
![Randomization](https://github.com/BTCtoolshed/TippingWallet/blob/main/Photos/Random2.png?raw=true)


<br><br>
# HARDWARE ASSEMBLY

Wire for external battery<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/02.png?raw=true)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/03.png?raw=true)

I like putting marine sealant on the connection so the wires dont break off from moving the unit around. I use electrical tape to hold the wires in place while it dries. Let it dry for a few hours/overnight before you try doing other steps.<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/11.jpeg?raw=true)

Print the 3D Printed Dashboard file in this repo. I suggest printing 2 so you have some spare flat plastic you can use for this next step. Plastic weld to hold the microcontroller using the 3d printer filament. (FYI I suck at 3d print design, I included the source file in case you want to change it in Free Cad)<br>

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/09.jpeg?raw=true)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/04.jpeg?raw=true)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/05.jpeg?raw=true)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/06.jpeg?raw=true)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/10.gif?raw=true)

You will need to leave the corner unwelded that corresponds to the header on the MCU unit (the thing that looks like multiple holes in a black rectangle), insert the MCU into your welded brackets, then weld the final one in place.

Don't pay attention to the rest of the stuff in this picture, we haven't gotten to the wiring yet.<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/08.jpeg?raw=true)

Now to the final step. Insert your rocker switches and printer. Check the reference photo at the very top for positioning. As with any 3d print, you may need to trim the holes in the 3d printed material. In the end, there will be a bunch of wires that look like this, unless you are much more organized than I am.<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/12.jpeg?raw=true)

First, let's connect the 9v batteries. They will be the power supply for the QR204 printer. Keep these fully charged as the printer uses a lot of power.<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/13.png?raw=true)

Connect the red wire you just soldered to the parallel 9v into the printers power jack. Red to Red. Connect a ground wire as well; I just used an old jumper I had, but you can cut your own. It doesn't have to be yellow.<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/14.jpeg?raw=true)

KEY: Solder all grounds together. Ground from the microcontroller (see below for pinout, or refer to the pic of all wiring shown higher in this section), from the printer (I put 2 grounds - one from power supply, one from serial/comms), from the 9V batteries<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/15.jpeg?raw=true)

![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/16.png?raw=true)

Next, we will connect the communications wiring from the printer to the MCU. Read the bottom of the QR204 printer to see the labels on the 5 pin connector. Pay attention to RX, TX, GND. GND is ground. Here it is helpful to have different colored wires to differentiate RX and TX.<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/17.jpeg?raw=true)

You can see where the blue and green wires seat in the header of the MCU for receiving and transmission. If on startup the printer doesn't make a noise or if printing doesn't work, you likely have these wires mixed up.

Also note the yellow wire.. that is the ground you soldered to the common ground.<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/18.jpeg?raw=true)

Next, we cut our hot/red wires and attach them to switches. 

This one is for the printer. I put that one up top.<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/19.jpeg?raw=true)

This one is for the MCU connection to its battery; the battery cable should come with the MCU to plug into the back of the board. I used the bottom switch to connect the wires to. Don't mind the many cuts I made to the wire; my mistake.<br>
![The Box](https://github.com/BTCtoolshed/TheBox/blob/main/photos/20.jpeg?raw=true)

Lastly, drill a hole in the 3d print for your push button. Take the wires from the button in the very first assembly step and push them through the hole. Solder your button leads, usually diagonal from each other, to each wire. Test and then use marine sealant to glue the button in place.


<br><br>
# OPERATING INSTRUCTIONS

**Charging**
Connect the usb cables to the usb hub from the shopping list and plug in to a usb charger. You should have in the hub 1) usb C to the MCU 2) the usb Cs of the 9V batteries

!!!Switch for MCU must be in ON position to charge.!!!<br>

**Access Menu**
* Click once to change quote
* Click 4 times rapidly (quadruple click) to access main menu

**Menu : after each selection please wait for screen to fully load**
* Click once to advance one position in the menu
* Triple click to set the number of prints you wish to make if you are going to choose a Wallet or OTP print. Dots will appear at the bottom of the screen to show how many prints there will be
* Double click to select an option
* Six rapid clicks will begin printing Bitcoin Wallets until the paper runs out, and it will keep trying even after you run out until you shut the MCU off
* Quadruple clicks will reset everything in most cases
* To hard exit or restart, turn the MCU switch on and off. Note this will not work if you are charging at the same time.








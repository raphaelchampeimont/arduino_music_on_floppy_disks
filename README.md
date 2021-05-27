# arduino_music_on_floppy_disks
Playing music stored on floppy disks with two Arduinos

Here is a video in which I present the result and explain the challenges: https://www.youtube.com/watch?v=-Ej4zM4t6mE

This project uses code from https://github.com/dhansel/ArduinoFDC

![General overview](/images/overview.jpg?raw=true)

# Required hardware
* 2 x Arduino Uno[1] R3 (probably works with earlier versions too but untested).
* 1 x regular 3.5" 1.44MB floppy drive
* 1 x regular 1.44 MB floppy disk
* 13 x 1 kohm resitors (or 3 x 1khom resistors and 5 x 2 kohm resistors)
* 1 x 100 µF (ore more) capacitor
* optional: 1 x operational amplifier circuit (only needed to drive a "raw" speaker, you don't need it to use headphones or "computer" speakers)
* optional: LEDs and their adapted resistors if you want the LEDs (just for debug/fun but the circuit works without LEDs of course)

[1] Note: In the YouTube video I used a Leonardo as the floppy disk controller, but here I uploaded code that runs on two Unos to make it easier for you, as I assume Unos are more widely available.

# Software
Here is what each directory contains:
* **floppy_reader** is the Arduino code to upload to the "floppy drive controller" Arduino Uno
* **sound_player_4bit** is the Arduino code to upload to the "sound player" Arduino Uno
* **make_floppy_image** is a C program I wrote to convert a 8-bit Mono WAV file to a 1.44 MB floppy image

# Circuit schematics
![Schematic for floppy drive controller](/images/circuit_fdc.jpg?raw=true)
![Schematic for sound player](/images/circuit_player.jpg?raw=true)

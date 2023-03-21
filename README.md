# musicInt

This program uses the Simple and Fast Multimedia Library (SFML) API to create a music interpreter on the command line.
As such, you will need to install the SFML API. Select the appropriate platform you will be using to install SFML here:

    https://www.sfml-dev.org/tutorials/2.5/

This program uses concepts found in math, physics, and music, in tandem with the SFML API, to produce sound. In order to understand the code, you need to have a basic understanding of these concepts.

## Concepts
### Music
Music is constructed by melody and rhythm. A melody is simply a sequence of notes. Rhythm, on the other hand, determines the length of notes, the pace of the melody as a whole, as well as the time signature of the score. As a matter of fact, this program will use these as inputs:
    - beats per bar
    - beat unit
    - beats per minute (bpm)
    - note
    - note length (type)

### Math and Physics
With our structure and inputs in place, we can now move on to the phase of processing them in a way that the SFML API can interpret it, and have your machine produce the specified sounds. But first, I need to explain a few more things:

Here is an in-depth explanation of how sound works: https://www.khanacademy.org/science/physics/mechanical-waves-and-sound/sound-topic/v/sound-properties-amplitude-period-frequency-wavelength. The TLDR for our purposes:

A note is a sound created by vibrating air molecules. To affect the pitch of a sound, we'd need to modify it's _frequency_. Each note has an associated frequency attached to it. You can find a list representing that here: https://pages.mtu.edu/~suits/notefreqs.html.

However, it would be cumbersome to write all of this down for a program. Instead, I used a frequency function that allows me to programmatically determine the frequency of a note based on an initial note (in this case A4=440Hz) and how many half steps away the desired note is. Find out more here: https://pages.mtu.edu/~suits/NoteFreqCalcs.html.

Frequencies can also be represented as a sine wave. This is important to us because this is how SFML can use our notes to output sound. This program was loosely based off of this tutorial on playing sine waves with SFML: https://github.com/SFML/SFML/wiki/Tutorial:-Play-Sine-Wave.

## Usage
To compile the program, execute the following:

    g++ -c sound.cpp 
    g++ sound.o -o musicInt -lsfml-audio -lsfml-system

After compiling the program, you'll need to suuply the following parameters, in this order:
    1. beats per bar
    2. beat unit
    3. beats per minute
    4. note
    5. note length

The note and note length parameters repeat, so you can have any number of notes you wish for your melody. Here's an example:
    
    ./musicInt 4 4 120 a4 quarter b4 quarter c5 quarter d5 quarter

This creates a time signature of 4/4, at 120 bpm, playing four quarter notes in sequence.

## Limitations
This program doesn't currently support the use of chords, notes shorter than sixtyfourth notes, and microtones.
 
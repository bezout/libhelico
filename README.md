# libhelico: an old-school multimedia library

-------------
Team
-------------

Project manager, leader and funder: Charly

Software "architect": Jeremy

Moaner: Big Datta

Guest member: Gaspard

Artist: Tintin

Boss of the Project manager: Céline

English guy: Morgan

-------------
Main Features
-------------

* ASCII-art animations
* Beeper music
* Helico drawing
* Aquarium simulator

Soon:

* Game module
* Musical frequencies analyzer

-------------
How to use this library?
-------------

**To compile and run the sample program:**

*make*

*./testhelico*


**Usage of the sample program:**

    testhelico
    
        anim anim/ascii_animation_file.txt time_between_each_frame_in_ms
    
        music snd/snd_file.txt

        helico

        simulator
        
        
With no parameters, the program will display a nice ASCII animation while playing a beautiful music with the beeper.


Note that you need to install the *beep* tool and load the *pcspkr* kernel module to be able to use the PC's beeper:

*sudo apt-get install beep*

*sudo modprobe pcspkr*


See *main.cpp* for more information about using the library in your own libhelico-powered programs (it's very simple, you'll see, my little chicken :3 love).


**Animation files format:**

number_of_lines_per_frame

frame1

frame2

...

See samples in the *anim/* directory.


**Music files format:**

time_in_ms_for_1_beat

Note1 harmonic_number number_of_beats

Note2 harmonic_number number_of_beats

...

The notes are: A, A#, B, D, D#, etc. R is for a Rest.
Harmonic numbers are 0-9. The bigger, the higher.

For example, to play a B (3rd harmonic) of 2s, a Rest of 1s, and an A (4th harmonic) of 0.25s (1 beat = 0.5s):

500

B 3 4

R 0 2

A 4 0.5


See samples in the *snd/* directory.



-------------
Comments and Complaints
-------------

If you have any problems/comments/complaints running this library or concerning the contents of the animations\* please contact the Moaner or the software architect\*\* who are more involded than the project manager (or not).

Or just GFY.

-------------

\* All characters appearing in this work are fictitious. Any resemblance to real persons, living or dead, is purely coincidental.

\*\* Such a lovely name for a such messy person.



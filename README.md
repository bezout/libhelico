# libhelico: an old-school multimedia library

-------------
Team
-------------

Project manager, leader and funder: Charly

Software "architect": Jeremy

Shadow member: Datta

Guest member: Gaspard

Supervisor: Tintin

Boss of the Project manager: Céline

-------------
How to use this library ?
-------------

**To compile and run the sample program:**

*make*

*./testhelico*


**Usage of the sample program:**

    testhelico
    
        anim anim/ascii_animation_file.txt time_between_each_frame_in_ms
    
        music snd/snd_file.txt

        helico


Note that you need to install the *beep* tool and load the *pcspkr* kernel module to be able to use the PC's beeper:

*sudo apt-get install beep*
*sudo aptitude modprobe pcspkr*


See *main.cpp* for more information about using the library in your own programs.


**Animation files format:**

number_of_lines_per_frame
frame1
frame2
...

See samples in the anim/ directory.


**Music files format:**





See samples in the snd/ directory.



-------------
Comments and Complaints
-------------

If you have any problems/comments/complaints running this library or concerning the contents of the animations\* please contact the shadow member or the software architect\*\* which are more involded than the project manager.

-------------

\* All characters appearing in this work are fictitious. Any resemblance to real persons, living or dead, is purely coincidental.

\*\* Such a lovely name for a such messy person.



This project aims to demonstrate the difference between Just Intonation and Equal Temperament in music.
We accomplish this through generation of sinusoidal waves with varying frequencies.

There will be three .wav files generated in this directory. 
They can be played through the OS's audio player. 

IMPLEMENTATION: 

Multiple sine waves are created and then synthesized together in 3 different .wav files. 

** NOTE: Dissonance between tones is heard in "wobbling" interactions **

The Just_Intonation.wav will be the pure tone, with a root, pure major third, and pure fifth from the root. 
(This sounds unnatural because we so rarely hear Justly tuned music. All modern music relies on Equal Temperament). 

The Equal_Temperament.wav will be the equally tuned tone. This will sound more natural, but it is ever
so slightly out of tune (you can listen to the middle note and hear some wobbling).  

The Both_Styles.wav will have a root, an equal temperament major third, a pure major third, a equal temperament
fifth, and a pure fifth. You can clearly hear the wobbling in this example. 

While the Just_Intonation.wav and Equal_Temperament.wav may sound the same, it is clear that they are out of 
tune with one another when combined. This is the purpose of this demonstration. 

BACKGROUND: 

Pythagoras (yes, from Pythagorean Theorem fame) mathematically derived the musical intervals that define Western music theory. 
For instance, Pythagoras found that a fifth (7 semitones) above a given note is 
1.5 times the frequency of that given note. A major third (4 semitones) is 1.25 times the frequency, while
an octave (12 semitones) is 2 times the frequency. This is now known as Just Intonation, and it produces the 
purest sounding intervals possible. 

However, Just Intonation only works for one key. If you try to play a chord from any note 
but the root note, it is wildly out of tune. More interestingly, you can move 12 semitones up from the root
in various intervals, but it still won't be an octave. This makes things very difficult for instruments that
can't rapidly retune, such as guitars and pianos. 

Therefore, modern Western music uses twelve-tone equal temperament. It must be the case that an octave above a base note 
is double the frequency of the base note, so it must also be the case that 12 equal subdivisions exist. Thus, each semitone
must be related to the 12th root of 2 (2 ^ (number of semitones)/12). 

While this makes it easy for instruments with fixed tuning to play in multiple keys, it means that some 
intervals will be out of tune. For instance, a major third (4 semitones) in Just Intonation has a ratio of 
1.250, but a major third in Equal Temperament has a 2 ^ (4/12) = 1.2599... ratio. This means that Equal Temperament
is slightly off, but not enough to be noticable. 
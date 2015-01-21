/********************************************************/
/* 6. Write a program that generates a melody header file
   to be included with your Arduino assignment from a MIDI.
   Match the old files as good as possible.

   The first command line argument is the melody's title,
   which defines the include guards and output filename.
   The MIDI-file should be read from standard input.

   Use your midi_read_notes function from task 5 and
   print all notes in your callback. No global variables
   are allowed!

   Hints:
   I. You can get the Arduino string for a MIDI note
   by accessing the corresponding index from midi_notes.
   e.g. midi_notes[69] gives you "NOTE_A4".
   II. Look at the manpages of fprintf and snprintf.
*/

/********************************************************/

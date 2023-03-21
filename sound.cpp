#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <map>
using namespace std;
using namespace sf;

struct Note {
  string name;
  double frequency;
  string type;
  float duration;
};

struct Sequence {
  int beats_per_bar;
  int beat_unit;
  int bpm;
  Note *notes;
};

double freq(int);
float duration_of(int, int, map<string, int>, string);
void dict_freq(map<string, float> &, string [], int, stringstream &, int);
void dict_types(map<string, int> &, string [], int);
void play_sound(unsigned, unsigned, unsigned, Note);
void play_sequence(Sequence, unsigned, unsigned, unsigned, int);

int main(int argc, char** argv) {

  // Create the note-to-frequency dictionary
  map<string, float> frequencies;
  string setnotes[12];
  stringstream sstm;
  int half_step = -57;    // amount of half-steps that C0 is from A4
  dict_freq(frequencies, setnotes, 12, sstm, half_step);

  // Create the type-to-number dictionary
  map<string, int> types;
  string settypes[7];
  dict_types(types, settypes, 7);

  // Commence input parsing
  const unsigned SAMPLES = 44100;
  const unsigned SAMPLE_RATE = 44100;
  const unsigned AMPLITUDE = 30000;

  Sequence s;
  s.beats_per_bar = atoi(argv[1]);
  s.beat_unit = atoi(argv[2]);
  s.bpm = atoi(argv[3]);

  int size = (argc - 4)/2;    // amount of notes in the sequence.
  s.notes = new Note[size];
  int counter = 0;

  // Finish populating the sequence and the notes
  for(int c = 4; c < argc; c+=2) {
    s.notes[counter].name = argv[c];
    s.notes[counter].frequency = frequencies[s.notes[counter].name];
    s.notes[counter].type = argv[c+1];
    s.notes[counter].duration = duration_of(s.beat_unit, s.bpm, types, s.notes[counter].type);
    counter++;
  }

  play_sequence(s, SAMPLES, SAMPLE_RATE, AMPLITUDE, size);

  return 0;

}

// Return the frequency for the amount of half_steps away from A4(440Hz).
double freq(int half_step) {

  return 440.0 * pow(pow(2.0, 1.0/12.0), half_step);

}

// Return the duration of a note given its type.
float duration_of(int beat_unit, int bpm, map<string, int> types, string type) {

  int bps = bpm/60;

  return ((float)(beat_unit)/(float)(types[type])) * ((float)(1)/(float)(bps));

}

// Creates the frequencies dictionary.
void dict_freq(map<string, float> &frequencies, string setnotes[], int size, stringstream &sstm, int half_step) {

  setnotes[0] = "c";
  setnotes[1] = "c#";
  setnotes[2] = "d";
  setnotes[3] = "d#";
  setnotes[4] = "e";
  setnotes[5] = "f";
  setnotes[6] = "f#";
  setnotes[7] = "g";
  setnotes[8] = "g#";
  setnotes[9] = "a";
  setnotes[10] = "a#";
  setnotes[11] = "b";

  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < size; j++) {
      sstm << setnotes[j] << i;
      frequencies[sstm.str()] = freq(half_step);
      sstm.str(string());
      half_step++;
    }
  }

}

// Creates the types dictionary.
void dict_types(map<string, int> &types, string settypes[], int size) {

  settypes[0] = "whole";
  settypes[1] = "half";
  settypes[2] = "quarter";
  settypes[3] = "eighth";
  settypes[4] = "sixteenth";
  settypes[5] = "thirtysecond";
  settypes[6] = "sixtyfourth";

  for(int c = 0; c < 7; c++) {
    types[settypes[c]] = pow(2, c);
  }

}

// Plays the sound with the given sample rate, amplitude, and note.
void play_sound(unsigned SAMPLES, unsigned SAMPLE_RATE, unsigned AMPLITUDE, Note note) {

  Int16 NOTE[SAMPLES];
  const double increment = note.frequency/SAMPLES;
  double x = 0;

  for(unsigned i = 0; i < SAMPLES; i++) {
    NOTE[i] = AMPLITUDE * sin(2 * M_PI * x);
    x += increment;
  }

  SoundBuffer Buffer;
  Buffer.loadFromSamples(NOTE, SAMPLES, 1, SAMPLE_RATE);
  Sound sound;
  sound.setBuffer(Buffer);
  sound.setLoop(true);

  sound.play();
  sleep(seconds(note.duration));
  sound.stop();

}

// Plays the sequence by iterating through each note and feeding it to play_sound.
void play_sequence(Sequence s, unsigned SAMPLES, unsigned SAMPLE_RATE, unsigned AMPLITUDE, int size) {

  for(int c = 0; c < size; c++) {
    play_sound(SAMPLES, SAMPLE_RATE, AMPLITUDE, s.notes[c]);
  }

}

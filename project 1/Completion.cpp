#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "wav.hpp"
using namespace std;


const int WAVFILE_SAMPLES_PER_SECOND = 44100;
     int ampl(int i){
    double a = i/25;
    // 
    return a;
    }
int main() {
	double bp = 153 / 60.0;
	double duration= 5.0;
	const int NUM_SAMPLES = WAVFILE_SAMPLES_PER_SECOND * duration;
	int*  waveform = new int[NUM_SAMPLES];
	int length = NUM_SAMPLES;
   double bpm = WAVFILE_SAMPLES_PER_SECOND * (1 / bp);
   int noteOne = 750;
   int noteTwo = 1000;
    int note = noteOne;
	int i;
	int i2 = 0;
	for(i=0;i<length;i++) {
		i2++;       
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		if (i2 >= bpm){
			if(note == noteOne){
			note = noteTwo;
		} else{
			note = noteOne;
		}
		i2 = 0;
			}
		waveform[i] = ampl(i)*sin(2*M_PI*note*t); 
	}
	
   MakeWavFromInt("tone2.wav",WAVFILE_SAMPLES_PER_SECOND, waveform, length); //file name can be changed but keep extension .wav 
   delete(waveform); 
	return 0;
}

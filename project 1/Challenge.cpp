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

void print(std::vector<double> const &frequency)
{
    for (int i = 0; i < frequency.size(); i++) {
        std::cout << frequency.at(i) << '\n';
    }
}

double A(double T, double t2, double note){
	double peak = 6000;
	double TT = (10*sqrt(peak)) / sqrt(T);
	T = peak*pow((1-(1/TT)),t2*300);
	std::cout << T << '\n';
	return T;
};

int main()
{
	std::vector<double> frequency;
	string line;    
	ifstream fin("odetojoy.txt");
	while(getline(fin,line)){
    frequency.push_back(stod(line));
}
	print(frequency);
	double bp = 144 / 60;
	const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*(1 / bp)*frequency.size());
	int* waveform = new int[NUM_SAMPLES];
	int length = NUM_SAMPLES;
   double bpm = WAVFILE_SAMPLES_PER_SECOND * (1 / bp);
   double bpm2 = WAVFILE_SAMPLES_PER_SECOND * (1 / bp);
	
   int note = 0;

	int i;
	int i2 = 0;
	for(i=0;i<length;i++) {
		         i2++;
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		
		if (i >= bpm2){
			note = note + 1;
			bpm2 = bpm2 + bpm;
			i2 = 0;
			}
			double t2 = (double) i2 / WAVFILE_SAMPLES_PER_SECOND;
   double dependentOne = 17*(8- log(frequency.at(note)))/ pow(log(frequency.at(note)),2);
   double dependentTwo = 20*(8- log(frequency.at(note)))/ frequency.at(note);
   double S = note / 200;
		waveform[i] = A(frequency.at(note), t2, note)*sin((frequency.at(note)*2*M_PI*t)+(dependentOne*sin(2*M_PI*(frequency.at(note)+S)*t))+(dependentTwo*sin(2*M_PI*(frequency.at(note)*4+S))*t));
	}
	
   MakeWavFromInt("tone3.wav",WAVFILE_SAMPLES_PER_SECOND, waveform, length); //file name can be changed but keep extension .wav 
   delete(waveform); 

	return 0;
}

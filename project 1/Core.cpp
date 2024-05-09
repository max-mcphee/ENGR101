#include <iostream> // input-output library 
#include <math.h>  // library for sin function 
#include <vector>
#include "wav.hpp" // make sure to include this helper library 
// " " instead of <> means that library is in the same folder as your program 
 
using namespace std; 
 
int main(){ 
   int sample_rate = 44160; // samples per second, select value which provides good quality sound  
   double duration= 5.0; // how long [seconds] it will sound 
   double n_samples = sample_rate * duration; // if sound is "duration" seconds long and there are "sample_rate" samples per second 
                        // - how many samples are there altogether? What type should this variable be? 
   double dt = 1.0/n_samples; // time between samples 
   std::vector<int> waveform; 
   double frequency= 360;// pitch of the sound 
   int volume= 6000;// 6000 is loud enough 
   
   for ( int i_sample = 0; i_sample < n_samples ; i_sample++){  
        waveform.push_back(volume*sin(2.0 * M_PI * frequency * i_sample * dt)); 
       //cout an be used here to check values of "waveform" 
   } 
   // generates sound file from waveform array, writes n_samples numbers  
   // into sound wav file 
   // should know sample_rate for sound timing 
   MakeWavFromVector("tone1.wav",sample_rate, waveform); //file name can be changed but keep extension .wav 
	waveform.clear();  

   return 0; 
} 

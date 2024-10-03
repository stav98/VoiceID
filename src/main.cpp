/***** Voice ID για Repeaters *****
-----------------------------------
Ήχος μονοφωνικός με συχνότητα δειγματοληψίας 16KHz και 8bit unsigned PCM αρχείο WAV 
SD format FAT32 - μέγεθος 8Gb
Ονόματα αρχείων voice00.wav, voice01.wav, voice02.wav, ..........
AUDACITY
========
Tracks > Mix -> Mix Stereo down to Mono    
Audio Setup -> Audio Settings -> Project Rate (HZ) > set to 32000, 22050, 16000 or 11025 (16kHz recommended)
File > Export > Export as WAV -> Save as type: Other uncompressed files
Format Options -> Select WAVEX(Microsoft), Unsigned 8 bit PCM  
*/
#include <Arduino.h>
#include "definitions.h"
#include "functions.h"



void setup()
 {
  pinMode(STATUS_LED, OUTPUT);
  pinMode(PTT, OUTPUT); 
  tmrpcm.speakerPin = AUDIO_OUT;
  tmrpcm.setVolume(5); //Μέχρι 5. Με 6 παραμορφώνει
  tmrpcm.quality(0); 
  Serial.begin(115200);
  Serial.println(F("Repeater Voice ID. (c) 2024 Stavros S. Fotoglou - SV6GMP"));  
  if (!SD.begin(SD_ChipSelectPin))  //Έλεγχος αν βρίσκει την SD
     {  
      Serial.println(F("SD fail"));  
      return;
     }
  //Διάβασε αρχείο ρυθμίσεων από SD
  read_settings();
  Serial.println(tracks); //Debug
  Serial.println(interval); //Debug
  timer.setInterval(interval * 60000, play_Next); //Slot 0
  press_PTT();
  tmrpcm.play("voice01.wav"); //Θα παίξει αυτό το track όταν κάνει reset
  timer.restartTimer(0);
 }

void loop()
 {  
  if (but_test.isPressed())
      play_Next();
  else
     {
      if(!tmrpcm.isPlaying())
        {
         butn_tst_lock = false;
         release_PTT();
         tmrpcm.disable(); 
        }
     }
  timer.run();
 }
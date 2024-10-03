#include "definitions.h"

void play_Next (void);
void press_PTT (void);
void release_PTT (void);
void compose_filename (byte);
void read_settings (void);

TMRpcm tmrpcm;
SimpleTimer timer;

Button but_test = Button(BUTTON_TEST, PULLUP);

byte track_playcnt = 0;
String FileName;
char FName[14];
boolean butn_tst_lock = false;
byte tracks = 0, interval = 0;

void play_Next()
{
  if (!butn_tst_lock)
     {
      butn_tst_lock = true;
      press_PTT();
      compose_filename(track_playcnt);
      if (track_playcnt < tracks - 1)
          ++track_playcnt;
      else
          track_playcnt = 0;
      Serial.println(FileName + "\n");
      if (!tmrpcm.isPlaying())
          tmrpcm.play(FName);
     }    
}
  
void press_PTT()
{
 digitalWrite(STATUS_LED, HIGH);
 digitalWrite(PTT, HIGH);
 delay(500);
}

void release_PTT()
{
 delay(200);
 digitalWrite(STATUS_LED, LOW);
 digitalWrite(PTT, LOW);
}

void compose_filename (byte n)
{
 FileName = "";
 String comp1 = String(n);
 if (comp1.length() <= 1)
     comp1 = "0" + comp1; 
 FileName = COMP0 + comp1;
 FileName = FileName + ".wav";
 FileName.toCharArray(FName, 14);
}

void read_settings ()
{
 String file_buffer, value1, value2;
 File file = SD.open("prefs.txt");
 while (file.available()) 
       {
        file_buffer = file.readStringUntil('\n');
        if (file_buffer.indexOf("::") > 0)
           {
            for (byte i = 0; i < file_buffer.length(); i++) 
                {
                 if (file_buffer.substring(i, i+2) == "::") 
                    {
                     value1 = file_buffer.substring(0, i);
                     value2 = file_buffer.substring(i + 2);
                     break;
                    }
                }
            if (value1 == "TRACKS")
                tracks = (byte) value2.toInt();
            else if (value1 == "INTERVAL")
                interval = (byte) value2.toInt();
           }
       }
 file.close();
}
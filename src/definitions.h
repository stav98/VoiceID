#include <SD.h>
#include <TMRpcm.h>
#include <SimpleTimer.h>
#include <Button.h>

#define SD_ChipSelectPin        10
#define AUDIO_OUT               9
#define PTT                     4
#define STATUS_LED              5
#define BUTTON_TEST             2

#define MAX_TRACKS              4
#define COMP0                   "voice"
#define INTERVAL                20  //20 mins

//**************************************
// struct FMA
//**************************************
//---- macro to generate RGBA-value ----
#ifndef __FMA__
#define __FMA__

//---- use #pragma to disable any memory lecks ----
#pragma pack(1) 

typedef struct {
  char  text[10];   // [-]     ('\0'term.str.) flight mode annunciator, text     
  char  textAtt[10];// [-]     ('\0'term.str.) flight mode annunciator, text attributes
  int   textVis;    // [-]     ( 0:off; 1:on ) flight mode annunciator, text visible
  //int   textCol;    // [-]     ( 0:off; 1:on ) flight mode annunciator, text color
  int   frameVis;   // [-]     ( 0:off; 1:on ) flight mode annunciator, frame visible
  int   frameCol;   // [-]     (RGBA-value   ) flight mode annunciator, frame color
} FMA;

typedef struct {
  char  text[20];   // [-]     ('\0'term.str.) flight mode annunciator, overlay, text     
  char  textAtt[20];// [-]     ('\0'term.str.) flight mode annunciator, overlay, text attributes
  int   textVis;    // [-]     ( 0:off; 1:on ) flight mode annunciator, overlay, text visible
  //int   textCol;    // [-]     ( 0:off; 1:on ) flight mode annunciator, overlay, text color
  int   frameVis;   // [-]     ( 0:off; 1:on ) flight mode annunciator, overlay, frame visible
  int   frameCol;   // [-]     (RGBA-value   ) flight mode annunciator, overlay, frame color
} FMAOVL;

#endif

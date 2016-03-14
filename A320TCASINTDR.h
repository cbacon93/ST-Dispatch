//**************************************
// struct TCASINTDR
//**************************************
//---- macro to generate RGBA-value ----
#ifndef __TCASINTDR__
#define __TCASINTDR__

//---- use #pragma to disable any memory lecks ----
#pragma pack(1) 

typedef struct {
  int   type;        // [-]     ( 0,1,2,3     ) advisory type ( 0:OT; 1:PR; 2:TA; 3:RA; )
  float lat;         // [rad]   ( -PI,...+PI  ) lateral position
  float lon;         // [rad]   ( -PI,...+PI  ) longitudinal position
  float range;       // [nm]    ( 0,...,128   ) intruder range
  float alt;         // [m]     (-3000,.,+3000) intruder altitude, relative
  int	  altVis;      // [-]     ( 0:off, 1:on ) intruder altitude, relative, visible
  int	  trendMode;   // [-]     ( 0,1,2       ) vertical trend arrow ( 0:OFF; 1:DESCEND; 2:CLIMB; )
  int	  bearFail;    // [-]     ( 0,1         ) relative bearing failure ( 0:VALID; 1:FAIL; )
  int	  offScale;    // [-]     ( 0,1         ) off scale flag ( 0:ONSCALE; 1:OFFSCALE; )
} TCASINTDR;

#endif

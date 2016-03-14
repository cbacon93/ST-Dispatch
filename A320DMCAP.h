//!******************************************************************************
//!
//! A320DMCAP.h
//! ===========
//!
//! \brief  Header file for the DMC animation protocol - DMCAP.
//! \author Jürgen Gotschlich (J.R.G)
//! \modified by Marcel Haupt
//!
//! Protocol definition
//! -------------------
//! 1. The DMCAP animation protocol is a flexible protocol to receive data for a 
//!    simulated Display Management Computer application (DMC).
//!    It has a variable length according to the various application needs. An 
//!    arbitrary number of different objects can be sent with specific information.
//! 
//! 2. The DMCAP animation protocol starts with the DMCAP_HEAD structure. 
//!    This defines the actual protocol version as well as the actual packet length.
//!    The objCnt defines the number of following objects. Any number is allowed.
//! 
//! 3. Each object starts with a header of type DMCAP_OBJHEAD, with defines the typ
//!    and the length of the specific object structure. If the typ is undefined, the 
//!    next (len) bytes following the header will be skipped. Otherwise the data will 
//!    be extracted. The setup flag is reserved for future use.
//!
//!
//! revision history:
//! -----------------
//! \version 18.09.13 J.R.G start V2.0; implement ARC-mode
//! \version 11.09.13 J.R.G V1.8.3, redesign flight plans (DMCAP_OBJ_FPLAN_WPT); reduce nr. of flight plans (DMCAP_FPLAN_MAX)
//! \version 17.06.13 J.R.G V1.8.3, rotSpeed implementation
//! \version 01.08.12 J.R.G V1.8.2, trueAirSpeed, indAirSpeed, pfdFailVis, ndFailVis implementation
//! \version 12.05.11 J.R.G V1.8, ND TCAS implementation
//! \version 21.10.10 J.R.G V1.7, separate VOR bearing and course
//! \version 20.09.10 J.R.G V1.6, redesign FMA
//! \version 25.05.10 J.R.G V1.5, new signals FDCrossBarHor, FDCrossBarVer
//! \version 09.12.09 J.R.G V1.3
//! \version 03.11.09 J.R.G first version
//!
//!******************************************************************************

#ifndef _A320DMCAP_h
#define _A320DMCAP_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#ifdef _WIN32
#include <algorithm>
#endif



#include "A320FMA.h"
#include "A320TCASINTDR.h"
using namespace std;

//!**** constants ***************************************************************

//!---- general ----
const float DMCAP_VERSION                  = 2.0;            //!< The current version
const string DMCAP_VERSION_STRING          = "2.0.0";        //!< The current version
const int   DMCAP_MAX_RECV_BUFFER          = 1024*10;	     //!< maximum receiving buffer size
const float DMCAP_DtoR                     = 1.745329252e-2; //!< convert DEG to RAD

//!---- return values ----
const int   DMCAP_STAT_OK                  = 0x0000;         //!< return status: OK               
const int   DMCAP_STAT_VERSERR             = 0x0001;         //!< return status: version error
const int   DMCAP_STAT_SIZEERR             = 0x0002;         //!< return status: size error
const int   DMCAP_STAT_SIZEERR_TOT         = 0x0003;         //!< return status: size error, total check
const int   DMCAP_STAT_SIZEERR_GEN         = 0x0004;         //!< return status: size error, GEN header
const int   DMCAP_STAT_SIZEERR_FPLAN       = 0x0005;         //!< return status: size error, FPLAN header
const int   DMCAP_STAT_SIZEERR_NAV         = 0x0006;         //!< return status: size error, NAV header
     
//!---- sizes ----     
const int   DMCAP_FPLAN_MAX                = 4;              //!< max nr. of flight plans
const int   DMCAP_FPLAN_WPT_MAX            = 100;            //!< max nr. of flight plan waypoints 
const int   DMCAP_NAVOBJ_MAX               = 1000;           //!< max nr. of nav. objects
     
//!---- object types ----     
const int   DMCAP_OBJ_TYP_GEN              = 0x0000;	     //!< general animation data
const int   DMCAP_OBJ_TYP_FPLAN            = 0x0001;	     //!< flight plan
const int   DMCAP_OBJ_TYP_NAV              = 0x0002;         //!< navigation objects list
     
const int   DMCAP_FPLAN_WPTTYP_STD         = 0x0000;	     //!< standard flight plan waypoint
const int   DMCAP_FPLAN_WPTTYP_ARCSTA      = 0x0001;	     //!< start ARC flight plan waypoint
const int   DMCAP_FPLAN_WPTTYP_ARCEND      = 0x0002;	     //!< end ARC flight plan waypoint

const int   DMCAP_NAV_OBJTYP_MASC_CLASS    = 0x0000FF00;     //!< masc to define class of nav. object
const int   DMCAP_NAV_OBJTYP_MASC_TYP      = 0x000000FF;     //!< masc to define specific nav. object typ

const int   DMCAP_NAV_OBJTYP_WPT           = 0x00000100;     //!< waypoint
 
const int   DMCAP_NAV_OBJTYP_NAVAID        = 0x00000200;     //!< navaid
const int   DMCAP_NAV_OBJTYP_NAVAID_VOR    = 0x00000200;     //!< VOR  navaid 
const int   DMCAP_NAV_OBJTYP_NAVAID_DME    = 0x00000201;     //!< DME or TACAN navaid
const int   DMCAP_NAV_OBJTYP_NAVAID_VORD   = 0x00000202;     //!< VORD navaid 
const int   DMCAP_NAV_OBJTYP_NAVAID_NDB    = 0x00000203;     //!< NDB  navaid 
 
const int   DMCAP_NAV_OBJTYP_PSWPT         = 0x00000400;     //!< pseudo waypoint
const int   DMCAP_NAV_OBJTYP_PSWPT_TOC     = 0x00000400;     //!< Top of Climb
const int   DMCAP_NAV_OBJTYP_PSWPT_LVOFF   = 0x00000401;     //!< Level off 
const int   DMCAP_NAV_OBJTYP_PSWPT_TOD     = 0x00000402;     //!< Top of Descent
const int   DMCAP_NAV_OBJTYP_PSWPT_SOC     = 0x00000403;     //!< Start of Climb
const int   DMCAP_NAV_OBJTYP_PSWPT_ICPNT   = 0x00000404;     //!< Intercept Point
const int   DMCAP_NAV_OBJTYP_PSWPT_SPCHG   = 0x00000405;     //!< Speed Change
const int   DMCAP_NAV_OBJTYP_PSWPT_DECPNT  = 0x00000406;     //!< Declrt Point
const int   DMCAP_NAV_OBJTYP_PSWPT_ALTCSTR = 0x00000407;     //!< ALT CSTR
const int   DMCAP_NAV_OBJTYP_PSWPT_ENCIRC  = 0x00000408;     //!< Energy Circle
                                                
const int   DMCAP_NAV_OBJTYP_ARPT          = 0x00000800;     //!< airport
const int   DMCAP_NAV_OBJTYP_ARPT_UNSPEC   = 0x00000800;     //!< airport, unspecified runway
const int   DMCAP_NAV_OBJTYP_ARPT_RWY      = 0x00000801;     //!< airport, specified runway
 
const int   DMCAP_NAV_OBJTYP_HPAT          = 0x00001000;     //!< holding pattern
const int   DMCAP_NAV_OBJTYP_HPAT_LA       = 0x00001000;     //!< holding pattern, left arrow
const int   DMCAP_NAV_OBJTYP_HPAT_RA       = 0x00001001;     //!< holding pattern, right arrow 
                                                
const int   DMCAP_TYPE_LIN                 = 0x00000000;     //!< type: LINEAR
const int   DMCAP_TYPE_GAP                 = 0x00000001;     //!< type: GAP
const int   DMCAP_TYPE_ARC                 = 0x00000002;     //!< type: ARC

const int   DMCAP_COLIDX_GREEN             = 0x00000000;     //!< color index: green
const int   DMCAP_COLIDX_YELLOW            = 0x00000001;     //!< color index: yellow
const int   DMCAP_COLIDX_WHITE             = 0x00000002;     //!< color index: white
const int   DMCAP_COLIDX_BLUE              = 0x00000003;     //!< color index: blue
const int   DMCAP_COLIDX_MAGENTA           = 0x00000004;     //!< color index: magenta
const int   DMCAP_COLIDX_AMBER             = 0x00000005;     //!< color index: amber
                                                
const int   DMCAP_STYLE_SOLID              = 0x00000000;     //!< style: solid
const int   DMCAP_STYLE_DASHED             = 0x00000001;     //!< style: dashed

//!**** protocol structures *****************************************************

//! Header for DMC animation protocol
typedef struct {
  float		           vers; 	         //!< [-]   DMCAP version
  int		             size;	         //!< [-]   byte length of actual packet
  int		             reply;          //!< [-]   reply order (for future use)
  int		             objCnt;         //!< [-]   number of objects
} DMCAP_HDR ;

//! Defines the data stream for the general object header.
typedef struct {
  int                typ;            //!< [-]   object typ
  int                len;            //!< [-]   object len in bytes
  int                index;          //!< [-]   index (for future use)      
  int	      	       setup;	         //!< [-]   set up flag (for future use)
} DMCAP_OBJ_HDR ;


//! Defines the data stream for the flight-plan object.
typedef struct {
  int		             objCnt;         //!< [-]   number of flight plan waypoints
} DMCAP_OBJ_FPLAN_HDR;

//! Defines the data stream for the flight-plan-waypoint object.
typedef struct {
  int         	     typ;            //!< [-]   type ( 0:LIN; 1:GAP; 2:ARC; )
  int  	      	     colIdx;	     	 //!< [-]   color index( 0:GREEN; 1:YELLOW; 2:WHITE; 3:BLUE; 4:MAGENTA; 5:AMBER;)
  int  	      	     styleIdx;   	   //!< [-]   style ( 0:SOLID; 1:DASHED; )
  float              lat;            //!< [rad] lateral position
  float              lon;            //!< [rad] longitudinal position
} DMCAP_OBJ_FPLAN_WPT;

//! Defines the data stream for the list of navigation objects.
typedef struct {
  int		             objCnt;         //!< [-]   number of navigation objects
} DMCAP_OBJ_NAV_HDR;

//! Defines the data stream for the navigation object.
typedef struct {
  int                typ;            //!< [-]   typ 
  int                colIdx;         //!< [-]   color index
  char               ID[6];          //!< [-]   ID
  char               label1[6];      //!< [-]   label1 (CSTR-WPT: ALT, ARPT: RWY-ID       ,HPAT:HDG[deg] )
  char               label2[6];      //!< [-]   label2 (CSTR-WPT: SPD, ARPT: RWY-HDG[deg] ,              )
  char               label3[6];      //!< [-]   label3 (CSTR-WPT: TIM, ARPT: RWY-LEN[m]   ,              )
  float              lat;            //!< [rad] lateral position
  float              lon;            //!< [rad] longitudinal position
} DMCAP_OBJ_NAVOBJ;



//********************************************************************************
//********************************************************************************
//! Defines the data stream for the general animation object.
//********************************************************************************
//********************************************************************************

typedef struct {

  //****************************
  // General
  //****************************

  int   flightPhase;         	     // [-]     ( 0-11 	 ) flight phase 

  //****************************
  // PFD
  //****************************

  //---- specific ground indications ----
  float elCmdSs;             	     // [-]     (-1.0,...,+1.0) elevator command, sidestick 
  float aiCmdSs;             	     // [-]     (-1.0,...,+1.0) aileron command, sidestick       		   
  int   ssIndicationVis;     	     // [-]     ( 0:off; 1:on ) sidestick indication, visible
  int   groundModeVis;       	     // [-]     ( 0:off; 1:on ) ground mode, visible
  float groundRoll;          	     // [-]     (-1.0,...,+1.0) ground roll guidance command bar
  int   groundRollVis;       	     // [-]     ( 0:off; 1:on ) ground roll guidance command bar, visible
   
  //---- attitude data ----   
  float roll;	    	     	         // [rad]   ( -PI,...,+PI ) bank angle                                         
  float rollOrderDelta;            // [rad]   ( -PI,...,+PI ) bank angle, order, delta
  int   rollProtMode;              // [-]     ( 0:off; 1:on ) bank angle protection, mode 
  float pitch;	    	     	       // [rad]   ( -PI,...,+PI ) pitch angle                                        
  int   pitchProtMode;        	   // [-]     ( 0:off; 1:on ) pitch protection, mode 
  float sideslip;            	     // [g]     (-0.3,...,+0.3) sideslip
  int   sideslipCol;         	     // [-]     (RGBA-value   ) sideslip, color
  int   FPVVis;                    // [-]     ( 0:off; 1:on ) flight path vector (FPV), visible 
  int   FPDVis;                    // [-]     ( 0:off; 1:on ) flight path director (FPD), visible 
	int   FDCrossBarHorVis;          // [-]     ( 0:off; 1:on ) flight director cross bar, horizontal, visible
	int   FDCrossBarVerVis;          // [-]     ( 0:off; 1:on ) flight director cross bar, vertical, visible
  float FDCrossBarHor;             // [rad]   ( -PI,...,+PI ) flight director cross bar, horizontal
  float FDCrossBarVer;             // [rad]   ( -PI,...,+PI ) flight director cross bar, vertical
  float fpath;                     // [rad]   ( -PI,...,+PI ) flight path angle
  float fpathOrderDelta;           // [rad]   ( -PI,...,+PI ) flight path angle, order, delta
  float drift;                     // [rad]   ( -PI,...,+PI ) drift angle
   
  //---- airspeed ----		   
  float trueAirSpeed;    	     	   // [kts]   ( 0,...,600   ) true airspeed                                
  float indAirSpeed;    	     	   // [kts]   ( 0,...,600   ) indicated airspeed                                
  float grndSpeed;             	   // [kts]   ( 0,...,600   ) ground speed                                       
  float speedTrend;            	   // [kts]   ( 0,...,600   ) speed trend                                       
  int   speedTrendVis;       	     // [-]     ( 0:off; 1:on ) speed trend, visible                                       
  float targetSpeed;         	     // [kts]   ( 0,...,600   ) target speed
  int   targetSpeedMode;           // [-]     ( 0-2         ) target speed, mode (0:SELECTED; 1:MANAGED; 2:ECON)
  int   overspeedProtMode;   	     // [-]     ( 0:off; 1:on ) overspeed protection mode  
  float mach;         	     	     // [-]     ( 0.0,...,1.0 ) mach number                                        
  int   machVis;             	     // [-]     ( 0:off; 1:on ) mach number, visible                                        
  int   speedProt;        	       // [kts]   ( 0,...,600   ) speed protection
  int   speedProtVis;        	     // [-]     ( 0:off; 1:on ) speed protection, visible                                       
  int   econSpeedRangeVis;	       // [-]     ( 0:off; 1:on ) ECON speed range, visible
  float econSpeedRangeMin;	       // [kts]   ( 0,...,600   ) ECON speed range min, relativ
  float econSpeedRangeMax;	       // [kts]   ( 0,...,600   ) ECON speed range max, relativ
  float minSelSpeed;               // [kts]   ( 0,...,600   ) min. selectable speed, relativ
  int   minSelSpeedVis;            // [-]     ( 0:off; 1:on ) min. selectable speed visible
  float alphaProtSpeed;            // [kts]   ( 0,...,600   ) alpha prot. speed, relativ
  int   alphaProtSpeedVis;         // [-]     ( 0:off; 1:on ) alpha prot. speed visible
  float alphaMaxSpeed;             // [kts]   ( 0,...,600   ) alpha max speed, relativ
  int   alphaMaxSpeedVis;          // [-]     ( 0:off; 1:on ) alpha max speed visible
  float maxAllowSpeed;             // [kts]   ( 0,...,600   ) Maximum Allowable Speed (VMAX), relativ
  int   maxAllowSpeedVis;          // [-]     ( 0:off; 1:on ) Maximum Allowable Speed (VMAX) visible
  float stallWarnSpeed;            // [kts]   ( 0,...,600   ) Stall Warning Speed (VSW), relativ
  int   stallWarnSpeedVis;         // [-]     ( 0:off; 1:on ) Stall Warning Speed (VSW) visible
  float decisionSpeed;             // [kts]   ( 0,...,600   ) Decision Speed, relativ
  int   decisionSpeedVis;          // [-]     ( 0:off; 1:on ) Decision Speed visible
  float minFlapRetractSpeed;       // [kts]   ( 0,...,600   ) Minimum Flap Retraction Speed, relativ
  int   minFlapRetractSpeedVis;    // [-]     ( 0:off; 1:on ) Minimum Flap Retraction Speed visible
  float minSlatRetractSpeed;       // [kts]   ( 0,...,600   ) Minimum Slat Retraction Speed, relativ
  int   minSlatRetractSpeedVis;    // [-]     ( 0:off; 1:on ) Minimum Slat Retraction Speed visible
  float maxFlapExtNextSpeed;       // [kts]   ( 0,...,600   ) Maximum Flap Extended Speed NEXT, relativ
  int   maxFlapExtNextSpeedVis;    // [-]     ( 0:off; 1:on ) Maximum Flap Extended Speed NEXT visible
  float engOutOpSpeed;             // [kts]   ( 0,...,600   ) Engine Out op. speed in clean config., relativ
  int   engOutOpSpeedVis;          // [-]     ( 0:off; 1:on ) Engine Out op. speed in clean config. visible
  float rotSpeed;                  // [kts]   ( 0,...,600   ) rot. speed, relativ
  int   rotSpeedVis;               // [-]     ( 0:off; 1:on ) rot. speed visible
   
  //---- altitude ----   
  float alt;           	     	     // [m]     ( 0,...,15000 ) altitude                                           
  int   altWinCol;       	         // [-]     (RGBA-value   ) altitude window, color
  int   altNumCol;       	         // [-]     (RGBA-value   ) altitude number, color
  float vertDev;             	     // [m]     ( 0,...,150   ) vertical deviation
  int   vertDevVis;                // [-]     ( 0:off; 1:on ) vertical deviation visible
  float altTargetSelAlt;           // [m]     ( 0,...,15000 ) target altitude, selected altitude
  float altTargetSelFl;            // [m]     ( 0,...,15000 ) target altitude, selected flight level
  int   altTargetMode;    	       // [-]     (0:off; 1:STD; 2:QNH ) target altitude, mode
  int   altTargetCol; 	           // [-]     (RGBA-value   ) target altitude color
  float altBaroRef;                // [hPa]   ( 0,...,1500  ) barometric reference (QNH)
  int   altBaroRefMode; 	         // [-]     (0:off; 1:STD; 2:QNH ) barometric reference mode 
  float altRadAlt;         	       // [m]     ( 0,...,15000 ) radio altitude
  int   altRadAltVis;      	       // [-]     ( 0:off; 1:on ) radio altitude visible
  int   altRadAltCol;      	       // [-]     (RGBA-value   ) radio altitude color
  int   altDecisionHeight; 	       // [m]     ( 0,...,15000 ) decision height
  int   altDecisionHeightReached;  // [-]     ( 0:no; 1:yes) decision height, reached
  float altLandElev;       	       // [m]     ( 0,...,15000 ) landing elevation
  int   altLandElevVis;    	       // [-]     ( 0:off; 1:on ) landing elevation visible
  float altGroundRef;      	       // [m]     ( 0,...,15000 ) ground reference
  int   altGroundRefVis;   	       // [-]     ( 0:off; 1:on ) ground reference visible
                                      
  //---- vertical speed ----         
  float vspeed;	     	             // [m/s]   (-30.,...,+30.) vert. velocity ( inertial vertical speed )
  int   vspeedCol;                 // [-]     (RGBA-value   ) vert. velocity, color (GREEN;AMBER)
  int   vspeedDigiVis;             // [-]     ( 0:off; 1:on ) vert. velocity, digital, visible
  int   vspeedDigiWinCol;          // [-]     ( RGBA-value  ) vert. velocity, digital window, color
                                      
  //---- heading/course ----          
  float head;	    	     	         // [rad]   ( -PI,...,+PI ) heading
  int   headTruVis;	     	         // [-]     ( 0:off; 1:on ) true heading flag, visible         
  float headSel;	     	           // [rad]   ( -PI,...,+PI ) selected heading         
  int   headSelVis;	     	         // [-]     ( 0:off; 1:on ) selected heading, visible         
  int   headSelAdiVis;	     	     // [-]     ( 0:off; 1:on ) selected heading, ADI, visible
  float headActTrack;              // [rad]   ( -PI,...,+PI ) actual track
  int   headActTrackVis;           // [-]     ( 0:off; 1:on ) actual track, visible    
  float headCourse;	     	         // [rad]   ( -PI,...,+PI ) ILS course
  int   headCourseVis;	     	     // [-]     ( 0:off; 1:on ) ILS course, visible

  //---- Flight Mode Annunciator (FMA) ----
  int    fmaVis;                   // [-]     ( 0:off; 1:on ) fma, visible
  FMA    fma[3][5];        	       // [-]     (             ) fma data structure ( 3*5*5 signals )
  FMAOVL fmaOvl[5];                // [-]     (             ) fma overlay data structure ( 5*5 signals )
                                      
  //---- trajectory deviation ----    
  float loc;    	     	           // [rad]   ( -PI,...,+PI ) localizer deviation                        
  int   locVis;  	     	           // [-]     ( 0:off; 1:on ) ILS localizer deviation scale visible (0:off; 1:on)
  int   locIndexVis;  	     	     // [-]     ( 0:off; 1:on ) ILS localizer deviation index visible (0:off; 1:on)
  float gls;    	     	           // [rad]   ( -PI,...,+PI ) glide slope deviation                      
  int   glsVis;  	     	           // [-]     ( 0:off; 1:on ) ILS glide slope deviation scale visible (0:off; 1:on)
  int   glsIndexVis;  	     	     // [-]     ( 0:off; 1:on ) ILS glide slope deviation index visible (0:off; 1:on)
  int   OMMarkerVis;  	     	     // [-]     ( 0:off; 1:on ) OM marker, visible
  int   MMMarkerVis;  	     	     // [-]     ( 0:off; 1:on ) MM marker, visible
  int   AWYMarkerVis;  	     	     // [-]     ( 0:off; 1:on ) AWY marker, visible
  int   vdevVis;                   // [-]     ( 0:off; 1:on ) vertical deviation scale visible (0:off; 1:on)
  int   pfdIlsInfoVis;             // [-]     ( 0:off; 1:on ) PFD, ILS info, visible
  int   pfdIlsMsgVis;              // [-]     ( 0:off; 1:on ) PFD, ILS message, visible

  //---- Flags and Messages displayed on PFD ----
  int   pfdFailVis;                // [-]     ( 0:off; 1:on ) PFD failure symbol visible
  int   pfdStartVis;               // [-]     ( 0:off; 1:on ) PFD start screen visible
  int   pfdATTFlagVis;             // [-]     ( 0:off; 1:on ) ATT flag visible
  int   pfdCHECKATTFlagVis;        // [-]     ( 0:off; 1:on ) CHECK ATT flag visible
  int   pfdSIFlagVis;              // [-]     ( 0:off; 1:on ) SI flag flag visible
  int   pfdFPVFlagVis;             // [-]     ( 0:off; 1:on ) FPV flag visible
  int   pfdFDFlagVis;              // [-]     ( 0:off; 1:on ) FD flag visible
  int   pfdSPDFlagVis;             // [-]     ( 0:off; 1:on ) SPD flag visible
  int   pfdSPDSELFlagVis;          // [-]     ( 0:off; 1:on ) SPD SEL flag visible 
  int   pfdSPDLIMFlagVis;          // [-]     ( 0:off; 1:on ) SPD LIM flag visible
  int   pfdV1INOPFlagVis;          // [-]     ( 0:off; 1:on ) V1 INOP flag visible
  int   pfdALTFlagVis;             // [-]     ( 0:off; 1:on ) ALT flag visible
  int   pfdCHECKALTFlagVis;        // [-]     ( 0:off; 1:on ) CHECK ALT visible
  int   pfdALTSELFlagVis;          // [-]     ( 0:off; 1:on ) ALT SEL flag visible
  int   pfdVSFlagVis;              // [-]     ( 0:off; 1:on ) V/S flag visible
  int   pfdLOCFlagVis;             // [-]     ( 0:off; 1:on ) LOC flag visible
  int   pfdGLSFlagVis;             // [-]     ( 0:off; 1:on ) GLS flag visible
  int   pfdVDEVFlagVis;            // [-]     ( 0:off; 1:on ) V/DEV flag visible
  int   pfdRAFlagVis;              // [-]     ( 0:off; 1:on ) RA flag visible
  int   pfdDHFlagVis;              // [-]     ( 0:off; 1:on ) DH flag visible 
  int   pfdHDGFlagVis;             // [-]     ( 0:off; 1:on ) HDG flag visible
  int   pfdCHECKHDGFlagVis;        // [-]     ( 0:off; 1:on ) CHECK HDG flag visible 
  int   pfdMACHFlagVis;            // [-]     ( 0:off; 1:on ) MACH flag visible
  int   pfdVDEVAPPRFlagVis;        // [-]     ( 0:off; 1:on ) GLS V/DEV flag visible
  int   pfdDME1FlagVis;            // [-]     ( 0:off; 1:on ) DME 1 flag visible
  int   pfdILS1FlagVis;            // [-]     ( 0:off; 1:on ) ILS1 flag visible
  int   pfdWINDSHEARFlagVis;       // [-]     ( 0:off; 1:on ) WINDSHEAR flag visible
					   

  //****************************
  // ND
  //****************************
                                      
  //---- position ----                
  float lat;                       // [rad]   ( -PI,...,PI  ) lateral position
  float lon;                       // [rad]   ( -PI,...,PI  ) longitudinal position
                                      
  //---- heading/course ----          
  float headActTrackLine;          // [nm]    (   0,...,+320) actual track line, length
  float headActTrackLineVis;       // [-]     ( 0:off; 1:on ) actual track line, visible
  float headActTrackLineCol;       // [-]     ( 0:off; 1:on ) actual track line, color
  float headCrossTrackErr;         // [nm]    (   0,...,+999) cross track error

  //---- trajectory deviation ----    
  int   ndLocVis;  	          	   // [-]     ( 0:off; 1:on ) ILS localizer deviation scale visible (0:off; 1:on)
  int   ndGlsVis;  	          	   // [-]     ( 0:off; 1:on ) ILS glide slope deviation scale visible (0:off; 1:on)

  //---- EFIS ----                    
  int   ndMode;                    // [-]     ( 0,1,2,3,4   ) ND mode ( 0:RoseILS; 1:RoseVOR; 2:RoseNAV; 3:ARC; 4:PLAN ) 
  int   optDataDispMode;           // [-]     ( 0:off; 1:CSTR; 2:WPT; 3:VORD; 4:NDB; 5:ARPT; ) optional data display mode, from EFIS control panel 
  int   FDMode;                    // [-]     ( 0:off; 1:on ) FD button mode, from EFIS control panel 
  int   ILSMode;                   // [-]     ( 0:off; 1:on ) ILS button mode, from EFIS control panel 
  int   rangeScale;                // [-]     ( 0,1,2,3,4,5 ) range scale ( 0:10nm; 1:20nm; 2:40nm; 3:80nm; 4:160nm; 5:320nm; )
  int   navaid1Sel;                // [-]     ( 0,1,2       ) navaid1 selected ( 0:off; 1:VOR; 2:ADF; ) 
  int   navaid2Sel;                // [-]     ( 0,1,2       ) navaid2 selected ( 0:off; 1:VOR; 2:ADF; ) 
                                      
  //---- nav selection ----                   
  int   ndFailVis;                 // [-]     ( 0:off; 1:on ) ND failure symbol
  int   ndStartVis;                // [-]     ( 0:off; 1:on ) ND start screen visible
  int   ndIlsInfoVis;              // [-]     ( 0:off; 1:on ) ND, ILS info, visible
  int   ndVorInfoVis;              // [-]     ( 0:off; 1:on ) ND, VOR info, visible
  int   ndTowptInfoVis;            // [-]     ( 0:off; 1:on ) ND, TOWPT info, visible
  int   ilsSel;                    // [-]     ( 0,1,2       ) ILS selected ( 0:off; 1:ILS1; 2:ILS2 ) 
  int   vorSel;                    // [-]     ( 0,1,2       ) VOR selected ( 0:off; 1:ILS1; 2:ILS2 ) 
  int   ilsMax;                    // [-]     ( 0,1,2       ) max. nr. of available ILS's
  int   vorMax;                    // [-]     ( 0,1,2       ) max. nr. of available VOR's
  int   adfMax;                    // [-]     ( 0,1,2       ) max. nr. of available ADF's
                                      
  //---- speed, wind info ----        
  int   speedWindInfoVis;          // [-]     speed, wind info, visible
  int   grndSpeedFail;             // [-]     ground speed, failure
  int   airSpeedFail;              // [-]     airspeed, failure
  int   windSpeedFail;             // [-]     wind speed, failure
  int   windDirFail;	        	   // [-]     wind direction, from, failure
  float windSpeed;	     	         // [kts]   wind speed                             
  float windDirAna;	     	         // [rad]   ( -PI,...,+PI ) wind direction, from, analog                   
  float windDirDig;	     	         // [rad]   ( -PI,...,+PI ) wind direction, from, digital                   
                                      
  //---- ILS1 ----                    
  char  ils1ID[10];                // [-]     ('\0'term.str.) ILS1 ID
  float ils1Course;                // [rad]   ( -PI,...,+PI ) ILS1 course    
  int   ils1CourseVis;             // [-]     ( 0:off; 1:on ) ILS1 course, visible
  float ils1Freq;                  // [MHz]   ( 0,...,200   ) ILS1 frequency
  int   ils1FreqVis;               // [-]     ( 0:off; 1:on ) ILS1 frequency, visible
  float ils1Dist;                  // [nm]    ( 0,...,320   ) ILS1 DME distance
  int   ils1DistVis;               // [-]     ( 0:off; 1:on ) ILS1 DME distance, visible
                                      
  //---- ILS2 ----                    
  char  ils2ID[10];                // [-]     ('\0'term.str.) ILS2 ID
  float ils2Course;                // [rad]   ( -PI,...,+PI ) ILS2 course    
  int   ils2CourseVis;             // [-]     ( 0:off; 1:on ) ILS2 course, visible
  float ils2Freq;                  // [MHz]   ( 0,...,200   ) ILS2 frequency
  int   ils2FreqVis;               // [-]     ( 0:off; 1:on ) ILS2 frequency, visible
  float ils2Dist;                  // [nm]    ( 0,...,320   ) ILS2 DME distance
  int   ils2DistVis;               // [-]     ( 0:off; 1:on ) ILS2 DME distance, visible
                                      
  //---- vor1 ----                    
  char  vor1ID[6];                 // [-]     ('\0'term.str.) vor1 ID
  int   vor1Tune;                  // [-]     ( 0,1,2       ) vor1 tune ( 0:MAN; 1:RMP; 2:AUTO; ) 
  float vor1Dev;                   // [rad]   ( -PI,...,+PI ) vor1 deviation 
  float vor1Bear;                  // [rad]   ( -PI,...,+PI ) vor1 bearing
  float vor1Course;                // [rad]   ( -PI,...,+PI ) vor1 course 
  int   vor1CourseVis;             // [-]     ( 0:off; 1:on ) vor1 course pointer visible
  float vor1Freq;                  // [MHz]   ( 0,...,200   ) vor1 frequency
  int   vor1FreqVis;               // [-]     ( 0:off; 1:on ) vor1 frequency, visible
  float vor1Dist;                  // [nm]    ( 0,...,320   ) vor1 DME distance
  int   vor1DistVis;               // [-]     ( 0:off; 1:on ) vor1 DME distance, visible
  int   vor1DevToFrom;             // [-]     ( 0:TO; 1:FROM) vor1 deviation, TO/FROM indicator
                                      
  //---- vor2 ----                    
  char  vor2ID[6];                 // [-]     ('\0'term.str.) vor2 ID
  int   vor2Tune;                  // [-]     ( 0,1,2       ) vor2 tune ( 0:MAN; 1:RMP; 2:AUTO; ) 
  float vor2Dev;                   // [rad]   ( -PI,...,+PI ) vor2 deviation 
  float vor2Bear;                  // [rad]   ( -PI,...,+PI ) vor2 bearing
  float vor2Course;                // [rad]   ( -PI,...,+PI ) vor2 course 
  int   vor2CourseVis;             // [-]     ( 0:off; 1:on ) vor2 course pointer visible
  float vor2Freq;                  // [MHz]   ( 0,...,200   ) vor2 frequency
  int   vor2FreqVis;               // [-]     ( 0:off; 1:on ) vor2 frequency, visible
  float vor2Dist;                  // [nm]    ( 0,...,320   ) vor2 DME distance
  int   vor2DistVis;               // [-]     ( 0:off; 1:on ) vor2 DME distance, visible
  int   vor2DevToFrom;             // [-]     ( 0:TO; 1:FROM) vor2 deviation, TO/FROM indicator
                                      
  //---- adf1 ----                    
  char  adf1ID[6];                 // [-]     ('\0'term.str.) adf1 ID
  int   adf1Tune;                  // [-]     ( 0,1,2       ) adf1 tune ( 0:MAN; 1:RMP; 2:AUTO; ) 
  float adf1Bear;                  // [rad]   ( -PI,...,+PI ) adf1 bearing
  int   adf1BearVis;               // [-]     ( 0:off; 1:on ) adf1 bearing pointer visible
  float adf1Freq;                  // [MHz]   ( 0,...,200   ) adf1 frequency
  int   adf1FreqVis;               // [-]     ( 0:off; 1:on ) adf1 frequency, visible
                                      
  //---- adf2 ----                    
  char  adf2ID[6];                 // [-]     ('\0'term.str.) adf2 ID
  int   adf2Tune;                  // [-]     ( 0,1,2       ) adf2 tune ( 0:MAN; 1:RMP; 2:AUTO; ) 
  float adf2Bear;                  // [rad]   ( -PI,...,+PI ) adf2 bearing
  int   adf2BearVis;               // [-]     ( 0:off; 1:on ) adf2 bearing pointer visible
  float adf2Freq;                  // [MHz]   ( 0,...,200   ) adf2 frequency
  int   adf2FreqVis;               // [-]     ( 0:off; 1:on ) adf2 frequency, visible
                                      
  //---- TOWPT ----                   
  char  towptID[6];                // [-]     ('\0'term.str.) TOWPT ID
  float towptTrack;                // [rad]   ( 0,...,360   ) TOWPT track to go
  int   towptTrackVis;             // [-]     ( 0:off; 1:on ) TOWPT track to go, visible
  float towptDist;                 // [nm]    ( 0,...,320   ) TOWPT distance  
  int   towptDistVis;              // [-]     ( 0:off; 1:on ) TOWPT distance, visible
  char  towptTime[6];              // [-]     ('\0'term.str.) TOWPT time of arrival

  //---- Flags and Messages displayed on ND ----
  int   ndHDGFlagVis;              // [-]     ( 0:off; 1:on ) HDG flag visible
  int   ndCHECKHDGFlagVis;         // [-]     ( 0:off; 1:on ) CHECK HDG flag visible 
  int   ndCenterPartMsg;           // [-]     ( 0,1,2,3     ) center part messages ( 0:OFF; 1:"MODE CHANGE"; 2:"RANGE CHANGE"; 3:"MAP NOT AVAIL" )
	int   ndLOCFlagVis;              // [-]     ( 0:off; 1:on ) LOC flag visible
  int   ndGLSFlagVis;              // [-]     ( 0:off; 1:on ) GLS flag visible
  int   ndVORFlagVis;              // [-]     ( 0:off; 1:on ) VOR flag visible
  int   ndVOR1FlagVis;             // [-]     ( 0:off; 1:on ) VOR1 flag visible
  int   ndADF1FlagVis;             // [-]     ( 0:off; 1:on ) ADF1 flag visible
  int   ndDME1FlagVis;             // [-]     ( 0:off; 1:on ) DME1 flag visible
  int   ndVOR2FlagVis;             // [-]     ( 0:off; 1:on ) VOR2 flag visible
  int   ndADF2FlagVis;             // [-]     ( 0:off; 1:on ) ADF2 flag visible
  int   ndDME2FlagVis;             // [-]     ( 0:off; 1:on ) DME2 flag visible
  int   ndVORCrsFlag;              // [-]     ( 0,1,2       ) VOR course flag ( 0:OFF; 1:"CRSXXX"; 2:"CRS---" )
  int   ndOtherMsg;                // [-]     ( 0,...,7     ) other messages 
	                                 //                         ( 0:OFF;
                                   //                           1:MAP PARTLY DISPLAYED (amber); 
                                   //                           2:NAV ACCUR UPGRAD (white); 
                                   //                           3:NAV ACCUR DOWNGRAD (amber);
                                   //                           4:SPECIFIC VOR/D UNAVAIL (amber); 
                                   //                           5:SET OFFSIDE RNG/MODE (amber);  
                                   //                           6:GPS PRIMARY (white, boxed white);
                                   //                           7:GPS PRIMARY LOST (amber, boxed white); )
  int   ndOtherMsgOvflArrVis;      // [-]     ( 0:off; 1:on ) other messages, overflow arrow (green);
  int   ndOFSTMsgVis;              // [-]     ( 0:off; 1:on ) offset flight plan message visible (green);
  float ndOFSTMsgVal;              // [NM]    (-999,...,+999) offset flight plan message value (neg. values will be marked 'L'; pos. values 'R')
  int   ndAppMsg;                  // [-]     ( 0,1,2,3     ) approach messages ( 0:OFF; 1:"ILS APP"; 2:"VOR APP"; 3:"GPS APP" )

	//---- chronometer ----
	int   chronTime;                 // [sec]   ( 0,...,360000) chronometer, elapsed time 
  int   chronVis;                  // [-]     ( 0:off; 1:on ) chronometer, visible

  //---- TCAS ----
  int   tcasMode;                  // [-]     ( 0:off; 1:on ) TCAS, mode
  int   tcasOpMsg;                 // [-]     ( 0,1,2       ) TCAS, operational message ( 0:OFF; 1:TAONLY; 2:TCAS; )
  int   tcasIntdrCnt;              // [-]     ( 0,...,8     ) nr. of valid intruder objects
  TCASINTDR tcasIntdr[8];          // [-]     (             ) TCAS intruder objects

  //---- PLAN-mode reference point ----
  float ndPlanRefPntLat;           // [rad]   ( 0,...,2*PI  )lateral position
  float ndPlanRefPntLon;           // [rad]   ( 0,...,2*PI  )longitudinal position

} DMCAP_OBJ_GEN_DATA;

//********************************************************************************
//********************************************************************************
//! end of general animation object data stream 
//********************************************************************************
//********************************************************************************

//! Defines the complete data object for the general animation data object
typedef struct {
  DMCAP_OBJ_HDR       hdr;               //!< [-]   Header with basic information.
  DMCAP_OBJ_GEN_DATA  data;              //!< [-]   general animation data
} DMCAP_OBJ_GEN;

//! Defines the complete data object for the flight-plan object (except waypoints itself !!!)
typedef struct {
  DMCAP_OBJ_HDR       hdr;               //!< [-]   Header with basic information.
  DMCAP_OBJ_FPLAN_HDR fplan;             //!< [-]   flight plan header
} DMCAP_OBJ_FPLAN;

//! Defines the complete data object for the list of navigation objects (except navigation objects itself!!!)
typedef struct {
  DMCAP_OBJ_HDR       hdr;               //!< [-]   Header with basic information.
  DMCAP_OBJ_NAV_HDR   nav;               //!< [-]   navigation object header
} DMCAP_OBJ_NAV;


//! Union structure for usage.
typedef struct {	     
  union  {	     
    DMCAP_OBJ_HDR       hdr;
    DMCAP_OBJ_GEN       gen;
    DMCAP_OBJ_FPLAN     fplan;
    DMCAP_OBJ_NAV       nav;
  } u;
} DMCAP_OBJ;   


//**************************************
// class A320DMCAP
//**************************************
class A320DMCAP {
public:

  //---- constructor ----
  A320DMCAP( void );

  //---- ----
  int  updateSndBuf( void );
  int  analyseRcvBuf( int rcvSizeAct );
  int  getGen( char **ps );
  int  getFplan( char **ps );
  int  getNav( char **ps );

  //---- ----
  float getVers( void ) { return vers; }
  int   getSizeExp( void ) { return size; }
  int   getSizeTot( void ) { return sizeTot; }
  int   getObjTyp( void ) { return objTyp; }
  int   getObjCntExp( void ) { return objCnt; }
  float getObjLenExp( void ) { return vers; }
  int   getReply( void ) { return reply; }

  //---- variables ----
  DMCAP_OBJ_GEN_DATA   gen;                                            //! general animation data

  int                  fplanCnt;                                       //! actual nr. of flight plans 
  DMCAP_OBJ_FPLAN_HDR  fplanHdr[DMCAP_FPLAN_MAX];                      //! flight plan header
  DMCAP_OBJ_FPLAN_WPT  fplanWpt[DMCAP_FPLAN_MAX][DMCAP_FPLAN_WPT_MAX]; //! flight plan waypoints 

  int                  navObjCnt;                                      //! actual nr. of nav. objects
  DMCAP_OBJ_NAVOBJ     navObj[DMCAP_NAVOBJ_MAX];                       //! nav. objects

  char                 buf[DMCAP_MAX_RECV_BUFFER];                     //! send/receive buffer

  int                  rcvSizeAct;                                     //!
  int                  reply;                                          //!
  float                vers;                                           //!
  int                  size;                                           //!
  int                  sizeTot;                                        //! total size
  int                  objCnt;                                         //! object count
  int                  objLen;                                         //! object length
  int                  objTyp;                                         //! object typ
};
#pragma pack() 

#endif

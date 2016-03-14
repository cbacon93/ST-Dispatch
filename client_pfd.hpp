//
//  client_pfd.hpp
//  ST-Dispatch
//
//  Created by Marcel Haupt on 14.03.16.
//  Copyright © 2016 Marcel Haupt. All rights reserved.
//

#ifndef client_pfd_hpp
#define client_pfd_hpp

#include "client.hpp"

class ClientPFD : public Client {
private:
    //data structures
    
    struct FMA {
        char text[10];
        char textAlt[10];
        
        int textVis;
        int frameVis;
        int frameCol;
    };
    
    struct FMAOVL {
        char text[20];
        char textAlt[20];
        
        int textVis;
        int frameVis;
        int frameCol;
    };
    
    struct TCASINTDR {
        int type;
        
        float lat;
        float lon;
        float range;
        float relAlt;
        
        int relAltVis;
        int vertTrend;
        int bearFail;
        int offScale;
    };
    
    struct DMCAPHeader {
        float version;
        int size;
        int reply;
        int objCnt;
    };
    
    struct DMCAPObjectHeader {
        int typ;
        int len;
        int index;
        int setup;
    };
    
    struct DMCAPObjectData {
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
    };
    
    
    struct DMCAPObject {
        DMCAPObjectHeader objHeader;
        DMCAPObjectData data;
    };
    
    struct DMCAP {
        DMCAPHeader header;
        DMCAPObject object;
    };
    
    struct recvData {
        int dummy;
    };
    
public:
    //inherit constructor of base class
    ClientPFD(Database * _db, std::string ip_adress, unsigned int sendPort, unsigned int recvPort):
    Client(_db, ip_adress, sendPort, recvPort) {}
    
    //sending and receiving data
    virtual void sendInfo();
    virtual void receiveInfo();
    
};

#endif /* client_pfd_hpp */

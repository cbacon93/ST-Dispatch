//******************************************************************************
//
// A320DMCAP.cpp
// ==========
//
// The DMCAP animation protocol is a flexible protocol to send/receive data for a 
// simulated Display Management Computer application (DMC).
//
// revision history:
// -----------------
// 24.11.09 J.R.G implement as flexible protocol
// 07.01.08 J.R.G first version
//
//******************************************************************************
 
//---- includes ----
#include "A320DMCAP.h"


//******************************************************************************
// A320DMCAP:: constructor
//******************************************************************************
A320DMCAP::A320DMCAP( void ) {
}

//******************************************************************************
// 
// return values: size: nr. of bytes in send buffer
//                  
//******************************************************************************
int A320DMCAP::updateSndBuf( void ) {

  int  i, j;
  char *ps, *psStart;
  char *sizePtr, *objCntPtr;
  int  objCnt=0;
  int  size;

  //****************************************
  // protocol start
  //****************************************

  //---- setup base address for send buffer ----
  psStart = &buf[0];
  ps      = psStart;

  //---- header: version, size, ... ----
  *(float*)ps = DMCAP_VERSION;                      ps+=4;        //!< [-]   the version
  sizePtr     = ps;                                 ps+=4;  	    //!< [-]   byte length of actual packet.
  *(int*)ps   = 0;                     	     	      ps+=4;  	    //!< [-]   reply order.
  objCntPtr   = ps;                    	            ps+=4;    		//!< [-]   number of objects.
 
  //****************************************
  // add general animation object
  //****************************************

  objCnt++;
  *(int*)ps = DMCAP_OBJ_TYP_GEN;                    ps+=4;        //!< [-]   object header: object typ
  *(int*)ps = sizeof(DMCAP_OBJ_GEN);                ps+=4;        //!< [-]   object header: object len in bytes                              
  *(int*)ps = 0;		              	                ps+=4;      	//!< [-]   object header: index (for future use)      
  *(int*)ps = 0;	                      	          ps+=4;      	//!< [-]   object header: set up flag (for future use)
  memcpy( ps, &gen, sizeof(DMCAP_OBJ_GEN_DATA) );   
  ps += sizeof(DMCAP_OBJ_GEN_DATA);
 
  //****************************************
  // add fplan objects
  //****************************************

  //---- loop to add all flight plans ----
  for( i=0; i<fplanCnt; i++ ) {
    objCnt++;
    *(int*)ps = DMCAP_OBJ_TYP_FPLAN;                ps+=4;        //!< [-]   object header: object typ
    *(int*)ps = sizeof(DMCAP_OBJ_FPLAN);            ps+=4;        //!< [-]   object header: object len in bytes                              
    *(int*)ps = 0;		               	              ps+=4;      	//!< [-]   object header: index (for future use)      
    *(int*)ps = 0;	                      	        ps+=4;      	//!< [-]   object header: set up flag (for future use)
    memcpy( ps, &fplanHdr[i], sizeof(DMCAP_OBJ_FPLAN_HDR) );
    ps += sizeof(DMCAP_OBJ_FPLAN_HDR);

    //---- loop to add all waypoints for this flight plan ----
    for( j=0; j<fplanHdr[i].objCnt; j++ ) {
      memcpy( ps, &fplanWpt[i][j], sizeof(DMCAP_OBJ_FPLAN_WPT) );
      ps += sizeof(DMCAP_OBJ_FPLAN_WPT);
    }
  }

  //****************************************
  // add nav. objects
  //****************************************

  if( navObjCnt>0 ) {
    objCnt++;
    *(int*)ps = DMCAP_OBJ_TYP_NAV;                  ps+=4;        //!< [-]   object header: object typ
    *(int*)ps = sizeof(DMCAP_OBJ_NAV);              ps+=4;        //!< [-]   object header: object len in bytes                              
    *(int*)ps = 0;		               	              ps+=4;    		//!< [-]   object header: index (for future use)      
    *(int*)ps = 0;	                      	        ps+=4;    		//!< [-]   object header: set up flag (for future use)
    memcpy( ps, &navObjCnt, sizeof(navObjCnt) );
    ps += sizeof(navObjCnt);

    //---- loop to add all nav objects ----
    for( j=0; j<navObjCnt; j++ ) {
      memcpy( ps, &navObj[j], sizeof(DMCAP_OBJ_NAVOBJ) );
      ps += sizeof(DMCAP_OBJ_NAVOBJ);
    }
  }

  //****************************************
  // protocol end
  //****************************************

  //---- setup packet size ----
  size = ps - psStart;
  *(int*)sizePtr   = size;                                                     //!< [-]   store byte length of actual packet.
  //---- setup nr. objects ----
  *(int*)objCntPtr = objCnt;                                                   //!< [-]   store number of objects.

  return size;
}

//******************************************************************************
// 
//******************************************************************************
int A320DMCAP::analyseRcvBuf( int rcvSizeAct ) {

  char *ps, *psStart;

  //****************************************
  // protocol start
  //****************************************

  //---- setup base address for send buffer ----
  psStart = &buf[0];
  ps      = psStart;

  //****************************************
  // header: version, size, ... 
  //****************************************
  vers   = *(float*)ps;                           ps+=4;            //!< [-]   the version
  size   = *(int*)ps;                             ps+=4;  	    //!< [-]   byte length of actual packet.
  reply  = *(int*)ps;                             ps+=4;  	    //!< [-]   reply order.
  objCnt = *(int*)ps;                             ps+=4;            //!< [-]   number of objects.

  if( fabs(vers-DMCAP_VERSION)>1.e-6 ) return DMCAP_STAT_VERSERR;
  if( size!= rcvSizeAct   ) return DMCAP_STAT_SIZEERR;

  //****************************************
  // handle objects
  //****************************************
  fplanCnt  = 0;
  navObjCnt = 0;
  for( int i=0; i<objCnt; i++ ) {
    objTyp = *(int*)ps;                            ps+=4;            //!< [-]   object header: object typ
    switch( objTyp ) {
    case DMCAP_OBJ_TYP_GEN  : { getGen(&ps); break; }
    case DMCAP_OBJ_TYP_FPLAN: { getFplan(&ps); break; }
    case DMCAP_OBJ_TYP_NAV  : { getNav(&ps); break; }
    }
  }

  //****************************************
  // protocol end; check total size
  //****************************************
  sizeTot = ps - psStart;
  if( sizeTot!=rcvSizeAct   ) return DMCAP_STAT_SIZEERR_TOT;

  return DMCAP_STAT_OK;
}

//******************************************************************************
// 
//******************************************************************************
int A320DMCAP::getGen( char **ps ) {

  //---- check object header ----
  objLen = *(int*)(*ps);                                                //!< [-]   object header: object len in bytes                              
  if( objLen!=sizeof(DMCAP_OBJ_GEN) ) return DMCAP_STAT_SIZEERR_GEN;    //!< [-]   
  /* index = *(int*)ps; */                                       	//!< [-]   object header: index (for future use)      
  /* setup = *(int*)ps; */                                       	//!< [-]   object header: set up flag (for future use)
  *ps+=12;
  
  //---- get object data: general animation data structure ----
  memcpy( &gen, *ps, sizeof(DMCAP_OBJ_GEN_DATA) );   
  *ps += sizeof(DMCAP_OBJ_GEN_DATA);

  return DMCAP_STAT_OK;
}



//******************************************************************************
// 
//******************************************************************************
int A320DMCAP::getFplan( char **ps ) {

  //---- check object header ----
  objLen = *(int*)(*ps);                                                //!< [-]   object header: object len in bytes                              
  if( objLen!=sizeof(DMCAP_OBJ_FPLAN) ) return DMCAP_STAT_SIZEERR_FPLAN;//!< [-]   
  // index = *(int*)ps;                                          	//!< [-]   object header: index (for future use)      
  // setup = *(int*)ps;                                         	//!< [-]   object header: set up flag (for future use)
  *ps+=12;
  
  //---- get object data: FPLAN header ----
  memcpy( &fplanHdr[fplanCnt], *ps, sizeof(DMCAP_OBJ_FPLAN_HDR) );   
  *ps += sizeof(DMCAP_OBJ_FPLAN_HDR);

  //---- loop to add all waypoints for this flight plan ----
  if( fplanCnt<DMCAP_FPLAN_MAX ) {
    for( int j=0; j<min(fplanHdr[fplanCnt].objCnt,DMCAP_FPLAN_WPT_MAX); j++ ) {
      memcpy( &fplanWpt[fplanCnt][j], *ps, sizeof(DMCAP_OBJ_FPLAN_WPT) );
      *ps += sizeof(DMCAP_OBJ_FPLAN_WPT);
    }
    fplanCnt++;
  }
  return DMCAP_STAT_OK;
}

//******************************************************************************
// get nav. objects
//******************************************************************************
int A320DMCAP::getNav( char **ps ) {

  //---- check object header ----
  objLen = *(int*)(*ps);                                                //!< [-]   object header: object len in bytes                              
  if( objLen!=sizeof(DMCAP_OBJ_NAV) ) return DMCAP_STAT_SIZEERR_NAV;    //!< [-]   
  // index = *(int*)ps;                                         	//!< [-]   object header: index (for future use)      
  // setup = *(int*)ps;                                         	//!< [-]   object header: set up flag (for future use)
  *ps+=12;
  
  //---- get object data: NAV header ----
  memcpy( &navObjCnt, *ps, sizeof(navObjCnt) );   
  *ps += sizeof(navObjCnt);

  //---- loop to add all nav objects for this nav. list ----
  for( int j=0; j<min(navObjCnt,DMCAP_NAVOBJ_MAX); j++ ) {
    memcpy( &navObj[j], *ps, sizeof(DMCAP_OBJ_NAVOBJ) );
    *ps += sizeof(DMCAP_OBJ_NAVOBJ);
  }

  return DMCAP_STAT_OK;
}

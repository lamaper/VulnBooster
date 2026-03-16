static void initATTables ( struct alltabs * at , SplineFont * sf , enum fontformat format ) {
 setos2 ( & at -> os2 , at , sf , format ) ;
 if ( at -> opentypemode ) {
 SFFindUnusedLookups ( sf ) ;
 otf_dumpgpos ( at , sf ) ;
 otf_dumpgsub ( at , sf ) ;
 otf_dumpgdef ( at , sf ) ;
 otf_dumpjstf ( at , sf ) ;
 otf_dumpbase ( at , sf ) ;
 otf_dump_math ( at , sf ) ;
 if ( at -> gi . flags & ttf_flag_dummyDSIG ) otf_dump_dummydsig ( at , sf ) ;
 }
 if ( at -> dovariations ) ttf_dumpvariations ( at , sf ) ;
 if ( at -> applemode ) {
 if ( ! at -> opentypemode ) SFFindUnusedLookups ( sf ) ;
 ttf_dumpkerns ( at , sf ) ;
 aat_dumplcar ( at , sf ) ;
 aat_dumpmorx ( at , sf ) ;
 aat_dumpopbd ( at , sf ) ;
 aat_dumpprop ( at , sf ) ;
 aat_dumpbsln ( at , sf ) ;
 }
 if ( ! at -> applemode && ( ! at -> opentypemode || ( at -> gi . flags & ttf_flag_oldkern ) ) ) ttf_dumpkerns ( at , sf ) ;
 dumpnames ( at , sf , format ) ;
 redoos2 ( at ) ;
 }
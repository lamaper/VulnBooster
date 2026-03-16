static inline double U_EXPORT2 utimer_getElapsedSeconds ( UTimer * timer ) {
 UTimer temp ;
 utimer_getTime ( & temp ) ;
 return uprv_delta ( timer , & temp ) ;
 }
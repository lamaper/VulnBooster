static inline void U_EXPORT2 utimer_getTime ( UTimer * timer ) {
 uprv_initFrequency ( timer ) ;
 uprv_start ( timer ) ;
 }
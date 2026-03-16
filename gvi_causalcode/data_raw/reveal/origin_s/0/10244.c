static inline double U_EXPORT2 utimer_loopUntilDone ( double thresholdTimeVal , int32_t * loopCount , FuntionToBeTimed fn , void * param ) {
 UTimer timer ;
 double currentVal = 0 ;
 * loopCount = 0 ;
 utimer_getTime ( & timer ) ;
 for ( ;
 currentVal < thresholdTimeVal ;
 ) {
 fn ( param ) ;
 currentVal = utimer_getElapsedSeconds ( & timer ) ;
 ( * loopCount ) ++ ;
 }
 return currentVal ;
 }
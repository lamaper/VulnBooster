static inline double U_EXPORT2 utimer_getDeltaSeconds ( UTimer * timer1 , UTimer * timer2 ) {
 if ( uprv_compareFrequency ( timer1 , timer2 ) ) {
 return uprv_delta ( timer1 , timer2 ) ;
 }
 return - 1 ;
 }
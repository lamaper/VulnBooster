static char * strdur ( time_t duration ) {
 static char out [ 50 ] ;
 int neg , days , hours , minutes , seconds ;
 if ( duration < 0 ) {
 duration *= - 1 ;
 neg = 1 ;
 }
 else neg = 0 ;
 days = duration / ( 24 * 3600 ) ;
 duration %= 24 * 3600 ;
 hours = duration / 3600 ;
 duration %= 3600 ;
 minutes = duration / 60 ;
 duration %= 60 ;
 seconds = duration ;
 snprintf ( out , sizeof ( out ) , "%s%d %s %02d:%02d:%02d" , neg ? "-" : "" , days , days == 1 ? "day" : "days" , hours , minutes , seconds ) ;
 return out ;
 }
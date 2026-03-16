static void nice_time ( double sec , char * buff , bool part_second ) {
 ulong tmp ;
 if ( sec >= 3600.0 * 24 ) {
 tmp = ( ulong ) floor ( sec / ( 3600.0 * 24 ) ) ;
 sec -= 3600.0 * 24 * tmp ;
 buff = int10_to_str ( ( long ) tmp , buff , 10 ) ;
 buff = strmov ( buff , tmp > 1 ? " days " : " day " ) ;
 }
 if ( sec >= 3600.0 ) {
 tmp = ( ulong ) floor ( sec / 3600.0 ) ;
 sec -= 3600.0 * tmp ;
 buff = int10_to_str ( ( long ) tmp , buff , 10 ) ;
 buff = strmov ( buff , tmp > 1 ? " hours " : " hour " ) ;
 }
 if ( sec >= 60.0 ) {
 tmp = ( ulong ) floor ( sec / 60.0 ) ;
 sec -= 60.0 * tmp ;
 buff = int10_to_str ( ( long ) tmp , buff , 10 ) ;
 buff = strmov ( buff , " min " ) ;
 }
 if ( part_second ) sprintf ( buff , "%.2f sec" , sec ) ;
 else sprintf ( buff , "%d sec" , ( int ) sec ) ;
 }
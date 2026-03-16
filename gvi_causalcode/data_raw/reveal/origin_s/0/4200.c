static void test_oid_to_str ( void ) {
 struct {
 unsigned int binlen ;
 unsigned char * bin ;
 char * str ;
 }
 tests [ ] = {
 {
 7 , "\x02\x82\x06\x01\x0A\x0C\x00" , "0.2.262.1.10.12.0" }
 , {
 7 , "\x02\x82\x06\x01\x0A\x0C\x01" , "0.2.262.1.10.12.1" }
 , {
 7 , "\x2A\x86\x48\xCE\x38\x04\x01" , "1.2.840.10040.4.1" }
 , {
 7 , "\x2A\x86\x48\xCE\x38\x04\x03" , "1.2.840.10040.4.3" }
 , {
 10 , "\x2B\x06\x01\x04\x01\xDA\x47\x02\x01\x01" , "1.3.6.1.4.1.11591.2.1.1" }
 , {
 3 , "\x55\x1D\x0E" , "2.5.29.14" }
 , {
 9 , "\x80\x02\x70\x50\x25\x46\xfd\x0c\xc0" , BADOID }
 , {
 1 , "\x80" , BADOID }
 , {
 2 , "\x81\x00" , "2.48" }
 , {
 2 , "\x81\x01" , "2.49" }
 , {
 2 , "\x81\x7f" , "2.175" }
 , {
 2 , "\x81\x80" , "2.48" }
 , {
 2 , "\x81\x81\x01" , "2.49" }
 , {
 0 , "" , "" }
 , {
 0 , NULL , NULL }
 }
 ;
 int tidx ;
 char * str ;
 for ( tidx = 0 ;
 tests [ tidx ] . bin ;
 tidx ++ ) {
 str = ksba_oid_to_str ( tests [ tidx ] . bin , tests [ tidx ] . binlen ) ;
 if ( ! str ) {
 perror ( "ksba_oid_to_str failed" ) ;
 exit ( 1 ) ;
 }
 if ( strcmp ( tests [ tidx ] . str , str ) ) {
 fprintf ( stderr , "ksba_oid_to_str test %d failed\n" , tidx ) ;
 fprintf ( stderr , " got=%s\n" , str ) ;
 fprintf ( stderr , " want=%s\n" , tests [ tidx ] . str ) ;
 exit ( 1 ) ;
 }
 }
 }
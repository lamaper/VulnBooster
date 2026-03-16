char * fstostr ( time_t ntp_stamp ) {
 char * buf ;
 struct tm * tm ;
 time_t unix_stamp ;
 LIB_GETBUF ( buf ) ;
 unix_stamp = ntp_stamp - JAN_1970 ;
 tm = gmtime ( & unix_stamp ) ;
 if ( NULL == tm ) # ifdef WAIT_FOR_NTP_CRYPTO_C_CALLERS_ABLE_TO_HANDLE_MORE_THAN_20_CHARS msnprintf ( buf , LIB_BUFLENGTH , "gmtime: %m" ) ;


 return buf ;
 }
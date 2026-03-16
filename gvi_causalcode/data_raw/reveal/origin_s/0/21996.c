static void test_2 ( void ) {
 static char * invalid_labels [ ] = {
 "C=de,FOO=something,O=bar" , "Y=foo, C=baz" , NULL }
 ;
 gpg_error_t err ;
 int i ;
 unsigned char * buf ;
 size_t off , len ;
 for ( i = 0 ;
 invalid_labels [ i ] ;
 i ++ ) {
 err = ksba_dn_str2der ( invalid_labels [ i ] , & buf , & len ) ;
 if ( gpg_err_code ( err ) != GPG_ERR_UNKNOWN_NAME ) fail ( "invalid label not detected" ) ;
 err = ksba_dn_teststr ( invalid_labels [ i ] , 0 , & off , & len ) ;
 if ( ! err ) fail ( "ksba_dn_test_str returned no error" ) ;
 printf ( "string ->%s<- error at %lu.%lu (%.*s)\n" , invalid_labels [ i ] , ( unsigned long ) off , ( unsigned long ) len , ( int ) len , invalid_labels [ i ] + off ) ;
 xfree ( buf ) ;
 }
 }
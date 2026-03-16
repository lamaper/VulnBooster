static void test_1 ( void ) {
 static char * empty_elements [ ] = {
 "C=de,O=foo,OU=,CN=joe" , "C=de,O=foo,OU= ,CN=joe" , "C=de,O=foo,OU=\"\" ,CN=joe" , "C=de,O=foo,OU=" , "C=de,O=foo,OU= " , "C=,O=foo,OU=bar " , "C = ,O=foo,OU=bar " , "C=" , NULL }
 ;
 gpg_error_t err ;
 int i ;
 unsigned char * buf ;
 size_t off , len ;
 for ( i = 0 ;
 empty_elements [ i ] ;
 i ++ ) {
 err = ksba_dn_str2der ( empty_elements [ i ] , & buf , & len ) ;
 if ( gpg_err_code ( err ) != GPG_ERR_SYNTAX ) fail ( "empty element not detected" ) ;
 err = ksba_dn_teststr ( empty_elements [ i ] , 0 , & off , & len ) ;
 if ( ! err ) fail ( "ksba_dn_teststr returned no error" ) ;
 printf ( "string ->%s<- error at %lu.%lu (%.*s)\n" , empty_elements [ i ] , ( unsigned long ) off , ( unsigned long ) len , ( int ) len , empty_elements [ i ] + off ) ;
 xfree ( buf ) ;
 }
 }
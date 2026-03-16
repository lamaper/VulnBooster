static void test_0 ( void ) {
 static char * good_strings [ ] = {
 "C=de,O=g10 Code,OU=qa,CN=Pépé le Moko" , "C= de, O=g10 Code , OU=qa ,CN=Pépé le Moko" , "CN=www.gnupg.org" , " CN=www.gnupg.org " , "C=fr,L=Paris,CN=Julien Duvivier,EMAIL=julien@example.org" , NULL }
 ;
 gpg_error_t err ;
 int i ;
 unsigned char * buf ;
 size_t off , len ;
 for ( i = 0 ;
 good_strings [ i ] ;
 i ++ ) {
 err = ksba_dn_str2der ( good_strings [ i ] , & buf , & len ) ;
 if ( err ) {
 fprintf ( stderr , "%s:%d: ksba_dn_str2der failed for `%s': %s\n" , __FILE__ , __LINE__ , good_strings [ i ] , gpg_strerror ( err ) ) ;
 exit ( 1 ) ;
 }
 err = ksba_dn_teststr ( good_strings [ i ] , 0 , & off , & len ) ;
 if ( err ) {
 fprintf ( stderr , "%s:%d: ksba_dn_teststr failed for `%s': %s\n" , __FILE__ , __LINE__ , good_strings [ i ] , gpg_strerror ( err ) ) ;
 exit ( 1 ) ;
 }
 xfree ( buf ) ;
 }
 }
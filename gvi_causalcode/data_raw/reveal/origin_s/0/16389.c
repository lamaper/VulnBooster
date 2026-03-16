static int kex_agree_hostkey ( LIBSSH2_SESSION * session , unsigned long kex_flags , unsigned char * hostkey , unsigned long hostkey_len ) {
 const LIBSSH2_HOSTKEY_METHOD * * hostkeyp = libssh2_hostkey_methods ( ) ;
 unsigned char * s ;
 if ( session -> hostkey_prefs ) {
 s = ( unsigned char * ) session -> hostkey_prefs ;
 while ( s && * s ) {
 unsigned char * p = ( unsigned char * ) strchr ( ( char * ) s , ',' ) ;
 size_t method_len = ( p ? ( size_t ) ( p - s ) : strlen ( ( char * ) s ) ) ;
 if ( kex_agree_instr ( hostkey , hostkey_len , s , method_len ) ) {
 const LIBSSH2_HOSTKEY_METHOD * method = ( const LIBSSH2_HOSTKEY_METHOD * ) kex_get_method_by_name ( ( char * ) s , method_len , ( const LIBSSH2_COMMON_METHOD * * ) hostkeyp ) ;
 if ( ! method ) {
 return - 1 ;
 }
 if ( ( ( kex_flags & LIBSSH2_KEX_METHOD_FLAG_REQ_ENC_HOSTKEY ) == 0 ) || ( method -> encrypt ) ) {
 if ( ( ( kex_flags & LIBSSH2_KEX_METHOD_FLAG_REQ_SIGN_HOSTKEY ) == 0 ) || ( method -> sig_verify ) ) {
 session -> hostkey = method ;
 return 0 ;
 }
 }
 }
 s = p ? p + 1 : NULL ;
 }
 return - 1 ;
 }
 while ( hostkeyp && ( * hostkeyp ) && ( * hostkeyp ) -> name ) {
 s = kex_agree_instr ( hostkey , hostkey_len , ( unsigned char * ) ( * hostkeyp ) -> name , strlen ( ( * hostkeyp ) -> name ) ) ;
 if ( s ) {
 if ( ( ( kex_flags & LIBSSH2_KEX_METHOD_FLAG_REQ_ENC_HOSTKEY ) == 0 ) || ( ( * hostkeyp ) -> encrypt ) ) {
 if ( ( ( kex_flags & LIBSSH2_KEX_METHOD_FLAG_REQ_SIGN_HOSTKEY ) == 0 ) || ( ( * hostkeyp ) -> sig_verify ) ) {
 session -> hostkey = * hostkeyp ;
 return 0 ;
 }
 }
 }
 hostkeyp ++ ;
 }
 return - 1 ;
 }
static int kex_agree_kex_hostkey ( LIBSSH2_SESSION * session , unsigned char * kex , unsigned long kex_len , unsigned char * hostkey , unsigned long hostkey_len ) {
 const LIBSSH2_KEX_METHOD * * kexp = libssh2_kex_methods ;
 unsigned char * s ;
 if ( session -> kex_prefs ) {
 s = ( unsigned char * ) session -> kex_prefs ;
 while ( s && * s ) {
 unsigned char * q , * p = ( unsigned char * ) strchr ( ( char * ) s , ',' ) ;
 size_t method_len = ( p ? ( size_t ) ( p - s ) : strlen ( ( char * ) s ) ) ;
 if ( ( q = kex_agree_instr ( kex , kex_len , s , method_len ) ) ) {
 const LIBSSH2_KEX_METHOD * method = ( const LIBSSH2_KEX_METHOD * ) kex_get_method_by_name ( ( char * ) s , method_len , ( const LIBSSH2_COMMON_METHOD * * ) kexp ) ;
 if ( ! method ) {
 return - 1 ;
 }
 if ( kex_agree_hostkey ( session , method -> flags , hostkey , hostkey_len ) == 0 ) {
 session -> kex = method ;
 if ( session -> burn_optimistic_kexinit && ( kex == q ) ) {
 session -> burn_optimistic_kexinit = 0 ;
 }
 return 0 ;
 }
 }
 s = p ? p + 1 : NULL ;
 }
 return - 1 ;
 }
 while ( * kexp && ( * kexp ) -> name ) {
 s = kex_agree_instr ( kex , kex_len , ( unsigned char * ) ( * kexp ) -> name , strlen ( ( * kexp ) -> name ) ) ;
 if ( s ) {
 if ( kex_agree_hostkey ( session , ( * kexp ) -> flags , hostkey , hostkey_len ) == 0 ) {
 session -> kex = * kexp ;
 if ( session -> burn_optimistic_kexinit && ( kex == s ) ) {
 session -> burn_optimistic_kexinit = 0 ;
 }
 return 0 ;
 }
 }
 kexp ++ ;
 }
 return - 1 ;
 }
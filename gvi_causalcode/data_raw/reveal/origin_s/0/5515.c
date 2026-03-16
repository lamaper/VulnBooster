static int kex_agree_methods ( LIBSSH2_SESSION * session , unsigned char * data , unsigned data_len ) {
 unsigned char * kex , * hostkey , * crypt_cs , * crypt_sc , * comp_cs , * comp_sc , * mac_cs , * mac_sc ;
 size_t kex_len , hostkey_len , crypt_cs_len , crypt_sc_len , comp_cs_len ;
 size_t comp_sc_len , mac_cs_len , mac_sc_len ;
 unsigned char * s = data ;
 s ++ ;
 s += 16 ;
 if ( kex_string_pair ( & s , data , data_len , & kex_len , & kex ) ) return - 1 ;
 if ( kex_string_pair ( & s , data , data_len , & hostkey_len , & hostkey ) ) return - 1 ;
 if ( kex_string_pair ( & s , data , data_len , & crypt_cs_len , & crypt_cs ) ) return - 1 ;
 if ( kex_string_pair ( & s , data , data_len , & crypt_sc_len , & crypt_sc ) ) return - 1 ;
 if ( kex_string_pair ( & s , data , data_len , & mac_cs_len , & mac_cs ) ) return - 1 ;
 if ( kex_string_pair ( & s , data , data_len , & mac_sc_len , & mac_sc ) ) return - 1 ;
 if ( kex_string_pair ( & s , data , data_len , & comp_cs_len , & comp_cs ) ) return - 1 ;
 if ( kex_string_pair ( & s , data , data_len , & comp_sc_len , & comp_sc ) ) return - 1 ;
 session -> burn_optimistic_kexinit = * ( s ++ ) ;
 if ( data_len < ( unsigned ) ( s - data ) ) return - 1 ;
 if ( kex_agree_kex_hostkey ( session , kex , kex_len , hostkey , hostkey_len ) ) {
 return - 1 ;
 }
 if ( kex_agree_crypt ( session , & session -> local , crypt_cs , crypt_cs_len ) || kex_agree_crypt ( session , & session -> remote , crypt_sc , crypt_sc_len ) ) {
 return - 1 ;
 }
 if ( kex_agree_mac ( session , & session -> local , mac_cs , mac_cs_len ) || kex_agree_mac ( session , & session -> remote , mac_sc , mac_sc_len ) ) {
 return - 1 ;
 }
 if ( kex_agree_comp ( session , & session -> local , comp_cs , comp_cs_len ) || kex_agree_comp ( session , & session -> remote , comp_sc , comp_sc_len ) ) {
 return - 1 ;
 }

 return - 1 ;
 }

 _libssh2_debug ( session , LIBSSH2_TRACE_KEX , "Agreed on HOSTKEY method: %s" , session -> hostkey -> name ) ;
 _libssh2_debug ( session , LIBSSH2_TRACE_KEX , "Agreed on CRYPT_CS method: %s" , session -> local . crypt -> name ) ;
 _libssh2_debug ( session , LIBSSH2_TRACE_KEX , "Agreed on CRYPT_SC method: %s" , session -> remote . crypt -> name ) ;
 _libssh2_debug ( session , LIBSSH2_TRACE_KEX , "Agreed on MAC_CS method: %s" , session -> local . mac -> name ) ;
 _libssh2_debug ( session , LIBSSH2_TRACE_KEX , "Agreed on MAC_SC method: %s" , session -> remote . mac -> name ) ;
 _libssh2_debug ( session , LIBSSH2_TRACE_KEX , "Agreed on COMP_CS method: %s" , session -> local . comp -> name ) ;
 _libssh2_debug ( session , LIBSSH2_TRACE_KEX , "Agreed on COMP_SC method: %s" , session -> remote . comp -> name ) ;
 return 0 ;
 }
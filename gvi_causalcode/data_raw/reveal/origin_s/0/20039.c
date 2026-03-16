static const char * mgs_readable_cvm ( mgs_client_verification_method_e m ) {
 switch ( m ) {
 case mgs_cvm_unset : return "unset" ;
 case mgs_cvm_cartel : return "cartel" ;
 case mgs_cvm_msva : return "msva" ;
 }
 return "unknown" ;
 }
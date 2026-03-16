static void decStatus ( decNumber * dn , uInt status , decContext * set ) {
 if ( status & DEC_NaNs ) {
 if ( status & DEC_sNaN ) status &= ~ DEC_sNaN ;
 else {
 uprv_decNumberZero ( dn ) ;
 dn -> bits = DECNAN ;
 }
 }
 uprv_decContextSetStatus ( set , status ) ;
 return ;
 }
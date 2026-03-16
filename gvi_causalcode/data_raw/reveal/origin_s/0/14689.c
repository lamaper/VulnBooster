static decNumber * decQuantizeOp ( decNumber * res , const decNumber * lhs , const decNumber * rhs , decContext * set , Flag quant , uInt * status ) {

 decNumber * allocrhs = NULL ;

 Int reqdigits = set -> digits ;
 Int reqexp ;
 Int residue = 0 ;
 Int etiny = set -> emin - ( reqdigits - 1 ) ;



 if ( lhs -> digits > reqdigits ) {
 alloclhs = decRoundOperand ( lhs , set , status ) ;
 if ( alloclhs == NULL ) break ;
 lhs = alloclhs ;
 }
 if ( rhs -> digits > reqdigits ) {
 allocrhs = decRoundOperand ( rhs , set , status ) ;
 if ( allocrhs == NULL ) break ;
 rhs = allocrhs ;
 }
 }

 if ( SPECIALARGS & ( DECSNAN | DECNAN ) ) decNaNs ( res , lhs , rhs , set , status ) ;
 else if ( ( lhs -> bits ^ rhs -> bits ) & DECINF ) * status |= DEC_Invalid_operation ;
 else uprv_decNumberCopy ( res , lhs ) ;
 break ;
 }
 if ( quant ) reqexp = inrhs -> exponent ;
 else {
 reqexp = decGetInt ( inrhs ) ;
 }


 * status |= DEC_Invalid_operation ;
 break ;
 }
 if ( ISZERO ( lhs ) ) {
 uprv_decNumberCopy ( res , lhs ) ;
 res -> exponent = reqexp ;


 else {
 Int adjust = reqexp - lhs -> exponent ;
 if ( ( lhs -> digits - adjust ) > reqdigits ) {
 * status |= DEC_Invalid_operation ;
 break ;
 }
 if ( adjust > 0 ) {
 decContext workset ;
 workset = * set ;
 workset . digits = lhs -> digits - adjust ;
 decCopyFit ( res , lhs , & workset , & residue , status ) ;
 decApplyRound ( res , & workset , residue , status ) ;
 residue = 0 ;
 if ( res -> exponent > reqexp ) {
 if ( res -> digits == reqdigits ) {
 * status &= ~ ( DEC_Inexact | DEC_Rounded ) ;
 * status |= DEC_Invalid_operation ;
 break ;
 }
 res -> digits = decShiftToMost ( res -> lsu , res -> digits , 1 ) ;
 res -> exponent -- ;
 }


 else {
 uprv_decNumberCopy ( res , lhs ) ;
 if ( adjust < 0 ) {
 res -> digits = decShiftToMost ( res -> lsu , res -> digits , - adjust ) ;
 res -> exponent += adjust ;
 }
 }
 }
 if ( res -> exponent > set -> emax - res -> digits + 1 ) {
 * status |= DEC_Invalid_operation ;
 break ;
 }
 else {
 decFinalize ( res , set , & residue , status ) ;
 * status &= ~ DEC_Underflow ;
 }
 }
 while ( 0 ) ;

 if ( alloclhs != NULL ) free ( alloclhs ) ;

 }
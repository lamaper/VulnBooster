static decNumber * decCompareOp ( decNumber * res , const decNumber * lhs , const decNumber * rhs , decContext * set , Flag op , uInt * status ) {

 decNumber * allocrhs = NULL ;

 uByte merged ;



 if ( lhs -> digits > set -> digits ) {
 alloclhs = decRoundOperand ( lhs , set , status ) ;
 if ( alloclhs == NULL ) {
 result = BADINT ;
 break ;
 }
 lhs = alloclhs ;
 }
 if ( rhs -> digits > set -> digits ) {
 allocrhs = decRoundOperand ( rhs , set , status ) ;
 if ( allocrhs == NULL ) {
 result = BADINT ;
 break ;
 }
 rhs = allocrhs ;
 }
 }

 if ( decNumberIsNegative ( lhs ) && ! decNumberIsNegative ( rhs ) ) {
 result = - 1 ;
 break ;
 }
 if ( ! decNumberIsNegative ( lhs ) && decNumberIsNegative ( rhs ) ) {
 result = + 1 ;
 break ;
 }
 }
 merged = ( lhs -> bits | rhs -> bits ) & ( DECSNAN | DECNAN ) ;
 if ( merged ) {
 if ( op == COMPARE ) ;
 else if ( op == COMPSIG ) * status |= DEC_Invalid_operation | DEC_sNaN ;
 else if ( op == COMPTOTAL ) {
 if ( ! decNumberIsNaN ( lhs ) ) result = - 1 ;
 else if ( ! decNumberIsNaN ( rhs ) ) result = + 1 ;
 else if ( decNumberIsSNaN ( lhs ) && decNumberIsQNaN ( rhs ) ) result = - 1 ;
 else if ( decNumberIsQNaN ( lhs ) && decNumberIsSNaN ( rhs ) ) result = + 1 ;
 else {
 result = decUnitCompare ( lhs -> lsu , D2U ( lhs -> digits ) , rhs -> lsu , D2U ( rhs -> digits ) , 0 ) ;
 }
 if ( decNumberIsNegative ( lhs ) ) result = - result ;
 break ;
 }
 else if ( merged & DECSNAN ) ;
 else {
 if ( ! decNumberIsNaN ( lhs ) || ! decNumberIsNaN ( rhs ) ) {
 op = COMPMAX ;
 if ( lhs -> bits & DECNAN ) result = - 1 ;
 else result = + 1 ;
 break ;
 }
 }
 op = COMPNAN ;
 decNaNs ( res , lhs , rhs , set , status ) ;
 break ;
 }
 if ( op == COMPMAXMAG || op == COMPMINMAG ) result = decCompare ( lhs , rhs , 1 ) ;
 else result = decCompare ( lhs , rhs , 0 ) ;
 }
 while ( 0 ) ;
 if ( result == BADINT ) * status |= DEC_Insufficient_storage ;
 else {
 if ( op == COMPARE || op == COMPSIG || op == COMPTOTAL ) {
 if ( op == COMPTOTAL && result == 0 ) {
 if ( lhs -> exponent != rhs -> exponent ) {
 if ( lhs -> exponent < rhs -> exponent ) result = - 1 ;
 else result = + 1 ;
 if ( decNumberIsNegative ( lhs ) ) result = - result ;
 }
 }
 uprv_decNumberZero ( res ) ;
 if ( result != 0 ) {
 * res -> lsu = 1 ;
 if ( result < 0 ) res -> bits = DECNEG ;
 }
 }
 else if ( op == COMPNAN ) ;
 else {
 Int residue = 0 ;
 const decNumber * choice ;
 if ( result == 0 ) {
 uByte slhs = ( lhs -> bits & DECNEG ) ;
 uByte srhs = ( rhs -> bits & DECNEG ) ;

 op = COMPMAX ;
 result = + 1 ;
 }
 else # endif if ( slhs != srhs ) {
 if ( slhs ) result = - 1 ;
 else result = + 1 ;
 }
 else if ( slhs && srhs ) {
 if ( lhs -> exponent < rhs -> exponent ) result = + 1 ;
 else result = - 1 ;
 }
 else {
 if ( lhs -> exponent > rhs -> exponent ) result = + 1 ;
 else result = - 1 ;
 }
 }
 if ( op == COMPMIN || op == COMPMINMAG ) result = - result ;
 choice = ( result > 0 ? lhs : rhs ) ;
 decCopyFit ( res , choice , set , & residue , status ) ;
 decFinish ( res , set , & residue , status ) ;
 }
 }

 if ( alloclhs != NULL ) free ( alloclhs ) ;

 }
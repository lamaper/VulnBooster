static decNumber * decNaNs ( decNumber * res , const decNumber * lhs , const decNumber * rhs , decContext * set , uInt * status ) {
 if ( lhs -> bits & DECSNAN ) * status |= DEC_Invalid_operation | DEC_sNaN ;
 else if ( rhs == NULL ) ;
 else if ( rhs -> bits & DECSNAN ) {
 lhs = rhs ;
 * status |= DEC_Invalid_operation | DEC_sNaN ;
 }
 else if ( lhs -> bits & DECNAN ) ;
 else lhs = rhs ;
 if ( lhs -> digits <= set -> digits ) uprv_decNumberCopy ( res , lhs ) ;
 else {
 const Unit * ul ;
 Unit * ur , * uresp1 ;
 res -> bits = lhs -> bits ;
 uresp1 = res -> lsu + D2U ( set -> digits ) ;
 for ( ur = res -> lsu , ul = lhs -> lsu ;
 ur < uresp1 ;
 ur ++ , ul ++ ) * ur = * ul ;
 res -> digits = D2U ( set -> digits ) * DECDPUN ;
 if ( res -> digits > set -> digits ) decDecap ( res , res -> digits - set -> digits ) ;
 }
 res -> bits &= ~ DECSNAN ;
 res -> bits |= DECNAN ;
 res -> exponent = 0 ;
 return res ;
 }
static uInt decCheckMath ( const decNumber * rhs , decContext * set , uInt * status ) {
 uInt save = * status ;
 if ( set -> digits > DEC_MAX_MATH || set -> emax > DEC_MAX_MATH || - set -> emin > DEC_MAX_MATH ) * status |= DEC_Invalid_context ;
 else if ( ( rhs -> digits > DEC_MAX_MATH || rhs -> exponent + rhs -> digits > DEC_MAX_MATH + 1 || rhs -> exponent + rhs -> digits < 2 * ( 1 - DEC_MAX_MATH ) ) && ! ISZERO ( rhs ) ) * status |= DEC_Invalid_operation ;
 return ( * status != save ) ;
 }
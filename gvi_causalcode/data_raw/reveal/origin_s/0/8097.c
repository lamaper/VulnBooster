static Int decCompare ( const decNumber * lhs , const decNumber * rhs , Flag abs_c ) {
 Int result ;
 Int sigr ;
 Int compare ;
 result = 1 ;
 if ( ISZERO ( lhs ) ) result = 0 ;
 if ( abs_c ) {
 if ( ISZERO ( rhs ) ) return result ;
 if ( result == 0 ) return - 1 ;
 }
 else {
 if ( result && decNumberIsNegative ( lhs ) ) result = - 1 ;
 sigr = 1 ;
 if ( ISZERO ( rhs ) ) sigr = 0 ;
 else if ( decNumberIsNegative ( rhs ) ) sigr = - 1 ;
 if ( result > sigr ) return + 1 ;
 if ( result < sigr ) return - 1 ;
 if ( result == 0 ) return 0 ;
 }
 if ( ( lhs -> bits | rhs -> bits ) & DECINF ) {
 if ( decNumberIsInfinite ( rhs ) ) {
 if ( decNumberIsInfinite ( lhs ) ) result = 0 ;
 else result = - result ;
 }
 return result ;
 }
 if ( lhs -> exponent > rhs -> exponent ) {
 const decNumber * temp = lhs ;
 lhs = rhs ;
 rhs = temp ;
 result = - result ;
 }
 compare = decUnitCompare ( lhs -> lsu , D2U ( lhs -> digits ) , rhs -> lsu , D2U ( rhs -> digits ) , rhs -> exponent - lhs -> exponent ) ;
 if ( compare != BADINT ) compare *= result ;
 return compare ;
 }
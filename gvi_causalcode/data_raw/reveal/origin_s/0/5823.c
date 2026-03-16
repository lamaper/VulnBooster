static void decSetOverflow ( decNumber * dn , decContext * set , uInt * status ) {
 Flag needmax = 0 ;
 uByte sign = dn -> bits & DECNEG ;
 if ( ISZERO ( dn ) ) {
 Int emax = set -> emax ;
 if ( set -> clamp ) emax -= set -> digits - 1 ;
 if ( dn -> exponent > emax ) {
 dn -> exponent = emax ;
 * status |= DEC_Clamped ;
 }
 return ;
 }
 uprv_decNumberZero ( dn ) ;
 switch ( set -> round ) {
 case DEC_ROUND_DOWN : {
 needmax = 1 ;
 break ;
 }
 case DEC_ROUND_05UP : {
 needmax = 1 ;
 break ;
 }
 case DEC_ROUND_CEILING : {
 if ( sign ) needmax = 1 ;
 break ;
 }
 case DEC_ROUND_FLOOR : {
 if ( ! sign ) needmax = 1 ;
 break ;
 }
 default : break ;
 }
 if ( needmax ) {
 decSetMaxValue ( dn , set ) ;
 dn -> bits = sign ;
 }
 else dn -> bits = sign | DECINF ;
 * status |= DEC_Overflow | DEC_Inexact | DEC_Rounded ;
 }
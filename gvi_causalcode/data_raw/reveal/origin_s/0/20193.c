static void decFinalize ( decNumber * dn , decContext * set , Int * residue , uInt * status ) {
 Int shift ;
 Int tinyexp = set -> emin - dn -> digits + 1 ;
 if ( dn -> exponent <= tinyexp ) {
 Int comp ;
 decNumber nmin ;
 if ( dn -> exponent < tinyexp ) {
 decSetSubnormal ( dn , set , residue , status ) ;
 return ;
 }
 uprv_decNumberZero ( & nmin ) ;
 nmin . lsu [ 0 ] = 1 ;
 nmin . exponent = set -> emin ;
 comp = decCompare ( dn , & nmin , 1 ) ;
 if ( comp == BADINT ) {
 * status |= DEC_Insufficient_storage ;
 return ;
 }
 if ( * residue < 0 && comp == 0 ) {
 decApplyRound ( dn , set , * residue , status ) ;
 decSetSubnormal ( dn , set , residue , status ) ;
 return ;
 }
 }
 if ( * residue != 0 ) decApplyRound ( dn , set , * residue , status ) ;
 if ( dn -> exponent <= set -> emax - set -> digits + 1 ) return ;
 if ( dn -> exponent > set -> emax - dn -> digits + 1 ) {
 decSetOverflow ( dn , set , status ) ;
 return ;
 }
 if ( ! set -> clamp ) return ;
 shift = dn -> exponent - ( set -> emax - set -> digits + 1 ) ;
 if ( ! ISZERO ( dn ) ) {
 dn -> digits = decShiftToMost ( dn -> lsu , dn -> digits , shift ) ;
 }
 dn -> exponent -= shift ;
 * status |= DEC_Clamped ;
 return ;
 }
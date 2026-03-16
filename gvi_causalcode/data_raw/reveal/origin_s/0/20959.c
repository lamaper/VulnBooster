static void decCopyFit ( decNumber * dest , const decNumber * src , decContext * set , Int * residue , uInt * status ) {
 dest -> bits = src -> bits ;
 dest -> exponent = src -> exponent ;
 decSetCoeff ( dest , set , src -> lsu , src -> digits , residue , status ) ;
 }
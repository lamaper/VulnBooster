static void lower_mv_precision ( MV * mv , int allow_hp ) {
 const int use_hp = allow_hp && vp9_use_mv_hp ( mv ) ;
 if ( ! use_hp ) {
 if ( mv -> row & 1 ) mv -> row += ( mv -> row > 0 ? - 1 : 1 ) ;
 if ( mv -> col & 1 ) mv -> col += ( mv -> col > 0 ? - 1 : 1 ) ;
 }
 }
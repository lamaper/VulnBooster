static void inc_mvs ( const MB_MODE_INFO * mbmi , const int_mv mvs [ 2 ] , nmv_context_counts * counts ) {
 int i ;
 for ( i = 0 ;
 i < 1 + has_second_ref ( mbmi ) ;
 ++ i ) {
 const MV * ref = & mbmi -> ref_mvs [ mbmi -> ref_frame [ i ] ] [ 0 ] . as_mv ;
 const MV diff = {
 mvs [ i ] . as_mv . row - ref -> row , mvs [ i ] . as_mv . col - ref -> col }
 ;
 vp9_inc_mv ( & diff , counts ) ;
 }
 }
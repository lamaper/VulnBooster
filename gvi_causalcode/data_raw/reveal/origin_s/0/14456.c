static void imdct_output ( TwinContext * tctx , enum FrameType ftype , int wtype , float * * out ) {
 const ModeTab * mtab = tctx -> mtab ;
 int size1 , size2 ;
 float * prev_buf = tctx -> prev_frame + tctx -> last_block_pos [ 0 ] ;
 int i ;
 for ( i = 0 ;
 i < tctx -> avctx -> channels ;
 i ++ ) {
 imdct_and_window ( tctx , ftype , wtype , tctx -> spectrum + i * mtab -> size , prev_buf + 2 * i * mtab -> size , i ) ;
 }
 if ( ! out ) return ;
 size2 = tctx -> last_block_pos [ 0 ] ;
 size1 = mtab -> size - size2 ;
 memcpy ( & out [ 0 ] [ 0 ] , prev_buf , size1 * sizeof ( out [ 0 ] [ 0 ] ) ) ;
 memcpy ( & out [ 0 ] [ size1 ] , tctx -> curr_frame , size2 * sizeof ( out [ 0 ] [ 0 ] ) ) ;
 if ( tctx -> avctx -> channels == 2 ) {
 memcpy ( & out [ 1 ] [ 0 ] , & prev_buf [ 2 * mtab -> size ] , size1 * sizeof ( out [ 1 ] [ 0 ] ) ) ;
 memcpy ( & out [ 1 ] [ size1 ] , & tctx -> curr_frame [ 2 * mtab -> size ] , size2 * sizeof ( out [ 1 ] [ 0 ] ) ) ;
 tctx -> fdsp . butterflies_float ( out [ 0 ] , out [ 1 ] , mtab -> size ) ;
 }
 }
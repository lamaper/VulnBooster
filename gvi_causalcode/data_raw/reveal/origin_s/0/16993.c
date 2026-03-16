static void read_mv_probs ( nmv_context * ctx , int allow_hp , vp9_reader * r ) {
 int i , j ;
 update_mv_probs ( ctx -> joints , MV_JOINTS - 1 , r ) ;
 for ( i = 0 ;
 i < 2 ;
 ++ i ) {
 nmv_component * const comp_ctx = & ctx -> comps [ i ] ;
 update_mv_probs ( & comp_ctx -> sign , 1 , r ) ;
 update_mv_probs ( comp_ctx -> classes , MV_CLASSES - 1 , r ) ;
 update_mv_probs ( comp_ctx -> class0 , CLASS0_SIZE - 1 , r ) ;
 update_mv_probs ( comp_ctx -> bits , MV_OFFSET_BITS , r ) ;
 }
 for ( i = 0 ;
 i < 2 ;
 ++ i ) {
 nmv_component * const comp_ctx = & ctx -> comps [ i ] ;
 for ( j = 0 ;
 j < CLASS0_SIZE ;
 ++ j ) update_mv_probs ( comp_ctx -> class0_fp [ j ] , MV_FP_SIZE - 1 , r ) ;
 update_mv_probs ( comp_ctx -> fp , 3 , r ) ;
 }
 if ( allow_hp ) {
 for ( i = 0 ;
 i < 2 ;
 ++ i ) {
 nmv_component * const comp_ctx = & ctx -> comps [ i ] ;
 update_mv_probs ( & comp_ctx -> class0_hp , 1 , r ) ;
 update_mv_probs ( & comp_ctx -> hp , 1 , r ) ;
 }
 }
 }
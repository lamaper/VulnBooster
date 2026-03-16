void vp9_write_nmv_probs ( VP9_COMMON * cm , int usehp , vp9_writer * w ) {
 int i , j ;
 nmv_context * const mvc = & cm -> fc . nmvc ;
 nmv_context_counts * const counts = & cm -> counts . mv ;
 write_mv_update ( vp9_mv_joint_tree , mvc -> joints , counts -> joints , MV_JOINTS , w ) ;
 for ( i = 0 ;
 i < 2 ;
 ++ i ) {
 nmv_component * comp = & mvc -> comps [ i ] ;
 nmv_component_counts * comp_counts = & counts -> comps [ i ] ;
 update_mv ( w , comp_counts -> sign , & comp -> sign , MV_UPDATE_PROB ) ;
 write_mv_update ( vp9_mv_class_tree , comp -> classes , comp_counts -> classes , MV_CLASSES , w ) ;
 write_mv_update ( vp9_mv_class0_tree , comp -> class0 , comp_counts -> class0 , CLASS0_SIZE , w ) ;
 for ( j = 0 ;
 j < MV_OFFSET_BITS ;
 ++ j ) update_mv ( w , comp_counts -> bits [ j ] , & comp -> bits [ j ] , MV_UPDATE_PROB ) ;
 }
 for ( i = 0 ;
 i < 2 ;
 ++ i ) {
 for ( j = 0 ;
 j < CLASS0_SIZE ;
 ++ j ) write_mv_update ( vp9_mv_fp_tree , mvc -> comps [ i ] . class0_fp [ j ] , counts -> comps [ i ] . class0_fp [ j ] , MV_FP_SIZE , w ) ;
 write_mv_update ( vp9_mv_fp_tree , mvc -> comps [ i ] . fp , counts -> comps [ i ] . fp , MV_FP_SIZE , w ) ;
 }
 if ( usehp ) {
 for ( i = 0 ;
 i < 2 ;
 ++ i ) {
 update_mv ( w , counts -> comps [ i ] . class0_hp , & mvc -> comps [ i ] . class0_hp , MV_UPDATE_PROB ) ;
 update_mv ( w , counts -> comps [ i ] . hp , & mvc -> comps [ i ] . hp , MV_UPDATE_PROB ) ;
 }
 }
 }
void vp9_encode_mv ( VP9_COMP * cpi , vp9_writer * w , const MV * mv , const MV * ref , const nmv_context * mvctx , int usehp ) {
 const MV diff = {
 mv -> row - ref -> row , mv -> col - ref -> col }
 ;
 const MV_JOINT_TYPE j = vp9_get_mv_joint ( & diff ) ;
 usehp = usehp && vp9_use_mv_hp ( ref ) ;
 vp9_write_token ( w , vp9_mv_joint_tree , mvctx -> joints , & mv_joint_encodings [ j ] ) ;
 if ( mv_joint_vertical ( j ) ) encode_mv_component ( w , diff . row , & mvctx -> comps [ 0 ] , usehp ) ;
 if ( mv_joint_horizontal ( j ) ) encode_mv_component ( w , diff . col , & mvctx -> comps [ 1 ] , usehp ) ;
 if ( cpi -> sf . mv . auto_mv_step_size ) {
 unsigned int maxv = MAX ( abs ( mv -> row ) , abs ( mv -> col ) ) >> 3 ;
 cpi -> max_mv_magnitude = MAX ( maxv , cpi -> max_mv_magnitude ) ;
 }
 }
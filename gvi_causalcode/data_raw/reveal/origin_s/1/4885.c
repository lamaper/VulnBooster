hb_shape_plan_t * hb_shape_plan_create_cached ( hb_face_t * face , const hb_segment_properties_t * props , const hb_feature_t * user_features , unsigned int num_user_features , const char * const * shaper_list ) {
 DEBUG_MSG_FUNC ( SHAPE_PLAN , NULL , "face=%p num_features=%d shaper_list=%p" , face , num_user_features , shaper_list ) ;
 hb_shape_plan_proposal_t proposal = {
 * props , shaper_list , user_features , num_user_features , NULL }
 ;
 if ( shaper_list ) {
 for ( const char * const * shaper_item = shaper_list ;
 * shaper_item ;
 shaper_item ++ ) if ( 0 ) ;

 proposal . shaper_func = _hb_ ## shaper ## _shape ;
 break ;
 }

 }
 retry : hb_face_t : : plan_node_t * cached_plan_nodes = ( hb_face_t : : plan_node_t * ) hb_atomic_ptr_get ( & face -> shape_plans ) ;
 for ( hb_face_t : : plan_node_t * node = cached_plan_nodes ;
 node ;
 node = node -> next ) if ( hb_shape_plan_matches ( node -> shape_plan , & proposal ) ) {
 DEBUG_MSG_FUNC ( SHAPE_PLAN , node -> shape_plan , "fulfilled from cache" ) ;
 return hb_shape_plan_reference ( node -> shape_plan ) ;
 }
 hb_shape_plan_t * shape_plan = hb_shape_plan_create ( face , props , user_features , num_user_features , shaper_list ) ;
 if ( hb_non_global_user_features_present ( user_features , num_user_features ) ) return shape_plan ;
 hb_face_t : : plan_node_t * node = ( hb_face_t : : plan_node_t * ) calloc ( 1 , sizeof ( hb_face_t : : plan_node_t ) ) ;
 if ( unlikely ( ! node ) ) return shape_plan ;
 node -> shape_plan = shape_plan ;
 node -> next = cached_plan_nodes ;
 if ( ! hb_atomic_ptr_cmpexch ( & face -> shape_plans , cached_plan_nodes , node ) ) {
 hb_shape_plan_destroy ( shape_plan ) ;
 free ( node ) ;
 goto retry ;
 }
 DEBUG_MSG_FUNC ( SHAPE_PLAN , shape_plan , "inserted into cache" ) ;
 return hb_shape_plan_reference ( shape_plan ) ;
 }
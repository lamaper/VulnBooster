static void hb_shape_plan_plan ( hb_shape_plan_t * shape_plan , const hb_feature_t * user_features , unsigned int num_user_features , const char * const * shaper_list ) {
 DEBUG_MSG_FUNC ( SHAPE_PLAN , shape_plan , "num_features=%d shaper_list=%p" , num_user_features , shaper_list ) ;
 const hb_shaper_pair_t * shapers = _hb_shapers_get ( ) ;

 if ( hb_ ## shaper ## _shaper_face_data_ensure ( shape_plan -> face_unsafe ) ) {
 HB_SHAPER_DATA ( shaper , shape_plan ) = HB_SHAPER_DATA_CREATE_FUNC ( shaper , shape_plan ) ( shape_plan , user_features , num_user_features ) ;
 shape_plan -> shaper_func = _hb_ ## shaper ## _shape ;
 shape_plan -> shaper_name = # shaper ;
 return ;
 }
 }
 HB_STMT_END if ( likely ( ! shaper_list ) ) {
 for ( unsigned int i = 0 ;
 i < HB_SHAPERS_COUNT ;
 i ++ ) if ( 0 ) ;


 else {
 for ( ;
 * shaper_list ;
 shaper_list ++ ) if ( 0 ) ;



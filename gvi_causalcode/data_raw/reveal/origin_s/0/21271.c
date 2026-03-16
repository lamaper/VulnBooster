hb_shape_plan_t * hb_shape_plan_create ( hb_face_t * face , const hb_segment_properties_t * props , const hb_feature_t * user_features , unsigned int num_user_features , const char * const * shaper_list ) {
 DEBUG_MSG_FUNC ( SHAPE_PLAN , NULL , "face=%p num_features=%d shaper_list=%p" , face , num_user_features , shaper_list ) ;
 hb_shape_plan_t * shape_plan ;
 hb_feature_t * features = NULL ;
 if ( unlikely ( ! face ) ) face = hb_face_get_empty ( ) ;
 if ( unlikely ( ! props ) ) return hb_shape_plan_get_empty ( ) ;
 if ( num_user_features && ! ( features = ( hb_feature_t * ) malloc ( num_user_features * sizeof ( hb_feature_t ) ) ) ) return hb_shape_plan_get_empty ( ) ;
 if ( ! ( shape_plan = hb_object_create < hb_shape_plan_t > ( ) ) ) {
 free ( features ) ;
 return hb_shape_plan_get_empty ( ) ;
 }
 assert ( props -> direction != HB_DIRECTION_INVALID ) ;
 hb_face_make_immutable ( face ) ;
 shape_plan -> default_shaper_list = shaper_list == NULL ;
 shape_plan -> face_unsafe = face ;
 shape_plan -> props = * props ;
 shape_plan -> num_user_features = num_user_features ;
 shape_plan -> user_features = features ;
 if ( num_user_features ) memcpy ( features , user_features , num_user_features * sizeof ( hb_feature_t ) ) ;
 hb_shape_plan_plan ( shape_plan , user_features , num_user_features , shaper_list ) ;
 return shape_plan ;
 }
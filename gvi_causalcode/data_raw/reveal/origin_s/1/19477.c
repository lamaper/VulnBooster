hb_bool_t hb_shape_plan_execute ( hb_shape_plan_t * shape_plan , hb_font_t * font , hb_buffer_t * buffer , const hb_feature_t * features , unsigned int num_features ) {
 DEBUG_MSG_FUNC ( SHAPE_PLAN , shape_plan , "num_features=%d shaper_func=%p" , num_features , shape_plan -> shaper_func ) ;
 if ( unlikely ( hb_object_is_inert ( shape_plan ) || hb_object_is_inert ( font ) || hb_object_is_inert ( buffer ) ) ) return false ;
 assert ( shape_plan -> face_unsafe == font -> face ) ;
 assert ( hb_segment_properties_equal ( & shape_plan -> props , & buffer -> props ) ) ;

 return HB_SHAPER_DATA ( shaper , shape_plan ) && hb_ ## shaper ## _shaper_font_data_ensure ( font ) && _hb_ ## shaper ## _shape ( shape_plan , font , buffer , features , num_features ) ;
 }
 HB_STMT_END if ( 0 ) ;


 }
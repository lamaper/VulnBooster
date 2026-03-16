static void arabic_fallback_shape ( const hb_ot_shape_plan_t * plan , hb_font_t * font , hb_buffer_t * buffer ) {
 const arabic_shape_plan_t * arabic_plan = ( const arabic_shape_plan_t * ) plan -> data ;
 if ( ! arabic_plan -> do_fallback ) return ;
 retry : arabic_fallback_plan_t * fallback_plan = ( arabic_fallback_plan_t * ) hb_atomic_ptr_get ( & arabic_plan -> fallback_plan ) ;
 if ( unlikely ( ! fallback_plan ) ) {
 fallback_plan = arabic_fallback_plan_create ( plan , font ) ;
 if ( unlikely ( ! hb_atomic_ptr_cmpexch ( & ( const_cast < arabic_shape_plan_t * > ( arabic_plan ) ) -> fallback_plan , NULL , fallback_plan ) ) ) {
 arabic_fallback_plan_destroy ( fallback_plan ) ;
 goto retry ;
 }
 }
 arabic_fallback_plan_shape ( fallback_plan , font , buffer ) ;
 }
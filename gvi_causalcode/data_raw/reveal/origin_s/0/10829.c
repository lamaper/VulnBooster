void hb_shape_plan_destroy ( hb_shape_plan_t * shape_plan ) {
 if ( ! hb_object_destroy ( shape_plan ) ) return ;


 free ( shape_plan ) ;
 }
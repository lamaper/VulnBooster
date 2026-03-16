static void data_destroy_arabic ( void * data ) {
 arabic_shape_plan_t * arabic_plan = ( arabic_shape_plan_t * ) data ;
 arabic_fallback_plan_destroy ( arabic_plan -> fallback_plan ) ;
 free ( data ) ;
 }
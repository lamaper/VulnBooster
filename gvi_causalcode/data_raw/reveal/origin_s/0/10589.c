static void setup_masks_arabic ( const hb_ot_shape_plan_t * plan , hb_buffer_t * buffer , hb_font_t * font HB_UNUSED ) {
 const arabic_shape_plan_t * arabic_plan = ( const arabic_shape_plan_t * ) plan -> data ;
 setup_masks_arabic_plan ( arabic_plan , buffer , plan -> props . script ) ;
 }
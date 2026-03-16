static void _hb_ ## name ## _destroy ( hb_ ## name ## _t * l ) {
 free ( l ) ;
 }
 HB_DEFINE_BOXED_TYPE ( name , _hb_ ## name ## _reference , _hb_ ## name ## _destroy ) ;
 HB_DEFINE_OBJECT_TYPE ( buffer ) HB_DEFINE_OBJECT_TYPE ( blob ) HB_DEFINE_OBJECT_TYPE ( face ) HB_DEFINE_OBJECT_TYPE ( font ) HB_DEFINE_OBJECT_TYPE ( font_funcs ) HB_DEFINE_OBJECT_TYPE ( set ) HB_DEFINE_OBJECT_TYPE ( shape_plan ) HB_DEFINE_OBJECT_TYPE ( unicode_funcs ) HB_DEFINE_VALUE_TYPE ( feature ) HB_DEFINE_VALUE_TYPE ( glyph_info )
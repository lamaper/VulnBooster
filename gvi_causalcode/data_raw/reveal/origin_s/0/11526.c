static hb_ ## name ## _t * _hb_ ## name ## _reference ( const hb_ ## name ## _t * l ) {
 hb_ ## name ## _t * c = ( hb_ ## name ## _t * ) calloc ( 1 , sizeof ( hb_ ## name ## _t ) ) ;
 if ( unlikely ( ! c ) ) return NULL ;
 * c = * l ;
 return c ;
 }
 static void _hb_ ## name ## _destroy ( hb_ ## name ## _t * l ) {
 free ( l ) ;
 }
 HB_DEFINE_BOXED_TYPE ( name , _hb_ ## name ## _reference , _hb_ ## name ## _destroy ) ;
 HB_DEFINE_OBJECT_TYPE ( buffer ) HB_DEFINE_OBJECT_TYPE ( blob ) HB_DEFINE_OBJECT_TYPE ( face ) HB_DEFINE_OBJECT_TYPE ( font ) HB_DEFINE_OBJECT_TYPE ( font_funcs ) HB_DEFINE_OBJECT_TYPE ( set ) HB_DEFINE_OBJECT_TYPE ( shape_plan ) HB_DEFINE_OBJECT_TYPE ( unicode_funcs ) HB_DEFINE_VALUE_TYPE ( feature ) HB_DEFINE_VALUE_TYPE ( glyph_info ) HB_DEFINE_VALUE_TYPE ( glyph_position )
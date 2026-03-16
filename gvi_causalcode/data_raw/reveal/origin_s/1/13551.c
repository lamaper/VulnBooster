GType hb_gobject_ ## name ## _get_type ( void ) \ {
 static gsize type_id = 0 ;
 if ( g_once_init_enter ( & type_id ) ) {
 GType id = g_boxed_type_register_static ( g_intern_static_string ( "hb_" # name "_t" ) , ( GBoxedCopyFunc ) copy_func , ( GBoxedFreeFunc ) free_func ) ;
 g_once_init_leave ( & type_id , id ) ;
 }
 return type_id ;
 \ }

 HB_DEFINE_OBJECT_TYPE ( buffer ) HB_DEFINE_OBJECT_TYPE ( blob ) HB_DEFINE_OBJECT_TYPE ( face ) HB_DEFINE_OBJECT_TYPE ( font ) HB_DEFINE_OBJECT_TYPE ( font_funcs ) HB_DEFINE_OBJECT_TYPE ( set ) HB_DEFINE_OBJECT_TYPE ( shape_plan ) HB_DEFINE_OBJECT_TYPE ( unicode_funcs ) static hb_feature_t * feature_reference ( hb_feature_t * g ) {
 hb_feature_t * c = ( hb_feature_t * ) calloc ( 1 , sizeof ( hb_feature_t ) ) ;
 if ( unlikely ( ! c ) ) return NULL ;
 * c = * g ;
 return c ;
 }
 static void feature_destroy ( hb_feature_t * g ) {
 free ( g ) ;
 }
 HB_DEFINE_BOXED_TYPE ( feature , feature_reference , feature_destroy )
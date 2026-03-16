static void basic_avp_reginfo ( diam_avp_t * a , const char * name , enum ftenum ft , field_display_e base , value_string_ext * vs_ext ) {
 hf_register_info hf ;
 gint * ettp = & ( a -> ett ) ;
 hf . p_id = & ( a -> hf_value ) ;
 hf . hfinfo . name = NULL ;
 hf . hfinfo . abbrev = NULL ;
 hf . hfinfo . type = ft ;
 hf . hfinfo . display = base ;
 hf . hfinfo . strings = NULL ;
 hf . hfinfo . bitmask = 0x0 ;
 hf . hfinfo . blurb = a -> vendor -> code ? wmem_strdup_printf ( wmem_epan_scope ( ) , "vendor=%d code=%d" , a -> vendor -> code , a -> code ) : wmem_strdup_printf ( wmem_epan_scope ( ) , "code=%d" , a -> code ) ;
 HFILL_INIT ( hf ) ;
 hf . hfinfo . name = wmem_strdup_printf ( wmem_epan_scope ( ) , "%s" , name ) ;
 hf . hfinfo . abbrev = alnumerize ( wmem_strdup_printf ( wmem_epan_scope ( ) , "diameter.%s" , name ) ) ;
 if ( vs_ext ) {
 hf . hfinfo . strings = vs_ext ;
 }
 wmem_array_append ( build_dict . hf , & hf , 1 ) ;
 g_ptr_array_add ( build_dict . ett , ettp ) ;
 }
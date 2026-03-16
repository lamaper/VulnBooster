static guint reginfo ( int * hf_ptr , const char * name , const char * abbr , const char * desc , enum ftenum ft , field_display_e base , value_string_ext * vs_ext , guint32 mask ) {
 hf_register_info hf ;
 hf . p_id = hf_ptr ;
 hf . hfinfo . name = name ;
 hf . hfinfo . abbrev = abbr ;
 hf . hfinfo . type = ft ;
 hf . hfinfo . display = base ;
 hf . hfinfo . strings = NULL ;
 hf . hfinfo . bitmask = mask ;
 hf . hfinfo . blurb = desc ;
 HFILL_INIT ( hf ) ;
 if ( vs_ext ) {
 hf . hfinfo . strings = vs_ext ;
 }
 wmem_array_append_one ( build_dict . hf , hf ) ;
 return wmem_array_get_count ( build_dict . hf ) ;
 }
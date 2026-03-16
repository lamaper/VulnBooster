static const char * hf_try_val64_to_str ( guint64 value , const header_field_info * hfinfo ) {
 if ( hfinfo -> display & BASE_VAL64_STRING ) return try_val64_to_str ( value , ( const val64_string * ) hfinfo -> strings ) ;
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 return NULL ;
 }
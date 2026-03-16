static diam_avp_t * build_simple_avp ( const avp_type_t * type , guint32 code , diam_vnd_t * vendor , const char * name , const value_string * vs , void * data _U_ ) {
 diam_avp_t * a ;
 value_string_ext * vs_ext = NULL ;
 field_display_e base ;
 guint i = 0 ;
 base = ( field_display_e ) type -> base ;
 if ( vs != NULL ) {
 switch ( type -> ft ) {
 case FT_UINT8 : case FT_UINT16 : case FT_UINT32 : case FT_INT8 : case FT_INT16 : case FT_INT32 : break ;
 default : report_failure ( "Diameter Dictionary: AVP '%s' has a list of values but isn't of a 32-bit or shorter integral type (%s)\n" , name , ftype_name ( type -> ft ) ) ;
 return NULL ;
 }
 while ( vs [ i ] . strptr ) {
 i ++ ;
 }
 vs_ext = value_string_ext_new ( vs , i + 1 , wmem_strdup_printf ( wmem_epan_scope ( ) , "%s_vals_ext" , name ) ) ;
 base = ( field_display_e ) ( base | BASE_EXT_STRING ) ;
 }
 a = ( diam_avp_t * ) wmem_alloc0 ( wmem_epan_scope ( ) , sizeof ( diam_avp_t ) ) ;
 a -> code = code ;
 a -> vendor = vendor ;
 a -> dissector_v16 = type -> v16 ;
 a -> dissector_rfc = type -> rfc ;
 a -> ett = - 1 ;
 a -> hf_value = - 1 ;
 basic_avp_reginfo ( a , name , type -> ft , base , vs_ext ) ;
 return a ;
 }
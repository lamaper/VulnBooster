static diam_avp_t * build_appid_avp ( const avp_type_t * type , guint32 code , diam_vnd_t * vendor , const char * name , const value_string * vs _U_ , void * data _U_ ) {
 diam_avp_t * a ;
 field_display_e base ;
 a = ( diam_avp_t * ) wmem_alloc0 ( wmem_epan_scope ( ) , sizeof ( diam_avp_t ) ) ;
 a -> code = code ;
 a -> vendor = vendor ;
 a -> dissector_v16 = type -> v16 ;
 a -> dissector_rfc = type -> rfc ;
 a -> ett = - 1 ;
 a -> hf_value = - 1 ;
 if ( vs != NULL ) {
 report_failure ( "Diameter Dictionary: AVP '%s' (of type AppId) has a list of values but the list won't be used\n" , name ) ;
 }
 base = ( field_display_e ) ( type -> base | BASE_EXT_STRING ) ;
 basic_avp_reginfo ( a , name , type -> ft , base , dictionary . applications ) ;
 return a ;
 }
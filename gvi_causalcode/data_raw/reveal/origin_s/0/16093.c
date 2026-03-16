static diam_avp_t * build_address_avp ( const avp_type_t * type _U_ , guint32 code , diam_vnd_t * vendor , const char * name , const value_string * vs _U_ , void * data _U_ ) {
 diam_avp_t * a = wmem_new0 ( wmem_epan_scope ( ) , diam_avp_t ) ;
 address_avp_t * t = wmem_new ( wmem_epan_scope ( ) , address_avp_t ) ;
 gint * ettp = & ( t -> ett ) ;
 a -> code = code ;
 a -> vendor = vendor ;
 a -> dissector_v16 = address_v16_avp ;
 if ( code < 256 ) {
 a -> dissector_rfc = address_v16_avp ;
 }
 else {
 a -> dissector_rfc = address_rfc_avp ;
 }
 a -> ett = - 1 ;
 a -> hf_value = - 1 ;
 a -> type_data = t ;
 t -> ett = - 1 ;
 t -> hf_address_type = - 1 ;
 t -> hf_ipv4 = - 1 ;
 t -> hf_ipv6 = - 1 ;
 t -> hf_other = - 1 ;
 basic_avp_reginfo ( a , name , FT_BYTES , BASE_NONE , NULL ) ;
 reginfo ( & ( t -> hf_address_type ) , wmem_strdup_printf ( wmem_epan_scope ( ) , "%s Address Family" , name ) , alnumerize ( wmem_strdup_printf ( wmem_epan_scope ( ) , "diameter.%s.addr_family" , name ) ) , NULL , FT_UINT16 , ( field_display_e ) ( BASE_DEC | BASE_EXT_STRING ) , & diameter_avp_data_addrfamily_vals_ext , 0 ) ;
 reginfo ( & ( t -> hf_ipv4 ) , wmem_strdup_printf ( wmem_epan_scope ( ) , "%s Address" , name ) , alnumerize ( wmem_strdup_printf ( wmem_epan_scope ( ) , "diameter.%s.IPv4" , name ) ) , NULL , FT_IPv4 , BASE_NONE , NULL , 0 ) ;
 reginfo ( & ( t -> hf_ipv6 ) , wmem_strdup_printf ( wmem_epan_scope ( ) , "%s Address" , name ) , alnumerize ( wmem_strdup_printf ( wmem_epan_scope ( ) , "diameter.%s.IPv6" , name ) ) , NULL , FT_IPv6 , BASE_NONE , NULL , 0 ) ;
 reginfo ( & ( t -> hf_other ) , wmem_strdup_printf ( wmem_epan_scope ( ) , "%s Address" , name ) , alnumerize ( wmem_strdup_printf ( wmem_epan_scope ( ) , "diameter.%s.Bytes" , name ) ) , NULL , FT_BYTES , BASE_NONE , NULL , 0 ) ;
 g_ptr_array_add ( build_dict . ett , ettp ) ;
 return a ;
 }
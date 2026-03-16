static diam_avp_t * build_proto_avp ( const avp_type_t * type _U_ , guint32 code , diam_vnd_t * vendor , const char * name _U_ , const value_string * vs _U_ , void * data ) {
 diam_avp_t * a = ( diam_avp_t * ) g_malloc0 ( sizeof ( diam_avp_t ) ) ;
 proto_avp_t * t = ( proto_avp_t * ) g_malloc0 ( sizeof ( proto_avp_t ) ) ;
 gint * ettp = & ( a -> ett ) ;
 a -> code = code ;
 a -> vendor = vendor ;
 a -> dissector_v16 = proto_avp ;
 a -> dissector_rfc = proto_avp ;
 a -> ett = - 1 ;
 a -> hf_value = - 2 ;
 a -> type_data = t ;
 t -> name = ( char * ) data ;
 t -> handle = NULL ;
 t -> reassemble_mode = REASEMBLE_NEVER ;
 g_ptr_array_add ( build_dict . ett , ettp ) ;
 return a ;
 }
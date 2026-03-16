protocol_t * find_protocol_by_id ( const int proto_id ) {
 header_field_info * hfinfo ;
 if ( proto_id < 0 ) return NULL ;
 PROTO_REGISTRAR_GET_NTH ( proto_id , hfinfo ) ;
 DISSECTOR_ASSERT_FIELD_TYPE ( hfinfo , FT_PROTOCOL ) ;
 return ( protocol_t * ) hfinfo -> strings ;
 }
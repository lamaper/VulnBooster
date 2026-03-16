static const char * protobuf_get_wiretype_name ( guint8 wire_type ) {
 if ( wire_type <= 5 ) {
 return protobuf_wiretype_names [ wire_type ] ;
 }
 return protobuf_wiretype_name_unknown ;
 }
static gint protobuf_iter_next ( protobuf_desc_t * pb , protobuf_tag_t * tag ) {
 gint len ;
 if ( pb -> bytes_left <= 0 ) {
 return 0 ;
 }
 tag -> value = get_varint64 ( pb -> tvb , pb -> offset , pb -> bytes_left , & len ) ;
 tag -> field_number = tag -> value >> 3 ;
 tag -> wire_type = tag -> value & 0x7 ;
 protobuf_seek_forward ( pb , len ) ;
 return pb -> bytes_left ;
 }
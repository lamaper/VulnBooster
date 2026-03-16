static void protobuf_seek_forward ( protobuf_desc_t * pb , gint len ) {
 pb -> offset += len ;
 pb -> bytes_left -= len ;
 }
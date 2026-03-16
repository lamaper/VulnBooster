static void steamdiscover_dissect_body_unknown ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint offset , gint bytes_left ) {
 gint len ;
 protobuf_desc_t pb = {
 tvb , offset , bytes_left }
 ;
 protobuf_tag_t tag = {
 0 , 0 , 0 }
 ;
 while ( protobuf_iter_next ( & pb , & tag ) ) {
 len = protobuf_dissect_unknown_field ( & pb , & tag , pinfo , tree , NULL ) ;
 protobuf_seek_forward ( & pb , len ) ;
 }
 }
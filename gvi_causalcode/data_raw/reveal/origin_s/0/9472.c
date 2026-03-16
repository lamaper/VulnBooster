guint16 de_cell_id ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string , int string_len ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 curr_offset += be_cell_id_aux ( tvb , tree , pinfo , offset , len , add_string , string_len , 0x02 ) ;
 return ( curr_offset - offset ) ;
 }
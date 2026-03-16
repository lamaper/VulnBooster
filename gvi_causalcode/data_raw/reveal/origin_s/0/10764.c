static int dissect_type_bitmap ( proto_tree * rr_tree , tvbuff_t * tvb , int cur_offset , int rr_len ) {
 int mask , blockbase , blocksize ;
 int i , initial_offset , rr_type ;
 guint8 bits ;
 initial_offset = cur_offset ;
 while ( rr_len != 0 ) {
 blockbase = tvb_get_guint8 ( tvb , cur_offset ) ;
 blocksize = tvb_get_guint8 ( tvb , cur_offset + 1 ) ;
 cur_offset += 2 ;
 rr_len -= 2 ;
 rr_type = blockbase * 256 ;
 for ( ;
 blocksize ;
 blocksize -- ) {
 bits = tvb_get_guint8 ( tvb , cur_offset ) ;
 mask = 1 << 7 ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) {
 if ( bits & mask ) {
 proto_tree_add_uint_format ( rr_tree , hf_dns_rr_type , tvb , cur_offset , 1 , rr_type , "RR type in bit map: %s" , val_to_str_ext ( rr_type , & dns_types_description_vals_ext , "Unknown (%d)" ) ) ;
 }
 mask >>= 1 ;
 rr_type ++ ;
 }
 cur_offset += 1 ;
 rr_len -= 1 ;
 }
 }
 return ( initial_offset - cur_offset ) ;
 }
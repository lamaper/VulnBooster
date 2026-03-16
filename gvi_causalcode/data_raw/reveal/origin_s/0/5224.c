static int dissect_type_bitmap_nxt ( proto_tree * rr_tree , tvbuff_t * tvb , int cur_offset , int rr_len ) {
 int mask ;
 int i , initial_offset , rr_type ;
 guint8 bits ;
 initial_offset = cur_offset ;
 rr_type = 0 ;
 while ( rr_len != 0 ) {
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
 return ( initial_offset - cur_offset ) ;
 }
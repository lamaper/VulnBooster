int dissect_ber_length ( packet_info * pinfo _U_ , proto_tree * tree , tvbuff_t * tvb , int offset , guint32 * length , gboolean * ind ) {
 int old_offset = offset ;
 guint32 tmp_length ;
 gboolean tmp_ind ;
 offset = get_ber_length ( tvb , offset , & tmp_length , & tmp_ind ) ;
 if ( show_internal_ber_fields ) {
 if ( tmp_ind ) {
 proto_tree_add_uint_format_value ( tree , hf_ber_length , tvb , old_offset , 1 , tmp_length , "Indefinite length %d" , tmp_length ) ;
 }
 else {
 proto_tree_add_uint ( tree , hf_ber_length , tvb , old_offset , offset - old_offset , tmp_length ) ;
 }
 }
 if ( length ) * length = tmp_length ;
 if ( ind ) * ind = tmp_ind ;


 last_ind = tmp_ind ;
 return offset ;
 }
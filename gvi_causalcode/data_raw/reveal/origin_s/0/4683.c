int dissect_ber_identifier ( packet_info * pinfo _U_ , proto_tree * tree , tvbuff_t * tvb , int offset , gint8 * ber_class , gboolean * pc , gint32 * tag ) {
 int old_offset = offset ;
 gint8 tmp_class ;
 gboolean tmp_pc ;
 gint32 tmp_tag ;
 offset = get_ber_identifier ( tvb , offset , & tmp_class , & tmp_pc , & tmp_tag ) ;
 if ( show_internal_ber_fields ) {
 proto_tree_add_uint ( tree , hf_ber_id_class , tvb , old_offset , 1 , tmp_class << 6 ) ;
 proto_tree_add_boolean ( tree , hf_ber_id_pc , tvb , old_offset , 1 , ( tmp_pc ) ? 0x20 : 0x00 ) ;
 if ( tmp_tag > 0x1F ) {
 if ( tmp_class == BER_CLASS_UNI ) {
 proto_tree_add_uint ( tree , hf_ber_id_uni_tag_ext , tvb , old_offset + 1 , offset - ( old_offset + 1 ) , tmp_tag ) ;
 }
 else {
 proto_tree_add_uint ( tree , hf_ber_id_tag_ext , tvb , old_offset + 1 , offset - ( old_offset + 1 ) , tmp_tag ) ;
 }
 }
 else {
 if ( tmp_class == BER_CLASS_UNI ) {
 proto_tree_add_uint ( tree , hf_ber_id_uni_tag , tvb , old_offset , 1 , tmp_tag ) ;
 }
 else {
 proto_tree_add_uint ( tree , hf_ber_id_tag , tvb , old_offset , 1 , tmp_tag ) ;
 }
 }
 }
 if ( ber_class ) * ber_class = tmp_class ;
 if ( pc ) * pc = tmp_pc ;
 if ( tag ) * tag = tmp_tag ;
 return offset ;
 }
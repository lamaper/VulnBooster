static int parse_CRowVariantArrayInfo ( tvbuff_t * tvb , int offset , proto_tree * tree , gboolean is_64bit , struct CRowVariant * variant ) {
 if ( is_64bit ) {
 variant -> content . array_vector . i64 . count = tvb_get_letoh64 ( tvb , offset ) ;
 proto_tree_add_uint64 ( tree , hf_mswsp_crowvariantinfo_count64 , tvb , offset , 8 , variant -> content . array_vector . i64 . count ) ;
 offset += 8 ;
 variant -> content . array_vector . i64 . array_address = tvb_get_letoh64 ( tvb , offset ) ;
 proto_tree_add_uint64 ( tree , hf_mswsp_arrayvector_address64 , tvb , offset , 8 , variant -> content . array_vector . i64 . array_address ) ;
 offset += 8 ;
 }
 else {
 variant -> content . array_vector . i32 . count = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_crowvariantinfo_count32 , tvb , offset , 4 , variant -> content . array_vector . i32 . count ) ;
 offset += 4 ;
 variant -> content . array_vector . i32 . array_address = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_arrayvector_address32 , tvb , offset , 4 , variant -> content . array_vector . i32 . array_address ) ;
 offset += 4 ;
 }
 return offset ;
 }
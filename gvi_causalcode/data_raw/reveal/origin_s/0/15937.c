int dissect_ber_bitstring32 ( gboolean implicit_tag , asn1_ctx_t * actx , proto_tree * parent_tree , tvbuff_t * tvb , int offset , int * * bit_fields , gint hf_id , gint ett_id , tvbuff_t * * out_tvb ) {
 tvbuff_t * tmp_tvb = NULL ;
 proto_tree * tree ;
 guint32 val ;
 int * * bf ;
 header_field_info * hfi ;
 const char * sep ;
 gboolean term ;
 unsigned int i , tvb_len ;
 offset = dissect_ber_bitstring ( implicit_tag , actx , parent_tree , tvb , offset , NULL , hf_id , ett_id , & tmp_tvb ) ;
 tree = proto_item_get_subtree ( actx -> created_item ) ;
 if ( bit_fields && tree && tmp_tvb ) {
 val = 0 ;
 tvb_len = tvb_reported_length ( tmp_tvb ) ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 val <<= 8 ;
 if ( i < tvb_len ) {
 val |= tvb_get_guint8 ( tmp_tvb , i ) ;
 }
 }
 bf = bit_fields ;
 sep = " (" ;
 term = FALSE ;
 while ( * bf ) {
 if ( * * bf >= 0 ) {
 proto_tree_add_boolean ( tree , * * bf , tmp_tvb , 0 , tvb_len , val ) ;
 hfi = proto_registrar_get_nth ( * * bf ) ;
 if ( val & hfi -> bitmask ) {
 proto_item_append_text ( actx -> created_item , "%s%s" , sep , hfi -> name ) ;
 sep = ", " ;
 term = TRUE ;
 }
 }
 bf ++ ;
 }
 if ( term ) proto_item_append_text ( actx -> created_item , ")" ) ;
 }
 if ( out_tvb ) * out_tvb = tmp_tvb ;
 return offset ;
 }
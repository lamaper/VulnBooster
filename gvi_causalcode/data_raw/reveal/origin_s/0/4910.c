static void ber_check_value64 ( gint64 value , gint64 min_len , gint64 max_len , asn1_ctx_t * actx , proto_item * item ) {
 if ( ( min_len != - 1 ) && ( value < min_len ) ) {
 expert_add_info_format ( actx -> pinfo , item , & ei_ber_size_constraint_value , "Size constraint: value too small: %" G_GINT64_MODIFIER "d (%" G_GINT64_MODIFIER "d .. %" G_GINT64_MODIFIER "d)" , value , min_len , max_len ) ;
 }
 else if ( ( max_len != - 1 ) && ( value > max_len ) ) {
 expert_add_info_format ( actx -> pinfo , item , & ei_ber_size_constraint_value , "Size constraint: value too big: %" G_GINT64_MODIFIER "d (%" G_GINT64_MODIFIER "d .. %" G_GINT64_MODIFIER "d)" , value , min_len , max_len ) ;
 }
 }
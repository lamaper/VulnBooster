static void ber_check_value ( guint32 value , gint32 min_len , gint32 max_len , asn1_ctx_t * actx , proto_item * item ) {
 if ( ( min_len != - 1 ) && ( value < ( guint32 ) min_len ) ) {
 expert_add_info_format ( actx -> pinfo , item , & ei_ber_size_constraint_value , "Size constraint: value too small: %d (%d .. %d)" , value , min_len , max_len ) ;
 }
 else if ( ( max_len != - 1 ) && ( value > ( guint32 ) max_len ) ) {
 expert_add_info_format ( actx -> pinfo , item , & ei_ber_size_constraint_value , "Size constraint: value too big: %d (%d .. %d)" , value , min_len , max_len ) ;
 }
 }
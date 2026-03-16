static void ber_check_items ( int cnt , gint32 min_len , gint32 max_len , asn1_ctx_t * actx , proto_item * item ) {
 if ( ( min_len != - 1 ) && ( cnt < min_len ) ) {
 expert_add_info_format ( actx -> pinfo , item , & ei_ber_size_constraint_items , "Size constraint: too few items: %d (%d .. %d)" , cnt , min_len , max_len ) ;
 }
 else if ( ( max_len != - 1 ) && ( cnt > max_len ) ) {
 expert_add_info_format ( actx -> pinfo , item , & ei_ber_size_constraint_items , "Size constraint: too many items: %d (%d .. %d)" , cnt , min_len , max_len ) ;
 }
 }
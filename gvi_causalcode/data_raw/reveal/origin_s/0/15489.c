static void ber_check_length ( guint32 length , gint32 min_len , gint32 max_len , asn1_ctx_t * actx , proto_item * item , gboolean bit ) {
 if ( ( min_len != - 1 ) && ( length < ( guint32 ) min_len ) ) {
 expert_add_info_format ( actx -> pinfo , item , & ei_ber_size_constraint_string , "Size constraint: %sstring too short: %d (%d .. %d)" , bit ? "bit " : "" , length , min_len , max_len ) ;
 }
 else if ( ( max_len != - 1 ) && ( length > ( guint32 ) max_len ) ) {
 expert_add_info_format ( actx -> pinfo , item , & ei_ber_size_constraint_string , "Size constraint: %sstring too long: %d (%d .. %d)" , bit ? "bit " : "" , length , min_len , max_len ) ;
 }
 }
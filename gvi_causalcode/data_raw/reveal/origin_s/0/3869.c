void proto_register_fields_manual ( const int parent , header_field_info * * hfi , const int num_records ) {
 int i ;
 protocol_t * proto ;
 proto = find_protocol_by_id ( parent ) ;
 for ( i = 0 ;
 i < num_records ;
 i ++ ) {
 if ( hfi [ i ] -> id != - 1 ) {
 fprintf ( stderr , "Duplicate field detected in call to proto_register_fields: %s is already registered\n" , hfi [ i ] -> abbrev ) ;
 return ;
 }
 proto_register_field_common ( proto , hfi [ i ] , parent ) ;
 }
 }
void proto_register_field_array ( const int parent , hf_register_info * hf , const int num_records ) {
 hf_register_info * ptr = hf ;
 protocol_t * proto ;
 int i ;
 proto = find_protocol_by_id ( parent ) ;
 for ( i = 0 ;
 i < num_records ;
 i ++ , ptr ++ ) {
 if ( * ptr -> p_id != - 1 && * ptr -> p_id != 0 ) {
 fprintf ( stderr , "Duplicate field detected in call to proto_register_field_array: %s is already registered\n" , ptr -> hfinfo . abbrev ) ;
 return ;
 }
 * ptr -> p_id = proto_register_field_common ( proto , & ptr -> hfinfo , parent ) ;
 }
 }
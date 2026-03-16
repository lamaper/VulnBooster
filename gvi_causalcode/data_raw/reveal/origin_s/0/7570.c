static int btatt_call_dissector_by_dissector_name_with_data ( const char * dissector_name , tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 dissector_handle_t handle ;
 handle = find_dissector ( dissector_name ) ;
 if ( handle != NULL ) return call_dissector_with_data ( handle , tvb , pinfo , tree , data ) ;
 else return call_data_dissector ( tvb , pinfo , tree ) ;
 }
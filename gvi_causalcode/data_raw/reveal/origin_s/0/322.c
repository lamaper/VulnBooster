static int dissect_field ( tvbuff_t * tvb , int offset , proto_tree * tree , lbmpdm_definition_field_t * field , gboolean string_field_names , int encoding ) {
 proto_item * field_item = NULL ;
 proto_tree * field_tree = NULL ;
 proto_item * ti = NULL ;
 int ofs = offset ;
 guint32 element_count = 0 ;
 guint32 idx ;
 int len_dissected = 0 ;
 field_item = proto_tree_add_item ( tree , hf_lbmpdm_field , tvb , offset , field -> len , ENC_NA ) ;
 field_tree = proto_item_add_subtree ( field_item , ett_lbmpdm_field ) ;
 ti = proto_tree_add_uint ( field_tree , hf_lbmpdm_field_id , tvb , 0 , 0 , field -> id ) ;
 PROTO_ITEM_SET_GENERATED ( ti ) ;
 if ( string_field_names ) {
 ti = proto_tree_add_string ( field_tree , hf_lbmpdm_field_string_name , tvb , 0 , 0 , field -> field_string_name ) ;
 }
 else {
 ti = proto_tree_add_uint ( field_tree , hf_lbmpdm_field_int_name , tvb , 0 , 0 , field -> field_int_name ) ;
 }
 PROTO_ITEM_SET_GENERATED ( ti ) ;
 ti = proto_tree_add_uint ( field_tree , hf_lbmpdm_field_type , tvb , 0 , 0 , field -> field_type ) ;
 PROTO_ITEM_SET_GENERATED ( ti ) ;
 if ( field -> num_array_elem == 0 ) {
 element_count = 1 ;
 }
 else {
 element_count = field -> num_array_elem ;
 if ( field -> fixed == PDM_DEFN_VARIABLE_LENGTH_FIELD ) {
 proto_tree_add_item ( field_tree , hf_lbmpdm_field_total_length , tvb , ofs , 4 , encoding ) ;
 len_dissected += 4 ;
 ofs += 4 ;
 }
 }
 for ( idx = 0 ;
 idx < element_count ;
 ++ idx ) {
 guint32 field_len = field -> len / element_count ;
 guint32 value_len = field_len ;
 int value_offset = ofs ;
 if ( field -> fixed == PDM_DEFN_VARIABLE_LENGTH_FIELD ) {
 proto_tree_add_item ( field_tree , hf_lbmpdm_field_length , tvb , ofs , 4 , encoding ) ;
 value_len = lbmpdm_fetch_uint32_encoded ( tvb , ofs , encoding ) ;
 field_len = value_len + 4 ;
 value_offset += 4 ;
 }
 else if ( field -> fixed_string_len > 0 ) {
 value_len = field -> fixed_string_len ;
 }
 dissect_field_value ( tvb , value_offset , field_tree , field -> base_type , value_len , encoding ) ;
 ofs += ( int ) field_len ;
 len_dissected += ( int ) field_len ;
 }
 return ( len_dissected ) ;
 }
static gint parse_arg ( tvbuff_t * tvb , packet_info * pinfo , proto_item * header_item , guint encoding , gint offset , proto_tree * field_tree , gboolean is_reply_to , guint8 type_id , guint8 field_code , guint8 * * signature , guint8 * signature_length , gint field_starting_offset ) {
 gint length ;
 gint padding_start ;
 const gchar * header_type_name = NULL ;
 switch ( type_id ) {
 case ARG_INVALID : header_type_name = "invalid" ;
 offset = round_to_8byte ( offset + 1 , field_starting_offset ) ;
 break ;
 case ARG_ARRAY : {
 static gchar bad_array_format [ ] = "BAD DATA: Array length (in bytes) is %d. Remaining packet length is %d." ;
 proto_item * item ;
 proto_tree * tree ;
 guint8 * sig_saved ;
 gint starting_offset ;
 gint number_of_items = 0 ;
 guint8 remaining_sig_length = * signature_length ;
 gint packet_length = ( gint ) tvb_reported_length ( tvb ) ;
 header_type_name = "array" ;
 if ( * signature == NULL || * signature_length < 1 ) {
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "BAD DATA: A %s argument needs a signature." , header_type_name ) ;
 return tvb_reported_length ( tvb ) ;
 }
 sig_saved = ( * signature ) + 1 ;
 padding_start = offset ;
 offset = round_to_4byte ( offset , field_starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 length = ( gint ) get_uint32 ( tvb , offset , encoding ) ;
 padding_start = offset + 4 ;
 starting_offset = pad_according_to_type ( padding_start , field_starting_offset , packet_length , * sig_saved ) ;
 if ( length < 0 || length > MAX_ARRAY_LEN || starting_offset + length > packet_length ) {
 col_add_fstr ( pinfo -> cinfo , COL_INFO , bad_array_format , length , tvb_reported_length_remaining ( tvb , starting_offset ) ) ;
 return tvb_reported_length ( tvb ) ;
 }
 item = proto_tree_add_item ( field_tree , hf_alljoyn_mess_body_array , tvb , offset , ( starting_offset - offset ) + length , encoding ) ;
 tree = proto_item_add_subtree ( item , ett_alljoyn_mess_body_parameters ) ;
 offset = starting_offset ;
 add_padding_item ( padding_start , offset , tvb , tree ) ;
 if ( 0 == length ) {
 advance_to_end_of_signature ( signature , & remaining_sig_length ) ;
 }
 else {
 while ( ( offset - starting_offset ) < length ) {
 guint8 * sig_pointer ;
 number_of_items ++ ;
 sig_pointer = sig_saved ;
 remaining_sig_length = * signature_length - 1 ;
 offset = parse_arg ( tvb , pinfo , header_item , encoding , offset , tree , is_reply_to , * sig_pointer , field_code , & sig_pointer , & remaining_sig_length , field_starting_offset ) ;
 * signature = sig_pointer ;
 }
 }
 * signature_length = remaining_sig_length ;
 if ( item ) {
 proto_item_append_text ( item , " of %d '%c' elements" , number_of_items , * sig_saved ) ;
 }
 }
 break ;
 case ARG_BOOLEAN : header_type_name = "boolean" ;
 padding_start = offset ;
 offset = round_to_4byte ( offset , field_starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 proto_tree_add_item ( field_tree , hf_alljoyn_boolean , tvb , offset , 4 , encoding ) ;
 offset += 4 ;
 break ;
 case ARG_DOUBLE : header_type_name = "IEEE 754 double" ;
 padding_start = offset ;
 offset = round_to_8byte ( offset , field_starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 proto_tree_add_item ( field_tree , hf_alljoyn_double , tvb , offset , 8 , encoding ) ;
 offset += 8 ;
 break ;
 case ARG_SIGNATURE : header_type_name = "signature" ;
 * signature_length = tvb_get_guint8 ( tvb , offset ) ;
 if ( * signature_length + 2 > tvb_reported_length_remaining ( tvb , offset ) ) {
 gint bytes_left = tvb_reported_length_remaining ( tvb , offset ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "BAD DATA: Signature length is %d. Only %d bytes left in packet." , ( gint ) ( * signature_length ) , bytes_left ) ;
 return tvb_reported_length ( tvb ) ;
 }
 length = * signature_length + 1 ;
 proto_tree_add_item ( field_tree , hf_alljoyn_mess_body_signature_length , tvb , offset , 1 , encoding ) ;
 offset += 1 ;
 proto_tree_add_item ( field_tree , hf_alljoyn_mess_body_signature , tvb , offset , length , ENC_ASCII | ENC_NA ) ;
 * signature = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset , length , ENC_ASCII ) ;
 if ( HDR_SIGNATURE == field_code ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " (%s)" , * signature ) ;
 }
 offset += length ;
 break ;
 case ARG_HANDLE : header_type_name = "socket handle" ;
 padding_start = offset ;
 offset = round_to_4byte ( offset , field_starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 proto_tree_add_item ( field_tree , hf_alljoyn_handle , tvb , offset , 4 , encoding ) ;
 offset += 4 ;
 break ;
 case ARG_INT32 : header_type_name = "int32" ;
 padding_start = offset ;
 offset = round_to_4byte ( offset , field_starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 proto_tree_add_item ( field_tree , hf_alljoyn_int32 , tvb , offset , 4 , encoding ) ;
 offset += 4 ;
 break ;
 case ARG_INT16 : header_type_name = "int16" ;
 padding_start = offset ;
 offset = round_to_2byte ( offset , field_starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 proto_tree_add_item ( field_tree , hf_alljoyn_int16 , tvb , offset , 2 , encoding ) ;
 offset += 2 ;
 break ;
 case ARG_OBJ_PATH : header_type_name = "object path" ;
 length = get_uint32 ( tvb , offset , encoding ) + 1 ;
 if ( length < 0 || length > MAX_ARRAY_LEN || length + 4 > tvb_reported_length_remaining ( tvb , offset ) ) {
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "BAD DATA: Object path length is %d. Only %d bytes left in packet." , length , tvb_reported_length_remaining ( tvb , offset + 4 ) ) ;
 return tvb_reported_length ( tvb ) ;
 }
 proto_tree_add_item ( field_tree , hf_alljoyn_uint32 , tvb , offset , 4 , encoding ) ;
 offset += 4 ;
 proto_tree_add_item ( field_tree , hf_alljoyn_string_data , tvb , offset , length , ENC_ASCII | ENC_NA ) ;
 offset += length ;
 break ;
 case ARG_UINT16 : header_type_name = "uint16" ;
 padding_start = offset ;
 offset = round_to_2byte ( offset , field_starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 proto_tree_add_item ( field_tree , hf_alljoyn_uint16 , tvb , offset , 2 , encoding ) ;
 offset += 2 ;
 break ;
 case ARG_STRING : header_type_name = "string" ;
 padding_start = offset ;
 offset = round_to_4byte ( offset , field_starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 proto_tree_add_item ( field_tree , hf_alljoyn_string_size_32bit , tvb , offset , 4 , encoding ) ;
 length = ( gint ) get_uint32 ( tvb , offset , encoding ) ;
 if ( length < 0 || length > tvb_reported_length_remaining ( tvb , offset ) ) {
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "BAD DATA: String length is %d. Remaining packet length is %d." , length , ( gint ) tvb_reported_length_remaining ( tvb , offset ) ) ;
 return tvb_reported_length ( tvb ) ;
 }
 length += 1 ;
 offset += 4 ;
 proto_tree_add_item ( field_tree , hf_alljoyn_string_data , tvb , offset , length , ENC_UTF_8 | ENC_NA ) ;
 if ( HDR_MEMBER == field_code ) {
 guint8 * member_name ;
 member_name = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset , length , ENC_UTF_8 ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " %s" , member_name ) ;
 }
 offset += length ;
 break ;
 case ARG_UINT64 : header_type_name = "uint64" ;
 padding_start = offset ;
 offset = round_to_8byte ( offset , field_starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 proto_tree_add_item ( field_tree , hf_alljoyn_uint64 , tvb , offset , 8 , encoding ) ;
 offset += 8 ;
 break ;
 case ARG_UINT32 : header_type_name = "uint32" ;
 padding_start = offset ;
 offset = round_to_4byte ( offset , field_starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 if ( is_reply_to ) {
 static const gchar format [ ] = " Replies to: %09u" ;
 guint32 replies_to ;
 replies_to = get_uint32 ( tvb , offset , encoding ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , format , replies_to ) ;
 if ( header_item ) {
 proto_item * item ;
 item = proto_tree_add_item ( field_tree , hf_alljoyn_uint32 , tvb , offset , 4 , encoding ) ;
 proto_item_set_text ( item , format + 1 , replies_to ) ;
 }
 }
 else {
 proto_tree_add_item ( field_tree , hf_alljoyn_uint32 , tvb , offset , 4 , encoding ) ;
 }
 offset += 4 ;
 break ;
 case ARG_VARIANT : {
 proto_item * item ;
 proto_tree * tree ;
 guint8 * sig_saved ;
 guint8 * sig_pointer ;
 guint8 variant_sig_length ;
 header_type_name = "variant" ;
 variant_sig_length = tvb_get_guint8 ( tvb , offset ) ;
 length = variant_sig_length ;
 if ( length > tvb_reported_length_remaining ( tvb , offset ) ) {
 gint bytes_left = tvb_reported_length_remaining ( tvb , offset ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "BAD DATA: Variant signature length is %d. Only %d bytes left in packet." , length , bytes_left ) ;
 offset = tvb_reported_length ( tvb ) ;
 }
 length += 1 ;
 item = proto_tree_add_item ( field_tree , hf_alljoyn_mess_body_variant , tvb , offset , 4 , encoding ) ;
 tree = proto_item_add_subtree ( item , ett_alljoyn_mess_body_parameters ) ;
 proto_tree_add_item ( tree , hf_alljoyn_mess_body_signature_length , tvb , offset , 1 , encoding ) ;
 offset += 1 ;
 tree = proto_item_add_subtree ( item , ett_alljoyn_mess_body_parameters ) ;
 proto_tree_add_item ( tree , hf_alljoyn_mess_body_signature , tvb , offset , length , ENC_ASCII | ENC_NA ) ;
 sig_saved = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset , length , ENC_ASCII ) ;
 offset += length ;
 sig_pointer = sig_saved ;
 while ( ( ( sig_pointer - sig_saved ) < ( length - 1 ) ) && ( tvb_reported_length_remaining ( tvb , offset ) > 0 ) ) {
 proto_item_append_text ( item , "%c" , * sig_pointer ) ;
 offset = parse_arg ( tvb , pinfo , header_item , encoding , offset , tree , is_reply_to , * sig_pointer , field_code , & sig_pointer , & variant_sig_length , field_starting_offset ) ;
 }
 proto_item_append_text ( item , "'" ) ;
 proto_item_set_end ( item , tvb , offset ) ;
 }
 break ;
 case ARG_INT64 : header_type_name = "int64" ;
 padding_start = offset ;
 offset = round_to_8byte ( offset , field_starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 proto_tree_add_item ( field_tree , hf_alljoyn_int64 , tvb , offset , 8 , encoding ) ;
 offset += 8 ;
 break ;
 case ARG_BYTE : header_type_name = "byte" ;
 proto_tree_add_item ( field_tree , hf_alljoyn_uint8 , tvb , offset , 1 , encoding ) ;
 offset += 1 ;
 break ;
 case ARG_DICT_ENTRY : case ARG_STRUCT : {
 proto_item * item ;
 proto_tree * tree ;
 int hf ;
 guint8 type_stop ;
 if ( type_id == ARG_STRUCT ) {
 header_type_name = "structure" ;
 hf = hf_alljoyn_mess_body_structure ;
 type_stop = ')' ;
 }
 else {
 header_type_name = "dictionary" ;
 hf = hf_alljoyn_mess_body_dictionary_entry ;
 type_stop = '}
' ;
 }
 if ( * signature == NULL || * signature_length < 1 ) {
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "BAD DATA: A %s argument needs a signature." , header_type_name ) ;
 return tvb_reported_length ( tvb ) ;
 }
 item = proto_tree_add_item ( field_tree , hf , tvb , offset , 4 , encoding ) ;
 append_struct_signature ( item , * signature , * signature_length , type_stop ) ;
 tree = proto_item_add_subtree ( item , ett_alljoyn_mess_body_parameters ) ;
 padding_start = offset ;
 offset = pad_according_to_type ( offset , field_starting_offset , tvb_reported_length ( tvb ) , type_id ) ;
 add_padding_item ( padding_start , offset , tvb , tree ) ;
 ( * signature ) ++ ;
 ( * signature_length ) -- ;
 while ( * signature && * * signature && * * signature != type_stop && tvb_reported_length_remaining ( tvb , offset ) > 0 ) {
 offset = parse_arg ( tvb , pinfo , header_item , encoding , offset , tree , is_reply_to , * * signature , field_code , signature , signature_length , field_starting_offset ) ;
 }
 proto_item_set_end ( item , tvb , offset ) ;
 }
 break ;
 default : header_type_name = "unexpected" ;
 offset = tvb_reported_length ( tvb ) ;
 break ;
 }
 if ( * signature && ARG_ARRAY != type_id && HDR_INVALID == field_code ) {
 ( * signature ) ++ ;
 ( * signature_length ) -- ;
 }
 if ( NULL != header_item && NULL != header_type_name ) {
 proto_item_append_text ( header_item , "%s" , header_type_name ) ;
 }
 if ( offset > ( gint ) tvb_reported_length ( tvb ) ) {
 offset = ( gint ) tvb_reported_length ( tvb ) ;
 }
 return offset ;
 }
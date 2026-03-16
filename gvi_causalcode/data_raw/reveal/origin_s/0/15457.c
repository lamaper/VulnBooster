static gint dissect_amf3_value_type ( tvbuff_t * tvb , gint offset , proto_tree * tree , proto_item * parent_ti ) {
 guint8 iObjType ;
 proto_item * ti ;
 proto_tree * val_tree ;
 gint iValueOffset = offset ;
 guint iValueLength ;
 guint32 iIntegerValue ;
 double iDoubleValue ;
 guint iStringLength ;
 gchar * iStringValue ;
 guint iArrayLength ;
 proto_item * subval_ti ;
 proto_tree * subval_tree ;
 guint i ;
 gboolean iTypeIsDynamic ;
 guint iTraitCount ;
 proto_item * traits_ti ;
 proto_tree * traits_tree ;
 proto_tree * name_tree ;
 proto_tree * member_tree ;
 guint8 * iByteArrayValue ;
 iObjType = tvb_get_guint8 ( tvb , offset ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , " %s" , val_to_str_const ( iObjType , amf3_type_vals , "Unknown" ) ) ;
 switch ( iObjType ) {
 case AMF3_ARRAY : ti = proto_tree_add_item ( tree , hf_amf_array , tvb , offset , - 1 , ENC_NA ) ;
 val_tree = proto_item_add_subtree ( ti , ett_amf_value ) ;
 break ;
 case AMF3_OBJECT : ti = proto_tree_add_item ( tree , hf_amf_object , tvb , offset , - 1 , ENC_NA ) ;
 val_tree = proto_item_add_subtree ( ti , ett_amf_value ) ;
 break ;
 default : val_tree = proto_tree_add_subtree ( tree , tvb , offset , - 1 , ett_amf_value , & ti , val_to_str_const ( iObjType , amf3_type_vals , "Unknown" ) ) ;
 break ;
 }
 proto_tree_add_uint ( val_tree , hf_amf_amf3_type , tvb , iValueOffset , 1 , iObjType ) ;
 iValueOffset ++ ;
 switch ( iObjType ) {
 case AMF3_UNDEFINED : case AMF3_NULL : break ;
 case AMF3_FALSE : proto_tree_add_boolean ( val_tree , hf_amf_boolean , tvb , 0 , 0 , FALSE ) ;
 proto_item_append_text ( ti , " false" ) ;
 break ;
 case AMF3_TRUE : proto_tree_add_boolean ( val_tree , hf_amf_boolean , tvb , 0 , 0 , TRUE ) ;
 proto_item_append_text ( ti , " true" ) ;
 break ;
 case AMF3_INTEGER : iIntegerValue = amf_get_u29 ( tvb , iValueOffset , & iValueLength ) ;
 proto_tree_add_uint ( val_tree , hf_amf_integer , tvb , iValueOffset , iValueLength , iIntegerValue ) ;
 proto_item_append_text ( ti , " %u" , iIntegerValue ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , " %u" , iIntegerValue ) ;
 iValueOffset += iValueLength ;
 break ;
 case AMF3_DOUBLE : iDoubleValue = tvb_get_ntohieee_double ( tvb , iValueOffset ) ;
 proto_tree_add_double ( val_tree , hf_amf_number , tvb , iValueOffset , 8 , iDoubleValue ) ;
 iValueOffset += 8 ;
 proto_item_append_text ( ti , " %." G_STRINGIFY ( DBL_DIG ) "g" , iDoubleValue ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , " %." G_STRINGIFY ( DBL_DIG ) "g" , iDoubleValue ) ;
 break ;
 case AMF3_STRING : iIntegerValue = amf_get_u29 ( tvb , iValueOffset , & iValueLength ) ;
 if ( iIntegerValue & 0x00000001 ) {
 iStringLength = iIntegerValue >> 1 ;
 proto_tree_add_uint ( val_tree , hf_amf_stringlength , tvb , iValueOffset , iValueLength , iStringLength ) ;
 iValueOffset += iValueLength ;
 iStringValue = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , iValueOffset , iStringLength , ENC_UTF_8 | ENC_NA ) ;
 if ( iStringLength != 0 ) proto_tree_add_string ( val_tree , hf_amf_string , tvb , iValueOffset , iStringLength , iStringValue ) ;
 iValueOffset += iStringLength ;
 proto_item_append_text ( ti , " '%s'" , iStringValue ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , " '%s'" , iStringValue ) ;
 }
 else {
 proto_tree_add_uint ( val_tree , hf_amf_string_reference , tvb , iValueOffset , iValueLength , iIntegerValue >> 1 ) ;
 iValueOffset += iValueLength ;
 proto_item_append_text ( ti , " reference %u" , iIntegerValue >> 1 ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , " reference %u" , iIntegerValue >> 1 ) ;
 }
 break ;
 case AMF3_DATE : iIntegerValue = amf_get_u29 ( tvb , iValueOffset , & iValueLength ) ;
 if ( iIntegerValue & 0x00000001 ) {
 nstime_t t ;
 iValueOffset += iValueLength ;
 iDoubleValue = tvb_get_ntohieee_double ( tvb , iValueOffset ) ;
 t . secs = ( time_t ) ( iDoubleValue / 1000 ) ;
 t . nsecs = ( int ) ( ( iDoubleValue - 1000 * ( double ) t . secs ) * 1000000 ) ;
 proto_tree_add_time ( val_tree , hf_amf_date , tvb , iValueOffset , 8 , & t ) ;
 iValueOffset += 8 ;
 proto_item_append_text ( ti , "%s" , abs_time_to_str ( wmem_packet_scope ( ) , & t , ABSOLUTE_TIME_LOCAL , TRUE ) ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , "%s" , abs_time_to_str ( wmem_packet_scope ( ) , & t , ABSOLUTE_TIME_LOCAL , TRUE ) ) ;
 }
 else {
 proto_tree_add_uint ( val_tree , hf_amf_object_reference , tvb , iValueOffset , iValueLength , iIntegerValue >> 1 ) ;
 iValueOffset += iValueLength ;
 proto_item_append_text ( ti , " object reference %u" , iIntegerValue >> 1 ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , " object reference %u" , iIntegerValue >> 1 ) ;
 }
 break ;
 case AMF3_ARRAY : iIntegerValue = amf_get_u29 ( tvb , iValueOffset , & iValueLength ) ;
 if ( iIntegerValue & 0x00000001 ) {
 iArrayLength = iIntegerValue >> 1 ;
 proto_tree_add_uint ( val_tree , hf_amf_arraydenselength , tvb , iValueOffset , iValueLength , iArrayLength ) ;
 iValueOffset += iValueLength ;
 for ( ;
 ;
 ) {
 iIntegerValue = amf_get_u29 ( tvb , iValueOffset , & iValueLength ) ;
 if ( iIntegerValue & 0x00000001 ) {
 iStringLength = iIntegerValue >> 1 ;
 if ( iStringLength == 0 ) {
 proto_tree_add_item ( val_tree , hf_amf_end_of_associative_part , tvb , iValueOffset , iValueLength , ENC_NA ) ;
 iValueOffset += iValueLength ;
 break ;
 }
 iStringValue = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , iValueOffset + iValueLength , iStringLength , ENC_UTF_8 | ENC_NA ) ;
 subval_tree = proto_tree_add_subtree ( val_tree , tvb , iValueOffset , iStringLength , ett_amf_array_element , & subval_ti , iStringValue ) ;
 proto_tree_add_uint ( subval_tree , hf_amf_stringlength , tvb , iValueOffset , iValueLength , iStringLength ) ;
 iValueOffset += iValueLength ;
 proto_tree_add_string ( subval_tree , hf_amf_string , tvb , iValueOffset , iStringLength , iStringValue ) ;
 }
 else {
 subval_tree = proto_tree_add_subtree_format ( val_tree , tvb , iValueOffset , iValueLength , ett_amf_array_element , & subval_ti , "Reference %u:" , iIntegerValue >> 1 ) ;
 proto_tree_add_uint ( subval_tree , hf_amf_string_reference , tvb , iValueOffset , iValueLength , iIntegerValue >> 1 ) ;
 }
 iObjType = tvb_get_guint8 ( tvb , offset ) ;
 proto_item_append_text ( subval_ti , "%s" , val_to_str_const ( iObjType , amf3_type_vals , "Unknown" ) ) ;
 iValueOffset = dissect_amf3_value_type ( tvb , iValueOffset , subval_tree , subval_ti ) ;
 }
 for ( i = 0 ;
 i < iArrayLength ;
 i ++ ) iValueOffset = dissect_amf3_value_type ( tvb , iValueOffset , val_tree , NULL ) ;
 proto_item_set_end ( ti , tvb , iValueOffset ) ;
 }
 else {
 proto_tree_add_uint ( val_tree , hf_amf_object_reference , tvb , iValueOffset , iValueLength , iIntegerValue >> 1 ) ;
 proto_item_append_text ( ti , " reference %u" , iIntegerValue >> 1 ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , " reference %u" , iIntegerValue >> 1 ) ;
 }
 break ;
 case AMF3_OBJECT : iIntegerValue = amf_get_u29 ( tvb , iValueOffset , & iValueLength ) ;
 if ( iIntegerValue & 0x00000001 ) {
 if ( iIntegerValue & 0x00000002 ) {
 if ( iIntegerValue & 0x00000004 ) {
 iValueOffset += iValueLength ;
 }
 else {
 iTypeIsDynamic = ( iIntegerValue & 0x00000008 ) ? TRUE : FALSE ;
 iTraitCount = iIntegerValue >> 4 ;
 proto_tree_add_uint ( val_tree , hf_amf_traitcount , tvb , iValueOffset , iValueLength , iTraitCount ) ;
 iValueOffset += iValueLength ;
 iIntegerValue = amf_get_u29 ( tvb , iValueOffset , & iValueLength ) ;
 if ( iIntegerValue & 0x00000001 ) {
 iStringLength = iIntegerValue >> 1 ;
 iStringValue = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , iValueOffset + iValueLength , iStringLength , ENC_UTF_8 | ENC_NA ) ;
 traits_tree = proto_tree_add_subtree_format ( val_tree , tvb , iValueOffset , - 1 , ett_amf_traits , & traits_ti , "Traits for class %s (%u member names)" , iStringValue , iTraitCount ) ;
 name_tree = proto_tree_add_subtree_format ( traits_tree , tvb , iValueOffset , iValueLength + iStringLength , ett_amf_string , NULL , "Class name: %s" , iStringValue ) ;
 proto_tree_add_uint ( name_tree , hf_amf_classnamelength , tvb , iValueOffset , iValueLength , iStringLength ) ;
 iValueOffset += iValueLength ;
 proto_tree_add_string ( name_tree , hf_amf_classname , tvb , iValueOffset , iStringLength , iStringValue ) ;
 iValueOffset += iStringLength ;
 }
 else {
 traits_tree = proto_tree_add_subtree_format ( val_tree , tvb , iValueOffset , iValueLength , ett_amf_traits , & traits_ti , "Traits for class (reference %u for name)" , iIntegerValue >> 1 ) ;
 proto_tree_add_uint ( traits_tree , hf_amf_string_reference , tvb , iValueOffset , iValueLength , iIntegerValue >> 1 ) ;
 iValueOffset += iValueLength ;
 }
 for ( i = 0 ;
 i < iTraitCount ;
 i ++ ) {
 iIntegerValue = amf_get_u29 ( tvb , iValueOffset , & iValueLength ) ;
 if ( iIntegerValue & 0x00000001 ) {
 iStringLength = iIntegerValue >> 1 ;
 iStringValue = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , iValueOffset + iValueLength , iStringLength , ENC_UTF_8 | ENC_NA ) ;
 member_tree = proto_tree_add_subtree_format ( traits_tree , tvb , iValueOffset , iValueLength + iStringLength , ett_amf_trait_member , NULL , "Member '%s'" , iStringValue ) ;
 proto_tree_add_uint ( member_tree , hf_amf_membernamelength , tvb , iValueOffset , iValueLength , iStringLength ) ;
 iValueOffset += iValueLength ;
 proto_tree_add_string ( member_tree , hf_amf_membername , tvb , iValueOffset , iStringLength , iStringValue ) ;
 iValueOffset += iStringLength ;
 }
 else {
 proto_tree_add_uint ( traits_tree , hf_amf_string_reference , tvb , iValueOffset , iValueLength , iIntegerValue >> 1 ) ;
 iValueOffset += iValueLength ;
 }
 }
 for ( i = 0 ;
 i < iTraitCount ;
 i ++ ) iValueOffset = dissect_amf3_value_type ( tvb , iValueOffset , traits_tree , NULL ) ;
 if ( iTypeIsDynamic ) {
 for ( ;
 ;
 ) {
 iIntegerValue = amf_get_u29 ( tvb , iValueOffset , & iValueLength ) ;
 if ( iIntegerValue & 0x00000001 ) {
 iStringLength = iIntegerValue >> 1 ;
 if ( iStringLength == 0 ) {
 proto_tree_add_item ( traits_tree , hf_amf_end_of_dynamic_members , tvb , iValueOffset , iValueLength , ENC_NA ) ;
 iValueOffset += iValueLength ;
 break ;
 }
 iStringValue = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , iValueOffset + iValueLength , iStringLength , ENC_UTF_8 | ENC_NA ) ;
 subval_tree = proto_tree_add_subtree_format ( traits_tree , tvb , iValueOffset , - 1 , ett_amf_array_element , & subval_ti , "%s:" , iStringValue ) ;
 name_tree = proto_tree_add_subtree_format ( subval_tree , tvb , iValueOffset , iValueLength + iStringLength , ett_amf_string , NULL , "Member name: %s" , iStringValue ) ;
 proto_tree_add_uint ( name_tree , hf_amf_membernamelength , tvb , iValueOffset , iValueLength , iStringLength ) ;
 iValueOffset += iValueLength ;
 proto_tree_add_string ( name_tree , hf_amf_membername , tvb , iValueOffset , iStringLength , iStringValue ) ;
 iValueOffset += iStringLength ;
 }
 else {
 subval_tree = proto_tree_add_subtree_format ( traits_tree , tvb , iValueOffset , iValueLength , ett_amf_array_element , & subval_ti , "Reference %u:" , iIntegerValue >> 1 ) ;
 proto_tree_add_uint ( subval_tree , hf_amf_string_reference , tvb , iValueOffset , iValueLength , iIntegerValue >> 1 ) ;
 iValueOffset += iValueLength ;
 }
 iValueOffset = dissect_amf3_value_type ( tvb , iValueOffset , subval_tree , subval_ti ) ;
 proto_item_set_end ( subval_ti , tvb , iValueOffset ) ;
 }
 }
 proto_item_set_end ( traits_ti , tvb , iValueOffset ) ;
 }
 }
 else {
 proto_tree_add_uint ( val_tree , hf_amf_trait_reference , tvb , iValueOffset , iValueLength , iIntegerValue >> 2 ) ;
 iValueOffset += iValueLength ;
 }
 }
 else {
 proto_tree_add_uint ( val_tree , hf_amf_object_reference , tvb , iValueOffset , iValueLength , iIntegerValue >> 1 ) ;
 proto_item_append_text ( ti , " reference %u" , iIntegerValue >> 1 ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , " reference %u" , iIntegerValue >> 1 ) ;
 }
 break ;
 case AMF3_XML : iIntegerValue = amf_get_u29 ( tvb , iValueOffset , & iValueLength ) ;
 if ( iIntegerValue & 0x00000001 ) {
 iStringLength = iIntegerValue >> 1 ;
 proto_tree_add_uint ( val_tree , hf_amf_xmllength , tvb , iValueOffset , iValueLength , iStringLength ) ;
 iValueOffset += iValueLength ;
 proto_tree_add_item ( val_tree , hf_amf_xml , tvb , iValueOffset , iStringLength , ENC_UTF_8 | ENC_NA ) ;
 }
 else {
 proto_tree_add_uint ( val_tree , hf_amf_object_reference , tvb , iValueOffset , iValueLength , iIntegerValue >> 1 ) ;
 proto_item_append_text ( ti , " reference %u" , iIntegerValue >> 1 ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , " reference %u" , iIntegerValue >> 1 ) ;
 }
 break ;
 case AMF3_BYTEARRAY : iIntegerValue = amf_get_u29 ( tvb , iValueOffset , & iValueLength ) ;
 if ( iIntegerValue & 0x00000001 ) {
 iArrayLength = iIntegerValue >> 1 ;
 proto_tree_add_uint ( val_tree , hf_amf_bytearraylength , tvb , iValueOffset , iValueLength , iArrayLength ) ;
 iValueOffset += iValueLength ;
 iByteArrayValue = ( guint8 * ) tvb_memdup ( wmem_packet_scope ( ) , tvb , iValueOffset , iArrayLength ) ;
 proto_tree_add_bytes ( val_tree , hf_amf_bytearray , tvb , iValueOffset , iArrayLength , iByteArrayValue ) ;
 proto_item_append_text ( ti , " %s" , bytes_to_str ( wmem_packet_scope ( ) , iByteArrayValue , iArrayLength ) ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , " %s" , bytes_to_str ( wmem_packet_scope ( ) , iByteArrayValue , iArrayLength ) ) ;
 }
 else {
 proto_tree_add_uint ( val_tree , hf_amf_object_reference , tvb , iValueOffset , iValueLength , iIntegerValue >> 1 ) ;
 proto_item_append_text ( ti , " reference %u" , iIntegerValue >> 1 ) ;
 if ( parent_ti != NULL ) proto_item_append_text ( parent_ti , " reference %u" , iIntegerValue >> 1 ) ;
 }
 break ;
 default : iValueOffset = tvb_reported_length ( tvb ) ;
 break ;
 }
 proto_item_set_end ( ti , tvb , iValueOffset ) ;
 return iValueOffset ;
 }
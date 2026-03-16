static gint dissect_amf0_property_list ( tvbuff_t * tvb , gint offset , proto_tree * tree , guint * countp , gboolean * amf3_encoding ) {
 proto_item * prop_ti ;
 proto_tree * prop_tree ;
 proto_tree * name_tree ;
 guint iStringLength ;
 gchar * iStringValue ;
 guint count = 0 ;
 for ( ;
 ;
 ) {
 iStringLength = tvb_get_ntohs ( tvb , offset ) ;
 if ( iStringLength == 0 && tvb_get_guint8 ( tvb , offset + 2 ) == AMF0_END_OF_OBJECT ) break ;
 count ++ ;
 iStringValue = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset + 2 , iStringLength , ENC_ASCII ) ;
 prop_tree = proto_tree_add_subtree_format ( tree , tvb , offset , - 1 , ett_amf_property , & prop_ti , "Property '%s'" , iStringValue ) ;
 name_tree = proto_tree_add_subtree_format ( prop_tree , tvb , offset , 2 + iStringLength , ett_amf_string , NULL , "Name: %s" , iStringValue ) ;
 proto_tree_add_uint ( name_tree , hf_amf_stringlength , tvb , offset , 2 , iStringLength ) ;
 offset += 2 ;
 proto_tree_add_item ( name_tree , hf_amf_string , tvb , offset , iStringLength , ENC_UTF_8 | ENC_NA ) ;
 offset += iStringLength ;
 offset = dissect_amf0_value_type ( tvb , offset , prop_tree , amf3_encoding , prop_ti ) ;
 proto_item_set_end ( prop_ti , tvb , offset ) ;
 }
 proto_tree_add_item ( tree , hf_amf_end_of_object_marker , tvb , offset , 3 , ENC_NA ) ;
 offset += 3 ;
 * countp = count ;
 return offset ;
 }
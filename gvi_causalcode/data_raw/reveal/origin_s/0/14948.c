void parseResultMask ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo _U_ , gint * pOffset ) {
 static const int * browseresult_mask [ ] = {
 & hf_opcua_resultMask_referencetype , & hf_opcua_resultMask_isforward , & hf_opcua_resultMask_nodeclass , & hf_opcua_resultMask_browsename , & hf_opcua_resultMask_displayname , & hf_opcua_resultMask_typedefinition , NULL }
 ;
 guint8 ResultMask = tvb_get_guint8 ( tvb , * pOffset ) ;
 if ( ResultMask == RESULTMASK_ALL ) {
 proto_tree_add_item ( tree , hf_opcua_resultMask_all , tvb , * pOffset , 4 , ENC_LITTLE_ENDIAN ) ;
 }
 else {
 proto_tree_add_bitmask ( tree , tvb , * pOffset , hf_opcua_resultMask , ett_opcua_resultMask , browseresult_mask , ENC_LITTLE_ENDIAN ) ;
 }
 * pOffset += 4 ;
 }
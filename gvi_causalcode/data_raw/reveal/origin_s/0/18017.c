void parseLocalizedText ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo , gint * pOffset , const char * szFieldName ) {
 static const int * loctext_mask [ ] = {
 & hf_opcua_loctext_mask_localeflag , & hf_opcua_loctext_mask_textflag , NULL }
 ;
 gint iOffset = * pOffset ;
 guint8 EncodingMask ;
 proto_tree * subtree ;
 proto_item * ti ;
 subtree = proto_tree_add_subtree_format ( tree , tvb , * pOffset , - 1 , ett_opcua_localizedtext , & ti , "%s: LocalizedText" , szFieldName ) ;
 EncodingMask = tvb_get_guint8 ( tvb , iOffset ) ;
 proto_tree_add_bitmask ( subtree , tvb , iOffset , hf_opcua_loctext_mask , ett_opcua_localizedtext_encodingmask , loctext_mask , ENC_LITTLE_ENDIAN ) ;
 iOffset ++ ;
 if ( EncodingMask & LOCALIZEDTEXT_ENCODINGBYTE_LOCALE ) {
 parseString ( subtree , tvb , pinfo , & iOffset , hf_opcua_localizedtext_locale ) ;
 }
 if ( EncodingMask & LOCALIZEDTEXT_ENCODINGBYTE_TEXT ) {
 parseString ( subtree , tvb , pinfo , & iOffset , hf_opcua_localizedtext_text ) ;
 }
 proto_item_set_end ( ti , tvb , iOffset ) ;
 * pOffset = iOffset ;
 }
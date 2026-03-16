void parseArraySimple ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo , gint * pOffset , const char * szFieldName , const char * szTypeName , int hfIndex , fctSimpleTypeParser pParserFunction , const gint idx ) {
 proto_item * ti ;
 proto_tree * subtree = proto_tree_add_subtree_format ( tree , tvb , * pOffset , - 1 , idx , & ti , "%s: Array of %s" , szFieldName , szTypeName ) ;
 int i ;
 gint32 iLen ;
 iLen = tvb_get_letohl ( tvb , * pOffset ) ;
 proto_tree_add_item ( subtree , hf_opcua_ArraySize , tvb , * pOffset , 4 , ENC_LITTLE_ENDIAN ) ;
 if ( iLen > MAX_ARRAY_LEN ) {
 proto_tree_add_expert_format ( subtree , pinfo , & ei_array_length , tvb , * pOffset , 4 , "Array length %d too large to process" , iLen ) ;
 return ;
 }
 * pOffset += 4 ;
 for ( i = 0 ;
 i < iLen ;
 i ++ ) {
 proto_item * arrayItem = ( * pParserFunction ) ( subtree , tvb , pinfo , pOffset , hfIndex ) ;
 if ( arrayItem != NULL ) {
 proto_item_prepend_text ( arrayItem , "[%i]: " , i ) ;
 }
 }
 proto_item_set_end ( ti , tvb , * pOffset ) ;
 }
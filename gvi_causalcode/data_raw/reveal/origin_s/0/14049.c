static int parse_PRSPEC_Kind ( tvbuff_t * tvb , int offset , proto_tree * tree , enum PRSPEC_Kind * prspec ) {
 static const value_string KIND [ ] = {
 {
 0 , "PRSPEC_LPWSTR" }
 , {
 1 , "PRSPEC_PROPID" }
 , {
 0 , NULL }
 }
 ;
 gint32 kind = tvb_get_letohl ( tvb , offset ) ;
 DISSECTOR_ASSERT ( kind < ( PRSPEC_PROPID + 1 ) ) ;
 if ( kind ) {
 * prspec = PRSPEC_PROPID ;
 }
 else {
 * prspec = PRSPEC_LPWSTR ;
 }
 proto_tree_add_string ( tree , hf_mswsp_cfullpropspec_kind , tvb , offset , 4 , val_to_str ( * prspec , KIND , "(Unknown: 0x%x)" ) ) ;
 offset += 4 ;
 return offset ;
 }
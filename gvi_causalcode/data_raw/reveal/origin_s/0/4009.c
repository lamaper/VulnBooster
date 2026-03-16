static int parse_relop ( tvbuff_t * tvb , int offset , proto_tree * tree , guint32 * relop , const char * * str ) {
 const char * str1 = NULL , * str2 = NULL ;
 guint32 tmp = tvb_get_letohl ( tvb , offset ) ;
 guint32 modifier = ( tmp & 0xF00 ) ;
 DISSECTOR_ASSERT ( ( tmp & 0xf ) < PRSomeBits + 1 ) ;
 switch ( tmp & 0xf ) {
 case PRLT : * relop = PRLT ;
 break ;
 case PRLE : * relop = PRLE ;
 break ;
 case PRGT : * relop = PRGT ;
 break ;
 case PRGE : * relop = PRGE ;
 break ;
 case PREQ : * relop = PREQ ;
 break ;
 case PRNE : * relop = PRNE ;
 break ;
 case PRRE : * relop = PRRE ;
 break ;
 case PRAllBits : * relop = PRAllBits ;
 break ;
 case PRSomeBits : * relop = PRSomeBits ;
 break ;
 default : break ;
 }
 str2 = val_to_str ( * relop , PR_VALS , "0x%04x" ) ;
 if ( modifier ) {
 switch ( modifier ) {
 case PRAll : * relop = * relop | PRAll ;
 break ;
 case PRAny : * relop |= PRAny ;
 break ;
 default : DISSECTOR_ASSERT ( FALSE ) ;
 break ;
 }
 str1 = try_val_to_str ( ( modifier ) , PR_VALS ) ;
 if ( str1 ) {
 str1 = wmem_strdup_printf ( wmem_packet_scope ( ) , "%s | " , str1 ) ;
 str2 = wmem_strdup_printf ( wmem_packet_scope ( ) , "%s%s" , str1 , str2 ) ;
 }
 }
 proto_tree_add_string_format_value ( tree , hf_mswsp_cproprestrict_relop , tvb , offset , 4 , str2 , "%s (0x%04x)" , str2 [ 0 ] == '\0' ? "" : str2 , * relop ) ;
 if ( str ) {
 * str = str2 ;
 }
 return offset + 4 ;
 }
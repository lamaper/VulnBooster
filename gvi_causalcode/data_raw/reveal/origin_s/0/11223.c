static int parse_rType ( tvbuff_t * tvb , int offset , proto_tree * tree , enum rType * rtype , const char * * str ) {
 const char * txt = NULL ;
 guint32 type = tvb_get_letohl ( tvb , offset ) ;
 switch ( type ) {
 case RTNone : * rtype = RTNone ;
 break ;
 case RTAnd : * rtype = RTAnd ;
 break ;
 case RTOr : * rtype = RTOr ;
 break ;
 case RTNot : * rtype = RTNot ;
 break ;
 case RTContent : * rtype = RTContent ;
 break ;
 case RTProperty : * rtype = RTProperty ;
 break ;
 case RTProximity : * rtype = RTProximity ;
 break ;
 case RTVector : * rtype = RTVector ;
 break ;
 case RTNatLanguage : * rtype = RTNatLanguage ;
 break ;
 case RTScope : * rtype = RTScope ;
 break ;
 case RTCoerce_Add : * rtype = RTCoerce_Add ;
 break ;
 case RTCoerce_Multiply : * rtype = RTCoerce_Multiply ;
 break ;
 case RTCoerce_Absolute : * rtype = RTCoerce_Absolute ;
 break ;
 case RTProb : * rtype = RTProb ;
 break ;
 case RTFeedback : * rtype = RTFeedback ;
 break ;
 case RTReldoc : * rtype = RTReldoc ;
 break ;
 case RTReuseWhere : * rtype = RTReuseWhere ;
 break ;
 case RTInternalProp : * rtype = RTInternalProp ;
 break ;
 default : DISSECTOR_ASSERT ( FALSE ) ;
 break ;
 }
 txt = val_to_str ( * rtype , RT_VALS , "0x%.8x" ) ;
 proto_tree_add_string_format_value ( tree , hf_mswsp_crestrict_ultype , tvb , offset , 4 , txt , "%s (0x%.8x)" , txt [ 0 ] == '0' ? "" : txt , * rtype ) ;
 if ( str ) {
 * str = txt ;
 }
 return offset + 4 ;
 }
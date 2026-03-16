static int parse_CInGroupSortAggregSet_type ( tvbuff_t * tvb , int offset , proto_tree * tree , enum CInGroupSortAggregSet_type * type ) {
 guint8 tmp = tvb_get_guint8 ( tvb , offset ) ;
 switch ( tmp ) {
 case GroupIdDefault : * type = GroupIdDefault ;
 break ;
 case GroupIdMinValue : * type = GroupIdMinValue ;
 break ;
 case GroupIdNull : * type = GroupIdNull ;
 break ;
 case GroupIdValue : * type = GroupIdValue ;
 break ;
 default : DISSECTOR_ASSERT ( FALSE ) ;
 break ;
 }
 proto_tree_add_uint ( tree , hf_mswsp_cingroupsortaggregset_type , tvb , offset , 1 , * type ) ;
 return offset + 1 ;
 }
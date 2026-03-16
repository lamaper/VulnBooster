static void dissect_zcl_appl_ctrl_wr_funcs ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 proto_tree * sub_tree = NULL ;
 guint tvb_len ;
 guint i = 0 ;
 tvb_len = tvb_reported_length ( tvb ) ;
 while ( * offset < tvb_len && i < ZBEE_ZCL_APPL_CTRL_NUM_FUNC_ETT ) {
 sub_tree = proto_tree_add_subtree_format ( tree , tvb , * offset , 0 , ett_zbee_zcl_appl_ctrl_func [ i ] , NULL , "Function #%d" , i ) ;
 i ++ ;
 dissect_zcl_appl_ctrl_attr_func ( tvb , sub_tree , offset ) ;
 }
 }
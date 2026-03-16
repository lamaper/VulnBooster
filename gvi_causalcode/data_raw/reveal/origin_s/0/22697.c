static int dissect_CPMSetCatState ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree _U_ , gboolean in _U_ , void * data _U_ ) {
 col_append_str ( pinfo -> cinfo , COL_INFO , "SetCatState" ) ;
 return tvb_reported_length ( tvb ) ;
 }
static int dissect_pvfs2_error ( tvbuff_t * tvb , proto_tree * tree , int offset , packet_info * pinfo ) {
 gint32 err ;
 const char * errmsg = NULL ;
 err = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_pvfs_error , tvb , offset , 4 , - err ) ;
 offset += 4 ;
 if ( err != 0 ) {
 errmsg = val_to_str ( - err , names_pvfs_error , "Unknown error: %u" ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " Error: %s" , errmsg ) ;
 }
 return offset ;
 }
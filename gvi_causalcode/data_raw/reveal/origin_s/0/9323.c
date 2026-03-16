static int dissect_pvfs_fh ( tvbuff_t * tvb , int offset , packet_info * pinfo , proto_tree * tree , const char * name , guint32 * hash ) {
 proto_tree * ftree ;
 ftree = proto_tree_add_subtree ( tree , tvb , offset , PVFS2_FH_LENGTH , ett_pvfs_fh , NULL , name ) ;
 proto_tree_add_uint ( ftree , hf_pvfs_fh_length , tvb , offset , 0 , PVFS2_FH_LENGTH ) ;
 dissect_fhandle_data ( tvb , offset , pinfo , ftree , hash ) ;
 offset += PVFS2_FH_LENGTH ;
 return offset ;
 }
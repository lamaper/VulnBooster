static int dissect_pvfs2_attrmask ( tvbuff_t * tvb , proto_tree * tree , int offset , guint32 * pattrmask ) {
 guint32 attrmask , i ;
 proto_item * attritem ;
 proto_tree * attrtree ;
 attrmask = tvb_get_letohl ( tvb , offset ) ;
 attritem = proto_tree_add_uint ( tree , hf_pvfs_attrmask , tvb , offset , 4 , attrmask ) ;
 attrtree = proto_item_add_subtree ( attritem , ett_pvfs_attrmask ) ;
 for ( i = 0 ;
 i < 32 ;
 i ++ ) {
 if ( attrmask & ( 1 << i ) ) proto_tree_add_uint ( attrtree , hf_pvfs_attr , tvb , offset , 4 , i ) ;
 }
 offset += 4 ;
 if ( pattrmask ) * pattrmask = attrmask ;
 return offset ;
 }
static int dissect_pvfs_distribution ( tvbuff_t * tvb , proto_tree * tree , int offset ) {
 proto_item * dist_item ;
 proto_tree * dist_tree ;
 guint32 distlen ;
 char * tmpstr ;
 guint8 issimplestripe = 0 ;
 guint32 total_len ;
 distlen = tvb_get_letohl ( tvb , offset ) ;
 tmpstr = ( char * ) tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset + 4 , distlen , ENC_ASCII ) ;
 total_len = roundup8 ( 4 + distlen + 1 ) ;
 if ( ( ( distlen + 1 ) == PVFS_DIST_SIMPLE_STRIPE_NAME_SIZE ) && ( g_ascii_strncasecmp ( tmpstr , PVFS_DIST_SIMPLE_STRIPE_NAME , distlen ) == 0 ) ) {
 total_len += 8 ;
 issimplestripe = 1 ;
 }
 dist_item = proto_tree_add_string ( tree , hf_pvfs_distribution , tvb , offset , total_len + 8 , tmpstr ) ;
 dist_tree = proto_item_add_subtree ( dist_item , ett_pvfs_distribution ) ;
 offset = dissect_pvfs_string ( tvb , dist_tree , hf_pvfs_io_dist , offset , NULL ) ;
 if ( issimplestripe ) offset = dissect_pvfs_uint64 ( tvb , dist_tree , offset , hf_pvfs_strip_size , NULL ) ;
 offset += 8 ;
 return offset ;
 }
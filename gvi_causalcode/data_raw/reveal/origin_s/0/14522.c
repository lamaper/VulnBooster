static guint8 nb_remote_session ( tvbuff_t * tvb , int offset , proto_tree * tree ) {
 guint8 remote_session = tvb_get_guint8 ( tvb , offset + NB_RMT_SES ) ;
 proto_tree_add_uint ( tree , hf_netb_remote_ses_no , tvb , offset + NB_RMT_SES , 1 , remote_session ) ;
 return remote_session ;
 }
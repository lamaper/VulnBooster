static guint8 nb_local_session ( tvbuff_t * tvb , int offset , proto_tree * tree ) {
 guint8 local_session = tvb_get_guint8 ( tvb , offset + NB_LOCAL_SES ) ;
 proto_tree_add_uint ( tree , hf_netb_local_ses_no , tvb , offset + NB_LOCAL_SES , 1 , local_session ) ;
 return local_session ;
 }
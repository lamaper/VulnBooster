static struct message_data * find_or_create_message_data ( struct mswsp_ct * conv_data , packet_info * pinfo , guint16 msg_id , gboolean is_request , void * data ) {
 struct message_data to_find ;
 struct message_data * msg_data = NULL ;
 GSList * result = NULL ;
 int * p_smb_level = ( int * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_mswsp , 0 ) ;
 to_find . is_request = is_request ;
 to_find . msg_id = msg_id ;
 to_find . smb_level = * p_smb_level ;
 if ( ! get_fid_and_frame ( pinfo , & to_find . fid , & to_find . frame , data ) || ! conv_data ) {
 return msg_data ;
 }
 result = g_slist_find_custom ( conv_data -> GSL_message_data , & to_find , ( GCompareFunc ) msg_data_find ) ;
 if ( ! result ) {
 msg_data = ( struct message_data * ) wmem_alloc ( wmem_file_scope ( ) , sizeof ( struct message_data ) ) ;
 * msg_data = to_find ;
 conv_data -> GSL_message_data = g_slist_prepend ( conv_data -> GSL_message_data , msg_data ) ;
 }
 else {
 msg_data = ( struct message_data * ) result -> data ;
 }
 return msg_data ;
 }
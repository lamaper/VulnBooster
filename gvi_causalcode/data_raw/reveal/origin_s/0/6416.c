static gint msg_data_find ( struct message_data * a , struct message_data * b ) {
 if ( a -> fid == b -> fid && a -> frame == b -> frame && a -> msg_id == b -> msg_id && a -> smb_level == b -> smb_level && a -> is_request == b -> is_request ) {
 return 0 ;
 }
 return 1 ;
 }
int remoteSerializeReplyError ( struct qemud_client * client , remote_error * rerr , remote_message_header * req ) {
 return remoteSerializeError ( client , rerr , req -> prog , req -> vers , req -> proc , req -> type == REMOTE_STREAM ? REMOTE_STREAM : REMOTE_REPLY , req -> serial ) ;
 }
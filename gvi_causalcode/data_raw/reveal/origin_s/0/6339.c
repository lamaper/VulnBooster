int remoteSerializeStreamError ( struct qemud_client * client , remote_error * rerr , int proc , int serial ) {
 return remoteSerializeError ( client , rerr , REMOTE_PROGRAM , REMOTE_PROTOCOL_VERSION , proc , REMOTE_STREAM , serial ) ;
 }
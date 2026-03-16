static void purple_rem_deny ( struct im_connection * ic , char * who ) {
 struct purple_data * pd = ic -> proto_data ;
 purple_privacy_deny_remove ( pd -> account , who , FALSE ) ;
 }
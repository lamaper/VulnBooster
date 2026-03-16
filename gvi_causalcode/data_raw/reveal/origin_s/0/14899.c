static void purple_add_deny ( struct im_connection * ic , char * who ) {
 struct purple_data * pd = ic -> proto_data ;
 purple_privacy_deny_add ( pd -> account , who , FALSE ) ;
 }
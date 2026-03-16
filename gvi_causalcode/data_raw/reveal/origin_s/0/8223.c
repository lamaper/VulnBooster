static void purple_add_permit ( struct im_connection * ic , char * who ) {
 struct purple_data * pd = ic -> proto_data ;
 purple_privacy_permit_add ( pd -> account , who , FALSE ) ;
 }
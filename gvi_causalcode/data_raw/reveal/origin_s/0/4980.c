static void purple_rem_permit ( struct im_connection * ic , char * who ) {
 struct purple_data * pd = ic -> proto_data ;
 purple_privacy_permit_remove ( pd -> account , who , FALSE ) ;
 }
static void purple_get_info ( struct im_connection * ic , char * who ) {
 struct purple_data * pd = ic -> proto_data ;
 serv_get_info ( purple_account_get_connection ( pd -> account ) , who ) ;
 }
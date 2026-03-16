static void purple_remove_buddy ( struct im_connection * ic , char * who , char * group ) {
 PurpleBuddy * pb ;
 struct purple_data * pd = ic -> proto_data ;
 pb = purple_find_buddy ( pd -> account , who ) ;
 if ( pb != NULL ) {
 PurpleGroup * group ;
 group = purple_buddy_get_group ( pb ) ;
 purple_account_remove_buddy ( pd -> account , pb , group ) ;
 purple_blist_remove_buddy ( pb ) ;
 }
 purple_gg_buddylist_export ( pd -> account -> gc ) ;
 }
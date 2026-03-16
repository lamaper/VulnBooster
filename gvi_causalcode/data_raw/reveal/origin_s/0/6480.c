static void purple_add_buddy ( struct im_connection * ic , char * who , char * group ) {
 PurpleBuddy * pb ;
 PurpleGroup * pg = NULL ;
 struct purple_data * pd = ic -> proto_data ;
 if ( group && ! ( pg = purple_find_group ( group ) ) ) {
 pg = purple_group_new ( group ) ;
 purple_blist_add_group ( pg , NULL ) ;
 }
 pb = purple_buddy_new ( pd -> account , who , NULL ) ;
 purple_blist_add_buddy ( pb , NULL , pg , NULL ) ;
 purple_account_add_buddy ( pd -> account , pb ) ;
 purple_gg_buddylist_export ( pd -> account -> gc ) ;
 }
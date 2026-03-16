static void prplcb_privacy_deny_removed ( PurpleAccount * account , const char * name ) {
 struct im_connection * ic = purple_ic_by_pa ( account ) ;
 void * n ;
 n = g_slist_find_custom ( ic -> deny , name , ( GCompareFunc ) ic -> acc -> prpl -> handle_cmp ) ;
 ic -> deny = g_slist_remove ( ic -> deny , n ) ;
 }
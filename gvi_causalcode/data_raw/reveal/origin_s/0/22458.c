static void prplcb_privacy_permit_removed ( PurpleAccount * account , const char * name ) {
 struct im_connection * ic = purple_ic_by_pa ( account ) ;
 void * n ;
 n = g_slist_find_custom ( ic -> permit , name , ( GCompareFunc ) ic -> acc -> prpl -> handle_cmp ) ;
 ic -> permit = g_slist_remove ( ic -> permit , n ) ;
 }
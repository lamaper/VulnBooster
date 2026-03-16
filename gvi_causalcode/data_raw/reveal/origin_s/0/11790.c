static void prplcb_privacy_deny_added ( PurpleAccount * account , const char * name ) {
 struct im_connection * ic = purple_ic_by_pa ( account ) ;
 if ( ! g_slist_find_custom ( ic -> deny , name , ( GCompareFunc ) ic -> acc -> prpl -> handle_cmp ) ) {
 ic -> deny = g_slist_prepend ( ic -> deny , g_strdup ( name ) ) ;
 }
 }
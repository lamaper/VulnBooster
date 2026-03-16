static void prplcb_privacy_permit_added ( PurpleAccount * account , const char * name ) {
 struct im_connection * ic = purple_ic_by_pa ( account ) ;
 if ( ! g_slist_find_custom ( ic -> permit , name , ( GCompareFunc ) ic -> acc -> prpl -> handle_cmp ) ) {
 ic -> permit = g_slist_prepend ( ic -> permit , g_strdup ( name ) ) ;
 }
 }
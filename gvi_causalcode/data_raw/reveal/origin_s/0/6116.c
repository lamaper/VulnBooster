static void prplcb_blist_update ( PurpleBuddyList * list , PurpleBlistNode * node ) {
 if ( node -> type == PURPLE_BLIST_BUDDY_NODE ) {
 PurpleBuddy * bud = ( PurpleBuddy * ) node ;
 PurpleGroup * group = purple_buddy_get_group ( bud ) ;
 struct im_connection * ic = purple_ic_by_pa ( bud -> account ) ;
 PurpleStatus * as ;
 int flags = 0 ;
 if ( ic == NULL ) {
 return ;
 }
 if ( bud -> server_alias ) {
 imcb_rename_buddy ( ic , bud -> name , bud -> server_alias ) ;
 }
 else if ( bud -> alias ) {
 imcb_rename_buddy ( ic , bud -> name , bud -> alias ) ;
 }
 if ( group ) {
 imcb_add_buddy ( ic , bud -> name , purple_group_get_name ( group ) ) ;
 }
 flags |= purple_presence_is_online ( bud -> presence ) ? OPT_LOGGED_IN : 0 ;
 flags |= purple_presence_is_available ( bud -> presence ) ? 0 : OPT_AWAY ;
 as = purple_presence_get_active_status ( bud -> presence ) ;
 imcb_buddy_status ( ic , bud -> name , flags , purple_status_get_name ( as ) , purple_status_get_attr_string ( as , "message" ) ) ;
 imcb_buddy_times ( ic , bud -> name , purple_presence_get_login_time ( bud -> presence ) , purple_presence_get_idle_time ( bud -> presence ) ) ;
 }
 }
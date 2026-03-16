static void prplcb_blist_new ( PurpleBlistNode * node ) {
 if ( node -> type == PURPLE_BLIST_BUDDY_NODE ) {
 PurpleBuddy * bud = ( PurpleBuddy * ) node ;
 struct im_connection * ic = purple_ic_by_pa ( bud -> account ) ;
 if ( ic == NULL ) {
 return ;
 }
 imcb_add_buddy ( ic , bud -> name , NULL ) ;
 prplcb_blist_update ( NULL , node ) ;
 }
 }
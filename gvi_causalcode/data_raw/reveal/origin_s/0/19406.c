void fe_channels_nicklist ( CHANNEL_REC * channel , int flags ) {
 NICK_REC * nick ;
 GSList * tmp , * nicklist , * sorted ;
 int nicks , normal , voices , halfops , ops ;
 const char * nick_flags ;
 nicks = normal = voices = halfops = ops = 0 ;
 nicklist = nicklist_getnicks ( channel ) ;
 sorted = NULL ;
 nick_flags = channel -> server -> get_nick_flags ( channel -> server ) ;
 for ( tmp = nicklist ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 nick = tmp -> data ;
 nicks ++ ;
 if ( nick -> op ) {
 ops ++ ;
 if ( ( flags & CHANNEL_NICKLIST_FLAG_OPS ) == 0 ) continue ;
 }
 else if ( nick -> halfop ) {
 halfops ++ ;
 if ( ( flags & CHANNEL_NICKLIST_FLAG_HALFOPS ) == 0 ) continue ;
 }
 else if ( nick -> voice ) {
 voices ++ ;
 if ( ( flags & CHANNEL_NICKLIST_FLAG_VOICES ) == 0 ) continue ;
 }
 else {
 normal ++ ;
 if ( ( flags & CHANNEL_NICKLIST_FLAG_NORMAL ) == 0 ) continue ;
 }
 sorted = g_slist_prepend ( sorted , nick ) ;
 }
 g_slist_free ( nicklist ) ;
 sorted = g_slist_sort_with_data ( sorted , ( GCompareDataFunc ) nicklist_compare , ( void * ) nick_flags ) ;
 if ( ( flags & CHANNEL_NICKLIST_FLAG_COUNT ) == 0 ) {
 printformat ( channel -> server , channel -> visible_name , MSGLEVEL_CLIENTCRAP , TXT_NAMES , channel -> visible_name , nicks , ops , halfops , voices , normal ) ;
 display_sorted_nicks ( channel , sorted ) ;
 }
 g_slist_free ( sorted ) ;
 printformat ( channel -> server , channel -> visible_name , MSGLEVEL_CLIENTNOTICE , TXT_ENDOFNAMES , channel -> visible_name , nicks , ops , halfops , voices , normal ) ;
 }
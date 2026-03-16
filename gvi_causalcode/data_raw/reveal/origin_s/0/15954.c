static int handle_grant_data ( TABLE_LIST * tables , bool drop , LEX_USER * user_from , LEX_USER * user_to ) {
 int result = 0 ;
 int found ;
 int ret ;
 DBUG_ENTER ( "handle_grant_data" ) ;
 if ( ( found = handle_grant_table ( tables , 0 , drop , user_from , user_to ) ) < 0 ) {
 result = - 1 ;
 }
 else {
 if ( ( ( ret = handle_grant_struct ( USER_ACL , drop , user_from , user_to ) > 0 ) && ! result ) || found ) {
 result = 1 ;
 if ( ! drop && ! user_to ) goto end ;
 }
 else if ( ret < 0 ) {
 result = - 1 ;
 goto end ;
 }
 }
 if ( ( found = handle_grant_table ( tables , 1 , drop , user_from , user_to ) ) < 0 ) {
 result = - 1 ;
 }
 else {
 if ( ( ( ( ret = handle_grant_struct ( DB_ACL , drop , user_from , user_to ) > 0 ) && ! result ) || found ) && ! result ) {
 result = 1 ;
 if ( ! drop && ! user_to ) goto end ;
 }
 else if ( ret < 0 ) {
 result = - 1 ;
 goto end ;
 }
 }
 if ( ( found = handle_grant_table ( tables , 4 , drop , user_from , user_to ) ) < 0 ) {
 result = - 1 ;
 }
 else {
 if ( ( ( ( ret = handle_grant_struct ( PROC_PRIVILEGES_HASH , drop , user_from , user_to ) > 0 ) && ! result ) || found ) && ! result ) {
 result = 1 ;
 if ( ! drop && ! user_to ) goto end ;
 }
 else if ( ret < 0 ) {
 result = - 1 ;
 goto end ;
 }
 if ( ( ( ( ret = handle_grant_struct ( FUNC_PRIVILEGES_HASH , drop , user_from , user_to ) > 0 ) && ! result ) || found ) && ! result ) {
 result = 1 ;
 if ( ! drop && ! user_to ) goto end ;
 }
 else if ( ret < 0 ) {
 result = - 1 ;
 goto end ;
 }
 }
 if ( ( found = handle_grant_table ( tables , 2 , drop , user_from , user_to ) ) < 0 ) {
 result = - 1 ;
 }
 else {
 if ( found && ! result ) {
 result = 1 ;
 if ( ! drop && ! user_to ) goto end ;
 }
 if ( ( found = handle_grant_table ( tables , 3 , drop , user_from , user_to ) ) < 0 ) {
 result = - 1 ;
 }
 else {
 if ( ( ( ( ret = handle_grant_struct ( COLUMN_PRIVILEGES_HASH , drop , user_from , user_to ) > 0 ) && ! result ) || found ) && ! result ) result = 1 ;
 else if ( ret < 0 ) result = - 1 ;
 }
 }
 end : DBUG_RETURN ( result ) ;
 }
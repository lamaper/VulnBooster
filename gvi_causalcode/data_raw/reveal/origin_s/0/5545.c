static void set_user_salt ( ACL_USER * acl_user , const char * password , uint password_len ) {
 if ( password_len == SCRAMBLED_PASSWORD_CHAR_LENGTH ) {
 get_salt_from_password ( acl_user -> salt , password ) ;
 acl_user -> salt_len = SCRAMBLE_LENGTH ;
 }
 else if ( password_len == SCRAMBLED_PASSWORD_CHAR_LENGTH_323 ) {
 get_salt_from_password_323 ( ( ulong * ) acl_user -> salt , password ) ;
 acl_user -> salt_len = SCRAMBLE_LENGTH_323 ;
 }
 else acl_user -> salt_len = 0 ;
 }
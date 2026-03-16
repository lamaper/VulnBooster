static void handle_new_lock_ctx ( struct xml_ctx * ctx , int tag_closed ) {
 struct remote_lock * lock = ( struct remote_lock * ) ctx -> userData ;
 git_SHA_CTX sha_ctx ;
 unsigned char lock_token_sha1 [ 20 ] ;
 if ( tag_closed && ctx -> cdata ) {
 if ( ! strcmp ( ctx -> name , DAV_ACTIVELOCK_OWNER ) ) {
 lock -> owner = xstrdup ( ctx -> cdata ) ;
 }
 else if ( ! strcmp ( ctx -> name , DAV_ACTIVELOCK_TIMEOUT ) ) {
 const char * arg ;
 if ( skip_prefix ( ctx -> cdata , "Second-" , & arg ) ) lock -> timeout = strtol ( arg , NULL , 10 ) ;
 }
 else if ( ! strcmp ( ctx -> name , DAV_ACTIVELOCK_TOKEN ) ) {
 lock -> token = xstrdup ( ctx -> cdata ) ;
 git_SHA1_Init ( & sha_ctx ) ;
 git_SHA1_Update ( & sha_ctx , lock -> token , strlen ( lock -> token ) ) ;
 git_SHA1_Final ( lock_token_sha1 , & sha_ctx ) ;
 lock -> tmpfile_suffix [ 0 ] = '_' ;
 memcpy ( lock -> tmpfile_suffix + 1 , sha1_to_hex ( lock_token_sha1 ) , 40 ) ;
 }
 }
 }
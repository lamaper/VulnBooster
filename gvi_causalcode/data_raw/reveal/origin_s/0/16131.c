int tls1_change_cipher_state ( SSL * s , int which ) {
 static const unsigned char empty [ ] = "" ;
 unsigned char * p , * mac_secret ;
 unsigned char * exp_label ;
 unsigned char tmp1 [ EVP_MAX_KEY_LENGTH ] ;
 unsigned char tmp2 [ EVP_MAX_KEY_LENGTH ] ;
 unsigned char iv1 [ EVP_MAX_IV_LENGTH * 2 ] ;
 unsigned char iv2 [ EVP_MAX_IV_LENGTH * 2 ] ;
 unsigned char * ms , * key , * iv ;
 int client_write ;
 EVP_CIPHER_CTX * dd ;
 const EVP_CIPHER * c ;


 int mac_type ;
 int * mac_secret_size ;
 EVP_MD_CTX * mac_ctx ;
 EVP_PKEY * mac_key ;
 int is_export , n , i , j , k , exp_label_len , cl ;
 int reuse_dd = 0 ;
 is_export = SSL_C_IS_EXPORT ( s -> s3 -> tmp . new_cipher ) ;
 c = s -> s3 -> tmp . new_sym_enc ;
 m = s -> s3 -> tmp . new_hash ;
 mac_type = s -> s3 -> tmp . new_mac_pkey_type ;


 printf ( "\talg= %ld/%ld, comp= %p\n" , s -> s3 -> tmp . new_cipher -> algorithm_mkey , s -> s3 -> tmp . new_cipher -> algorithm_auth , comp ) ;
 printf ( "\tevp_cipher == %p ==? &d_cbc_ede_cipher3\n" , c ) ;
 printf ( "\tevp_cipher: nid, blksz= %d, %d, keylen=%d, ivlen=%d\n" , c -> nid , c -> block_size , c -> key_len , c -> iv_len ) ;
 printf ( "\tkey_block: len= %d, data= " , s -> s3 -> tmp . key_block_length ) ;
 {
 int i ;
 for ( i = 0 ;
 i < s -> s3 -> tmp . key_block_length ;
 i ++ ) printf ( "%02x" , s -> s3 -> tmp . key_block [ i ] ) ;
 printf ( "\n" ) ;
 }

 if ( s -> s3 -> tmp . new_cipher -> algorithm2 & TLS1_STREAM_MAC ) s -> mac_flags |= SSL_MAC_FLAG_READ_MAC_STREAM ;
 else s -> mac_flags &= ~ SSL_MAC_FLAG_READ_MAC_STREAM ;
 if ( s -> enc_read_ctx != NULL ) reuse_dd = 1 ;
 else if ( ( s -> enc_read_ctx = OPENSSL_malloc ( sizeof ( EVP_CIPHER_CTX ) ) ) == NULL ) goto err ;
 else EVP_CIPHER_CTX_init ( s -> enc_read_ctx ) ;
 dd = s -> enc_read_ctx ;
 mac_ctx = ssl_replace_hash ( & s -> read_hash , NULL ) ;

 COMP_CTX_free ( s -> expand ) ;
 s -> expand = NULL ;
 }
 if ( comp != NULL ) {
 s -> expand = COMP_CTX_new ( comp -> method ) ;
 if ( s -> expand == NULL ) {
 SSLerr ( SSL_F_TLS1_CHANGE_CIPHER_STATE , SSL_R_COMPRESSION_LIBRARY_ERROR ) ;
 goto err2 ;
 }
 if ( s -> s3 -> rrec . comp == NULL ) s -> s3 -> rrec . comp = ( unsigned char * ) OPENSSL_malloc ( SSL3_RT_MAX_ENCRYPTED_LENGTH ) ;
 if ( s -> s3 -> rrec . comp == NULL ) goto err ;
 }

 mac_secret = & ( s -> s3 -> read_mac_secret [ 0 ] ) ;
 mac_secret_size = & ( s -> s3 -> read_mac_secret_size ) ;
 }
 else {
 if ( s -> s3 -> tmp . new_cipher -> algorithm2 & TLS1_STREAM_MAC ) s -> mac_flags |= SSL_MAC_FLAG_WRITE_MAC_STREAM ;
 else s -> mac_flags &= ~ SSL_MAC_FLAG_WRITE_MAC_STREAM ;
 if ( s -> enc_write_ctx != NULL ) reuse_dd = 1 ;
 else if ( ( s -> enc_write_ctx = OPENSSL_malloc ( sizeof ( EVP_CIPHER_CTX ) ) ) == NULL ) goto err ;
 else EVP_CIPHER_CTX_init ( s -> enc_write_ctx ) ;
 dd = s -> enc_write_ctx ;
 mac_ctx = ssl_replace_hash ( & s -> write_hash , NULL ) ;

 COMP_CTX_free ( s -> compress ) ;
 s -> compress = NULL ;
 }
 if ( comp != NULL ) {
 s -> compress = COMP_CTX_new ( comp -> method ) ;
 if ( s -> compress == NULL ) {
 SSLerr ( SSL_F_TLS1_CHANGE_CIPHER_STATE , SSL_R_COMPRESSION_LIBRARY_ERROR ) ;
 goto err2 ;
 }
 }

 mac_secret = & ( s -> s3 -> write_mac_secret [ 0 ] ) ;
 mac_secret_size = & ( s -> s3 -> write_mac_secret_size ) ;
 }
 if ( reuse_dd ) EVP_CIPHER_CTX_cleanup ( dd ) ;
 p = s -> s3 -> tmp . key_block ;
 i = * mac_secret_size = s -> s3 -> tmp . new_mac_secret_size ;
 cl = EVP_CIPHER_key_length ( c ) ;
 j = is_export ? ( cl < SSL_C_EXPORT_KEYLENGTH ( s -> s3 -> tmp . new_cipher ) ? cl : SSL_C_EXPORT_KEYLENGTH ( s -> s3 -> tmp . new_cipher ) ) : cl ;
 if ( EVP_CIPHER_mode ( c ) == EVP_CIPH_GCM_MODE ) k = EVP_GCM_TLS_FIXED_IV_LEN ;
 else k = EVP_CIPHER_iv_length ( c ) ;
 if ( ( which == SSL3_CHANGE_CIPHER_CLIENT_WRITE ) || ( which == SSL3_CHANGE_CIPHER_SERVER_READ ) ) {
 ms = & ( p [ 0 ] ) ;
 n = i + i ;
 key = & ( p [ n ] ) ;
 n += j + j ;
 iv = & ( p [ n ] ) ;
 n += k + k ;
 exp_label = ( unsigned char * ) TLS_MD_CLIENT_WRITE_KEY_CONST ;
 exp_label_len = TLS_MD_CLIENT_WRITE_KEY_CONST_SIZE ;
 client_write = 1 ;
 }
 else {
 n = i ;
 ms = & ( p [ n ] ) ;
 n += i + j ;
 key = & ( p [ n ] ) ;
 n += j + k ;
 iv = & ( p [ n ] ) ;
 n += k ;
 exp_label = ( unsigned char * ) TLS_MD_SERVER_WRITE_KEY_CONST ;
 exp_label_len = TLS_MD_SERVER_WRITE_KEY_CONST_SIZE ;
 client_write = 0 ;
 }
 if ( n > s -> s3 -> tmp . key_block_length ) {
 SSLerr ( SSL_F_TLS1_CHANGE_CIPHER_STATE , ERR_R_INTERNAL_ERROR ) ;
 goto err2 ;
 }
 memcpy ( mac_secret , ms , i ) ;
 if ( ! ( EVP_CIPHER_flags ( c ) & EVP_CIPH_FLAG_AEAD_CIPHER ) ) {
 mac_key = EVP_PKEY_new_mac_key ( mac_type , NULL , mac_secret , * mac_secret_size ) ;
 EVP_DigestSignInit ( mac_ctx , NULL , m , NULL , mac_key ) ;
 EVP_PKEY_free ( mac_key ) ;
 }

 {
 int z ;
 for ( z = 0 ;
 z < i ;
 z ++ ) printf ( "%02X%c" , ms [ z ] , ( ( z + 1 ) % 16 ) ? ' ' : '\n' ) ;
 }

 if ( ! tls1_PRF ( ssl_get_algorithm2 ( s ) , exp_label , exp_label_len , s -> s3 -> client_random , SSL3_RANDOM_SIZE , s -> s3 -> server_random , SSL3_RANDOM_SIZE , NULL , 0 , NULL , 0 , key , j , tmp1 , tmp2 , EVP_CIPHER_key_length ( c ) ) ) goto err2 ;
 key = tmp1 ;
 if ( k > 0 ) {
 if ( ! tls1_PRF ( ssl_get_algorithm2 ( s ) , TLS_MD_IV_BLOCK_CONST , TLS_MD_IV_BLOCK_CONST_SIZE , s -> s3 -> client_random , SSL3_RANDOM_SIZE , s -> s3 -> server_random , SSL3_RANDOM_SIZE , NULL , 0 , NULL , 0 , empty , 0 , iv1 , iv2 , k * 2 ) ) goto err2 ;
 if ( client_write ) iv = iv1 ;
 else iv = & ( iv1 [ k ] ) ;
 }
 }
 s -> session -> key_arg_length = 0 ;

 int i ;
 printf ( "EVP_CipherInit_ex(dd,c,key=,iv=,which)\n" ) ;
 printf ( "\tkey= " ) ;
 for ( i = 0 ;
 i < c -> key_len ;
 i ++ ) printf ( "%02x" , key [ i ] ) ;
 printf ( "\n" ) ;
 printf ( "\t iv= " ) ;
 for ( i = 0 ;
 i < c -> iv_len ;
 i ++ ) printf ( "%02x" , iv [ i ] ) ;
 printf ( "\n" ) ;
 }

 EVP_CipherInit_ex ( dd , c , NULL , key , NULL , ( which & SSL3_CC_WRITE ) ) ;
 EVP_CIPHER_CTX_ctrl ( dd , EVP_CTRL_GCM_SET_IV_FIXED , k , iv ) ;
 }
 else EVP_CipherInit_ex ( dd , c , NULL , key , iv , ( which & SSL3_CC_WRITE ) ) ;
 if ( ( EVP_CIPHER_flags ( c ) & EVP_CIPH_FLAG_AEAD_CIPHER ) && * mac_secret_size ) EVP_CIPHER_CTX_ctrl ( dd , EVP_CTRL_AEAD_SET_MAC_KEY , * mac_secret_size , mac_secret ) ;

 {
 int z ;
 for ( z = 0 ;
 z < EVP_CIPHER_key_length ( c ) ;
 z ++ ) printf ( "%02X%c" , key [ z ] , ( ( z + 1 ) % 16 ) ? ' ' : '\n' ) ;
 }
 printf ( "\niv=" ) ;
 {
 int z ;
 for ( z = 0 ;
 z < k ;
 z ++ ) printf ( "%02X%c" , iv [ z ] , ( ( z + 1 ) % 16 ) ? ' ' : '\n' ) ;
 }
 printf ( "\n" ) ;

 OPENSSL_cleanse ( tmp2 , sizeof ( tmp1 ) ) ;
 OPENSSL_cleanse ( iv1 , sizeof ( iv1 ) ) ;
 OPENSSL_cleanse ( iv2 , sizeof ( iv2 ) ) ;
 return ( 1 ) ;
 err : SSLerr ( SSL_F_TLS1_CHANGE_CIPHER_STATE , ERR_R_MALLOC_FAILURE ) ;
 err2 : return ( 0 ) ;
 }
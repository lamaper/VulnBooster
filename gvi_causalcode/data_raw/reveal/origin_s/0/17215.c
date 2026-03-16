size_t crypto_sec_header_size ( const char * crypto_cipher_type , const char * crypto_hash_type ) {
 int crypto_cipher = string_to_crypto_cipher_type ( crypto_cipher_type ) ;
 int crypto_hash = string_to_crypto_hash_type ( crypto_hash_type ) ;
 size_t hdr_size = 0 ;
 int block_size = 0 ;
 hdr_size = sizeof ( struct crypto_config_header ) ;
 if ( crypto_hash ) {
 hdr_size += hash_len [ crypto_hash ] ;
 }
 if ( crypto_cipher ) {
 hdr_size += SALT_SIZE ;
 if ( cypher_block_len [ crypto_cipher ] ) {
 block_size = cypher_block_len [ crypto_cipher ] ;
 }
 else {
 block_size = PK11_GetBlockSize ( crypto_cipher , NULL ) ;
 if ( block_size < 0 ) {
 block_size = 64 ;
 }
 }
 hdr_size += ( block_size * 2 ) ;
 }
 return hdr_size ;
 }
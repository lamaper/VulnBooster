static uint64_t byte_budget ( const EVP_CIPHER * cipher ) {
 int ivlen = EVP_CIPHER_iv_length ( cipher ) ;
 int blklen = EVP_CIPHER_block_size ( cipher ) ;
 int len = blklen > 1 ? blklen : ivlen > 1 ? ivlen : 8 ;
 int bits = len * 4 - 1 ;
 return bits < 64 ? UINT64_C ( 1 ) << bits : UINT64_MAX ;
 }
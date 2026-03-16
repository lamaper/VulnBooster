static void init_encoding_ctx ( struct pk_encoding_ctx * ctx , enum pk_operation op , unsigned int nbits ) {
 ctx -> op = op ;
 ctx -> nbits = nbits ;
 ctx -> encoding = PUBKEY_ENC_UNKNOWN ;
 ctx -> flags = 0 ;
 ctx -> hash_algo = GCRY_MD_SHA1 ;
 ctx -> label = NULL ;
 ctx -> labellen = 0 ;
 ctx -> saltlen = 20 ;
 ctx -> verify_cmp = NULL ;
 ctx -> verify_arg = NULL ;
 }
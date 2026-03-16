unsigned long # define BN_LONG long # define BN_BITS 128 # define BN_BYTES 8 # define BN_BITS2 64 # define BN_BITS4 32 # define BN_MASK ( 0xffffffffffffffffffffffffffffffffLL ) # define BN_MASK2 ( 0xffffffffffffffffL ) # define BN_MASK2l ( 0xffffffffL ) # define BN_MASK2h ( 0xffffffff00000000L ) # define BN_MASK2h1 ( 0xffffffff80000000L ) # define BN_TBIT ( 0x8000000000000000L ) # define BN_DEC_CONV ( 10000000000000000000UL ) # define BN_DEC_FMT1 "%lu" # define BN_DEC_FMT2 "%019lu" # define BN_DEC_NUM 19 # define BN_HEX_FMT1 "%lX" # define BN_HEX_FMT2 "%016lX" # endif # ifdef SIXTY_FOUR_BIT # undef BN_LLONG # undef BN_ULLONG # define BN_ULONG unsigned long long # define BN_LONG long long # define BN_BITS 128 # define BN_BYTES 8 # define BN_BITS2 64 # define BN_BITS4 32 # define BN_MASK2 ( 0xffffffffffffffffLL ) # define BN_MASK2l ( 0xffffffffL ) # define BN_MASK2h ( 0xffffffff00000000LL ) # define BN_MASK2h1 ( 0xffffffff80000000LL ) # define BN_TBIT ( 0x8000000000000000LL ) # define BN_DEC_CONV ( 10000000000000000000ULL ) # define BN_DEC_FMT1 "%llu" # define BN_DEC_FMT2 "%019llu" # define BN_DEC_NUM 19 # define BN_HEX_FMT1 "%llX" # define BN_HEX_FMT2 "%016llX" # endif # ifdef THIRTY_TWO_BIT # ifdef BN_LLONG # if defined ( _WIN32 ) && ! defined ( __GNUC__ ) # define BN_ULLONG unsigned __int64 # define BN_MASK ( 0xffffffffffffffffI64 ) # else # define BN_ULLONG unsigned long long # define BN_MASK ( 0xffffffffffffffffLL ) # endif # endif # define BN_ULONG unsigned int # define BN_LONG int # define BN_BITS 64 # define BN_BYTES 4 # define BN_BITS2 32 # define BN_BITS4 16 # define BN_MASK2 ( 0xffffffffL ) # define BN_MASK2l ( 0xffff ) # define BN_MASK2h1 ( 0xffff8000L ) # define BN_MASK2h ( 0xffff0000L ) # define BN_TBIT ( 0x80000000L ) # define BN_DEC_CONV ( 1000000000L ) # define BN_DEC_FMT1 "%u" # define BN_DEC_FMT2 "%09u" # define BN_DEC_NUM 9 # define BN_HEX_FMT1 "%X" # define BN_HEX_FMT2 "%08X" # endif # define BN_DEFAULT_BITS 1280 # define BN_FLG_MALLOCED 0x01 # define BN_FLG_STATIC_DATA 0x02 # define BN_FLG_CONSTTIME 0x04 # ifndef OPENSSL_NO_DEPRECATED # define BN_FLG_EXP_CONSTTIME BN_FLG_CONSTTIME # endif # ifndef OPENSSL_NO_DEPRECATED # define BN_FLG_FREE 0x8000 # endif # define BN_set_flags ( b , n ) ( ( b ) -> flags |= ( n ) ) # define BN_get_flags ( b , n ) ( ( b ) -> flags & ( n ) ) # define BN_with_flags ( dest , b , n ) ( ( dest ) -> d = ( b ) -> d , \ ( dest ) -> top = ( b ) -> top , \ ( dest ) -> dmax = ( b ) -> dmax , \ ( dest ) -> neg = ( b ) -> neg , \ ( dest ) -> flags = ( ( ( dest ) -> flags & BN_FLG_MALLOCED ) \ | ( ( b ) -> flags & ~ BN_FLG_MALLOCED ) \ | BN_FLG_STATIC_DATA \ | ( n ) ) ) # if 0 typedef struct bignum_st BIGNUM ;
 typedef struct bignum_ctx BN_CTX ;
 typedef struct bn_blinding_st BN_BLINDING ;
 typedef struct bn_mont_ctx_st BN_MONT_CTX ;
 typedef struct bn_recp_ctx_st BN_RECP_CTX ;
 typedef struct bn_gencb_st BN_GENCB ;

 BN_ULONG * d ;
 int top ;
 int dmax ;
 int neg ;
 int flags ;
 }
 ;
 struct bn_mont_ctx_st {
 int ri ;
 BIGNUM RR ;
 BIGNUM N ;
 BIGNUM Ni ;
 BN_ULONG n0 [ 2 ] ;
 int flags ;
 }
 ;
 struct bn_recp_ctx_st {
 BIGNUM N ;
 BIGNUM Nr ;
 int num_bits ;
 int shift ;
 int flags ;
 }
 ;
 struct bn_gencb_st {
 unsigned int ver ;
 void * arg ;
 union {
 void ( * cb_1 ) ( int , int , void * ) ;
 int ( * cb_2 ) ( int , int , BN_GENCB * ) ;
 }
 cb ;
 }
 ;
 int BN_GENCB_call ( BN_GENCB * cb , int a , int b ) ;

 \ BN_GENCB * tmp_gencb = ( gencb ) ;
 \ tmp_gencb -> ver = 1 ;
 \ tmp_gencb -> arg = ( cb_arg ) ;
 \ tmp_gencb -> cb . cb_1 = ( callback ) ;
 }

 \ BN_GENCB * tmp_gencb = ( gencb ) ;
 \ tmp_gencb -> ver = 2 ;
 \ tmp_gencb -> arg = ( cb_arg ) ;
 \ tmp_gencb -> cb . cb_2 = ( callback ) ;
 }

 \ BIGNUM * _tmp_bn = ( a ) ;
 \ _tmp_bn -> top = 0 ;
 \ _tmp_bn -> neg = 0 ;
 \ }
 while ( 0 ) # ifdef OPENSSL_NO_DEPRECATED # define BN_zero ( a ) BN_zero_ex ( a ) # else # define BN_zero ( a ) ( BN_set_word ( ( a ) , 0 ) ) # endif const BIGNUM * BN_value_one ( void ) ;
 char * BN_options ( void ) ;
 BN_CTX * BN_CTX_new ( void ) ;


 void BN_CTX_start ( BN_CTX * ctx ) ;
 BIGNUM * BN_CTX_get ( BN_CTX * ctx ) ;
 void BN_CTX_end ( BN_CTX * ctx ) ;
 int BN_rand ( BIGNUM * rnd , int bits , int top , int bottom ) ;
 int BN_pseudo_rand ( BIGNUM * rnd , int bits , int top , int bottom ) ;
 int BN_rand_range ( BIGNUM * rnd , const BIGNUM * range ) ;
 int BN_pseudo_rand_range ( BIGNUM * rnd , const BIGNUM * range ) ;
 int BN_num_bits ( const BIGNUM * a ) ;
 int BN_num_bits_word ( BN_ULONG l ) ;
 BIGNUM * BN_new ( void ) ;
 void BN_init ( BIGNUM * ) ;
 void BN_clear_free ( BIGNUM * a ) ;
 BIGNUM * BN_copy ( BIGNUM * a , const BIGNUM * b ) ;
 void BN_swap ( BIGNUM * a , BIGNUM * b ) ;
 BIGNUM * BN_bin2bn ( const unsigned char * s , int len , BIGNUM * ret ) ;
 int BN_bn2bin ( const BIGNUM * a , unsigned char * to ) ;
 BIGNUM * BN_mpi2bn ( const unsigned char * s , int len , BIGNUM * ret ) ;
 int BN_bn2mpi ( const BIGNUM * a , unsigned char * to ) ;
 int BN_sub ( BIGNUM * r , const BIGNUM * a , const BIGNUM * b ) ;
 int BN_usub ( BIGNUM * r , const BIGNUM * a , const BIGNUM * b ) ;
 int BN_uadd ( BIGNUM * r , const BIGNUM * a , const BIGNUM * b ) ;
 int BN_add ( BIGNUM * r , const BIGNUM * a , const BIGNUM * b ) ;
 int BN_mul ( BIGNUM * r , const BIGNUM * a , const BIGNUM * b , BN_CTX * ctx ) ;
 int BN_sqr ( BIGNUM * r , const BIGNUM * a , BN_CTX * ctx ) ;
 void BN_set_negative ( BIGNUM * b , int n ) ;


 int BN_mod_add ( BIGNUM * r , const BIGNUM * a , const BIGNUM * b , const BIGNUM * m , BN_CTX * ctx ) ;
 int BN_mod_add_quick ( BIGNUM * r , const BIGNUM * a , const BIGNUM * b , const BIGNUM * m ) ;
 int BN_mod_sub ( BIGNUM * r , const BIGNUM * a , const BIGNUM * b , const BIGNUM * m , BN_CTX * ctx ) ;
 int BN_mod_sub_quick ( BIGNUM * r , const BIGNUM * a , const BIGNUM * b , const BIGNUM * m ) ;
 int BN_mod_mul ( BIGNUM * r , const BIGNUM * a , const BIGNUM * b , const BIGNUM * m , BN_CTX * ctx ) ;
 int BN_mod_sqr ( BIGNUM * r , const BIGNUM * a , const BIGNUM * m , BN_CTX * ctx ) ;
 int BN_mod_lshift1 ( BIGNUM * r , const BIGNUM * a , const BIGNUM * m , BN_CTX * ctx ) ;
 int BN_mod_lshift1_quick ( BIGNUM * r , const BIGNUM * a , const BIGNUM * m ) ;
 int BN_mod_lshift ( BIGNUM * r , const BIGNUM * a , int n , const BIGNUM * m , BN_CTX * ctx ) ;
 int BN_mod_lshift_quick ( BIGNUM * r , const BIGNUM * a , int n , const BIGNUM * m ) ;
 BN_ULONG BN_mod_word ( const BIGNUM * a , BN_ULONG w ) ;
 BN_ULONG BN_div_word ( BIGNUM * a , BN_ULONG w )
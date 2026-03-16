static inline int get_hash_algo ( const char * s , size_t n ) {
 static const struct {
 const char * name ;
 int algo ;
 }
 hashnames [ ] = {
 {
 "sha1" , GCRY_MD_SHA1 }
 , {
 "md5" , GCRY_MD_MD5 }
 , {
 "sha256" , GCRY_MD_SHA256 }
 , {
 "ripemd160" , GCRY_MD_RMD160 }
 , {
 "rmd160" , GCRY_MD_RMD160 }
 , {
 "sha384" , GCRY_MD_SHA384 }
 , {
 "sha512" , GCRY_MD_SHA512 }
 , {
 "sha224" , GCRY_MD_SHA224 }
 , {
 "md2" , GCRY_MD_MD2 }
 , {
 "md4" , GCRY_MD_MD4 }
 , {
 "tiger" , GCRY_MD_TIGER }
 , {
 "haval" , GCRY_MD_HAVAL }
 , {
 NULL , 0 }
 }
 ;
 int algo ;
 int i ;
 for ( i = 0 ;
 hashnames [ i ] . name ;
 i ++ ) {
 if ( strlen ( hashnames [ i ] . name ) == n && ! memcmp ( hashnames [ i ] . name , s , n ) ) break ;
 }
 if ( hashnames [ i ] . name ) algo = hashnames [ i ] . algo ;
 else {
 char * tmpname ;
 tmpname = gcry_malloc ( n + 1 ) ;
 if ( ! tmpname ) algo = 0 ;
 else {
 memcpy ( tmpname , s , n ) ;
 tmpname [ n ] = 0 ;
 algo = gcry_md_map_name ( tmpname ) ;
 gcry_free ( tmpname ) ;
 }
 }
 return algo ;
 }
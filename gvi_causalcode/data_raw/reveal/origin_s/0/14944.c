void aes_crypt_cbc ( aes_context * ctx , int mode , int length , unsigned char iv [ 16 ] , const unsigned char * input , unsigned char * output ) {
 int i ;
 unsigned char temp [ 16 ] ;

 if ( padlock_xcryptcbc ( ctx , mode , length , iv , input , output ) == 0 ) return ;
 }

 while ( length > 0 ) {
 memcpy ( temp , input , 16 ) ;
 aes_crypt_ecb ( ctx , mode , input , output ) ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) output [ i ] = ( unsigned char ) ( output [ i ] ^ iv [ i ] ) ;
 memcpy ( iv , temp , 16 ) ;
 input += 16 ;
 output += 16 ;
 length -= 16 ;
 }
 }
 else {
 while ( length > 0 ) {
 for ( i = 0 ;
 i < 16 ;
 i ++ ) output [ i ] = ( unsigned char ) ( input [ i ] ^ iv [ i ] ) ;
 aes_crypt_ecb ( ctx , mode , output , output ) ;
 memcpy ( iv , output , 16 ) ;
 input += 16 ;
 output += 16 ;
 length -= 16 ;
 }
 }
 }
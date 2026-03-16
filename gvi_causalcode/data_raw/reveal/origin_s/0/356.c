static inline int base_key_length ( const cipher_type_t * cipher , int key_length ) {
 switch ( cipher -> id ) {
 case AES_128_ICM : case AES_192_ICM : case AES_256_ICM : return key_length - 14 ;
 break ;
 case AES_128_GCM : return 16 ;
 break ;
 case AES_256_GCM : return 32 ;
 break ;
 default : return key_length ;
 break ;
 }
 }
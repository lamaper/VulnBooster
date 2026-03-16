int tls1_generate_master_secret ( SSL * s , unsigned char * out , unsigned char * p , int len ) {
 unsigned char buff [ SSL_MAX_MASTER_KEY_LENGTH ] ;
 const void * co = NULL , * so = NULL ;
 int col = 0 , sol = 0 ;


 co = s -> s3 -> client_opaque_prf_input ;
 col = s -> s3 -> server_opaque_prf_input_len ;
 so = s -> s3 -> server_opaque_prf_input ;
 sol = s -> s3 -> client_opaque_prf_input_len ;
 }


 BIO_dump_fp ( stderr , ( char * ) p , len ) ;
 fprintf ( stderr , "Client Random:\n" ) ;
 BIO_dump_fp ( stderr , ( char * ) s -> s3 -> client_random , SSL3_RANDOM_SIZE ) ;
 fprintf ( stderr , "Server Random:\n" ) ;
 BIO_dump_fp ( stderr , ( char * ) s -> s3 -> server_random , SSL3_RANDOM_SIZE ) ;
 fprintf ( stderr , "Master Secret:\n" ) ;
 BIO_dump_fp ( stderr , ( char * ) s -> session -> master_key , SSL3_MASTER_SECRET_SIZE ) ;


 }
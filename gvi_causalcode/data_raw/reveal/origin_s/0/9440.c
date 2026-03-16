int ssl_cert_type ( const X509 * x , const EVP_PKEY * pk ) {
 if ( pk == NULL && ( pk = X509_get0_pubkey ( x ) ) == NULL ) return - 1 ;
 switch ( EVP_PKEY_id ( pk ) ) {
 default : return - 1 ;
 case EVP_PKEY_RSA : return SSL_PKEY_RSA_ENC ;
 case EVP_PKEY_DSA : return SSL_PKEY_DSA_SIGN ;


 case NID_id_GostR3410_2012_256 : return SSL_PKEY_GOST12_256 ;
 case NID_id_GostR3410_2012_512 : return SSL_PKEY_GOST12_512 ;

 }
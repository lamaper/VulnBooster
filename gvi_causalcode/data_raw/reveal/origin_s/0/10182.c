int PEM_write_ ## name ( FILE * fp , type * x ) ;







 int PEM_get_EVP_CIPHER_INFO ( char * header , EVP_CIPHER_INFO * cipher ) ;
 int PEM_do_header ( EVP_CIPHER_INFO * cipher , unsigned char * data , long * len , pem_password_cb * callback , void * u ) ;
 int PEM_read_bio ( BIO * bp , char * * name , char * * header , unsigned char * * data , long * len ) ;

 int PEM_bytes_read_bio_secmem ( unsigned char * * pdata , long * plen , char * * pnm , const char * name , BIO * bp , pem_password_cb * cb , void * u ) ;
 int PEM_write_bio ( BIO * bp , const char * name , const char * hdr , const unsigned char * data , long len ) ;
 int PEM_bytes_read_bio ( unsigned char * * pdata , long * plen , char * * pnm , const char * name , BIO * bp , pem_password_cb * cb , void * u ) ;
 void * PEM_ASN1_read_bio ( d2i_of_void * d2i , const char * name , BIO * bp , void * * x , pem_password_cb * cb , void * u ) ;
 int PEM_ASN1_write_bio ( i2d_of_void * i2d , const char * name , BIO * bp , void * x , const EVP_CIPHER * enc , unsigned char * kstr , int klen , pem_password_cb * cb , void * u ) ;
 STACK_OF ( X509_INFO ) * PEM_X509_INFO_read_bio ( BIO * bp , STACK_OF ( X509_INFO ) * sk , pem_password_cb * cb , void * u ) ;
 int PEM_X509_INFO_write_bio ( BIO * bp , X509_INFO * xi , EVP_CIPHER * enc , unsigned char * kstr , int klen , pem_password_cb * cd , void * u ) ;

 int PEM_write ( FILE * fp , const char * name , const char * hdr , const unsigned char * data , long len ) ;
 void * PEM_ASN1_read ( d2i_of_void * d2i , const char * name , FILE * fp , void * * x , pem_password_cb * cb , void * u ) ;
 int PEM_ASN1_write ( i2d_of_void * i2d , const char * name , FILE * fp , void * x , const EVP_CIPHER * enc , unsigned char * kstr , int klen , pem_password_cb * callback , void * u ) ;
 STACK_OF ( X509_INFO ) * PEM_X509_INFO_read ( FILE * fp , STACK_OF ( X509_INFO ) * sk , pem_password_cb * cb , void * u ) ;

 int PEM_SignUpdate ( EVP_MD_CTX * ctx , unsigned char * d , unsigned int cnt ) ;
 int PEM_SignFinal ( EVP_MD_CTX * ctx , unsigned char * sigret , unsigned int * siglen , EVP_PKEY * pkey ) ;
 int PEM_def_callback ( char * buf , int num , int rwflag , void * userdata ) ;
 void PEM_proc_type ( char * buf , int type ) ;
 void PEM_dek_info ( char * buf , const char * type , int len , char * str ) ;

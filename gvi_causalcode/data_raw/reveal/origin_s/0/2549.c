static ossl_inline STACK_OF ( t1 ) * sk_ ## t1 ## _deep_copy ( const STACK_OF ( t1 ) * sk , sk_ ## t1 ## _copyfunc copyfunc , sk_ ## t1 ## _freefunc freefunc ) {
 return ( STACK_OF ( t1 ) * ) OPENSSL_sk_deep_copy ( ( const OPENSSL_STACK * ) sk , ( OPENSSL_sk_copyfunc ) copyfunc , ( OPENSSL_sk_freefunc ) freefunc ) ;
 }
 static ossl_inline sk_ ## t1 ## _compfunc sk_ ## t1 ## _set_cmp_func ( STACK_OF ( t1 ) * sk , sk_ ## t1 ## _compfunc compare ) {
 return ( sk_ ## t1 ## _compfunc ) OPENSSL_sk_set_cmp_func ( ( OPENSSL_STACK * ) sk , ( OPENSSL_sk_compfunc ) compare ) ;
 }

 typedef const char * OPENSSL_CSTRING ;
 DEFINE_SPECIAL_STACK_OF ( OPENSSL_STRING , char ) DEFINE_SPECIAL_STACK_OF_CONST ( OPENSSL_CSTRING , char ) typedef void * OPENSSL_BLOCK ;
 DEFINE_SPECIAL_STACK_OF ( OPENSSL_BLOCK , void )
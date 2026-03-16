void Init_ossl_x509name ( void ) {
 VALUE utf8str , ptrstr , ia5str , hash ;

 eOSSLError = rb_define_class_under ( mOSSL , "OpenSSLError" , rb_eStandardError ) ;
 mX509 = rb_define_module_under ( mOSSL , "X509" ) ;

 eX509NameError = rb_define_class_under ( mX509 , "NameError" , eOSSLError ) ;
 cX509Name = rb_define_class_under ( mX509 , "Name" , rb_cObject ) ;
 rb_include_module ( cX509Name , rb_mComparable ) ;
 rb_define_alloc_func ( cX509Name , ossl_x509name_alloc ) ;
 rb_define_method ( cX509Name , "initialize" , ossl_x509name_initialize , - 1 ) ;
 rb_define_copy_func ( cX509Name , ossl_x509name_initialize_copy ) ;
 rb_define_method ( cX509Name , "add_entry" , ossl_x509name_add_entry , - 1 ) ;
 rb_define_method ( cX509Name , "to_s" , ossl_x509name_to_s , - 1 ) ;
 rb_define_method ( cX509Name , "to_a" , ossl_x509name_to_a , 0 ) ;
 rb_define_method ( cX509Name , "cmp" , ossl_x509name_cmp , 1 ) ;
 rb_define_alias ( cX509Name , "<=>" , "cmp" ) ;
 rb_define_method ( cX509Name , "eql?" , ossl_x509name_eql , 1 ) ;
 rb_define_method ( cX509Name , "hash" , ossl_x509name_hash , 0 ) ;


 utf8str = INT2NUM ( V_ASN1_UTF8STRING ) ;
 ptrstr = INT2NUM ( V_ASN1_PRINTABLESTRING ) ;
 ia5str = INT2NUM ( V_ASN1_IA5STRING ) ;
 rb_define_const ( cX509Name , "DEFAULT_OBJECT_TYPE" , utf8str ) ;
 hash = rb_hash_new ( ) ;
 RHASH_SET_IFNONE ( hash , utf8str ) ;
 rb_hash_aset ( hash , rb_str_new2 ( "C" ) , ptrstr ) ;
 rb_hash_aset ( hash , rb_str_new2 ( "countryName" ) , ptrstr ) ;
 rb_hash_aset ( hash , rb_str_new2 ( "serialNumber" ) , ptrstr ) ;
 rb_hash_aset ( hash , rb_str_new2 ( "dnQualifier" ) , ptrstr ) ;
 rb_hash_aset ( hash , rb_str_new2 ( "DC" ) , ia5str ) ;
 rb_hash_aset ( hash , rb_str_new2 ( "domainComponent" ) , ia5str ) ;
 rb_hash_aset ( hash , rb_str_new2 ( "emailAddress" ) , ia5str ) ;
 rb_define_const ( cX509Name , "OBJECT_TYPE_TEMPLATE" , hash ) ;
 rb_define_const ( cX509Name , "COMPAT" , ULONG2NUM ( XN_FLAG_COMPAT ) ) ;
 rb_define_const ( cX509Name , "RFC2253" , ULONG2NUM ( XN_FLAG_RFC2253 ) ) ;
 rb_define_const ( cX509Name , "ONELINE" , ULONG2NUM ( XN_FLAG_ONELINE ) ) ;
 rb_define_const ( cX509Name , "MULTILINE" , ULONG2NUM ( XN_FLAG_MULTILINE ) ) ;
 }
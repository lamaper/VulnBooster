void name ## _free ( type * a ) ;


 TYPEDEF_I2D_OF ( type ) TYPEDEF_D2I2D_OF ( void ) ;





 int type ;
 union {
 char * ptr ;
 ASN1_BOOLEAN boolean ;
 ASN1_STRING * asn1_string ;
 ASN1_OBJECT * object ;
 ASN1_INTEGER * integer ;
 ASN1_ENUMERATED * enumerated ;
 ASN1_BIT_STRING * bit_string ;
 ASN1_OCTET_STRING * octet_string ;
 ASN1_PRINTABLESTRING * printablestring ;
 ASN1_T61STRING * t61string ;
 ASN1_IA5STRING * ia5string ;
 ASN1_GENERALSTRING * generalstring ;
 ASN1_BMPSTRING * bmpstring ;
 ASN1_UNIVERSALSTRING * universalstring ;
 ASN1_UTCTIME * utctime ;
 ASN1_GENERALIZEDTIME * generalizedtime ;
 ASN1_VISIBLESTRING * visiblestring ;
 ASN1_UTF8STRING * utf8string ;
 ASN1_STRING * set ;
 ASN1_STRING * sequence ;
 ASN1_VALUE * asn1_value ;
 }
 value ;
 }
 ASN1_TYPE ;
 DEFINE_STACK_OF ( ASN1_TYPE ) typedef STACK_OF ( ASN1_TYPE ) ASN1_SEQUENCE_ANY ;
 DECLARE_ASN1_ENCODE_FUNCTIONS_const ( ASN1_SEQUENCE_ANY , ASN1_SEQUENCE_ANY ) DECLARE_ASN1_ENCODE_FUNCTIONS_const ( ASN1_SEQUENCE_ANY , ASN1_SET_ANY ) typedef struct BIT_STRING_BITNAME_st {
 int bitnum ;
 const char * lname ;
 const char * sname ;
 }
 BIT_STRING_BITNAME ;

 void ASN1_TYPE_set ( ASN1_TYPE * a , int type , void * value ) ;
 int ASN1_TYPE_set1 ( ASN1_TYPE * a , int type , const void * value ) ;
 int ASN1_TYPE_cmp ( const ASN1_TYPE * a , const ASN1_TYPE * b ) ;
 ASN1_TYPE * ASN1_TYPE_pack_sequence ( const ASN1_ITEM * it , void * s , ASN1_TYPE * * t ) ;
 void * ASN1_TYPE_unpack_sequence ( const ASN1_ITEM * it , const ASN1_TYPE * t ) ;
 ASN1_OBJECT * ASN1_OBJECT_new ( void ) ;
 void ASN1_OBJECT_free ( ASN1_OBJECT * a ) ;
 int i2d_ASN1_OBJECT ( const ASN1_OBJECT * a , unsigned char * * pp ) ;
 ASN1_OBJECT * d2i_ASN1_OBJECT ( ASN1_OBJECT * * a , const unsigned char * * pp , long length ) ;
 DECLARE_ASN1_ITEM ( ASN1_OBJECT ) DEFINE_STACK_OF ( ASN1_OBJECT ) ASN1_STRING * ASN1_STRING_new ( void ) ;
 void ASN1_STRING_free ( ASN1_STRING * a ) ;
 void ASN1_STRING_clear_free ( ASN1_STRING * a ) ;
 int ASN1_STRING_copy ( ASN1_STRING * dst , const ASN1_STRING * str ) ;
 ASN1_STRING * ASN1_STRING_dup ( const ASN1_STRING * a ) ;
 ASN1_STRING * ASN1_STRING_type_new ( int type ) ;
 int ASN1_STRING_cmp ( const ASN1_STRING * a , const ASN1_STRING * b ) ;
 int ASN1_STRING_set ( ASN1_STRING * str , const void * data , int len ) ;
 void ASN1_STRING_set0 ( ASN1_STRING * str , void * data , int len ) ;
 int ASN1_STRING_length ( const ASN1_STRING * x ) ;
 void ASN1_STRING_length_set ( ASN1_STRING * x , int n ) ;
 int ASN1_STRING_type ( const ASN1_STRING * x ) ;
 DEPRECATEDIN_1_1_0 ( unsigned char * ASN1_STRING_data ( ASN1_STRING * x ) ) const unsigned char * ASN1_STRING_get0_data ( const ASN1_STRING * x ) ;
 DECLARE_ASN1_FUNCTIONS ( ASN1_BIT_STRING ) int ASN1_BIT_STRING_set ( ASN1_BIT_STRING * a , unsigned char * d , int length ) ;
 int ASN1_BIT_STRING_set_bit ( ASN1_BIT_STRING * a , int n , int value ) ;
 int ASN1_BIT_STRING_get_bit ( const ASN1_BIT_STRING * a , int n ) ;
 int ASN1_BIT_STRING_check ( const ASN1_BIT_STRING * a , const unsigned char * flags , int flags_len ) ;
 int ASN1_BIT_STRING_name_print ( BIO * out , ASN1_BIT_STRING * bs , BIT_STRING_BITNAME * tbl , int indent ) ;
 int ASN1_BIT_STRING_num_asc ( const char * name , BIT_STRING_BITNAME * tbl ) ;
 int ASN1_BIT_STRING_set_asc ( ASN1_BIT_STRING * bs , const char * name , int value , BIT_STRING_BITNAME * tbl ) ;
 DECLARE_ASN1_FUNCTIONS ( ASN1_INTEGER )
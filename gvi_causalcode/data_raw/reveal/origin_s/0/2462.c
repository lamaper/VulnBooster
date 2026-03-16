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

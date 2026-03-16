ASN1_TYPE * ossl_asn1_get_asn1type ( VALUE obj ) {
 ASN1_TYPE * ret ;
 VALUE value , rflag ;
 void * ptr ;
 void ( * free_func ) ( ) ;
 int tag , flag ;
 tag = ossl_asn1_default_tag ( obj ) ;
 value = ossl_asn1_get_value ( obj ) ;
 switch ( tag ) {
 case V_ASN1_BOOLEAN : ptr = ( void * ) ( VALUE ) obj_to_asn1bool ( value ) ;
 free_func = NULL ;
 break ;
 case V_ASN1_INTEGER : case V_ASN1_ENUMERATED : ptr = obj_to_asn1int ( value ) ;
 free_func = ASN1_INTEGER_free ;
 break ;
 case V_ASN1_BIT_STRING : rflag = rb_attr_get ( obj , sivUNUSED_BITS ) ;
 flag = NIL_P ( rflag ) ? - 1 : NUM2INT ( rflag ) ;
 ptr = obj_to_asn1bstr ( value , flag ) ;
 free_func = ASN1_BIT_STRING_free ;
 break ;
 case V_ASN1_NULL : ptr = obj_to_asn1null ( value ) ;
 free_func = ASN1_NULL_free ;
 break ;
 case V_ASN1_OCTET_STRING : case V_ASN1_UTF8STRING : case V_ASN1_NUMERICSTRING : case V_ASN1_PRINTABLESTRING : case V_ASN1_T61STRING : case V_ASN1_VIDEOTEXSTRING : case V_ASN1_IA5STRING : case V_ASN1_GRAPHICSTRING : case V_ASN1_ISO64STRING : case V_ASN1_GENERALSTRING : case V_ASN1_UNIVERSALSTRING : case V_ASN1_BMPSTRING : ptr = obj_to_asn1str ( value ) ;
 free_func = ASN1_STRING_free ;
 break ;
 case V_ASN1_OBJECT : ptr = obj_to_asn1obj ( value ) ;
 free_func = ASN1_OBJECT_free ;
 break ;
 case V_ASN1_UTCTIME : ptr = obj_to_asn1utime ( value ) ;
 free_func = ASN1_TIME_free ;
 break ;
 case V_ASN1_GENERALIZEDTIME : ptr = obj_to_asn1gtime ( value ) ;
 free_func = ASN1_TIME_free ;
 break ;
 case V_ASN1_SET : case V_ASN1_SEQUENCE : ptr = obj_to_asn1derstr ( obj ) ;
 free_func = ASN1_STRING_free ;
 break ;
 default : ossl_raise ( eASN1Error , "unsupported ASN.1 type" ) ;
 }
 if ( ! ( ret = OPENSSL_malloc ( sizeof ( ASN1_TYPE ) ) ) ) {
 if ( free_func ) free_func ( ptr ) ;
 ossl_raise ( eASN1Error , "ASN1_TYPE alloc failure" ) ;
 }
 memset ( ret , 0 , sizeof ( ASN1_TYPE ) ) ;
 ASN1_TYPE_set ( ret , tag , ptr ) ;
 return ret ;
 }
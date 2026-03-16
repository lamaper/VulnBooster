static VALUE ossl_asn1_ ## klass ( int argc , VALUE * argv , VALUE self ) \ {
 return rb_funcall3 ( cASN1 ## klass , rb_intern ( "new" ) , argc , argv ) ;
 }
 OSSL_ASN1_IMPL_FACTORY_METHOD ( Boolean ) OSSL_ASN1_IMPL_FACTORY_METHOD ( Integer ) OSSL_ASN1_IMPL_FACTORY_METHOD ( Enumerated ) OSSL_ASN1_IMPL_FACTORY_METHOD ( BitString ) OSSL_ASN1_IMPL_FACTORY_METHOD ( OctetString ) OSSL_ASN1_IMPL_FACTORY_METHOD ( UTF8String ) OSSL_ASN1_IMPL_FACTORY_METHOD ( NumericString ) OSSL_ASN1_IMPL_FACTORY_METHOD ( PrintableString )
static Node * simplify_boolean_equality ( Oid opno , List * args ) {
 Node * leftop ;
 Node * rightop ;
 Assert ( list_length ( args ) == 2 ) ;
 leftop = linitial ( args ) ;
 rightop = lsecond ( args ) ;
 if ( leftop && IsA ( leftop , Const ) ) {
 Assert ( ! ( ( Const * ) leftop ) -> constisnull ) ;
 if ( opno == BooleanEqualOperator ) {
 if ( DatumGetBool ( ( ( Const * ) leftop ) -> constvalue ) ) return rightop ;
 else return negate_clause ( rightop ) ;
 }
 else {
 if ( DatumGetBool ( ( ( Const * ) leftop ) -> constvalue ) ) return negate_clause ( rightop ) ;
 else return rightop ;
 }
 }
 if ( rightop && IsA ( rightop , Const ) ) {
 Assert ( ! ( ( Const * ) rightop ) -> constisnull ) ;
 if ( opno == BooleanEqualOperator ) {
 if ( DatumGetBool ( ( ( Const * ) rightop ) -> constvalue ) ) return leftop ;
 else return negate_clause ( leftop ) ;
 }
 else {
 if ( DatumGetBool ( ( ( Const * ) rightop ) -> constvalue ) ) return negate_clause ( leftop ) ;
 else return leftop ;
 }
 }
 return NULL ;
 }
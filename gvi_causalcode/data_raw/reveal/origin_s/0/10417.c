Oid getBaseType ( Oid typid ) {
 int32 typmod = - 1 ;
 return getBaseTypeAndTypmod ( typid , & typmod ) ;
 }
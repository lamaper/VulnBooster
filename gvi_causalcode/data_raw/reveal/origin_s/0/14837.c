static int lms_predict ( WmallDecodeCtx * s , int ich , int ilms ) {
 int pred = 0 , icoef ;
 int recent = s -> cdlms [ ich ] [ ilms ] . recent ;
 for ( icoef = 0 ;
 icoef < s -> cdlms [ ich ] [ ilms ] . order ;
 icoef ++ ) pred += s -> cdlms [ ich ] [ ilms ] . coefs [ icoef ] * s -> cdlms [ ich ] [ ilms ] . lms_prevvalues [ icoef + recent ] ;
 return pred ;
 }
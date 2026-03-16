static decNumber * decDecap ( decNumber * dn , Int drop ) {
 Unit * msu ;
 Int cut ;
 if ( drop >= dn -> digits ) {


 dn -> digits = 1 ;
 return dn ;
 }
 msu = dn -> lsu + D2U ( dn -> digits - drop ) - 1 ;
 cut = MSUDIGITS ( dn -> digits - drop ) ;
 if ( cut != DECDPUN ) * msu %= powers [ cut ] ;
 dn -> digits = decGetDigits ( dn -> lsu , msu - dn -> lsu + 1 ) ;
 return dn ;
 }
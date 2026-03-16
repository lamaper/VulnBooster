VALUE asn1time_to_time ( const ASN1_TIME * time ) {
 struct tm tm ;
 VALUE argv [ 6 ] ;
 int count ;
 if ( ! time || ! time -> data ) return Qnil ;
 memset ( & tm , 0 , sizeof ( struct tm ) ) ;
 switch ( time -> type ) {
 case V_ASN1_UTCTIME : count = sscanf ( ( const char * ) time -> data , "%2d%2d%2d%2d%2d%2dZ" , & tm . tm_year , & tm . tm_mon , & tm . tm_mday , & tm . tm_hour , & tm . tm_min , & tm . tm_sec ) ;
 if ( count == 5 ) {
 tm . tm_sec = 0 ;
 }
 else if ( count != 6 ) {
 ossl_raise ( rb_eTypeError , "bad UTCTIME format: \"%s\"" , time -> data ) ;
 }
 if ( tm . tm_year < 69 ) {
 tm . tm_year += 2000 ;
 }
 else {
 tm . tm_year += 1900 ;
 }
 break ;
 case V_ASN1_GENERALIZEDTIME : if ( sscanf ( ( const char * ) time -> data , "%4d%2d%2d%2d%2d%2dZ" , & tm . tm_year , & tm . tm_mon , & tm . tm_mday , & tm . tm_hour , & tm . tm_min , & tm . tm_sec ) != 6 ) {
 ossl_raise ( rb_eTypeError , "bad GENERALIZEDTIME format" ) ;
 }
 break ;
 default : rb_warning ( "unknown time format" ) ;
 return Qnil ;
 }
 argv [ 0 ] = INT2NUM ( tm . tm_year ) ;
 argv [ 1 ] = INT2NUM ( tm . tm_mon ) ;
 argv [ 2 ] = INT2NUM ( tm . tm_mday ) ;
 argv [ 3 ] = INT2NUM ( tm . tm_hour ) ;
 argv [ 4 ] = INT2NUM ( tm . tm_min ) ;
 argv [ 5 ] = INT2NUM ( tm . tm_sec ) ;
 return rb_funcall2 ( rb_cTime , rb_intern ( "utc" ) , 6 , argv ) ;
 }
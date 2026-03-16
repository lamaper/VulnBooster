static int getfoghex ( _IO * io ) {
 int ch , val ;
 while ( isspace ( ch = getc ( io -> fog ) ) ) ;
 if ( isdigit ( ch ) ) val = ch - '0' ;
 else if ( ch >= 'A' && ch <= 'F' ) val = ch - 'A' + 10 ;
 else if ( ch >= 'a' && ch <= 'f' ) val = ch - 'a' + 10 ;
 else return ( EOF ) ;
 val <<= 4 ;
 while ( isspace ( ch = getc ( io -> fog ) ) ) ;
 if ( isdigit ( ch ) ) val |= ch - '0' ;
 else if ( ch >= 'A' && ch <= 'F' ) val |= ch - 'A' + 10 ;
 else if ( ch >= 'a' && ch <= 'f' ) val |= ch - 'a' + 10 ;
 else return ( EOF ) ;
 return ( val ) ;
 }
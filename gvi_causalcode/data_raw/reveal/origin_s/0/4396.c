static const char * html_replace ( char ch , char * buf ) {
 switch ( ch ) {
 case '<' : return "&lt;
" ;
 case '>' : return "&gt;
" ;
 case '"' : return "&quot;
" ;
 case '\'' : return "&#039;
" ;
 case '&' : return "&amp;
" ;
 default : break ;
 }
 buf [ 0 ] = ch ;
 buf [ 1 ] = '\0' ;
 return buf ;
 }
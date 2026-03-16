static int nextch ( IO * wrapper ) {
 int ch ;
 _IO * io = wrapper -> top ;
 static const char * foguvec [ ] = {
 "moveto " , "rlineto " , "rrcurveto " , " " , " " , "Cache " , "10 div setlinewidth " , "ShowInt " , " " , " " , " " , " " , "FillStroke " , " " , " " , "SetWid " , "100 mul add " , "togNS_ " , " " , "closepath " , " " , "SG " }
 ;
 while ( io != NULL ) {
 if ( io -> backedup != EOF ) {
 ch = io -> backedup ;
 io -> backedup = EOF ;
 return ( ch ) ;
 }
 else if ( io -> ps != NULL ) {
 if ( ( ch = getc ( io -> ps ) ) != EOF ) return ( ch ) ;
 }
 else if ( io -> fog != NULL ) {
 if ( io -> macro != NULL && * io -> macro != '\0' ) return ( * ( io -> macro ++ ) ) ;
 ch = getfoghex ( io ) ;
 if ( ch >= 233 ) {
 io -> macro = foguvec [ ch - 233 ] ;
 return ( * ( io -> macro ++ ) ) ;
 }
 else if ( ch != EOF && ch < 200 ) {
 sprintf ( io -> fogbuf , "%d " , ch - 100 ) ;
 io -> macro = io -> fogbuf ;
 return ( * ( io -> macro ++ ) ) ;
 }
 else if ( ch != EOF ) {
 sprintf ( io -> fogbuf , "%d %s " , ch - 233 + 17 , io -> fogns ? "2 exch exp 3 1 roll 100 mul add mul" : "100 mul add" ) ;
 io -> macro = io -> fogbuf ;
 return ( * ( io -> macro ++ ) ) ;
 }
 }
 else {
 if ( ( ch = * ( io -> macro ++ ) ) != '\0' ) return ( ch ) ;
 if ( -- io -> cnt > 0 ) {
 io -> macro = io -> start ;
 return ( nextch ( wrapper ) ) ;
 }
 }
 wrapper -> top = io -> prev ;
 if ( io -> isstopped ) wrapper -> endedstopped = true ;
 if ( io -> start != NULL ) free ( io -> start ) ;
 io -> start = NULL ;
 free ( io ) ;
 io = wrapper -> top ;
 }
 return ( EOF ) ;
 }
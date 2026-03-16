PyObject * PyString_FromFormatV ( const char * format , va_list vargs ) {
 va_list count ;
 Py_ssize_t n = 0 ;
 const char * f ;
 char * s ;
 PyObject * string ;




 * f ;
 f ++ ) {
 if ( * f == '%' ) {


 while ( * ++ f && * f != '%' && ! isalpha ( Py_CHARMASK ( * f ) ) ) ;
 if ( * f == 'l' ) {
 if ( f [ 1 ] == 'd' || f [ 1 ] == 'u' ) {
 ++ f ;
 }

 longlongflag = 1 ;
 f += 2 ;
 }

 else if ( * f == 'z' && ( f [ 1 ] == 'd' || f [ 1 ] == 'u' ) ) {
 ++ f ;
 }
 switch ( * f ) {
 case 'c' : ( void ) va_arg ( count , int ) ;
 case '%' : n ++ ;
 break ;
 case 'd' : case 'u' : case 'i' : case 'x' : ( void ) va_arg ( count , int ) ;

 else # endif n += 20 ;
 break ;
 case 's' : s = va_arg ( count , char * ) ;
 n += strlen ( s ) ;
 break ;
 case 'p' : ( void ) va_arg ( count , int ) ;
 n += 19 ;
 break ;
 default : n += strlen ( p ) ;
 goto expand ;
 }
 }
 else n ++ ;
 }
 expand : string = PyString_FromStringAndSize ( NULL , n ) ;
 if ( ! string ) return NULL ;
 s = PyString_AsString ( string ) ;
 for ( f = format ;
 * f ;
 f ++ ) {
 if ( * f == '%' ) {
 const char * p = f ++ ;
 Py_ssize_t i ;
 int longflag = 0 ;


 n = 0 ;
 while ( isdigit ( Py_CHARMASK ( * f ) ) ) n = ( n * 10 ) + * f ++ - '0' ;
 if ( * f == '.' ) {
 f ++ ;
 n = 0 ;
 while ( isdigit ( Py_CHARMASK ( * f ) ) ) n = ( n * 10 ) + * f ++ - '0' ;
 }
 while ( * f && * f != '%' && ! isalpha ( Py_CHARMASK ( * f ) ) ) f ++ ;
 if ( * f == 'l' ) {
 if ( f [ 1 ] == 'd' || f [ 1 ] == 'u' ) {
 longflag = 1 ;
 ++ f ;
 }

 longlongflag = 1 ;
 f += 2 ;
 }

 else if ( * f == 'z' && ( f [ 1 ] == 'd' || f [ 1 ] == 'u' ) ) {
 size_tflag = 1 ;
 ++ f ;
 }
 switch ( * f ) {
 case 'c' : * s ++ = va_arg ( vargs , int ) ;
 break ;
 case 'd' : if ( longflag ) sprintf ( s , "%ld" , va_arg ( vargs , long ) ) ;


 else sprintf ( s , "%d" , va_arg ( vargs , int ) ) ;
 s += strlen ( s ) ;
 break ;
 case 'u' : if ( longflag ) sprintf ( s , "%lu" , va_arg ( vargs , unsigned long ) ) ;


 else sprintf ( s , "%u" , va_arg ( vargs , unsigned int ) ) ;
 s += strlen ( s ) ;
 break ;
 case 'i' : sprintf ( s , "%i" , va_arg ( vargs , int ) ) ;
 s += strlen ( s ) ;
 break ;
 case 'x' : sprintf ( s , "%x" , va_arg ( vargs , int ) ) ;
 s += strlen ( s ) ;
 break ;
 case 's' : p = va_arg ( vargs , char * ) ;
 i = strlen ( p ) ;
 if ( n > 0 && i > n ) i = n ;
 Py_MEMCPY ( s , p , i ) ;
 s += i ;
 break ;
 case 'p' : sprintf ( s , "%p" , va_arg ( vargs , void * ) ) ;
 if ( s [ 1 ] == 'X' ) s [ 1 ] = 'x' ;
 else if ( s [ 1 ] != 'x' ) {
 memmove ( s + 2 , s , strlen ( s ) + 1 ) ;
 s [ 0 ] = '0' ;
 s [ 1 ] = 'x' ;
 }
 s += strlen ( s ) ;
 break ;
 case '%' : * s ++ = '%' ;
 break ;
 default : strcpy ( s , p ) ;
 s += strlen ( s ) ;
 goto end ;
 }
 }
 else * s ++ = * f ;
 }
 end : if ( _PyString_Resize ( & string , s - PyString_AS_STRING ( string ) ) ) return NULL ;
 return string ;
 }
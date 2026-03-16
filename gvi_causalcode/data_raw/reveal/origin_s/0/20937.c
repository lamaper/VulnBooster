void check_comment_sanity ( int * e ) {
 if ( ! strcmp ( comment_author , "" ) ) error [ ( * e ) ++ ] . message = strdup ( "Author name was not entered" ) ;
 if ( ! strcmp ( comment_data , "" ) ) error [ ( * e ) ++ ] . message = strdup ( "Comment data was not entered" ) ;
 return ;
 }
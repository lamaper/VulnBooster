inline bool is_response_body_precluded ( HTTPStatus status_code , int method ) {
 if ( ( method == HTTP_WKSIDX_HEAD ) || is_response_body_precluded ( status_code ) ) {
 return true ;
 }
 else {
 return false ;
 }
 }
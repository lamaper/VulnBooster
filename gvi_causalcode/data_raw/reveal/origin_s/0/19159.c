inline bool is_response_body_precluded ( HTTPStatus status_code ) {
 if ( ( ( status_code != HTTP_STATUS_OK ) && ( ( status_code == HTTP_STATUS_NOT_MODIFIED ) || ( ( status_code < HTTP_STATUS_OK ) && ( status_code >= HTTP_STATUS_CONTINUE ) ) || ( status_code == HTTP_STATUS_NO_CONTENT ) ) ) ) {
 return true ;
 }
 else {
 return false ;
 }
 }
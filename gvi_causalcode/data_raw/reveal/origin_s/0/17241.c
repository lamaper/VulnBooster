TEST_F ( TemplateURLTest , GoogleBaseSuggestURL ) {
 static const struct {
 const char * const base_url ;
 const char * const base_suggest_url ;
 }
 data [ ] = {
 {
 "http://google.com/" , "http://google.com/complete/" , }
 , {
 "http://www.google.com/" , "http://www.google.com/complete/" , }
 , {
 "http://www.google.co.uk/" , "http://www.google.co.uk/complete/" , }
 , {
 "http://www.google.com.by/" , "http://www.google.com.by/complete/" , }
 , {
 "http://google.com/intl/xx/" , "http://google.com/complete/" , }
 , }
 ;
 for ( size_t i = 0 ;
 i < arraysize ( data ) ;
 ++ i ) CheckSuggestBaseURL ( data [ i ] . base_url , data [ i ] . base_suggest_url ) ;
 }
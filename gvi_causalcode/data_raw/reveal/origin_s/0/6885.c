TEST_F ( TemplateURLTest , IsSearchResults ) {
 TemplateURLData data ;
 data . SetURL ( "http://bar/search?q={
searchTerms}
" ) ;
 data . instant_url = "http://bar/instant#q={
searchTerms}
" ;
 data . new_tab_url = "http://barewtab" ;
 data . alternate_urls . push_back ( "http://bar/?q={
searchTerms}
" ) ;
 data . alternate_urls . push_back ( "http://bar/#q={
searchTerms}
" ) ;
 data . alternate_urls . push_back ( "http://bar/search#q{
searchTerms}
" ) ;
 data . alternate_urls . push_back ( "http://bar/webhp#q={
searchTerms}
" ) ;
 TemplateURL search_provider ( data ) ;
 const struct {
 const char * const url ;
 bool result ;
 }
 url_data [ ] = {
 {
 "http://bar/search?q=foo&oq=foo" , true , }
 , {
 "http://bar/?q=foo&oq=foo" , true , }
 , {
 "http://bar/#output=search&q=foo&oq=foo" , true , }
 , {
 "http://bar/webhp#q=foo&oq=foo" , true , }
 , {
 "http://bar/#q=foo&oq=foo" , true , }
 , {
 "http://bar/?ext=foo&q=foo#ref=bar" , true , }
 , {
 "http://bar/url?url=http://www.foo.com/&q=foo#ref=bar" , false , }
 , {
 "http://bar/" , false , }
 , {
 "http://foo/" , false , }
 , {
 "http://barewtab" , false , }
 , }
 ;
 for ( size_t i = 0 ;
 i < arraysize ( url_data ) ;
 ++ i ) {
 EXPECT_EQ ( url_data [ i ] . result , search_provider . IsSearchURL ( GURL ( url_data [ i ] . url ) , search_terms_data_ ) ) ;
 }
 }
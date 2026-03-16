TEST_F ( TemplateURLTest , GetURLNoSuggestionsURL ) {
 TemplateURLData data ;
 data . SetURL ( "http://google.com/?q={
searchTerms}
" ) ;
 data . instant_url = "http://google.com/instant#q={
searchTerms}
" ;
 data . alternate_urls . push_back ( "http://google.com/alt?q={
searchTerms}
" ) ;
 data . alternate_urls . push_back ( "{
google:baseURL}
/alt/#q={
searchTerms}
" ) ;
 TemplateURL url ( data ) ;
 const std : : vector < TemplateURLRef > & url_refs = url . url_refs ( ) ;
 ASSERT_EQ ( 3U , url_refs . size ( ) ) ;
 EXPECT_EQ ( "http://google.com/alt?q={
searchTerms}
" , url_refs [ 0 ] . GetURL ( ) ) ;
 EXPECT_EQ ( "{
google:baseURL}
/alt/#q={
searchTerms}
" , url_refs [ 1 ] . GetURL ( ) ) ;
 EXPECT_EQ ( "http://google.com/?q={
searchTerms}
" , url_refs [ 2 ] . GetURL ( ) ) ;
 }
TEST_F ( TemplateURLTest , GenerateSearchURL ) {
 struct GenerateSearchURLCase {
 const char * test_name ;
 const char * url ;
 const char * expected ;
 }
 generate_url_cases [ ] = {
 {
 "invalid URL" , "foo{
searchTerms}
" , "" }
 , {
 "URL with no replacements" , "http://foo/" , "http://foo/" }
 , {
 "basic functionality" , "http://foo/{
searchTerms}
" , "http://foo/blah.blah.blah.blah.blah" }
 }
 ;
 for ( size_t i = 0 ;
 i < arraysize ( generate_url_cases ) ;
 ++ i ) {
 TemplateURLData data ;
 data . SetURL ( generate_url_cases [ i ] . url ) ;
 TemplateURL t_url ( data ) ;
 EXPECT_EQ ( t_url . GenerateSearchURL ( search_terms_data_ ) . spec ( ) , generate_url_cases [ i ] . expected ) << generate_url_cases [ i ] . test_name << " failed." ;
 }
 }
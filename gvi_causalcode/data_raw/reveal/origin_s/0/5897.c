TEST_F ( TemplateURLTest , SearchTermKeyLocation ) {
 struct TestData {
 const std : : string url ;
 const url : : Parsed : : ComponentType location ;
 const std : : string path ;
 size_t position_in_path ;
 }
 test_data [ ] = {
 {
 "http://blah/{
searchTerms}
/" , url : : Parsed : : PATH , "//" , 1 }
 , {
 "http://blah/{
searchTerms}
" , url : : Parsed : : PATH , "/" , 1 }
 , {
 "http://blah/begin/{
searchTerms}
/end" , url : : Parsed : : PATH , "/begin//end" , 7 }
 , {
 "http://blah/?foo=bar&q={
searchTerms}
&b=x" , url : : Parsed : : QUERY , "/" , std : : string : : npos }
 , {
 "http://blah/?foo=bar#x={
searchTerms}
&b=x" , url : : Parsed : : REF , "/" , std : : string : : npos }
 , {
 "http://blah/?foo=bar#x=012345678901234&a=b&{
searchTerms}
=x" , url : : Parsed : : QUERY , std : : string ( ) , std : : string : : npos }
 , {
 "http://blah/{
searchTerms}
?q={
searchTerms}
" , url : : Parsed : : QUERY , "" , std : : string : : npos }
 , {
 "http://blah/{
searchTerms}

searchTerms}
" , url : : Parsed : : QUERY , "" , std : : string : : npos }
 , {
 "http://blah/?q={
searchTerms}

searchTerms}
" , url : : Parsed : : QUERY , "" , std : : string : : npos }
 , }
 ;
 for ( size_t i = 0 ;
 i < arraysize ( test_data ) ;
 ++ i ) {
 TemplateURLData data ;
 data . SetURL ( test_data [ i ] . url ) ;
 TemplateURL url ( data ) ;
 EXPECT_EQ ( test_data [ i ] . location , url . url_ref ( ) . GetSearchTermKeyLocation ( search_terms_data_ ) ) ;
 EXPECT_EQ ( test_data [ i ] . path , url . url_ref ( ) . GetPath ( search_terms_data_ ) ) ;
 EXPECT_EQ ( test_data [ i ] . position_in_path , url . url_ref ( ) . GetSearchTermPositionInPath ( search_terms_data_ ) ) ;
 }
 }
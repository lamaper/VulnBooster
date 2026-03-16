TEST_F ( TemplateURLTest , GetURLOnlyOneURL ) {
 TemplateURLData data ;
 data . SetURL ( "http://www.google.co.uk/" ) ;
 TemplateURL url ( data ) ;
 const std : : vector < TemplateURLRef > & url_refs = url . url_refs ( ) ;
 ASSERT_EQ ( 1U , url_refs . size ( ) ) ;
 EXPECT_EQ ( "http://www.google.co.uk/" , url_refs [ 0 ] . GetURL ( ) ) ;
 }
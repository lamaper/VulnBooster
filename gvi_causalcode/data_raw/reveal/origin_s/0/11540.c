TEST_F ( OmniboxEditTest , AdjustTextForCopy ) {
 struct Data {
 const char * perm_text ;
 const int sel_start ;
 const bool is_all_selected ;
 const char * input ;
 const char * expected_output ;
 const bool write_url ;
 const char * expected_url ;
 }
 input [ ] = {
 {
 "a.de/b" , 0 , true , "a.de/b" , "http://a.de/b" , true , "http://a.de/b" , }
 , {
 "a.de/b" , 0 , false , "a.de/" , "http://a.de/" , true , "http://a.de/" }
 , {
 "a.de/b" , 0 , false , "a.de/c" , "http://a.de/c" , true , "http://a.de/c" }
 , {
 "a.de/b" , 0 , false , "a.com/b" , "a.com/b" , false , "" }
 , {
 "a.de/b" , 1 , false , "a.de/b" , "a.de/b" , false , "" }
 , {
 "a.de/" , 0 , false , "a.d" , "a.d" , false , "" }
 , {
 "https://a.com/" , 0 , false , "a.com/" , "a.com/" , false , "" }
 , {
 "a.de/" , 0 , false , "a.de.com/" , "a.de.com/" , false , "" }
 , {
 "a.de/" , 0 , false , "http://a.de/" , "http://a.de/" , true , "http://a.de/" }
 , {
 "b/foo" , 0 , true , "b/foo" , "http://b/foo" , true , "http://b/foo" }
 , {
 "www.google.com/search?" , 0 , false , "foo" , "foo" , false , "" }
 , }
 ;
 for ( size_t i = 0 ;
 i < arraysize ( input ) ;
 ++ i ) {
 toolbar_model ( ) -> set_text ( base : : ASCIIToUTF16 ( input [ i ] . perm_text ) ) ;
 model ( ) -> UpdatePermanentText ( ) ;
 base : : string16 result = base : : ASCIIToUTF16 ( input [ i ] . input ) ;
 GURL url ;
 bool write_url ;
 model ( ) -> AdjustTextForCopy ( input [ i ] . sel_start , input [ i ] . is_all_selected , & result , & url , & write_url ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( input [ i ] . expected_output ) , result ) << "@: " << i ;
 EXPECT_EQ ( input [ i ] . write_url , write_url ) << " @" << i ;
 if ( write_url ) EXPECT_EQ ( input [ i ] . expected_url , url . spec ( ) ) << " @" << i ;
 }
 }
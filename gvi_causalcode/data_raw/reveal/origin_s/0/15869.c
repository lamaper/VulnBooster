TEST ( AutocompleteMatchTest , Duplicates ) {
 struct DuplicateCases {
 const wchar_t * input ;
 const std : : string url1 ;
 const std : : string url2 ;
 const bool expected_duplicate ;
 }
 cases [ ] = {
 {
 L"g" , "http://www.google.com/" , "https://www.google.com/" , true }
 , {
 L"g" , "http://www.google.com/" , "http://www.google.com" , true }
 , {
 L"g" , "http://google.com/" , "http://www.google.com/" , true }
 , {
 L"g" , "http://www.google.com/" , "HTTP://www.GOOGLE.com/" , true }
 , {
 L"g" , "http://www.google.com/" , "http://www.google.com" , true }
 , {
 L"g" , "https://www.google.com/" , "http://google.com" , true }
 , {
 L"g" , "http://www.google.com/" , "wss://www.google.com/" , false }
 , {
 L"g" , "http://www.google.com/1" , "http://www.google.com/1/" , false }
 , {
 L"g" , "http://www.google.com/" , "http://www.google.com/1" , false }
 , {
 L"g" , "http://www.google.com/" , "http://www.goo.com/" , false }
 , {
 L"g" , "http://www.google.com/" , "http://w2.google.com/" , false }
 , {
 L"g" , "http://www.google.com/" , "http://m.google.com/" , false }
 , {
 L"g" , "http://www.google.com/" , "http://www.google.com/?foo" , false }
 , {
 L"http://g" , "http://google.com/" , "https://google.com/" , false }
 , {
 L"http://g" , "http://blah.com/" , "https://blah.com/" , true }
 , {
 L"http://g" , "http://google.com/1" , "https://google.com/1" , false }
 , {
 L"http://g hello" , "http://google.com/" , "https://google.com/" , false }
 , {
 L"hello http://g" , "http://google.com/" , "https://google.com/" , false }
 , {
 L"hello http://g" , "http://blah.com/" , "https://blah.com/" , true }
 , {
 L"http://b http://g" , "http://google.com/" , "https://google.com/" , false }
 , {
 L"http://b http://g" , "http://blah.com/" , "https://blah.com/" , false }
 , {
 L"x" , "http://xn--1lq90ic7f1rc.cn/" , "https://xn--1lq90ic7f1rc.cn/" , true }
 , {
 L"http://\x5317 x" , "http://xn--1lq90ic7f1rc.cn/" , "https://xn--1lq90ic7f1rc.cn/" , false }
 , {
 L"http://\x89c6 x" , "http://xn--1lq90ic7f1rc.cn/" , "https://xn--1lq90ic7f1rc.cn/" , true }
 , }
 ;
 for ( size_t i = 0 ;
 i < arraysize ( cases ) ;
 ++ i ) {
 SCOPED_TRACE ( "input=" + base : : WideToUTF8 ( cases [ i ] . input ) + " url1=" + cases [ i ] . url1 + " url2=" + cases [ i ] . url2 ) ;
 AutocompleteInput input ( base : : WideToUTF16 ( cases [ i ] . input ) , base : : string16 : : npos , std : : string ( ) , GURL ( ) , metrics : : OmniboxEventProto : : INVALID_SPEC , false , false , true , true , false , TestSchemeClassifier ( ) ) ;
 AutocompleteMatch m1 ( nullptr , 100 , false , AutocompleteMatchType : : URL_WHAT_YOU_TYPED ) ;
 m1 . destination_url = GURL ( cases [ i ] . url1 ) ;
 m1 . ComputeStrippedDestinationURL ( input , nullptr ) ;
 AutocompleteMatch m2 ( nullptr , 100 , false , AutocompleteMatchType : : URL_WHAT_YOU_TYPED ) ;
 m2 . destination_url = GURL ( cases [ i ] . url2 ) ;
 m2 . ComputeStrippedDestinationURL ( input , nullptr ) ;
 EXPECT_EQ ( cases [ i ] . expected_duplicate , AutocompleteMatch : : DestinationsEqual ( m1 , m2 ) ) ;
 }
 }
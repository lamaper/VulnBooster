TEST ( URLFixerTest , FixupURL ) {
 for ( size_t i = 0 ;
 i < arraysize ( fixup_cases ) ;
 ++ i ) {
 FixupCase value = fixup_cases [ i ] ;
 EXPECT_EQ ( value . output , url_formatter : : FixupURL ( value . input , "" ) . possibly_invalid_spec ( ) ) << "input: " << value . input ;
 }
 FixupCase tld_cases [ ] = {
 {
 "somedomainthatwillnotbeagtld" , "http://www.somedomainthatwillnotbeagtld.com/" }
 , {
 "somedomainthatwillnotbeagtld." , "http://www.somedomainthatwillnotbeagtld.com/" }
 , {
 "somedomainthatwillnotbeagtld.." , "http://www.somedomainthatwillnotbeagtld.com/" }
 , {
 ".somedomainthatwillnotbeagtld" , "http://www.somedomainthatwillnotbeagtld.com/" }
 , {
 "www.somedomainthatwillnotbeagtld" , "http://www.somedomainthatwillnotbeagtld.com/" }
 , {
 "somedomainthatwillnotbeagtld.com" , "http://somedomainthatwillnotbeagtld.com/" }
 , {
 "http://somedomainthatwillnotbeagtld" , "http://www.somedomainthatwillnotbeagtld.com/" }
 , {
 "..somedomainthatwillnotbeagtld.." , "http://www.somedomainthatwillnotbeagtld.com/" }
 , {
 "http://www.somedomainthatwillnotbeagtld" , "http://www.somedomainthatwillnotbeagtld.com/" }
 , {
 "9999999999999999" , "http://www.9999999999999999.com/" }
 , {
 "somedomainthatwillnotbeagtld/foo" , "http://www.somedomainthatwillnotbeagtld.com/foo" }
 , {
 "somedomainthatwillnotbeagtld.com/foo" , "http://somedomainthatwillnotbeagtld.com/foo" }
 , {
 "somedomainthatwillnotbeagtld/?foo=.com" , "http://www.somedomainthatwillnotbeagtld.com/?foo=.com" }
 , {
 "www.somedomainthatwillnotbeagtld/?foo=www." , "http://www.somedomainthatwillnotbeagtld.com/?foo=www." }
 , {
 "somedomainthatwillnotbeagtld.com/?foo=.com" , "http://somedomainthatwillnotbeagtld.com/?foo=.com" }
 , {
 "http://www.somedomainthatwillnotbeagtld.com" , "http://www.somedomainthatwillnotbeagtld.com/" }
 , {
 "somedomainthatwillnotbeagtld:123" , "http://www.somedomainthatwillnotbeagtld.com:123/" }
 , {
 "http://somedomainthatwillnotbeagtld:123" , "http://www.somedomainthatwillnotbeagtld.com:123/" }
 , }
 ;
 for ( size_t i = 0 ;
 i < arraysize ( tld_cases ) ;
 ++ i ) {
 FixupCase value = tld_cases [ i ] ;
 EXPECT_EQ ( value . output , url_formatter : : FixupURL ( value . input , "com" ) . possibly_invalid_spec ( ) ) ;
 }
 }
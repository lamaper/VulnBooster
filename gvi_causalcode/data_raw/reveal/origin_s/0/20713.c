TEST_F ( AutocompleteResultTest , CopyOldMatches ) {
 TestData last [ ] = {
 {
 0 , 1 , 1000 , true }
 , {
 1 , 1 , 500 , true }
 , }
 ;
 TestData current [ ] = {
 {
 2 , 1 , 400 , true }
 , }
 ;
 TestData result [ ] = {
 {
 2 , 1 , 400 , true }
 , {
 1 , 1 , 399 , true }
 , }
 ;
 ASSERT_NO_FATAL_FAILURE ( RunCopyOldMatchesTest ( last , arraysize ( last ) , current , arraysize ( current ) , result , arraysize ( result ) ) ) ;
 }
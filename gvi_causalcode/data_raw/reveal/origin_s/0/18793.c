TEST_F ( AutocompleteResultTest , CopyOldMatchesMultipleProviders ) {
 TestData last [ ] = {
 {
 0 , 1 , 1300 , false }
 , {
 1 , 2 , 1250 , true }
 , {
 2 , 1 , 1200 , false }
 , {
 3 , 2 , 1150 , true }
 , {
 4 , 1 , 1100 , false }
 , }
 ;
 TestData current [ ] = {
 {
 5 , 1 , 1000 , false }
 , {
 6 , 2 , 800 , true }
 , {
 7 , 1 , 500 , true }
 , }
 ;
 TestData result [ ] = {
 {
 6 , 2 , 800 , true }
 , {
 5 , 1 , 1000 , false }
 , {
 3 , 2 , 799 , true }
 , {
 7 , 1 , 500 , true }
 , {
 4 , 1 , 499 , false }
 , }
 ;
 ASSERT_NO_FATAL_FAILURE ( RunCopyOldMatchesTest ( last , arraysize ( last ) , current , arraysize ( current ) , result , arraysize ( result ) ) ) ;
 }
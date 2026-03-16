TEST_F ( AutocompleteResultTest , CopyOldMatchesAllowedToBeDefault ) {
 TestData last [ ] = {
 {
 0 , 1 , 1300 , true }
 , {
 1 , 1 , 1200 , true }
 , {
 2 , 1 , 1100 , true }
 , }
 ;
 TestData current [ ] = {
 {
 3 , 1 , 1000 , false }
 , {
 4 , 1 , 900 , true }
 , }
 ;
 TestData result [ ] = {
 {
 4 , 1 , 900 , true }
 , {
 3 , 1 , 1000 , false }
 , {
 2 , 1 , 899 , true }
 , }
 ;
 ASSERT_NO_FATAL_FAILURE ( RunCopyOldMatchesTest ( last , arraysize ( last ) , current , arraysize ( current ) , result , arraysize ( result ) ) ) ;
 }
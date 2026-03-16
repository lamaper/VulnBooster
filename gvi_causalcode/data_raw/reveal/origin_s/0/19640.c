TEST_F ( AutocompleteResultTest , CopyOldMatchesWithOneProviderWithoutDefault ) {
 TestData last [ ] = {
 {
 0 , 2 , 1250 , true }
 , {
 1 , 2 , 1150 , true }
 , {
 2 , 1 , 900 , false }
 , {
 3 , 1 , 800 , false }
 , {
 4 , 1 , 700 , false }
 , }
 ;
 TestData current [ ] = {
 {
 5 , 1 , 1000 , true }
 , {
 6 , 2 , 800 , false }
 , {
 7 , 1 , 500 , true }
 , }
 ;
 TestData result [ ] = {
 {
 5 , 1 , 1000 , true }
 , {
 1 , 2 , 999 , true }
 , {
 6 , 2 , 800 , false }
 , {
 4 , 1 , 700 , false }
 , {
 7 , 1 , 500 , true }
 , }
 ;
 ASSERT_NO_FATAL_FAILURE ( RunCopyOldMatchesTest ( last , arraysize ( last ) , current , arraysize ( current ) , result , arraysize ( result ) ) ) ;
 }
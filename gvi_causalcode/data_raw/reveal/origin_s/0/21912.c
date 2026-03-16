TEST_F ( FullscreenControllerStateUnitTest , TransitionsForEachState ) {
 AddTab ( browser ( ) , GURL ( url : : kAboutBlankURL ) ) ;
 TestTransitionsForEachState ( ) ;
 }
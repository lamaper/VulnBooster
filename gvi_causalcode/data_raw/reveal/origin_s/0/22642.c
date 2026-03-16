TEST_F ( UsbBlocklistTest , StringsWithNoValidEntries ) {
 SetDynamicBlocklist ( "" ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( "~!@#$%^&*()-_=+[]{
}
/*-" ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( ":" ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( "::" ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( "," ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( ",," ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( ",::," ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( "1:2:3" ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( "18D1:2:3000" ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( "0000:0x00:0000" ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( "0000: 0:0000" ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( "000g:0000:0000" ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 SetDynamicBlocklist ( "☯" ) ;
 EXPECT_EQ ( 0u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 }
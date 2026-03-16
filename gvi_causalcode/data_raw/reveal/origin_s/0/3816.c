TEST_F ( UsbBlocklistTest , StringsWithOneValidEntry ) {
 SetDynamicBlocklist ( "18D1:58F0:0101" ) ;
 EXPECT_EQ ( 1u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x18D1 , 0x58F0 , 0x0101 }
 ) ) ;
 SetDynamicBlocklist ( " 18D1:58F0:0200 " ) ;
 EXPECT_EQ ( 1u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x18D1 , 0x58F0 , 0x0200 }
 ) ) ;
 SetDynamicBlocklist ( ", 18D1:58F0:0201, " ) ;
 EXPECT_EQ ( 1u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x18D1 , 0x58F0 , 0x0201 }
 ) ) ;
 SetDynamicBlocklist ( "18D1:58F0:0202, 0000:1:0000" ) ;
 EXPECT_EQ ( 1u , list ( ) . GetDynamicEntryCountForTest ( ) ) ;
 EXPECT_TRUE ( list ( ) . IsExcluded ( {
 0x18D1 , 0x58F0 , 0x0202 }
 ) ) ;
 }
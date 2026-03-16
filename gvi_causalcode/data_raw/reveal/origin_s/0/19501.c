TEST_F ( MdDownloadsDOMHandlerTest , ClearAll ) {
 std : : vector < content : : DownloadItem * > downloads ;
 testing : : StrictMock < content : : MockDownloadItem > in_progress ;
 EXPECT_CALL ( in_progress , IsDangerous ( ) ) . WillOnce ( testing : : Return ( false ) ) ;
 EXPECT_CALL ( in_progress , GetState ( ) ) . WillOnce ( testing : : Return ( content : : DownloadItem : : IN_PROGRESS ) ) ;
 downloads . push_back ( & in_progress ) ;
 testing : : StrictMock < content : : MockDownloadItem > dangerous ;
 EXPECT_CALL ( dangerous , IsDangerous ( ) ) . WillOnce ( testing : : Return ( true ) ) ;
 EXPECT_CALL ( dangerous , Remove ( ) ) ;
 downloads . push_back ( & dangerous ) ;
 testing : : StrictMock < content : : MockDownloadItem > completed ;
 EXPECT_CALL ( completed , IsDangerous ( ) ) . WillOnce ( testing : : Return ( false ) ) ;
 EXPECT_CALL ( completed , GetState ( ) ) . WillOnce ( testing : : Return ( content : : DownloadItem : : COMPLETE ) ) ;
 EXPECT_CALL ( completed , GetId ( ) ) . WillOnce ( testing : : Return ( 1 ) ) ;
 EXPECT_CALL ( completed , UpdateObservers ( ) ) ;
 downloads . push_back ( & completed ) ;
 ASSERT_TRUE ( DownloadItemModel ( & completed ) . ShouldShowInShelf ( ) ) ;
 TestMdDownloadsDOMHandler handler ( manager ( ) , web_ui ( ) ) ;
 handler . RemoveDownloads ( downloads ) ;
 EXPECT_FALSE ( DownloadItemModel ( & completed ) . ShouldShowInShelf ( ) ) ;
 EXPECT_CALL ( * manager ( ) , GetDownload ( 1 ) ) . WillOnce ( testing : : Return ( & completed ) ) ;
 EXPECT_CALL ( completed , Remove ( ) ) ;
 handler . FinalizeRemovals ( ) ;
 }
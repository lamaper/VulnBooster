TEST ( ExtensionDetermineDownloadFilenameInternal , ExtensionDetermineDownloadFilenameInternal ) {
 std : : string winner_id ;
 base : : FilePath filename ;
 downloads : : FilenameConflictAction conflict_action = downloads : : FILENAME_CONFLICT_ACTION_UNIQUIFY ;
 WarningSet warnings ;
 warnings . clear ( ) ;
 ExtensionDownloadsEventRouter : : DetermineFilenameInternal ( base : : FilePath ( FILE_PATH_LITERAL ( "a" ) ) , downloads : : FILENAME_CONFLICT_ACTION_OVERWRITE , "suggester" , base : : Time : : Now ( ) , "" , base : : Time ( ) , & winner_id , & filename , & conflict_action , & warnings ) ;
 EXPECT_EQ ( "suggester" , winner_id ) ;
 EXPECT_EQ ( FILE_PATH_LITERAL ( "a" ) , filename . value ( ) ) ;
 EXPECT_EQ ( downloads : : FILENAME_CONFLICT_ACTION_OVERWRITE , conflict_action ) ;
 EXPECT_TRUE ( warnings . empty ( ) ) ;
 warnings . clear ( ) ;
 ExtensionDownloadsEventRouter : : DetermineFilenameInternal ( base : : FilePath ( FILE_PATH_LITERAL ( "b" ) ) , downloads : : FILENAME_CONFLICT_ACTION_PROMPT , "suggester" , base : : Time : : Now ( ) - base : : TimeDelta : : FromDays ( 1 ) , "incumbent" , base : : Time : : Now ( ) , & winner_id , & filename , & conflict_action , & warnings ) ;
 EXPECT_EQ ( "incumbent" , winner_id ) ;
 EXPECT_EQ ( FILE_PATH_LITERAL ( "a" ) , filename . value ( ) ) ;
 EXPECT_EQ ( downloads : : FILENAME_CONFLICT_ACTION_OVERWRITE , conflict_action ) ;
 EXPECT_FALSE ( warnings . empty ( ) ) ;
 EXPECT_EQ ( Warning : : kDownloadFilenameConflict , warnings . begin ( ) -> warning_type ( ) ) ;
 EXPECT_EQ ( "suggester" , warnings . begin ( ) -> extension_id ( ) ) ;
 warnings . clear ( ) ;
 ExtensionDownloadsEventRouter : : DetermineFilenameInternal ( base : : FilePath ( FILE_PATH_LITERAL ( "b" ) ) , downloads : : FILENAME_CONFLICT_ACTION_PROMPT , "suggester" , base : : Time : : Now ( ) , "incumbent" , base : : Time : : Now ( ) - base : : TimeDelta : : FromDays ( 1 ) , & winner_id , & filename , & conflict_action , & warnings ) ;
 EXPECT_EQ ( "suggester" , winner_id ) ;
 EXPECT_EQ ( FILE_PATH_LITERAL ( "b" ) , filename . value ( ) ) ;
 EXPECT_EQ ( downloads : : FILENAME_CONFLICT_ACTION_PROMPT , conflict_action ) ;
 EXPECT_FALSE ( warnings . empty ( ) ) ;
 EXPECT_EQ ( Warning : : kDownloadFilenameConflict , warnings . begin ( ) -> warning_type ( ) ) ;
 EXPECT_EQ ( "incumbent" , warnings . begin ( ) -> extension_id ( ) ) ;
 }
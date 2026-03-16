TEST_F ( MdDownloadsDOMHandlerTest , HandleSaveDownload ) {
 testing : : StrictMock < content : : MockDownloadItem > dangerous_file_type ;
 EXPECT_CALL ( dangerous_file_type , GetDangerType ( ) ) . WillRepeatedly ( testing : : Return ( content : : DOWNLOAD_DANGER_TYPE_DANGEROUS_FILE ) ) ;
 EXPECT_CALL ( dangerous_file_type , GetId ( ) ) . WillOnce ( testing : : Return ( uint32_t ( ) ) ) ;
 TestMdDownloadsDOMHandler handler ( manager ( ) , web_ui ( ) ) ;
 EXPECT_EQ ( 0 , handler . danger_prompt_count ( ) ) ;
 handler . SaveDownload ( & dangerous_file_type ) ;
 EXPECT_EQ ( 0 , handler . danger_prompt_count ( ) ) ;
 testing : : StrictMock < content : : MockDownloadItem > malicious_download ;
 EXPECT_CALL ( malicious_download , GetDangerType ( ) ) . WillRepeatedly ( testing : : Return ( content : : DOWNLOAD_DANGER_TYPE_DANGEROUS_URL ) ) ;
 handler . SaveDownload ( & malicious_download ) ;
 EXPECT_EQ ( 1 , handler . danger_prompt_count ( ) ) ;
 }
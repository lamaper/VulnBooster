TEST_F ( SoundContentSettingObserverTest , AudioMutingUpdatesWithNavigation ) {
 EXPECT_FALSE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 ChangeSoundContentSettingTo ( CONTENT_SETTING_BLOCK ) ;
 EXPECT_TRUE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 NavigateAndCommit ( GURL ( kURL2 ) ) ;
 EXPECT_FALSE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 NavigateAndCommit ( GURL ( kURL1 ) ) ;
 EXPECT_TRUE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 }
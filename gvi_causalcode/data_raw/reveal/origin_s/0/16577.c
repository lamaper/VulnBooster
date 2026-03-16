TEST_F ( SoundContentSettingObserverTest , AudioMutingUpdatesWithContentSetting ) {
 EXPECT_FALSE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 ChangeSoundContentSettingTo ( CONTENT_SETTING_BLOCK ) ;
 EXPECT_TRUE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 ChangeSoundContentSettingTo ( CONTENT_SETTING_ALLOW ) ;
 EXPECT_FALSE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 ChangeSoundContentSettingTo ( CONTENT_SETTING_DEFAULT ) ;
 EXPECT_FALSE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 ChangeDefaultSoundContentSettingTo ( CONTENT_SETTING_BLOCK ) ;
 EXPECT_TRUE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 ChangeSoundContentSettingTo ( CONTENT_SETTING_ALLOW ) ;
 EXPECT_FALSE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 ChangeSoundContentSettingTo ( CONTENT_SETTING_DEFAULT ) ;
 EXPECT_TRUE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 ChangeDefaultSoundContentSettingTo ( CONTENT_SETTING_ALLOW ) ;
 EXPECT_FALSE ( web_contents ( ) -> IsAudioMuted ( ) ) ;
 }
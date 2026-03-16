TEST_F ( ExtensionWelcomeNotificationTest , TimeExpiredNotification ) {
 StartPreferenceSyncing ( ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissed ) ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissedLocal ) ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationPreviouslyPoppedUp ) ) ;
 EXPECT_EQ ( GetInt64Pref ( prefs : : kWelcomeNotificationExpirationTimestamp ) , 0 ) ;
 EXPECT_TRUE ( task_runner ( ) -> GetPendingTasks ( ) . empty ( ) ) ;
 ShowChromeNowNotification ( ) ;
 base : : TimeDelta requested_show_time = base : : TimeDelta : : FromDays ( ExtensionWelcomeNotification : : kRequestedShowTimeDays ) ;
 EXPECT_EQ ( task_runner ( ) -> GetPendingTasks ( ) . size ( ) , 1U ) ;
 EXPECT_EQ ( task_runner ( ) -> NextPendingTaskDelay ( ) , requested_show_time ) ;
 EXPECT_EQ ( message_center ( ) -> add_notification_calls ( ) , 1 ) ;
 EXPECT_EQ ( message_center ( ) -> remove_notification_calls ( ) , 0 ) ;
 EXPECT_EQ ( message_center ( ) -> notifications_with_shown_as_popup ( ) , 0 ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissed ) ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissedLocal ) ) ;
 EXPECT_TRUE ( GetBooleanPref ( prefs : : kWelcomeNotificationPreviouslyPoppedUp ) ) ;
 EXPECT_EQ ( GetInt64Pref ( prefs : : kWelcomeNotificationExpirationTimestamp ) , ( GetStartTime ( ) + requested_show_time ) . ToInternalValue ( ) ) ;
 SetElapsedTime ( requested_show_time ) ;
 task_runner ( ) -> RunPendingTasks ( ) ;
 EXPECT_TRUE ( task_runner ( ) -> GetPendingTasks ( ) . empty ( ) ) ;
 EXPECT_EQ ( message_center ( ) -> add_notification_calls ( ) , 1 ) ;
 EXPECT_EQ ( message_center ( ) -> remove_notification_calls ( ) , 1 ) ;
 EXPECT_EQ ( message_center ( ) -> notifications_with_shown_as_popup ( ) , 0 ) ;
 EXPECT_FALSE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissed ) ) ;
 EXPECT_TRUE ( GetBooleanPref ( prefs : : kWelcomeNotificationDismissedLocal ) ) ;
 EXPECT_TRUE ( GetBooleanPref ( prefs : : kWelcomeNotificationPreviouslyPoppedUp ) ) ;
 EXPECT_EQ ( GetInt64Pref ( prefs : : kWelcomeNotificationExpirationTimestamp ) , ( GetStartTime ( ) + requested_show_time ) . ToInternalValue ( ) ) ;
 }
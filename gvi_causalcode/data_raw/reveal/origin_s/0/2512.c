TEST_F ( PromoResourceServiceTest , NotificationPromoCompatNoStringsTest ) {
 NotificationPromoTest promo_test ;
 promo_test . Init ( "{
" " \"ntp_notification_promo\": [" " {
" " \"date\":" " [" " {
" " \"start\":\"3 Aug 1999 9:26:06 GMT\"," " \"end\":\"$1\"" " }
" " ]," " \"grouping\":" " {
" " \"buckets\":1000," " \"segment\":200," " \"increment\":100," " \"increment_frequency\":3600," " \"increment_max\":400" " }
," " \"payload\":" " {
" " \"promo_message_short\":" " \"What do you think of Chrome?\"," " \"days_active\":7," " \"install_age_days\":21" " }
," " \"max_views\":30" " }
" " ]" "}
" , "What do you think of Chrome?" , 933672366 , 1000 , 200 , 100 , 3600 , 400 , 30 ) ;
 promo_test . InitPromoFromJson ( true ) ;
 promo_test . InitPromoFromJson ( false ) ;
 promo_test . TestInitFromPrefs ( ) ;
 }
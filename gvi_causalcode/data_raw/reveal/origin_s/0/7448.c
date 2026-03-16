TEST_F ( PromoResourceServiceTest , PromoServerURLTest ) {
 GURL promo_server_url = NotificationPromo : : PromoServerURL ( ) ;
 EXPECT_FALSE ( promo_server_url . is_empty ( ) ) ;
 EXPECT_TRUE ( promo_server_url . is_valid ( ) ) ;
 EXPECT_TRUE ( promo_server_url . SchemeIs ( url : : kHttpsScheme ) ) ;
 }
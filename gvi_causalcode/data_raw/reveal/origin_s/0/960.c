TEST_F ( TemplateURLTest , URLRefTestImageURLWithPOST ) {
 const char kInvalidPostParamsString [ ] = "unknown_template={
UnknownTemplate}
,bad_value=bad{
value}
," "{
google:sbiSource}
" ;
 const char kValidPostParamsString [ ] = "image_content={
google:imageThumbnail}
,image_url={
google:imageURL}
," "sbisrc={
google:imageSearchSource}
,language={
language}
,empty_param=," "constant_param=constant,width={
google:imageOriginalWidth}
" ;
 const char KImageSearchURL [ ] = "http://foo.com/sbi" ;
 TemplateURLData data ;
 data . image_url = KImageSearchURL ;
 data . image_url_post_params = kInvalidPostParamsString ;
 TemplateURL url_bad ( data ) ;
 ASSERT_FALSE ( url_bad . image_url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 const TemplateURLRef : : PostParams & bad_post_params = url_bad . image_url_ref ( ) . post_params_ ;
 ASSERT_EQ ( 2U , bad_post_params . size ( ) ) ;
 ExpectPostParamIs ( bad_post_params [ 0 ] , "unknown_template" , "{
UnknownTemplate}
" ) ;
 ExpectPostParamIs ( bad_post_params [ 1 ] , "bad_value" , "bad{
value}
" ) ;
 data . image_url_post_params = kValidPostParamsString ;
 TemplateURL url ( data ) ;
 ASSERT_TRUE ( url . image_url_ref ( ) . IsValid ( search_terms_data_ ) ) ;
 ASSERT_FALSE ( url . image_url_ref ( ) . SupportsReplacement ( search_terms_data_ ) ) ;
 TemplateURLRef : : SearchTermsArgs search_args ( ASCIIToUTF16 ( "X" ) ) ;
 search_args . image_thumbnail_content = "dummy-image-thumbnail" ;
 search_args . image_url = GURL ( "http://dummyimage.com/dummy.jpg" ) ;
 search_args . image_original_size = gfx : : Size ( 10 , 10 ) ;
 TestingSearchTermsData search_terms_data ( "http://X" ) ;
 GURL result ( url . image_url_ref ( ) . ReplaceSearchTerms ( search_args , search_terms_data ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( KImageSearchURL , result . spec ( ) ) ;
 TemplateURLRef : : PostContent post_content ;
 result = GURL ( url . image_url_ref ( ) . ReplaceSearchTerms ( search_args , search_terms_data , & post_content ) ) ;
 ASSERT_TRUE ( result . is_valid ( ) ) ;
 EXPECT_EQ ( KImageSearchURL , result . spec ( ) ) ;
 ASSERT_FALSE ( post_content . first . empty ( ) ) ;
 ASSERT_FALSE ( post_content . second . empty ( ) ) ;
 const TemplateURLRef : : Replacements & replacements = url . image_url_ref ( ) . replacements_ ;
 const TemplateURLRef : : PostParams & post_params = url . image_url_ref ( ) . post_params_ ;
 EXPECT_EQ ( 7U , post_params . size ( ) ) ;
 for ( TemplateURLRef : : PostParams : : const_iterator i = post_params . begin ( ) ;
 i != post_params . end ( ) ;
 ++ i ) {
 TemplateURLRef : : Replacements : : const_iterator j = replacements . begin ( ) ;
 for ( ;
 j != replacements . end ( ) ;
 ++ j ) {
 if ( j -> is_post_param && j -> index == static_cast < size_t > ( i - post_params . begin ( ) ) ) {
 switch ( j -> type ) {
 case TemplateURLRef : : GOOGLE_IMAGE_ORIGINAL_WIDTH : ExpectPostParamIs ( * i , "width" , base : : IntToString ( search_args . image_original_size . width ( ) ) ) ;
 break ;
 case TemplateURLRef : : GOOGLE_IMAGE_SEARCH_SOURCE : ExpectPostParamIs ( * i , "sbisrc" , search_terms_data . GoogleImageSearchSource ( ) ) ;
 break ;
 case TemplateURLRef : : GOOGLE_IMAGE_THUMBNAIL : ExpectPostParamIs ( * i , "image_content" , search_args . image_thumbnail_content , "image/jpeg" ) ;
 break ;
 case TemplateURLRef : : GOOGLE_IMAGE_URL : ExpectPostParamIs ( * i , "image_url" , search_args . image_url . spec ( ) ) ;
 break ;
 case TemplateURLRef : : LANGUAGE : ExpectPostParamIs ( * i , "language" , "en" ) ;
 break ;
 default : ADD_FAILURE ( ) ;
 }
 break ;
 }
 }
 if ( j != replacements . end ( ) ) continue ;
 if ( i -> name == "empty_param" ) ExpectPostParamIs ( * i , "empty_param" , std : : string ( ) ) ;
 else ExpectPostParamIs ( * i , "constant_param" , "constant" ) ;
 }
 }
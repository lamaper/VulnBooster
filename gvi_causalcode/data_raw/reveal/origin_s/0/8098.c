static int put_payload_parsing_info ( AVFormatContext * s , unsigned sendtime , unsigned duration , int nb_payloads , int padsize ) {
 ASFContext * asf = s -> priv_data ;
 AVIOContext * pb = s -> pb ;
 int ppi_size , i ;
 int64_t start = avio_tell ( pb ) ;
 int iLengthTypeFlags = ASF_PPI_LENGTH_TYPE_FLAGS ;
 padsize -= PACKET_HEADER_MIN_SIZE ;
 if ( asf -> multi_payloads_present ) padsize -- ;
 av_assert0 ( padsize >= 0 ) ;
 avio_w8 ( pb , ASF_PACKET_ERROR_CORRECTION_FLAGS ) ;
 for ( i = 0 ;
 i < ASF_PACKET_ERROR_CORRECTION_DATA_SIZE ;
 i ++ ) avio_w8 ( pb , 0x0 ) ;
 if ( asf -> multi_payloads_present ) iLengthTypeFlags |= ASF_PPI_FLAG_MULTIPLE_PAYLOADS_PRESENT ;
 if ( padsize > 0 ) {
 if ( padsize < 256 ) iLengthTypeFlags |= ASF_PPI_FLAG_PADDING_LENGTH_FIELD_IS_BYTE ;
 else iLengthTypeFlags |= ASF_PPI_FLAG_PADDING_LENGTH_FIELD_IS_WORD ;
 }
 avio_w8 ( pb , iLengthTypeFlags ) ;
 avio_w8 ( pb , ASF_PPI_PROPERTY_FLAGS ) ;
 if ( iLengthTypeFlags & ASF_PPI_FLAG_PADDING_LENGTH_FIELD_IS_WORD ) avio_wl16 ( pb , padsize - 2 ) ;
 if ( iLengthTypeFlags & ASF_PPI_FLAG_PADDING_LENGTH_FIELD_IS_BYTE ) avio_w8 ( pb , padsize - 1 ) ;
 avio_wl32 ( pb , sendtime ) ;
 avio_wl16 ( pb , duration ) ;
 if ( asf -> multi_payloads_present ) avio_w8 ( pb , nb_payloads | ASF_PAYLOAD_FLAGS ) ;
 ppi_size = avio_tell ( pb ) - start ;
 return ppi_size ;
 }
static guint8 fpdu_pad_length ( guint16 ulpdu_length ) {
 guint32 length = ulpdu_length + MPA_ULPDU_LENGTH_LEN ;
 return ( MPA_ALIGNMENT - ( length % MPA_ALIGNMENT ) ) % MPA_ALIGNMENT ;
 }
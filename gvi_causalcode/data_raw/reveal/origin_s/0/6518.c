static void xhci_calc_iso_kick ( XHCIState * xhci , XHCITransfer * xfer , XHCIEPContext * epctx , uint64_t mfindex ) {
 if ( xfer -> trbs [ 0 ] . control & TRB_TR_SIA ) {
 uint64_t asap = ( ( mfindex + epctx -> interval - 1 ) & ~ ( epctx -> interval - 1 ) ) ;
 if ( asap >= epctx -> mfindex_last && asap <= epctx -> mfindex_last + epctx -> interval * 4 ) {
 xfer -> mfindex_kick = epctx -> mfindex_last + epctx -> interval ;
 }
 else {
 xfer -> mfindex_kick = asap ;
 }
 }
 else {
 xfer -> mfindex_kick = ( ( xfer -> trbs [ 0 ] . control >> TRB_TR_FRAMEID_SHIFT ) & TRB_TR_FRAMEID_MASK ) << 3 ;
 xfer -> mfindex_kick |= mfindex & ~ 0x3fff ;
 if ( xfer -> mfindex_kick + 0x100 < mfindex ) {
 xfer -> mfindex_kick += 0x4000 ;
 }
 }
 }
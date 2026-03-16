void ff_aac_coder_init_mips(AACEncContext *c) {


    AACCoefficientsEncoder *e = c->coder;

    int option = c->options.aac_coder;



    if (option == 2) {

        e->quantize_and_encode_band = quantize_and_encode_band_mips;

        e->encode_window_bands_info = codebook_trellis_rate;


        e->search_for_quantizers    = search_for_quantizers_twoloop;


    }


    e->search_for_ms            = search_for_ms_mips;



}

static int decode_5(SANMVideoContext *ctx)

{


    uint16_t *frm;

    int npixels;


    uint8_t *dst = (uint8_t*)ctx->frm0;



    if (rle_decode(ctx, dst, ctx->buf_size))

        return AVERROR_INVALIDDATA;


    npixels = ctx->npixels;

    frm = ctx->frm0;

    while (npixels--)

        *frm++ = av_bswap16(*frm);




    return 0;

}

static enum AVPixelFormat get_format(HEVCContext *s, const HEVCSPS *sps)

{


    enum AVPixelFormat pix_fmts[HWACCEL_MAX + 2], *fmt = pix_fmts;



    switch (sps->pix_fmt) {

    case AV_PIX_FMT_YUV420P:

    case AV_PIX_FMT_YUVJ420P:


        *fmt++ = AV_PIX_FMT_DXVA2_VLD;



        *fmt++ = AV_PIX_FMT_D3D11VA_VLD;



        *fmt++ = AV_PIX_FMT_VAAPI;



        *fmt++ = AV_PIX_FMT_VDPAU;


        break;

    case AV_PIX_FMT_YUV420P10:


        *fmt++ = AV_PIX_FMT_DXVA2_VLD;



        *fmt++ = AV_PIX_FMT_D3D11VA_VLD;



        *fmt++ = AV_PIX_FMT_VAAPI;


        break;

    }



    *fmt++ = sps->pix_fmt;

    *fmt = AV_PIX_FMT_NONE;



    return ff_thread_get_format(s->avctx, pix_fmts);

}

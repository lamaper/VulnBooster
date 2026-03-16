static av_cold int vsink_init(AVFilterContext *ctx, const char *args, void *opaque)

{

    BufferSinkContext *buf = ctx->priv;

    av_unused AVBufferSinkParams *params;



    if (!opaque) {

        av_log(ctx, AV_LOG_ERROR,

               "No opaque field provided\n");

        return AVERROR(EINVAL);

    } else {


        buf->pixel_fmts = (const enum PixelFormat *)opaque;


        params = (AVBufferSinkParams *)opaque;

        buf->pixel_fmts = params->pixel_fmts;


    }



    return common_init(ctx);

}

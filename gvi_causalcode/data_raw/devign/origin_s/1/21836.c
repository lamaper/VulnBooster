void aio_context_setup(AioContext *ctx, Error **errp)

{


    assert(!ctx->epollfd);

    ctx->epollfd = epoll_create1(EPOLL_CLOEXEC);

    if (ctx->epollfd == -1) {

        ctx->epoll_available = false;

    } else {

        ctx->epoll_available = true;

    }


}

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>
#include <time.h>
static ngx_int_t ngx_http_hello_filter_init(ngx_conf_t *cf);
static ngx_int_t ngx_http_hello_body_filter(ngx_http_request_t *r, ngx_chain_t *in);

ngx_http_output_body_filter_pt ngx_http_hello_next_body_filter;

static ngx_command_t ngx_http_hello_commands[]={
     ngx_null_command
};
static ngx_http_module_t ngx_http_hello_module_ctx={
     NULL,/*preconfiguration*/
     ngx_http_hello_filter_init,/*postconfiguration*/
     NULL,/*create_main_conf*/
     NULL,/*init_main_conf*/
     NULL,/*create_srv_conf*/
     NULL,/*merge_srv_conf*/
     NULL,/*create_loc_conf*/
     NULL/*merge_loc_conf */
};
ngx_module_t ngx_http_hellofilter_module={
     NGX_MODULE_V1,
     &ngx_http_hello_module_ctx,
     ngx_http_hello_commands,
     NGX_HTTP_MODULE,
     NULL,/* init master */
     NULL,/* init module */
     NULL,/* init process */
     NULL,/* init thread */
     NULL,/* exit thread */
     NULL,/* exit process */
     NULL,/* exit master */
     NGX_MODULE_V1_PADDING
};

static ngx_int_t
ngx_http_hello_filter_init(ngx_conf_t *cf)
{
    ngx_log_error(NGX_LOG_DEBUG, cf->log, 0, "ngx_http_hello_filter_init\n");
    ngx_http_hello_next_body_filter = ngx_http_top_body_filter;
    ngx_http_top_body_filter = ngx_http_hello_body_filter;

    return NGX_OK;
}

static ngx_int_t ngx_http_hello_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "begin into function ngx_http_hello_body_filter");
    ngx_chain_t *cl;
    ngx_chain_t **ll = NULL;
    ngx_int_t chain_contains_last_buffer = 0;
    ngx_int_t rc;

    if (in == NULL || r->header_only) {
        ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "ngx_chain_t in is null");
    }

    for (cl = in; cl; cl = cl->next) {
        ll = &cl->next; // value of ll is the address of the next pointer null of last chain
        if (cl->buf->last_buf || cl->buf->last_in_chain) {
            ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "set chain_contains_last_buffer = 1");
            chain_contains_last_buffer = 1;
        }
        cl->buf->last_buf = 0; // essential
    }

    ngx_buf_t *b;
    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        return NGX_ERROR;
    }
    ngx_str_t str = ngx_string("keything---->net");
    b->pos = str.data;
    b->last = b->pos + str.len;
    b->last_buf = 1;
    b->memory = 1;
    b->last_in_chain = 1;

    ngx_chain_t *added_link;
    added_link = ngx_palloc(r->pool, sizeof(ngx_chain_t));
    added_link->buf = b;
    added_link->next = NULL;
    *ll = added_link;

    for (cl = in; cl; cl = cl->next) {
        if (cl->buf->last - cl->buf->pos) {
            ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "buf content:%s len:%d last_buf:%d, last_in_chain:%d",
                 cl->buf->pos, cl->buf->last - cl->buf->pos, cl->buf->last_buf, cl->buf->last_in_chain);
        }
    }

    rc = ngx_http_hello_next_body_filter(r, in);
    if (rc == NGX_ERROR || rc > NGX_OK) {
        ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "body sends failed");
        return rc;
    }
    ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "body sends succeed");
    return rc;
}

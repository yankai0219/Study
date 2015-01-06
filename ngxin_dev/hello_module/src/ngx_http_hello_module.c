#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>
#include <time.h>
char * ngx_hello_hello(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
ngx_int_t ngx_http_hello_handler(ngx_http_request_t *r);
static ngx_int_t ngx_http_hello_filter_init(ngx_conf_t *cf);
static ngx_int_t ngx_http_hello_body_filter(ngx_http_request_t *r, ngx_chain_t *in);
static ngx_command_t ngx_http_hello_commands[]={
     {
          ngx_string("hello"),
          NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
          ngx_hello_hello,
          0,
          0,
          NULL
     },
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
static ngx_http_output_body_filter_pt    ngx_http_next_body_filter;
ngx_module_t ngx_http_hello_module={
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
char * ngx_hello_hello(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_log_error(NGX_LOG_DEBUG, cf->log, 0, "ngx_hello_hello\n");
     ngx_http_core_loc_conf_t *clcf;
     clcf = ngx_http_conf_get_module_loc_conf(cf,ngx_http_core_module);
     clcf->handler = ngx_http_hello_handler;
     return NGX_CONF_OK;
}
ngx_int_t ngx_http_hello_handler(ngx_http_request_t *r)
{
    ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "begin into ngx_http_hello_handler\n");
    ngx_buf_t * b;
    ngx_chain_t out;
    ngx_str_t output_data = ngx_string("hello,yankai\n");
    ngx_str_t my_content_type = ngx_string("text/plain");
    r->headers_out.content_type.len = my_content_type.len;
    r->headers_out.content_type.data = my_content_type.data;
    r->headers_out.content_encoding = ngx_list_push(&r->headers_out.headers);
    if (r->headers_out.content_encoding == NULL) {
        return NGX_ERROR;
    }

    r->headers_out.content_encoding->hash = 1;
    ngx_str_t my_content_encoding_key = ngx_string("Content-Encoding");
    r->headers_out.content_encoding->key.len = my_content_encoding_key.len;
    r->headers_out.content_encoding->key.data = my_content_encoding_key.data;
    ngx_str_t my_content_encoding_value = ngx_string("deflate");
    r->headers_out.content_encoding->value.len = my_content_encoding_value.len;
    r->headers_out.content_encoding->value.data = my_content_encoding_value.data;

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = output_data.len;
    ngx_http_send_header(r);

    b = ngx_palloc(r->pool,sizeof(ngx_buf_t));
    out.buf = b;
    out.next = NULL;

    b->pos = output_data.data;
    b->last = output_data.data + output_data.len;

    b->memory = 1;
    b->last_buf = 1;
    ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "output_data");

    return ngx_http_output_filter( r,&out);
}


static ngx_int_t ngx_http_hello_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "begin into ngx_http_hello_body_filter\n");
    ngx_chain_t *chain_link;
    int chain_contains_last_buffer = 0;
    for (chain_link = in; chain_link->next != NULL; chain_link = chain_link->next) {
        if (chain_link->buf->last_buf) {
            chain_contains_last_buffer = 1;
        }
    }

    if (! chain_contains_last_buffer) {
        return ngx_http_next_body_filter(r, in);
    }

    ngx_buf_t *b;
    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        return NGX_ERROR;
    }


    b->pos = (u_char *)"<!-- Served by Nginx ---";
    b->last = b->pos + sizeof("<!-- Served by Nginx ---") - 1;
    ngx_chain_t *added_link;
    added_link = ngx_palloc(r->pool, sizeof(ngx_chain_t));
    added_link->buf = b;
    added_link->next = NULL;

    chain_link->next = added_link;
    chain_link->buf->last_buf = 0;
    chain_link->buf->last_buf = 1;

    return ngx_http_next_body_filter(r, in);
}
static ngx_int_t
ngx_http_hello_filter_init(ngx_conf_t *cf)
{
    ngx_log_error(NGX_LOG_DEBUG, cf->log, 0, "ngx_http_hello_filter_init\n");
    ngx_http_next_body_filter = ngx_http_top_body_filter;
    ngx_http_top_body_filter = ngx_http_hello_body_filter;
    printf("nggx_http_hello_filter_init set filter succeed");

    ngx_log_error(NGX_LOG_DEBUG, cf->log, 0, "ngx_http_hello_filter_init set filter succeed\n");
    return NGX_OK;
}

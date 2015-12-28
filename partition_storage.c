/* ---===### include/vdef.h ###===--- */

/*-
 * Copyright (c) 2006 Verdens Gang AS
 * Copyright (c) 2012 Fastly Inc
 * Copyright (c) 2006-2015 Varnish Software AS
 * All rights reserved.
 *
 * Author: Poul-Henning Kamp <phk@phk.freebsd.dk>
 * Author: Rogier 'DocWilco' Mulhuijzen <rogier@fastly.com>
 *
 * Inspired by FreeBSD's <sys/cdefs.h>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef VDEF_H_INCLUDED
#define VDEF_H_INCLUDED

/* Safe printf into a fixed-size buffer */
#define bprintf(buf, fmt, ...)						\
	do {								\
		assert(snprintf(buf, sizeof buf, fmt, __VA_ARGS__)	\
		    < sizeof buf);					\
	} while (0)

/* Safe printf into a fixed-size buffer */
#define vbprintf(buf, fmt, ap)						\
	do {								\
		assert(vsnprintf(buf, sizeof buf, fmt, ap)		\
		    < sizeof buf);					\
	} while (0)


#ifndef __GNUC_PREREQ
# if defined __GNUC__ && defined __GNUC_MINOR__
#  define __GNUC_PREREQ(maj, min) \
	(__GNUC__ > (maj) || (__GNUC__ == (maj) && __GNUC_MINOR__ >= (min)))
# else
#  define __GNUC_PREREQ(maj, min) 0
# endif
#endif

#ifdef __printflike
#  define __v_printflike(f,a) __printflike(f,a)
#elif __GNUC_PREREQ(2, 95) || defined(__INTEL_COMPILER)
#  define __v_printflike(f,a) __attribute__((format(printf, f, a)))
#else
#  define __v_printflike(f,a)
#endif

/**********************************************************************
 * FlexeLint and compiler shutuppery
 */

/*
 * In OO-light situations, functions have to match their prototype
 * even if that means not const'ing a const'able argument.
 * The typedef should be specified as argument to the macro.
 */
#define __match_proto__(xxx)		/*lint -e{818} */

#define NEEDLESS_RETURN(foo)	return (foo)

#endif /* VDEF_H_INCLUDED */

/* ---===### include/vcl.h ###===--- */

/*
 * NB:  This file is machine generated, DO NOT EDIT!
 *
 * Edit and run generate.py instead
 */

struct vrt_ctx;
#define VRT_CTX const struct vrt_ctx *ctx
struct req;
struct busyobj;
struct ws;
struct cli;
struct worker;

enum vcl_event_e {
	VCL_EVENT_LOAD,
	VCL_EVENT_WARM,
	VCL_EVENT_USE,
	VCL_EVENT_COLD,
	VCL_EVENT_DISCARD,
};

typedef int vcl_event_f(VRT_CTX, enum vcl_event_e);
typedef int vcl_init_f(VRT_CTX);
typedef void vcl_fini_f(VRT_CTX);
typedef int vcl_func_f(VRT_CTX);

/* VCL Methods */
#define VCL_MET_RECV			(1U << 1)
#define VCL_MET_PIPE			(1U << 2)
#define VCL_MET_PASS			(1U << 3)
#define VCL_MET_HASH			(1U << 4)
#define VCL_MET_PURGE			(1U << 5)
#define VCL_MET_MISS			(1U << 6)
#define VCL_MET_HIT			(1U << 7)
#define VCL_MET_DELIVER			(1U << 8)
#define VCL_MET_SYNTH			(1U << 9)
#define VCL_MET_BACKEND_FETCH		(1U << 10)
#define VCL_MET_BACKEND_RESPONSE	(1U << 11)
#define VCL_MET_BACKEND_ERROR		(1U << 12)
#define VCL_MET_INIT			(1U << 13)
#define VCL_MET_FINI			(1U << 14)

#define VCL_MET_MAX			15

#define VCL_MET_MASK			0x7fff

/* VCL Returns */
#define VCL_RET_ABANDON			0
#define VCL_RET_DELIVER			1
#define VCL_RET_FAIL			2
#define VCL_RET_FETCH			3
#define VCL_RET_HASH			4
#define VCL_RET_LOOKUP			5
#define VCL_RET_MISS			6
#define VCL_RET_OK			7
#define VCL_RET_PASS			8
#define VCL_RET_PIPE			9
#define VCL_RET_PURGE			10
#define VCL_RET_RESTART			11
#define VCL_RET_RETRY			12
#define VCL_RET_SYNTH			13

#define VCL_RET_MAX			14

struct VCL_conf {
	unsigned			magic;
#define VCL_CONF_MAGIC			0x7406c509	/* from /dev/random */

	struct director			**default_director;
	const struct vrt_backend_probe	*default_probe;
	unsigned			nref;
	struct vrt_ref			*ref;

	unsigned			nsrc;
	const char			**srcname;
	const char			**srcbody;

	vcl_event_f			*event_vcl;
	vcl_func_f	*recv_func;
	vcl_func_f	*pipe_func;
	vcl_func_f	*pass_func;
	vcl_func_f	*hash_func;
	vcl_func_f	*purge_func;
	vcl_func_f	*miss_func;
	vcl_func_f	*hit_func;
	vcl_func_f	*deliver_func;
	vcl_func_f	*synth_func;
	vcl_func_f	*backend_fetch_func;
	vcl_func_f	*backend_response_func;
	vcl_func_f	*backend_error_func;
	vcl_func_f	*init_func;
	vcl_func_f	*fini_func;

};

/* ---===### include/vrt.h ###===--- */

/*-
 * Copyright (c) 2006 Verdens Gang AS
 * Copyright (c) 2006-2015 Varnish Software AS
 * All rights reserved.
 *
 * Author: Poul-Henning Kamp <phk@phk.freebsd.dk>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Runtime support for compiled VCL programs and VMODs.
 *
 * NB: When this file is changed, lib/libvcc/generate.py *MUST* be rerun.
 */

/***********************************************************************
 * Major and minor VRT API versions.
 *
 * Whenever something is added, increment MINOR version
 * Whenever something is deleted or changed in a way which is not
 * binary/load-time compatible, increment MAJOR version
 *
 * changes to consider with next VRT_MAJOR_VERSION bump:
 * - cache_vrt.c: -> ssize_t VRT_CacheReqBody(VRT_CTX, size_t)
 *
 * changes to consider with next VRT_MINOR_VERSION bump for 4.1:
 * - cache_vcl.c: -> VRT_ref_vcl, VRT_rel_vcl
 */

#define VRT_MAJOR_VERSION	3U

#define VRT_MINOR_VERSION	0U


/***********************************************************************/

struct VCL_conf;
struct busyobj;
struct director;
struct http;
struct req;
struct suckaddr;
struct vcl;
struct vmod;
struct vsb;
struct vsl_log;
struct ws;

/***********************************************************************
 * This is the central definition of the mapping from VCL types to
 * C-types.  The python scripts read these from here.
 * (alphabetic order)
 */

typedef const struct director *			VCL_BACKEND;
typedef const struct vmod_priv *		VCL_BLOB;
typedef unsigned				VCL_BOOL;
typedef double					VCL_BYTES;
typedef double					VCL_DURATION;
typedef const char *				VCL_ENUM;
typedef const struct gethdr_s *			VCL_HEADER;
typedef struct http *				VCL_HTTP;
typedef long					VCL_INT;
typedef const struct suckaddr *			VCL_IP;
typedef const struct vrt_backend_probe *	VCL_PROBE;
typedef double					VCL_REAL;
typedef const char *				VCL_STRING;
typedef double					VCL_TIME;
typedef void					VCL_VOID;

/***********************************************************************
 * This is the composite argument we pass to compiled VCL and VRT
 * functions.
 */

struct vrt_ctx {
	unsigned			magic;
#define VRT_CTX_MAGIC			0x6bb8f0db

	unsigned			method;
	unsigned			*handling;

	struct vsb			*msg;	// Only in ...init()
	struct vsl_log			*vsl;
	struct vcl			*vcl;
	struct ws			*ws;

	struct req			*req;
	struct http			*http_req;
	struct http			*http_req_top;
	struct http			*http_resp;

	struct busyobj			*bo;
	struct http			*http_bereq;
	struct http			*http_beresp;

	double				now;

	/*
	 * method specific argument:
	 *    hash:		struct SHA256Context
	 *    synth+error:	struct vsb *
	 */
	void				*specific;
};

#define VRT_CTX		const struct vrt_ctx *ctx

/***********************************************************************/

struct vmod_data {
	/* The version/id fields must be first, they protect the rest */
	unsigned			vrt_major;
	unsigned			vrt_minor;
	const char			*file_id;

	const char			*name;
	const void			*func;
	int				func_len;
	const char			*proto;
	const char			* const *spec;
	const char			*abi;
};

/***********************************************************************/

enum gethdr_e { HDR_REQ, HDR_REQ_TOP, HDR_RESP, HDR_OBJ, HDR_BEREQ,
		HDR_BERESP };

struct gethdr_s {
	enum gethdr_e	where;
	const char	*what;
};

extern const void * const vrt_magic_string_end;
extern const void * const vrt_magic_string_unset;

/***********************************************************************
 * We want the VCC to spit this structs out as const, but when VMODs
 * come up with them we want to clone them into malloc'ed space which
 * we can free again.
 * We collect all the knowledge here by macroizing the fields and make
 * a macro for handling them all.
 * See also:  cache_backend.h & cache_backend_cfg.c
 * One of those things...
 */

#define VRT_BACKEND_FIELDS(rigid)				\
	rigid char			*vcl_name;		\
	rigid char			*ipv4_addr;		\
	rigid char			*ipv6_addr;		\
	rigid char			*port;			\
	rigid char			*hosthdr;		\
	double				connect_timeout;	\
	double				first_byte_timeout;	\
	double				between_bytes_timeout;	\
	unsigned			max_connections;

#define VRT_BACKEND_HANDLE()			\
	do {					\
		DA(vcl_name);			\
		DA(ipv4_addr);			\
		DA(ipv6_addr);			\
		DA(port);			\
		DA(hosthdr);			\
		DN(connect_timeout);		\
		DN(first_byte_timeout);		\
		DN(between_bytes_timeout);	\
		DN(max_connections);		\
	} while(0)

struct vrt_backend {
	unsigned			magic;
#define VRT_BACKEND_MAGIC		0x4799ce6b
	VRT_BACKEND_FIELDS(const)
	const struct suckaddr		*ipv4_suckaddr;
	const struct suckaddr		*ipv6_suckaddr;
	const struct vrt_backend_probe	*probe;
};

#define VRT_BACKEND_PROBE_FIELDS(rigid)				\
	double				timeout;		\
	double				interval;		\
	unsigned			exp_status;		\
	unsigned			window;			\
	unsigned			threshold;		\
	unsigned			initial;

#define VRT_BACKEND_PROBE_HANDLE()		\
	do {					\
		DN(timeout);			\
		DN(interval);			\
		DN(exp_status);			\
		DN(window);			\
		DN(threshold);			\
		DN(initial);			\
	} while (0)

struct vrt_backend_probe {
	unsigned			magic;
#define VRT_BACKEND_PROBE_MAGIC		0x84998490
	const char			*url;
	const char			*request;
	VRT_BACKEND_PROBE_FIELDS(const)
};

/***********************************************************************/

/*
 * other stuff.
 * XXX: document when bored
 */

struct vrt_ref {
	unsigned	source;
	unsigned	offset;
	unsigned	line;
	unsigned	pos;
	const char	*token;
};

/* ACL related */
#define VRT_ACL_MAXADDR		16	/* max(IPv4, IPv6) */

void VRT_acl_log(VRT_CTX, const char *msg);

/* req related */

int VRT_CacheReqBody(VRT_CTX, long long maxsize);

/* Regexp related */
void VRT_re_init(void **, const char *);
void VRT_re_fini(void *);
int VRT_re_match(VRT_CTX, const char *, void *re);
const char *VRT_regsub(VRT_CTX, int all, const char *, void *, const char *);

void VRT_ban_string(VRT_CTX, const char *);
void VRT_purge(VRT_CTX, double ttl, double grace, double keep);

void VRT_count(VRT_CTX, unsigned);
void VRT_synth(VRT_CTX, unsigned, const char *);

struct http *VRT_selecthttp(VRT_CTX, enum gethdr_e);
const char *VRT_GetHdr(VRT_CTX, const struct gethdr_s *);
void VRT_SetHdr(VRT_CTX, const struct gethdr_s *, const char *, ...);
void VRT_handling(VRT_CTX, unsigned hand);

void VRT_hashdata(VRT_CTX, const char *str, ...);

/* Simple stuff */
int VRT_strcmp(const char *s1, const char *s2);
void VRT_memmove(void *dst, const void *src, unsigned len);

void VRT_Rollback(VRT_CTX, const struct http *);

/* Synthetic pages */
void VRT_synth_page(VRT_CTX, const char *, ...);

/* Backend related */
struct director *VRT_new_backend(VRT_CTX, const struct vrt_backend *);
void VRT_delete_backend(VRT_CTX, struct director **);

/* Suckaddr related */
int VRT_VSA_GetPtr(const struct suckaddr *sua, const unsigned char ** dst);

/* VMOD/Modules related */
int VRT_Vmod_Init(struct vmod **hdl, void *ptr, int len, const char *nm,
    const char *path, const char *file_id, VRT_CTX);
void VRT_Vmod_Fini(struct vmod **hdl);

struct vmod_priv;
typedef void vmod_priv_free_f(void *);
struct vmod_priv {
	void			*priv;
	int			len;
	vmod_priv_free_f	*free;
};

#ifdef VCL_RET_MAX
typedef int vmod_event_f(VRT_CTX, struct vmod_priv *, enum vcl_event_e);
#endif

void VRT_ref_vcl(VRT_CTX);
void VRT_rel_vcl(VRT_CTX);

void VRT_priv_fini(const struct vmod_priv *p);
struct vmod_priv *VRT_priv_task(VRT_CTX, void *vmod_id);
struct vmod_priv *VRT_priv_top(VRT_CTX, void *vmod_id);

/* Stevedore related functions */
int VRT_Stv(const char *nm);

/* Convert things to string */

char *VRT_IP_string(VRT_CTX, VCL_IP);
char *VRT_INT_string(VRT_CTX, VCL_INT);
char *VRT_REAL_string(VRT_CTX, VCL_REAL);
char *VRT_TIME_string(VRT_CTX, VCL_TIME);
const char *VRT_BOOL_string(VCL_BOOL);
const char *VRT_BACKEND_string(VCL_BACKEND);
const char *VRT_CollectString(VRT_CTX, const char *p, ...);

/* ---===### include/vrt_obj.h ###===--- */

/*
 * NB:  This file is machine generated, DO NOT EDIT!
 *
 * Edit and run generate.py instead
 */

VCL_HTTP VRT_r_bereq(VRT_CTX);

VCL_BACKEND VRT_r_bereq_backend(VRT_CTX);
void VRT_l_bereq_backend(VRT_CTX, VCL_BACKEND);

VCL_DURATION VRT_r_bereq_between_bytes_timeout(VRT_CTX);
void VRT_l_bereq_between_bytes_timeout(VRT_CTX, VCL_DURATION);

VCL_DURATION VRT_r_bereq_connect_timeout(VRT_CTX);
void VRT_l_bereq_connect_timeout(VRT_CTX, VCL_DURATION);

VCL_DURATION VRT_r_bereq_first_byte_timeout(VRT_CTX);
void VRT_l_bereq_first_byte_timeout(VRT_CTX, VCL_DURATION);


VCL_STRING VRT_r_bereq_method(VRT_CTX);
void VRT_l_bereq_method(VRT_CTX, const char *, ...);

VCL_STRING VRT_r_bereq_proto(VRT_CTX);
void VRT_l_bereq_proto(VRT_CTX, const char *, ...);

VCL_INT VRT_r_bereq_retries(VRT_CTX);

VCL_BOOL VRT_r_bereq_uncacheable(VRT_CTX);

VCL_STRING VRT_r_bereq_url(VRT_CTX);
void VRT_l_bereq_url(VRT_CTX, const char *, ...);

VCL_STRING VRT_r_bereq_xid(VRT_CTX);

VCL_HTTP VRT_r_beresp(VRT_CTX);

VCL_DURATION VRT_r_beresp_age(VRT_CTX);

VCL_BACKEND VRT_r_beresp_backend(VRT_CTX);

VCL_IP VRT_r_beresp_backend_ip(VRT_CTX);

VCL_STRING VRT_r_beresp_backend_name(VRT_CTX);

VCL_BOOL VRT_r_beresp_do_esi(VRT_CTX);
void VRT_l_beresp_do_esi(VRT_CTX, VCL_BOOL);

VCL_BOOL VRT_r_beresp_do_gunzip(VRT_CTX);
void VRT_l_beresp_do_gunzip(VRT_CTX, VCL_BOOL);

VCL_BOOL VRT_r_beresp_do_gzip(VRT_CTX);
void VRT_l_beresp_do_gzip(VRT_CTX, VCL_BOOL);

VCL_BOOL VRT_r_beresp_do_stream(VRT_CTX);
void VRT_l_beresp_do_stream(VRT_CTX, VCL_BOOL);

VCL_DURATION VRT_r_beresp_grace(VRT_CTX);
void VRT_l_beresp_grace(VRT_CTX, VCL_DURATION);


VCL_DURATION VRT_r_beresp_keep(VRT_CTX);
void VRT_l_beresp_keep(VRT_CTX, VCL_DURATION);

VCL_STRING VRT_r_beresp_proto(VRT_CTX);
void VRT_l_beresp_proto(VRT_CTX, const char *, ...);

VCL_STRING VRT_r_beresp_reason(VRT_CTX);
void VRT_l_beresp_reason(VRT_CTX, const char *, ...);

VCL_INT VRT_r_beresp_status(VRT_CTX);
void VRT_l_beresp_status(VRT_CTX, VCL_INT);

VCL_STRING VRT_r_beresp_storage_hint(VRT_CTX);
void VRT_l_beresp_storage_hint(VRT_CTX, const char *, ...);

VCL_DURATION VRT_r_beresp_ttl(VRT_CTX);
void VRT_l_beresp_ttl(VRT_CTX, VCL_DURATION);

VCL_BOOL VRT_r_beresp_uncacheable(VRT_CTX);
void VRT_l_beresp_uncacheable(VRT_CTX, VCL_BOOL);

VCL_BOOL VRT_r_beresp_was_304(VRT_CTX);

VCL_STRING VRT_r_client_identity(VRT_CTX);
void VRT_l_client_identity(VRT_CTX, const char *, ...);

VCL_IP VRT_r_client_ip(VRT_CTX);

VCL_IP VRT_r_local_ip(VRT_CTX);

VCL_TIME VRT_r_now(VRT_CTX);

VCL_DURATION VRT_r_obj_age(VRT_CTX);

VCL_DURATION VRT_r_obj_grace(VRT_CTX);

VCL_INT VRT_r_obj_hits(VRT_CTX);


VCL_DURATION VRT_r_obj_keep(VRT_CTX);

VCL_STRING VRT_r_obj_proto(VRT_CTX);

VCL_STRING VRT_r_obj_reason(VRT_CTX);

VCL_INT VRT_r_obj_status(VRT_CTX);

VCL_DURATION VRT_r_obj_ttl(VRT_CTX);

VCL_BOOL VRT_r_obj_uncacheable(VRT_CTX);

VCL_IP VRT_r_remote_ip(VRT_CTX);

VCL_HTTP VRT_r_req(VRT_CTX);

VCL_BACKEND VRT_r_req_backend_hint(VRT_CTX);
void VRT_l_req_backend_hint(VRT_CTX, VCL_BACKEND);

VCL_BOOL VRT_r_req_can_gzip(VRT_CTX);

VCL_BOOL VRT_r_req_esi(VRT_CTX);
void VRT_l_req_esi(VRT_CTX, VCL_BOOL);

VCL_INT VRT_r_req_esi_level(VRT_CTX);

VCL_BOOL VRT_r_req_hash_always_miss(VRT_CTX);
void VRT_l_req_hash_always_miss(VRT_CTX, VCL_BOOL);

VCL_BOOL VRT_r_req_hash_ignore_busy(VRT_CTX);
void VRT_l_req_hash_ignore_busy(VRT_CTX, VCL_BOOL);


VCL_STRING VRT_r_req_method(VRT_CTX);
void VRT_l_req_method(VRT_CTX, const char *, ...);

VCL_STRING VRT_r_req_proto(VRT_CTX);
void VRT_l_req_proto(VRT_CTX, const char *, ...);

VCL_INT VRT_r_req_restarts(VRT_CTX);

VCL_DURATION VRT_r_req_ttl(VRT_CTX);
void VRT_l_req_ttl(VRT_CTX, VCL_DURATION);

VCL_STRING VRT_r_req_url(VRT_CTX);
void VRT_l_req_url(VRT_CTX, const char *, ...);

VCL_STRING VRT_r_req_xid(VRT_CTX);


VCL_STRING VRT_r_req_top_method(VRT_CTX);

VCL_STRING VRT_r_req_top_proto(VRT_CTX);

VCL_STRING VRT_r_req_top_url(VRT_CTX);

VCL_HTTP VRT_r_resp(VRT_CTX);


VCL_BOOL VRT_r_resp_is_streaming(VRT_CTX);

VCL_STRING VRT_r_resp_proto(VRT_CTX);
void VRT_l_resp_proto(VRT_CTX, const char *, ...);

VCL_STRING VRT_r_resp_reason(VRT_CTX);
void VRT_l_resp_reason(VRT_CTX, const char *, ...);

VCL_INT VRT_r_resp_status(VRT_CTX);
void VRT_l_resp_status(VRT_CTX, VCL_INT);

VCL_STRING VRT_r_server_hostname(VRT_CTX);

VCL_STRING VRT_r_server_identity(VRT_CTX);

VCL_IP VRT_r_server_ip(VRT_CTX);

double VRT_Stv_free_space(const char *);
double VRT_Stv_used_space(const char *);
unsigned VRT_Stv_happy(const char *);

/* ---===### Source Code ###===---*/

#define VGC_NSRCS 2

static const char *srcname[VGC_NSRCS] = {
	"input",
	"Builtin",
};

static const char *srcbody[2] = {
    /* "input"*/
	"vcl 4.0;\n"
	"import std;\n"
	"\n"
	"backend default {\n"
	"    .host = \"198.51.100.1\";\n"
	"    .port = \"80\";\n"
	"}\n"
	"\n"
	"sub vcl_recv {\n"
	"}\n"
	"\n"
	"sub vcl_backend_response {\n"
	"    if (bereq.http.host ~ \"foo\") {\n"
	"        set beresp.storage_hint = \"foo\";\n"
	"        set beresp.http.x-storage = \"foo\";\n"
	"    } else if (bereq.http.host ~ \"bar\") {\n"
	"        set beresp.storage_hint = \"bar\";\n"
	"        set beresp.http.x-storage = \"bar\";\n"
	"    } else {\n"
	"        set beresp.storage_hint = \"default\";\n"
	"        set beresp.http.x-storage = \"default\";\n"
	"    }\n"
	"}\n"
	"\n"
	"sub vcl_deliver {\n"
	"}\n"
	"",
    /* "Builtin"*/
	"/*-\n"
	" * Copyright (c) 2006 Verdens Gang AS\n"
	" * Copyright (c) 2006-2015 Varnish Software AS\n"
	" * All rights reserved.\n"
	" *\n"
	" * Author: Poul-Henning Kamp <phk@phk.freebsd.dk>\n"
	" *\n"
	" * Redistribution and use in source and binary forms, with or without\n"
	" * modification, are permitted provided that the following conditions\n"
	" * are met:\n"
	" * 1. Redistributions of source code must retain the above copyright\n"
	" *    notice, this list of conditions and the following disclaimer.\n"
	" * 2. Redistributions in binary form must reproduce the above copyright\n"
	" *    notice, this list of conditions and the following disclaimer in the\n"
	" *    documentation and/or other materials provided with the distribution.\n"
	" *\n"
	" * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND\n"
	" * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n"
	" * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n"
	" * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE\n"
	" * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n"
	" * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\n"
	" * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\n"
	" * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\n"
	" * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY\n"
	" * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF\n"
	" * SUCH DAMAGE.\n"
	" *\n"
	"\n"
	" *\n"
	" * The built-in (previously called default) VCL code.\n"
	" *\n"
	" * NB! You do NOT need to copy & paste all of these functions into your\n"
	" * own vcl code, if you do not provide a definition of one of these\n"
	" * functions, the compiler will automatically fall back to the default\n"
	" * code from this file.\n"
	" *\n"
	" * This code will be prefixed with a backend declaration built from the\n"
	" * -b argument.\n"
	" */\n"
	"\n"
	"vcl 4.0;\n"
	"\n"
	"#######################################################################\n"
	"# Client side\n"
	"\n"
	"sub vcl_recv {\n"
	"    if (req.method == \"PRI\") {\n"
	"\t/* We do not support SPDY or HTTP/2.0 */\n"
	"\treturn (synth(405));\n"
	"    }\n"
	"    if (req.method != \"GET\" &&\n"
	"      req.method != \"HEAD\" &&\n"
	"      req.method != \"PUT\" &&\n"
	"      req.method != \"POST\" &&\n"
	"      req.method != \"TRACE\" &&\n"
	"      req.method != \"OPTIONS\" &&\n"
	"      req.method != \"DELETE\") {\n"
	"        /* Non-RFC2616 or CONNECT which is weird. */\n"
	"        return (pipe);\n"
	"    }\n"
	"\n"
	"    if (req.method != \"GET\" && req.method != \"HEAD\") {\n"
	"        /* We only deal with GET and HEAD by default */\n"
	"        return (pass);\n"
	"    }\n"
	"    if (req.http.Authorization || req.http.Cookie) {\n"
	"        /* Not cacheable by default */\n"
	"        return (pass);\n"
	"    }\n"
	"    return (hash);\n"
	"}\n"
	"\n"
	"sub vcl_pipe {\n"
	"    # By default Connection: close is set on all piped requests, to stop\n"
	"    # connection reuse from sending future requests directly to the\n"
	"    # (potentially) wrong backend. If you do want this to happen, you can undo\n"
	"    # it here.\n"
	"    # unset bereq.http.connection;\n"
	"    return (pipe);\n"
	"}\n"
	"\n"
	"sub vcl_pass {\n"
	"    return (fetch);\n"
	"}\n"
	"\n"
	"sub vcl_hash {\n"
	"    hash_data(req.url);\n"
	"    if (req.http.host) {\n"
	"        hash_data(req.http.host);\n"
	"    } else {\n"
	"        hash_data(server.ip);\n"
	"    }\n"
	"    return (lookup);\n"
	"}\n"
	"\n"
	"sub vcl_purge {\n"
	"    return (synth(200, \"Purged\"));\n"
	"}\n"
	"\n"
	"sub vcl_hit {\n"
	"    if (obj.ttl >= 0s) {\n"
	"        // A pure unadultered hit, deliver it\n"
	"        return (deliver);\n"
	"    }\n"
	"    if (obj.ttl + obj.grace > 0s) {\n"
	"        // Object is in grace, deliver it\n"
	"        // Automatically triggers a background fetch\n"
	"        return (deliver);\n"
	"    }\n"
	"    // fetch & deliver once we get the result\n"
	"    return (miss);\n"
	"}\n"
	"\n"
	"sub vcl_miss {\n"
	"    return (fetch);\n"
	"}\n"
	"\n"
	"sub vcl_deliver {\n"
	"    return (deliver);\n"
	"}\n"
	"\n"
	"/*\n"
	" * We can come here \"invisibly\" with the following errors: 413, 417 & 503\n"
	" */\n"
	"sub vcl_synth {\n"
	"    set resp.http.Content-Type = \"text/html; charset=utf-8\";\n"
	"    set resp.http.Retry-After = \"5\";\n"
	"    synthetic( {\"<!DOCTYPE html>\n"
	"<html>\n"
	"  <head>\n"
	"    <title>\"} + resp.status + \" \" + resp.reason + {\"</title>\n"
	"  </head>\n"
	"  <body>\n"
	"    <h1>Error \"} + resp.status + \" \" + resp.reason + {\"</h1>\n"
	"    <p>\"} + resp.reason + {\"</p>\n"
	"    <h3>Guru Meditation:</h3>\n"
	"    <p>XID: \"} + req.xid + {\"</p>\n"
	"    <hr>\n"
	"    <p>Varnish cache server</p>\n"
	"  </body>\n"
	"</html>\n"
	"\"} );\n"
	"    return (deliver);\n"
	"}\n"
	"\n"
	"#######################################################################\n"
	"# Backend Fetch\n"
	"\n"
	"sub vcl_backend_fetch {\n"
	"    return (fetch);\n"
	"}\n"
	"\n"
	"sub vcl_backend_response {\n"
	"    if (beresp.ttl <= 0s ||\n"
	"      beresp.http.Set-Cookie ||\n"
	"      beresp.http.Surrogate-control ~ \"no-store\" ||\n"
	"      (!beresp.http.Surrogate-Control &&\n"
	"        beresp.http.Cache-Control ~ \"no-cache|no-store|private\") ||\n"
	"      beresp.http.Vary == \"*\") {\n"
	"        /*\n"
	"        * Mark as \"Hit-For-Pass\" for the next 2 minutes\n"
	"        */\n"
	"        set beresp.ttl = 120s;\n"
	"        set beresp.uncacheable = true;\n"
	"    }\n"
	"    return (deliver);\n"
	"}\n"
	"\n"
	"sub vcl_backend_error {\n"
	"    set beresp.http.Content-Type = \"text/html; charset=utf-8\";\n"
	"    set beresp.http.Retry-After = \"5\";\n"
	"    synthetic( {\"<!DOCTYPE html>\n"
	"<html>\n"
	"  <head>\n"
	"    <title>\"} + beresp.status + \" \" + beresp.reason + {\"</title>\n"
	"  </head>\n"
	"  <body>\n"
	"    <h1>Error \"} + beresp.status + \" \" + beresp.reason + {\"</h1>\n"
	"    <p>\"} + beresp.reason + {\"</p>\n"
	"    <h3>Guru Meditation:</h3>\n"
	"    <p>XID: \"} + bereq.xid + {\"</p>\n"
	"    <hr>\n"
	"    <p>Varnish cache server</p>\n"
	"  </body>\n"
	"</html>\n"
	"\"} );\n"
	"    return (deliver);\n"
	"}\n"
	"\n"
	"#######################################################################\n"
	"# Housekeeping\n"
	"\n"
	"sub vcl_init {\n"
	"}\n"
	"\n"
	"sub vcl_fini {\n"
	"    return (ok);\n"
	"}\n"
	"",
};

/* ---===### Location Counters ###===---*/

#define VGC_NREFS 37

static struct vrt_ref VGC_ref[VGC_NREFS] = {
  [  1] = { 0,      104,   10,   1,  "}" },
  [  2] = { 0,      138,   13,   5,  "if" },
  [  3] = { 0,      177,   14,   9,  "set" },
  [  4] = { 0,      303,   17,   9,  "set" },
  [  5] = { 0,      400,   20,   9,  "set" },
  [  6] = { 0,      511,   26,   1,  "}" },
  [  7] = { 1,     1960,   48,   5,  "if" },
  [  8] = { 1,     2030,   50,   9,  "return" },
  [  9] = { 1,     2061,   52,   5,  "if" },
  [ 10] = { 1,     2334,   60,   9,  "return" },
  [ 11] = { 1,     2360,   63,   5,  "if" },
  [ 12] = { 1,     2475,   65,   9,  "return" },
  [ 13] = { 1,     2500,   67,   5,  "if" },
  [ 14] = { 1,     2596,   69,   9,  "return" },
  [ 15] = { 1,     2621,   71,   5,  "return" },
  [ 16] = { 1,     2928,   80,   5,  "return" },
  [ 17] = { 1,     2965,   84,   5,  "return" },
  [ 18] = { 1,     3003,   88,   5,  "hash_data" },
  [ 19] = { 1,     3056,   90,   9,  "hash_data" },
  [ 20] = { 1,     3103,   92,   9,  "hash_data" },
  [ 21] = { 1,     3175,   98,   5,  "return" },
  [ 22] = { 1,     3227,  102,   5,  "if" },
  [ 23] = { 1,     3302,  104,   9,  "return" },
  [ 24] = { 1,     3330,  106,   5,  "if" },
  [ 25] = { 1,     3465,  109,   9,  "return" },
  [ 26] = { 1,     3539,  112,   5,  "return" },
  [ 27] = { 1,     3576,  116,   5,  "return" },
  [ 28] = { 1,     3617,  120,   5,  "return" },
  [ 29] = { 1,     3739,  127,   5,  "set" },
  [ 30] = { 1,     4327,  151,   5,  "return" },
  [ 31] = { 1,     4377,  155,   5,  "if" },
  [ 32] = { 1,     4713,  164,   9,  "set" },
  [ 33] = { 1,     4785,  167,   5,  "return" },
  [ 34] = { 1,     4834,  171,   5,  "set" },
  [ 35] = { 1,     5424,  195,   1,  "}" },
  [ 36] = { 1,     5446,  198,   5,  "return" },
};

/* ---===### VCC generated .h code ###===---*/

extern const struct VCL_conf VCL_conf;

/* --- BEGIN VMOD std --- */

static struct vmod *VGC_vmod_std;
static struct vmod_priv vmod_priv_std;

/* Functions */
typedef VCL_STRING td_std_toupper(VRT_CTX, const char *, ...);
typedef VCL_STRING td_std_tolower(VRT_CTX, const char *, ...);
typedef VCL_VOID td_std_set_ip_tos(VRT_CTX, VCL_INT);
typedef VCL_REAL td_std_random(VRT_CTX, VCL_REAL, VCL_REAL);
typedef VCL_VOID td_std_log(VRT_CTX, const char *, ...);
typedef VCL_VOID td_std_syslog(VRT_CTX, VCL_INT, const char *,
    ...);
typedef VCL_STRING td_std_fileread(VRT_CTX, struct vmod_priv *,
    VCL_STRING);
typedef VCL_VOID td_std_collect(VRT_CTX, VCL_HEADER);
typedef VCL_DURATION td_std_duration(VRT_CTX, VCL_STRING,
    VCL_DURATION);
typedef VCL_INT td_std_integer(VRT_CTX, VCL_STRING, VCL_INT);
typedef VCL_IP td_std_ip(VRT_CTX, VCL_STRING, VCL_IP);
typedef VCL_REAL td_std_real(VRT_CTX, VCL_STRING, VCL_REAL);
typedef VCL_INT td_std_real2integer(VRT_CTX, VCL_REAL, VCL_INT);
typedef VCL_TIME td_std_real2time(VRT_CTX, VCL_REAL, VCL_TIME);
typedef VCL_INT td_std_time2integer(VRT_CTX, VCL_TIME, VCL_INT);
typedef VCL_REAL td_std_time2real(VRT_CTX, VCL_TIME, VCL_REAL);
typedef VCL_BOOL td_std_healthy(VRT_CTX, VCL_BACKEND);
typedef VCL_INT td_std_port(VRT_CTX, VCL_IP);
typedef VCL_VOID td_std_rollback(VRT_CTX, VCL_HTTP);
typedef VCL_VOID td_std_timestamp(VRT_CTX, VCL_STRING);
typedef VCL_STRING td_std_querysort(VRT_CTX, VCL_STRING);
typedef VCL_VOID td_std_cache_req_body(VRT_CTX, VCL_BYTES);
typedef VCL_STRING td_std_strstr(VRT_CTX, VCL_STRING,
    VCL_STRING);
typedef VCL_TIME td_std_time(VRT_CTX, VCL_STRING, VCL_TIME);

struct Vmod_std_Func {

	/* Functions */
	td_std_toupper			*toupper;
	td_std_tolower			*tolower;
	td_std_set_ip_tos		*set_ip_tos;
	td_std_random			*random;
	td_std_log			*log;
	td_std_syslog			*syslog;
	td_std_fileread			*fileread;
	td_std_collect			*collect;
	td_std_duration			*duration;
	td_std_integer			*integer;
	td_std_ip			*ip;
	td_std_real			*real;
	td_std_real2integer		*real2integer;
	td_std_real2time		*real2time;
	td_std_time2integer		*time2integer;
	td_std_time2real		*time2real;
	td_std_healthy			*healthy;
	td_std_port			*port;
	td_std_rollback			*rollback;
	td_std_timestamp		*timestamp;
	td_std_querysort		*querysort;
	td_std_cache_req_body		*cache_req_body;
	td_std_strstr			*strstr;
	td_std_time			*time;

	/* Init/Fini */
};
static struct Vmod_std_Func Vmod_std_Func;

/* --- END VMOD std --- */


static struct director *vgc_backend_default;

/* "198.51.100.1 80" -> 198.51.100.1 */
static const unsigned long long suckaddr_0[4] = {
    0x500000024b1e9335ULL,
    0x00000000016433c6ULL,
    0x0000000000000000ULL,
    0x0000000000000000ULL
};

static const struct vrt_backend vgc_dir_priv_vgc_backend_default = {
	.magic = VRT_BACKEND_MAGIC,
	.vcl_name = "default",
	.ipv4_suckaddr = (const struct suckaddr *)(const void*)suckaddr_0,
	.ipv4_addr = "198.51.100.1",
	.port = "80",
	.hosthdr = "198.51.100.1",
};
static const struct gethdr_s VGC_HDR_BEREQ_host =
    { HDR_BEREQ, "\005host:"};
static void *VGC_re_1;
static const struct gethdr_s VGC_HDR_BERESP_x_2d_storage =
    { HDR_BERESP, "\012x-storage:"};
static void *VGC_re_2;
static const struct gethdr_s VGC_HDR_REQ_Authorization =
    { HDR_REQ, "\016Authorization:"};
static const struct gethdr_s VGC_HDR_REQ_Cookie =
    { HDR_REQ, "\007Cookie:"};
static const struct gethdr_s VGC_HDR_REQ_host =
    { HDR_REQ, "\005host:"};
static const struct gethdr_s VGC_HDR_RESP_Content_2d_Type =
    { HDR_RESP, "\015Content-Type:"};
static const struct gethdr_s VGC_HDR_RESP_Retry_2d_After =
    { HDR_RESP, "\014Retry-After:"};
static const struct gethdr_s VGC_HDR_BERESP_Set_2d_Cookie =
    { HDR_BERESP, "\013Set-Cookie:"};
static const struct gethdr_s VGC_HDR_BERESP_Surrogate_2d_control =
    { HDR_BERESP, "\022Surrogate-control:"};
static void *VGC_re_3;
static const struct gethdr_s VGC_HDR_BERESP_Surrogate_2d_Control =
    { HDR_BERESP, "\022Surrogate-Control:"};
static const struct gethdr_s VGC_HDR_BERESP_Cache_2d_Control =
    { HDR_BERESP, "\016Cache-Control:"};
static void *VGC_re_4;
static const struct gethdr_s VGC_HDR_BERESP_Vary =
    { HDR_BERESP, "\005Vary:"};
static const struct gethdr_s VGC_HDR_BERESP_Content_2d_Type =
    { HDR_BERESP, "\015Content-Type:"};
static const struct gethdr_s VGC_HDR_BERESP_Retry_2d_After =
    { HDR_BERESP, "\014Retry-After:"};

int __match_proto__(vcl_func_f) VGC_function_vcl_backend_error(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_backend_fetch(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_backend_response(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_deliver(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_fini(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_hash(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_hit(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_init(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_miss(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_pass(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_pipe(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_purge(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_recv(VRT_CTX);
int __match_proto__(vcl_func_f) VGC_function_vcl_synth(VRT_CTX);

static unsigned vgc_inistep;

/* ---===### VCC generated .c code ###===---*/

int __match_proto__(vcl_func_f)
VGC_function_vcl_backend_error(VRT_CTX)
{
  /* ... from ('Builtin' Line 170 Pos 5) */
  {
    {
      VRT_count(ctx, 34);
      VRT_SetHdr(ctx, &VGC_HDR_BERESP_Content_2d_Type,
        "text/html; charset=utf-8",
          vrt_magic_string_end
      );
      VRT_SetHdr(ctx, &VGC_HDR_BERESP_Retry_2d_After,
        "5",
          vrt_magic_string_end
      );
      VRT_synth_page(ctx,       "<!DOCTYPE html>\n"
        	"<html>\n"
        	"  <head>\n"
        	"    <title>",
        VRT_INT_string(ctx, VRT_r_beresp_status(ctx)),
        " ",
        VRT_r_beresp_reason(ctx),
        "</title>\n"
        	"  </head>\n"
        	"  <body>\n"
        	"    <h1>Error ",
        VRT_INT_string(ctx, VRT_r_beresp_status(ctx)),
        " ",
        VRT_r_beresp_reason(ctx),
        "</h1>\n"
        	"    <p>",
        VRT_r_beresp_reason(ctx),
        "</p>\n"
        	"    <h3>Guru Meditation:</h3>\n"
        	"    <p>XID: ",
        VRT_r_bereq_xid(ctx),
        "</p>\n"
        	"    <hr>\n"
        	"    <p>Varnish cache server</p>\n"
        	"  </body>\n"
        	"</html>\n"
        	"",
        vrt_magic_string_end
);
      VRT_handling(ctx, VCL_RET_DELIVER);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_backend_fetch(VRT_CTX)
{
  /* ... from ('Builtin' Line 150 Pos 5) */
  {
    {
      VRT_count(ctx, 30);
      VRT_handling(ctx, VCL_RET_FETCH);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_backend_response(VRT_CTX)
{
  /* ... from ('input' Line 12 Pos 5) */
  {
    {
      VRT_count(ctx, 2);
      if (
        VRT_re_match(ctx, VRT_GetHdr(ctx, &VGC_HDR_BEREQ_host), VGC_re_1)
      )
        {
          VRT_count(ctx, 3);
          VRT_l_beresp_storage_hint(ctx, 
            "foo",
              vrt_magic_string_end
          );
          VRT_SetHdr(ctx, &VGC_HDR_BERESP_x_2d_storage,
            "foo",
              vrt_magic_string_end
          );
        }
      else if (
        VRT_re_match(ctx, VRT_GetHdr(ctx, &VGC_HDR_BEREQ_host), VGC_re_2)
      )
        {
          VRT_count(ctx, 4);
          VRT_l_beresp_storage_hint(ctx, 
            "bar",
              vrt_magic_string_end
          );
          VRT_SetHdr(ctx, &VGC_HDR_BERESP_x_2d_storage,
            "bar",
              vrt_magic_string_end
          );
        }
      else
        {
          VRT_count(ctx, 5);
          VRT_l_beresp_storage_hint(ctx, 
            "default",
              vrt_magic_string_end
          );
          VRT_SetHdr(ctx, &VGC_HDR_BERESP_x_2d_storage,
            "default",
              vrt_magic_string_end
          );
        }
    }
  }
  /* ... from ('Builtin' Line 154 Pos 5) */
  {
    {
      VRT_count(ctx, 31);
      if (
        (
          (VRT_r_beresp_ttl(ctx) <= 0)||
          (VRT_GetHdr(ctx, &VGC_HDR_BERESP_Set_2d_Cookie) != 0)||
          VRT_re_match(ctx, VRT_GetHdr(ctx, &VGC_HDR_BERESP_Surrogate_2d_control), VGC_re_3)||
          ((
            !((VRT_GetHdr(ctx, &VGC_HDR_BERESP_Surrogate_2d_Control) != 0))&&
            VRT_re_match(ctx, VRT_GetHdr(ctx, &VGC_HDR_BERESP_Cache_2d_Control), VGC_re_4)))||
          !VRT_strcmp(VRT_GetHdr(ctx, &VGC_HDR_BERESP_Vary), "*"))
      )
        {
          VRT_count(ctx, 32);
          VRT_l_beresp_ttl(ctx, 
            120
          );
          VRT_l_beresp_uncacheable(ctx, 
            (0==0)
          );
        }
      VRT_count(ctx, 33);
      VRT_handling(ctx, VCL_RET_DELIVER);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_deliver(VRT_CTX)
{
  /* ... from ('input' Line 25 Pos 5) */
  {
    {
      VRT_count(ctx, 6);
    }
  }
  /* ... from ('Builtin' Line 119 Pos 5) */
  {
    {
      VRT_count(ctx, 28);
      VRT_handling(ctx, VCL_RET_DELIVER);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_fini(VRT_CTX)
{
  /* ... from ('Builtin' Line 197 Pos 5) */
  {
    {
      VRT_count(ctx, 36);
      VRT_handling(ctx, VCL_RET_OK);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_hash(VRT_CTX)
{
  /* ... from ('Builtin' Line 87 Pos 5) */
  {
    {
      VRT_count(ctx, 18);
      VRT_hashdata(ctx,
        VRT_r_req_url(ctx),
        vrt_magic_string_end
      );
      if (
        (VRT_GetHdr(ctx, &VGC_HDR_REQ_host) != 0)
      )
        {
          VRT_count(ctx, 19);
          VRT_hashdata(ctx,
            VRT_GetHdr(ctx, &VGC_HDR_REQ_host),
            vrt_magic_string_end
          );
        }
      else
        {
          VRT_count(ctx, 20);
          VRT_hashdata(ctx,
            VRT_IP_string(ctx, VRT_r_server_ip(ctx)),
            vrt_magic_string_end
          );
        }
      VRT_handling(ctx, VCL_RET_LOOKUP);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_hit(VRT_CTX)
{
  /* ... from ('Builtin' Line 101 Pos 5) */
  {
    {
      VRT_count(ctx, 22);
      if (
        (VRT_r_obj_ttl(ctx) >= 0)
      )
        {
          VRT_count(ctx, 23);
          VRT_handling(ctx, VCL_RET_DELIVER);
          return (1);
        }
      VRT_count(ctx, 24);
      if (
        ((VRT_r_obj_ttl(ctx)+VRT_r_obj_grace(ctx)) > 0)
      )
        {
          VRT_count(ctx, 25);
          VRT_handling(ctx, VCL_RET_DELIVER);
          return (1);
        }
      VRT_count(ctx, 26);
      VRT_handling(ctx, VCL_RET_MISS);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_init(VRT_CTX)
{
  VRT_handling(ctx, VCL_RET_OK);
  /* ... from ('Builtin' Line 194 Pos 5) */
  {
    {
      VRT_count(ctx, 35);
    }
  }
  return(1);
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_miss(VRT_CTX)
{
  /* ... from ('Builtin' Line 115 Pos 5) */
  {
    {
      VRT_count(ctx, 27);
      VRT_handling(ctx, VCL_RET_FETCH);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_pass(VRT_CTX)
{
  /* ... from ('Builtin' Line 83 Pos 5) */
  {
    {
      VRT_count(ctx, 17);
      VRT_handling(ctx, VCL_RET_FETCH);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_pipe(VRT_CTX)
{
  /* ... from ('Builtin' Line 74 Pos 5) */
  {
    {
      VRT_count(ctx, 16);
      VRT_handling(ctx, VCL_RET_PIPE);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_purge(VRT_CTX)
{
  /* ... from ('Builtin' Line 97 Pos 5) */
  {
    {
      VRT_count(ctx, 21);
      VRT_synth(ctx,
        200
        ,
        "Purged"
      );
      VRT_handling(ctx, VCL_RET_SYNTH);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_recv(VRT_CTX)
{
  /* ... from ('input' Line 9 Pos 5) */
  {
    {
      VRT_count(ctx, 1);
    }
  }
  /* ... from ('Builtin' Line 47 Pos 5) */
  {
    {
      VRT_count(ctx, 7);
      if (
        !VRT_strcmp(VRT_r_req_method(ctx), "PRI")
      )
        {
          VRT_count(ctx, 8);
          VRT_synth(ctx,
            405
            ,
            (const char*)0
          );
          VRT_handling(ctx, VCL_RET_SYNTH);
          return (1);
        }
      VRT_count(ctx, 9);
      if (
        (
          VRT_strcmp(VRT_r_req_method(ctx), "GET")&&
          VRT_strcmp(VRT_r_req_method(ctx), "HEAD")&&
          VRT_strcmp(VRT_r_req_method(ctx), "PUT")&&
          VRT_strcmp(VRT_r_req_method(ctx), "POST")&&
          VRT_strcmp(VRT_r_req_method(ctx), "TRACE")&&
          VRT_strcmp(VRT_r_req_method(ctx), "OPTIONS")&&
          VRT_strcmp(VRT_r_req_method(ctx), "DELETE"))
      )
        {
          VRT_count(ctx, 10);
          VRT_handling(ctx, VCL_RET_PIPE);
          return (1);
        }
      VRT_count(ctx, 11);
      if (
        (
          VRT_strcmp(VRT_r_req_method(ctx), "GET")&&
          VRT_strcmp(VRT_r_req_method(ctx), "HEAD"))
      )
        {
          VRT_count(ctx, 12);
          VRT_handling(ctx, VCL_RET_PASS);
          return (1);
        }
      VRT_count(ctx, 13);
      if (
        (
          (VRT_GetHdr(ctx, &VGC_HDR_REQ_Authorization) != 0)||
          (VRT_GetHdr(ctx, &VGC_HDR_REQ_Cookie) != 0))
      )
        {
          VRT_count(ctx, 14);
          VRT_handling(ctx, VCL_RET_PASS);
          return (1);
        }
      VRT_count(ctx, 15);
      VRT_handling(ctx, VCL_RET_HASH);
      return (1);
    }
  }
}

int __match_proto__(vcl_func_f)
VGC_function_vcl_synth(VRT_CTX)
{
  /* ... from ('Builtin' Line 126 Pos 5) */
  {
    {
      VRT_count(ctx, 29);
      VRT_SetHdr(ctx, &VGC_HDR_RESP_Content_2d_Type,
        "text/html; charset=utf-8",
          vrt_magic_string_end
      );
      VRT_SetHdr(ctx, &VGC_HDR_RESP_Retry_2d_After,
        "5",
          vrt_magic_string_end
      );
      VRT_synth_page(ctx,       "<!DOCTYPE html>\n"
        	"<html>\n"
        	"  <head>\n"
        	"    <title>",
        VRT_INT_string(ctx, VRT_r_resp_status(ctx)),
        " ",
        VRT_r_resp_reason(ctx),
        "</title>\n"
        	"  </head>\n"
        	"  <body>\n"
        	"    <h1>Error ",
        VRT_INT_string(ctx, VRT_r_resp_status(ctx)),
        " ",
        VRT_r_resp_reason(ctx),
        "</h1>\n"
        	"    <p>",
        VRT_r_resp_reason(ctx),
        "</p>\n"
        	"    <h3>Guru Meditation:</h3>\n"
        	"    <p>XID: ",
        VRT_r_req_xid(ctx),
        "</p>\n"
        	"    <hr>\n"
        	"    <p>Varnish cache server</p>\n"
        	"  </body>\n"
        	"</html>\n"
        	"",
        vrt_magic_string_end
);
      VRT_handling(ctx, VCL_RET_DELIVER);
      return (1);
    }
  }
}

static int
VGC_Load(VRT_CTX)
{

	vgc_inistep = 0;

	/* 1 */
	if (VRT_Vmod_Init(&VGC_vmod_std,
	    &Vmod_std_Func,
	    sizeof(Vmod_std_Func),
	    "std",
	    "/usr/lib64/varnish/vmods/libvmod_std.so",
	    "PRIGUGDCCKRJWOSEJJPKGZYYAFHPDYKW",
	    ctx))
		return(1);
	vgc_inistep = 1;

	/* 2 */
	vgc_backend_default =
	    VRT_new_backend(ctx, &vgc_dir_priv_vgc_backend_default);
	vgc_inistep = 2;

	/* 3 */
	VRT_re_init(&VGC_re_1, "foo");
	vgc_inistep = 3;

	/* 4 */
	VRT_re_init(&VGC_re_2, "bar");
	vgc_inistep = 4;

	/* 5 */
	VRT_re_init(&VGC_re_3, "no-store");
	vgc_inistep = 5;

	/* 6 */
	VRT_re_init(&VGC_re_4, "no-cache|no-store|private");
	vgc_inistep = 6;

	(void)VGC_function_vcl_init(ctx);
	return(*ctx->handling == VCL_RET_OK ? 0: -1);
}

static int
VGC_Discard(VRT_CTX)
{

	(void)VGC_function_vcl_fini(ctx);

	/* 6 */
	if (vgc_inistep >= 6) {
		VRT_re_fini(VGC_re_4);
	}

	/* 5 */
	if (vgc_inistep >= 5) {
		VRT_re_fini(VGC_re_3);
	}

	/* 4 */
	if (vgc_inistep >= 4) {
		VRT_re_fini(VGC_re_2);
	}

	/* 3 */
	if (vgc_inistep >= 3) {
		VRT_re_fini(VGC_re_1);
	}

	/* 1 */
	if (vgc_inistep >= 1) {
		VRT_priv_fini(&vmod_priv_std);
		VRT_Vmod_Fini(&VGC_vmod_std);
	}

	return(0);
}

static int
VGC_Event(VRT_CTX, enum vcl_event_e ev)
{
	if (ev == VCL_EVENT_LOAD)
		return(VGC_Load(ctx));
	if (ev == VCL_EVENT_DISCARD)
		return(VGC_Discard(ctx));

	return (0);
}

const struct VCL_conf VCL_conf = {
	.magic = VCL_CONF_MAGIC,
	.event_vcl = VGC_Event,
	.default_director = &vgc_backend_default,
	.ref = VGC_ref,
	.nref = VGC_NREFS,
	.nsrc = VGC_NSRCS,
	.srcname = srcname,
	.srcbody = srcbody,
	.backend_error_func = VGC_function_vcl_backend_error,
	.backend_fetch_func = VGC_function_vcl_backend_fetch,
	.backend_response_func = VGC_function_vcl_backend_response,
	.deliver_func = VGC_function_vcl_deliver,
	.fini_func = VGC_function_vcl_fini,
	.hash_func = VGC_function_vcl_hash,
	.hit_func = VGC_function_vcl_hit,
	.init_func = VGC_function_vcl_init,
	.miss_func = VGC_function_vcl_miss,
	.pass_func = VGC_function_vcl_pass,
	.pipe_func = VGC_function_vcl_pipe,
	.purge_func = VGC_function_vcl_purge,
	.recv_func = VGC_function_vcl_recv,
	.synth_func = VGC_function_vcl_synth,
};


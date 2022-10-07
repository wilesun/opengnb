/*
   Copyright (C) gnbdev

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "gnb_config_sqlite.h"
#include "sqlite3.h"

typedef struct _gnb_conf_node_opt_t {
    char key[64];
    char value[256];
} gnb_conf_node_opt_t;

typedef struct _gnb_conf_route_t {
    uint32_t nodeid;
    char tun_ipv4[20];
    char tun_netmask[20];
} gnb_conf_route_t;

typedef struct _gnb_conf_sqlite_ctx_t {
    sqlite3 *db;
    gnb_log_ctx_t *log;
} gnb_conf_sqlite_ctx_t;

static gnb_conf_sqlite_ctx_t ctx;

static int open_conf_sqlite() {
    int rc = sqlite3_open("zsl.db", &ctx.db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "无法打开数据库: %s\n", sqlite3_errmsg(ctx.db));
        sqlite3_close(ctx.db);
        return SQLITE_ERROR;
    }

    char *zErrMsg = 0;
    rc = sqlite3_exec(ctx.db,
                      "create table if not exists node(nodeid bigint primary key, private_key varchar(1024), public_key varchar(1024), if_up varchar(1024), if_down varchar(1024))",
                      NULL,
                      0,
                      &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(ctx.db);
        return SQLITE_ERROR;
    }

    rc = sqlite3_exec(ctx.db,
                      "create table if not exists node_params(nodeid bigint, key varchar(64), val varchar(256),PRIMARY KEY (nodeid, key))",
                      NULL,
                      0,
                      &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(ctx.db);
        return (1);
    }

    rc = sqlite3_exec(ctx.db,
                      "create table if not exists indexes(nodeid bigint, attrib varchar(5), inodeid bigint, host varchar(64), port SMALLINT, primary key(nodeid, inodeid))",
                      NULL,
                      0,
                      &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(ctx.db);
        return SQLITE_ERROR;
    }

    rc = sqlite3_exec(ctx.db,
                      "create table if not exists route(nodeid bigint, rnodeid bigint, tun_ipv4 varchar(20), tun_netmask varchar(20), public_key varchar(1024), primary key(nodeid, rnodeid, tun_ipv4))",
                      NULL,
                      0,
                      &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(ctx.db);
        return SQLITE_ERROR;
    }

    rc = sqlite3_exec(ctx.db,
                      "create table if not exists relay(nodeid bigint, rnodeid bigint, relay_mode varchar(20), relay_nodeid1 varchar(20), relay_nodeid2 varchar(20), relay_nodeid3 varchar(20), relay_nodeid4 varchar(20), relay_nodeid5 varchar(20))",
                      NULL,
                      0,
                      &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(ctx.db);
        return SQLITE_ERROR;
    }
    return SQLITE_OK;
}

static gnb_conf_route_t *get_conf_node(char *nodeid, int *rowCount) {

}

static gnb_conf_route_t *get_conf_routes(uint32_t nodeid, int *rowCount) {
    sqlite3_stmt *res = 0;
    int rc = sqlite3_prepare_v2(ctx.db, "select rnodeid nodeid, tun_ipv4, tun_netmask from route where nodeid=?", -1,
                                &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(ctx.db));
        return NULL;
    }
    rc = sqlite3_bind_int64(res, 1, (sqlite3_int64) nodeid);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Bind error: %s\n", sqlite3_errmsg(ctx.db));
        return NULL;
    }
    sqlite3_reset(res);
    int rows = 0;
    while (sqlite3_step(res) != SQLITE_DONE) {
        rows++;
    }
    sqlite3_reset(res);
    gnb_conf_route_t *routes = malloc(rows * sizeof(gnb_conf_route_t));
    while (sqlite3_step(res) != SQLITE_DONE) {
        routes->nodeid = (uint32_t) sqlite3_column_int64(res, 0);
        strcpy(routes->tun_ipv4, (const char *restrict) sqlite3_column_text(res, 1));
        strcpy(routes->tun_netmask, (const char *restrict) sqlite3_column_text(res, 2));
        routes++;
    }
    routes = routes - rows;
    sqlite3_finalize(res);
    *rowCount = rows;
    return routes;
}

void local_node_sqlite_config(gnb_core_t *gnb_core) {

}

size_t gnb_get_node_num_from_sqlite(gnb_conf_t *conf) {
    if (ctx.db == NULL) {
        if (open_conf_sqlite() != 0) {
            return 0;
        }
    }
    int rowCount = 0;
    gnb_conf_route_t *routes = get_conf_routes(conf->local_uuid, &rowCount);
    if (routes == NULL) {
        sqlite3_close(ctx.db);
        return 0;
    }
    free(routes);
    return rowCount;
}

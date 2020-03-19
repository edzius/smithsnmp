/*
 * This file is part of SmithSNMP
 * Copyright (C) 2014, Credo Semiconductor Inc.
 * Copyright (C) 2015, Leo Ma <begeekmyfriend@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef _ANS1_H_
#define _ANS1_H_

#include <stdint.h>

#define ASN1_OID_MAX_LEN     64
#define ASN1_VALUE_MAX_LEN   (1024)
#define ASN1_TAG_VALID(tag)  ((tag) < ASN1_TAG_NO_SUCH_OBJ)

/* SNMP request type */
typedef enum snmp_request {
  SNMP_REQ_GET     = 0xA0,
  SNMP_REQ_GETNEXT = 0xA1,
  SNMP_RESP        = 0xA2,
  SNMP_REQ_SET     = 0xA3,
  SNMP_TRAP_V1     = 0xA4,
  SNMP_REQ_BULKGET = 0xA5,
  SNMP_REQ_INFO    = 0xA6,
  SNMP_TRAP_V2     = 0xA7,
  SNMP_REPO        = 0xA8,
} SNMP_REQ_E;

/* ASN1 variable type */
enum asn1_variable_type {
  ASN1_TAG_BOOL            = 0x01,
  ASN1_TAG_INT             = 0x02,
  ASN1_TAG_BITSTR          = 0x03,
  ASN1_TAG_OCTSTR          = 0x04,
  ASN1_TAG_NUL             = 0x05,
  ASN1_TAG_OBJID           = 0x06,
  ASN1_TAG_SEQ             = 0x30,
  ASN1_TAG_IPADDR          = 0x40,
  ASN1_TAG_CNT             = 0x41,
  ASN1_TAG_GAU             = 0x42,
  ASN1_TAG_TIMETICKS       = 0x43,
  ASN1_TAG_OPAQ            = 0x44,
  ASN1_TAG_CNT64           = 0x46,
  ASN1_TAG_NO_SUCH_OBJ     = 0x80,
  ASN1_TAG_NO_SUCH_INST    = 0x81,
  ASN1_TAG_END_OF_MIB_VIEW = 0x82,
};

/* A map of simple data type syntax between ANSI C and ASN.1 */
typedef int integer_t;
typedef char octstr_t;
typedef long opaq_t;
typedef unsigned char ipaddr_t;
typedef unsigned int oid_t;
typedef unsigned int count_t;
typedef unsigned int count32_t;
typedef unsigned long long count64_t;
typedef unsigned int gauge_t;
typedef unsigned int timeticks_t;

/* variable as TLV */
typedef struct {
  uint8_t tag;
  /* Number of elements according to tag */
  uint16_t len;
  union {
    integer_t i;
    count_t c;
    count32_t c32;
    count64_t c64;
    ipaddr_t ip[6];
    octstr_t s[ASN1_VALUE_MAX_LEN];
    opaq_t o[ASN1_VALUE_MAX_LEN];
    oid_t id[ASN1_OID_MAX_LEN];
    gauge_t g;
    timeticks_t t;
  } value;
} Variable;

#define tag(var) ((var)->tag)
#define length(var) ((var)->len)
#define value(var) ((void *)&((var)->value))
#define integer(var) ((var)->value.i)
#define opaque(var) ((var)->value.o)
#define octstr(var) ((var)->value.s)
#define count(var) ((var)->value.c)
#define count32(var) ((var)->value.c32)
#define count64(var) ((var)->value.c64)
#define oid(var) ((var)->value.id)
#define ipaddr(var) ((var)->value.ip)
#define gauge(var) ((var)->value.g)
#define timeticks(var) ((var)->value.t)

#endif /* _ANS1_H_ */

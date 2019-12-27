// Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
//
// This file is subject to the terms and conditions defined in file 'LICENSE',
// which is part of this source code package.

#ifndef _ral_h_
#define _ral_h_

#if defined(CFG_lgw1) && defined(CFG_lgw2)
#error Only one of the two params can be set: CFG_lgw1 CFG_lgw2
#endif

#include "s2e.h"
#include "timesync.h"

// Encoding of xtime:
//  bits:
//   63    sign (always positive)
//   62-56 radio unit where the time stamp originated from (max 128)
//   55-48 random value to disambiguate different SX1301 sessions (never 0, aka valid xtime is never 0)
//   47-0  microseconds since SX1301 start (rollover every 9y >> uptime of sessions)
//
// Encoding of rctx:
//   6-0   radio unit
#define RAL_TXUNIT_SHIFT 56
#define RAL_XTSESS_SHIFT 48
#define RAL_TXUNIT_MASK  0x7F
#define RAL_XTSESS_MASK  0xFF

#define RAL_TX_OK     0  // ok
#define RAL_TX_FAIL  -1  // unspecific error
#define RAL_TX_NOCA  -2  // channel access denied (LBT)

#define ral_xtime2sess(  xtime) ((u1_t)(((xtime)>>RAL_XTSESS_SHIFT)&RAL_XTSESS_MASK))
#define ral_xtime2txunit(xtime) ((u1_t)(((xtime)>>RAL_TXUNIT_SHIFT)&RAL_TXUNIT_MASK))
#define ral_xtime2rctx(  xtime) ((sL_t)ral_xtime2txunit(xtime))
#define ral_rctx2txunit(  rctx) ((u1_t)((rctx)&RAL_TXUNIT_MASK))

struct chrps {
    u1_t minSF :3; // s2w SF* enum
    u1_t maxSF :3;
    u1_t bw    :2; // s2e BW* enum
};

typedef struct {
    u4_t freq[MAX_UPCHNLS];
    struct chrps rps[MAX_UPCHNLS];
} chdefl_t;

typedef struct {
    u4_t freq;
    struct chrps rps;
} chdef_t;

enum {
    CHALLOC_START,
    CHALLOC_CHIP_START,
    CHALLOC_CH,
    CHALLOC_CHIP_DONE,
    CHALLOC_DONE
};

typedef union {
struct {
    u1_t chip  :3 ; // MAX_130X <= 8
    u1_t chan  :4 ; // 10 channels per chip
    u1_t rff   :1 ; // 2 RFF per chip
    u4_t rff_freq;
    chdef_t chdef;
};
// CHALLOC_CHIP_DONE
struct {
    u1_t chipid  :4 ; // MAX_130X <= 8
    u1_t chans   :4 ; // 10 channels per chip
    u4_t minFreq;
    u4_t maxFreq;
};
} challoc_t;

typedef void (*challoc_cb) (void* ctx, challoc_t* ch, int flag);
int   ral_challoc (chdefl_t* upchs, challoc_cb alloc_cb, void* ctx);

int ral_rps2bw (rps_t rps);
int ral_rps2sf (rps_t rps);

void  ral_ini ();
void  ral_stop ();
int   ral_config (str_t hwspec, u4_t cca_region, char* json, int jsonlen, chdefl_t* upchs);
int   ral_txstatus (u1_t txunit);
void  ral_txabort (u1_t txunit);
int   ral_tx  (txjob_t* txjob, s2ctx_t* s2ctx, int nocca);
u1_t  ral_altAntennas (u1_t txunit);


// RAL internal APIs and shared code
int ral_getTimesync (u1_t pps_en, sL_t* last_xtime, timesync_t* timesync);


#endif // _ral_h_

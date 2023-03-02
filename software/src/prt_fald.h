/*
     __        __   __   ___ ___ ___  __  
    |__)  /\  |__) |__) |__   |   |  /  \ 
    |    /~~\ |  \ |  \ |___  |   |  \__/ 

    Module: FALD Header
    (c) 2023 by Parretto B.V.

    History
    =======
    v1.0 - Initial release

    License
    =======
    This License will apply to the use of the IP-core (as defined in the License). 
    Please read the License carefully so that you know what your rights and obligations are when using the IP-core.
    The acceptance of this License constitutes a valid and binding agreement between Parretto and you for the use of the IP-core. 
    If you download and/or make any use of the IP-core you agree to be bound by this License. 
    The License is available for download and print at www.parretto.com/license.html
    Parretto grants you, as the Licensee, a free, non-exclusive, non-transferable, limited right to use the IP-core 
    solely for internal business purposes for the term and conditions of the License. 
    You are also allowed to create Modifications for internal business purposes, but explicitly only under the conditions of art. 3.2.
    You are, however, obliged to pay the License Fees to Parretto for the use of the IP-core, or any Modification, in, or embodied in, 
    a physical or non-tangible product or service that has substantial commercial, industrial or non-consumer uses. 
*/

#pragma once

// Contorl register
#define PRT_FALD_DEV_CTL_IG_SHIFT		0
#define PRT_FALD_DEV_CTL_OG_SHIFT		8

// Outgress
#define PRT_FALD_OG_CTL				    0
#define PRT_FALD_OG_BEAT			    1
#define PRT_FALD_OG_ZONES			    2
#define PRT_FALD_OG_GAIN_BIAS		    3
#define PRT_FALD_OG_BLK	        	    4

#define PRT_FALD_OG_CTL_RUN			    (1 << 0)
#define PRT_FALD_OG_CTL_LPB_CLR		    (1 << 1)
#define PRT_FALD_OG_BEAT_PERIOD_SHIFT   16
#define PRT_FALD_OG_ZONES_WIDTH_SHIFT   16
#define PRT_FALD_OG_ZONES_HEIGHT_SHIFT  24
#define PRT_FALD_OG_BIAS_SHIFT		    8
#define PRT_FALD_OG_BLK_HEIGHT_SHIFT    8

// Device structure
typedef struct {
	prt_u32 ctl;
   	prt_u32 ig;		// Ingress 
	prt_u32 og;		// Outgress
	prt_u32 lpb;		// Led pixel buffer
} prt_fald_dev_struct;

// Data structure
typedef struct {
	volatile prt_fald_dev_struct 	*dev;	// Device
    prt_u16 zones;
} prt_fald_ds_struct;

// Prototypes
void prt_fald_set_base (prt_fald_ds_struct *fald, prt_u32 base);
void prt_fald_set_og (prt_fald_ds_struct *fald, prt_u8 og, prt_u32 dat);
prt_u32 prt_fald_get_og (prt_fald_ds_struct *fald, prt_u8 og);
void prt_fald_set_beat (prt_fald_ds_struct *fald, prt_u16 init, prt_u16 period);
void prt_fald_set_zones (prt_fald_ds_struct *fald, prt_u16 zones, prt_u8 zone_width, prt_u8 zone_height);
void prt_fald_set_gain_bias (prt_fald_ds_struct *fald, prt_u8 gain, prt_u8 bias);
void prt_fald_set_blk (prt_fald_ds_struct *fald, prt_u8 blk_width, prt_u8 blk_height);
void prt_fald_lpb_wr (prt_fald_ds_struct *fald, prt_u8 *buf);
void prt_fald_str (prt_fald_ds_struct *fald);
void prt_fald_stp (prt_fald_ds_struct *fald);

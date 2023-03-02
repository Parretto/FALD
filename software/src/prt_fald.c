/*
     __        __   __   ___ ___ ___  __  
    |__)  /\  |__) |__) |__   |   |  /  \ 
    |    /~~\ |  \ |  \ |___  |   |  \__/ 

    Module: FALD Driver
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

// Includes
#include "prt_types.h"
#include "prt_fald.h"
#include "prt_printf.h"

// Set base address
void prt_fald_set_base (prt_fald_ds_struct *fald, prt_u32 base)
{
	// Base address
	fald->dev = (prt_fald_dev_struct *) base;
}

// Write outgress
void prt_fald_set_og (prt_fald_ds_struct *fald, prt_u8 og, prt_u32 dat)
{
	fald->dev->ctl = (og << PRT_FALD_DEV_CTL_OG_SHIFT);
	fald->dev->og = dat;
}

// Read outgress
prt_u32 prt_fald_get_og (prt_fald_ds_struct *fald, prt_u8 og)
{
	fald->dev->ctl = (og << PRT_FALD_DEV_CTL_OG_SHIFT);
	return fald->dev->og;
}

// Set beat
void prt_fald_set_beat (prt_fald_ds_struct *fald, prt_u16 init, prt_u16 period)
{
	// Variables
	prt_u32 dat;

	dat = period;
	dat <<= PRT_FALD_OG_BEAT_PERIOD_SHIFT;
	dat |= init;

	prt_fald_set_og (fald, PRT_FALD_OG_BEAT, dat);
}

// Set zones
void prt_fald_set_zones (prt_fald_ds_struct *fald, prt_u16 zones, prt_u8 zone_width, prt_u8 zone_height)
{
	// Variables
	prt_u32 dat;

	// Zones
	dat = zones;

	// Zone width
	dat |= (zone_width << PRT_FALD_OG_ZONES_WIDTH_SHIFT);

	// Zone height
	dat |= (zone_height << PRT_FALD_OG_ZONES_HEIGHT_SHIFT);

	prt_fald_set_og (fald, PRT_FALD_OG_ZONES, dat);

	// Store in data structure
	fald->zones = zones;
}

// Set gain and bias
void prt_fald_set_gain_bias (prt_fald_ds_struct *fald, prt_u8 gain, prt_u8 bias)
{
	// Variables
	prt_u32 dat;

	dat = bias;
	dat <<= PRT_FALD_OG_BIAS_SHIFT;
	
	dat |= gain;

	prt_fald_set_og (fald, PRT_FALD_OG_GAIN_BIAS, dat);
}

// Set block size
void prt_fald_set_blk (prt_fald_ds_struct *fald, prt_u8 blk_width, prt_u8 blk_height)
{
	// Variables
	prt_u32 dat;

	dat = blk_height;
	dat <<= PRT_FALD_OG_BLK_HEIGHT_SHIFT;
	
	dat |= blk_width;

	prt_fald_set_og (fald, PRT_FALD_OG_BLK, dat);
}

// Write led pixel buffer
void prt_fald_lpb_wr (prt_fald_ds_struct *fald, prt_u8 *buf)
{
	// Variables
	prt_u32 dat;
	prt_u16 zones = fald->zones;

	// Read control register
	dat = prt_fald_get_og (fald, PRT_FALD_OG_CTL);

	// Set led pixel buffer clear
	dat |= PRT_FALD_OG_CTL_LPB_CLR;
	
	// Write control register
	prt_fald_set_og (fald, PRT_FALD_OG_CTL, dat);

	// Clear led pixel buffer clear
	dat &= ~(PRT_FALD_OG_CTL_LPB_CLR);

	// Write control register
	prt_fald_set_og (fald, PRT_FALD_OG_CTL, dat);

	// Copy data
	for (prt_u16 i = 0; i < zones; i++)
	{
		fald->dev->lpb = *(buf + i);
	}
}

// Start
void prt_fald_str (prt_fald_ds_struct *fald)
{
	// Variables
	prt_u32 dat;

	// Read control register
	dat = prt_fald_get_og (fald, PRT_FALD_OG_CTL);

	// Set run flag
	dat |= PRT_FALD_OG_CTL_RUN;
	
	// Write control register
	prt_fald_set_og (fald, PRT_FALD_OG_CTL, dat);
}

// Stop
void prt_fald_stp (prt_fald_ds_struct *fald)
{
	// Variables
	prt_u32 dat;

	// Read control register
	dat = prt_fald_get_og (fald, PRT_FALD_OG_CTL);

	// Clear run flag
	dat &= ~(PRT_FALD_OG_CTL_RUN);
	
	// Write control register
	prt_fald_set_og (fald, PRT_FALD_OG_CTL, dat);
}

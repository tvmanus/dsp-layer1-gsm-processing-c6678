/*
 * phy_read_write.c
 *
 *  Created on: Jul 21, 2014
 *      Author: nachiappanr
 */
#include <xdc/std.h>
#include "csl_mdio.h"
#include "csl_mdioAux.h"
#include "UsrConfig.h"

void phy_read_write(uint32_t port_num)
{
    uint8_t reg=0;
    CSL_MDIO_USERACCESS    user_access_reg;

	uart_write("platform_get_phy_link_status (portnum = %d) called \n", port_num);


/* ***** Read register 0 ********** */
    for(reg=0;reg<32;reg++)
    {
          user_access_reg.phyAddr = port_num;       // Setup phy and MDIO register address
          user_access_reg.regAddr = reg;

          // Do a read access to the phy's MDIO register
          hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR, user_access_reg.phyAddr) |
                                                          CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, user_access_reg.regAddr) |
                                                          CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 0) |
                                                          CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u);


          // Wait for MDIO state machine finishing
          while (CSL_MDIO_isUserAccessPending (0));

          // Read result from USERACCESS register
          CSL_MDIO_getUserAccessRegister (0, &user_access_reg);

          uart_write("PHY register %d is 0x%04x\n",reg, user_access_reg.data);
    }
}

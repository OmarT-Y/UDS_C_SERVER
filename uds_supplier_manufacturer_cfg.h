/****************************************************************************************************
 *  File Name           : uds_suppiler_manufacturer_cfg.h
 *  Description         : Header file for the supplier checks and manufacturer checks 
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#ifndef UDS_SUPP_MANUF_CFG_H
#define UDS_SUPP_MANUF_CFG_H
#include "uds_server_cfg.h"
#include "uds_types.h"

/**
 * @brief Dummy function that runs at the start of check of Manufacturer or Supplier 
 */
UDS_RESPONSE_SUPPRESSION_t UDS_Manufac_supplier_dummy(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server);
#ifdef UDS_SUPPLIER_CHECK_SUPPORTED
//#include "supplierCheckFile.h"
#define UDS_SUPPLIER_CHECK_FUNCTION UDS_Manufac_supplier_dummy
#endif

#ifdef UDS_MANUFACTURER_CHECK_SUPPORTED
//#include "manufacturerCheckFile.h"
#define UDS_MANUFACTURER_CHECK_FUNCTION UDS_Manufac_supplier_dummy
#endif

#endif
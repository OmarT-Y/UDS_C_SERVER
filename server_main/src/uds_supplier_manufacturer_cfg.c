/****************************************************************************************************
 *  File Name           : uds_suppiler_manufacturer_cfg.h
 *  Description         : Header file for the supplier checks and manufacturer checks 
 *  Author              : eJad SDV SOTA Graduation Project 2025 Team
 *  Modification Logs   : 15-2-2025 File Creation
 ****************************************************************************************************/

#include "uds_supplier_manufacturer_cfg.h"

/*this a test dummy*/
#ifdef UDS_SUPPLIER_CHECK_SUPPORTED
/*#include "supplierCheckFile.h"*/
UDS_RESPONSE_SUPPRESSION_t UDS_Manufac_supplier_dummy(UDS_REQ_t *request,UDS_RES_t * response,UDS_Server_t * server)
{
    return UDS_NO_SUPPRESS_RESPONSE;
}
#endif

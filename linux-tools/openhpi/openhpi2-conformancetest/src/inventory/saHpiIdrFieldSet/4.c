/*      -*- linux-c -*-
 *
 * (C) Copyright IBM Corp. 2004, 2005
 *
 *   This program is free software; you can redistribute it and/or modify 
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or 
 *   (at your option) any later version.
 *   This program is distributed in the hope that it will be useful, 
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *   GNU General Public License for more details. 
 *   You should have received a copy of the GNU General Public License 
 *   along with this program; if not, write to the Free Software 
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 
 *   USA 
 *
 * Author(s):
 *      Carl McAdams <carlmc@us.ibm.com>
 *      Donald A. Barre <dbarre@unh.edu>
 *
 * Spec:        HPI-B.01.01
 * Function:    saHpiIdrFieldSet
 * Description:
 *   Call on a resource which does not support Inventory Data Repositories.
 *   Expected return: SA_ERR_HPI_CAPABILITY.
 * Line:        P111-17:P111-18
 *    
 */

#include <stdio.h>
#include "../include/inventory_test.h"

/**********************************************************************
 *
 * Try setting a field for a resource that does not support inventories.
 *
 **********************************************************************/

int TestField(SaHpiSessionIdT sessionId, SaHpiResourceIdT resourceId)
{
	SaErrorT status;
	int retval = SAF_TEST_UNKNOWN;
	SaHpiIdrFieldT Field;

	Field.Field.Data[0] = 'a';
	Field.Field.DataLength = 1;
	Field.Field.DataType = SAHPI_TL_TYPE_TEXT;
	Field.FieldId = 1;
	Field.Field.Language = SAHPI_LANG_ENGLISH;
	Field.AreaId = 1;
	Field.ReadOnly = SAHPI_FALSE;
	Field.Type = SAHPI_IDR_FIELDTYPE_CUSTOM;

	status = saHpiIdrFieldSet(sessionId,
				  resourceId,
				  SAHPI_DEFAULT_INVENTORY_ID, &Field);

	if (status == SA_ERR_HPI_CAPABILITY) {
		retval = SAF_TEST_PASS;
	} else {
		retval = SAF_TEST_FAIL;
		e_print(saHpiIdrFieldSet, SA_ERR_HPI_CAPABILITY, status);
	}

	return retval;
}

/**********************************************************************
 *
 * Test a resource that does not support inventories.
 *
 **********************************************************************/

int Test_Resource(SaHpiSessionIdT sessionId,
		  SaHpiRptEntryT report, callback2_t func)
{
	int retval = SAF_TEST_NOTSUPPORT;

	if (!hasInventoryCapability(&report)) {
		retval = TestField(sessionId, report.ResourceId);
	}

	return retval;
}

/**********************************************************************
 *
 *
 *
 **********************************************************************/

int main(int argc, char **argv)
{
	return process_all_domains(Test_Resource, NULL, NULL);
}

/***************************************************************************
 *   Nipper - The network infrastructure parser                            *
 *   Copyright (C) 2006 - 2008 by Ian Ventura-Whiting                      *
 *   fizz@titania.co.uk                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version. However, there are a number of    *
 *   exceptions listed below.                                              *
 *                                                                         *
 *   EXCEPTIONS TO THE GPL License:                                        *
 *      1. This code cannot be used as part of a commercial product. If a  *
 *         commercial license is required, contact fizz@titania.co.uk for  *
 *         licensing information.                                          *
 *      2. Any code that integrates Nipper MUST display the copyright      *
 *         information below with the programs own copyright information.  *
 *                                                                         *
 *         "Nipper Copyright (C) 2006 - 2008 by Ian Ventura-Whiting"       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/


void pixUsersConfig(struct nipperConfig *nipper)
{
	// Variables...
	struct enablePIXPassword *enablePIXPointer = 0;
	struct usernamePIX *usernamePIXPointer = 0;

	// Login Password
	if (nipper->pix->password[0] != 0)
	{
		if (nipper->outputFormat == output_xml)
			fprintf(nipper->reportFile, "    <text>");
		fprintf(nipper->reportFile, "%s %s.", settings_logon_password, nipper->pix->password);
		if (nipper->outputFormat == output_xml)
			fprintf(nipper->reportFile, "</text>\n");
		output_newPara(nipper);
	}

	// Enable Password
	if (nipper->pix->enable != 0)
	{
		output_table(nipper, true, settings_enable_table, &report_enablepix_heading);
		enablePIXPointer = nipper->pix->enable;
		while (enablePIXPointer != 0)
		{
			fprintf(nipper->reportFile, "%s%d", nipper->tablerow_start, enablePIXPointer->level);
			fprintf(nipper->reportFile, "%s%s", nipper->tablerow_mid, enablePIXPointer->passwordEncrypted);
			fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			enablePIXPointer = enablePIXPointer->next;
		}
		output_table(nipper, false, settings_enable_table, &report_enablepix_heading);
	}

	// Usernames
	if (nipper->pix->username != 0)
	{
		output_table(nipper, true, settings_users_table, &report_userspix_heading);
		usernamePIXPointer = nipper->pix->username;
		while (usernamePIXPointer != 0)
		{
			fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_start, usernamePIXPointer->username, nipper->tablerow_mid);
			fprintf(nipper->reportFile, "%d%s", usernamePIXPointer->level, nipper->tablerow_mid);
			switch (usernamePIXPointer->encryption)
			{
				case encrypt_none:
					fprintf(nipper->reportFile, "N/A");
					break;
				case encrypt_pix:
					fprintf(nipper->reportFile, "Standard");
					break;
				case encrypt_mschap:
					fprintf(nipper->reportFile, "MS-CHAP");
					addAbbreviation("MS-CHAP", false);
					break;
				case encrypt_ntenc:
					fprintf(nipper->reportFile, "NT Encrypted");
					addAbbreviation("NT", false);
					break;
			}
			if (nipper->passwords == true)
			{
				if (usernamePIXPointer->passwordEncrypted[0] == 0)
					fprintf(nipper->reportFile, "%sNone%s", nipper->tablerow_mid, nipper->tablerow_end);
				else
					fprintf(nipper->reportFile, "%s%s%s", nipper->tablerow_mid, usernamePIXPointer->passwordEncrypted, nipper->tablerow_end);
			}
			else
				fprintf(nipper->reportFile, "%s", nipper->tablerow_end);
			usernamePIXPointer = usernamePIXPointer->next;
		}
		output_table(nipper, false, settings_users_table, &report_userspix_heading);
	}
}



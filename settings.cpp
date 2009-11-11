/***************************************************************************
 *   Copyright (C) 2009 by Andrey Esin                                     *
 *   gmlastik@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *

 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <ReadWriteIni.h>
#include "settings.h"

using namespace std;

Setting::Setting()
{
	//rcFilePath="/program files/gmitter/gmitter.ini";
	//rcFilePath="\\Disk\\Program Files\\gmitter\\gmitter.ini";
	rcFilePath=L"\\Disk\\Program Files\\gmitter\\gmitter.ini";
	
}
void Setting::applySettings(wstring uname, std::wstring pass,std::wstring api,bool is) {
    tw_uname = uname;
    tw_pass = pass;
}

void Setting::parseString(wstring str) {
}

void Setting::loadSettings() {

	TCHAR* sAccount;
	TCHAR* sPass;
	IniReadString(L"config",L"Account",&sAccount,rcFilePath.c_str());
	wsprintf(tw_uname.c_str(),L"%s",sAccount);
	IniReadString(L"config",L"Pass",&sPass,rcFilePath.c_str());
	wsprintf(tw_pass.c_str(),L"%s",sPass);

}

void Setting::saveSettings(std::wstring uname, std::wstring pass) {
    tw_uname = uname;
    tw_pass = pass;

	IniReadString(L"config",L"Account",tw_uname.c_str(),rcFilePath.c_str());
	IniReadString(L"config",L"Pass",    tw_pass.c_str(),rcFilePath.c_str());
}



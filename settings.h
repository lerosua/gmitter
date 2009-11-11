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

#ifndef _SETTINGS_H
#define	_SETTINGS_H

#include "base64.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
//#define UNICODE
#define _UNICODE

using namespace std;

class Setting
{
public:
	Setting();
	void applySettings(wstring uname, wstring pass,wstring api=L"http://li2z.cn/t",bool is=true);
	void loadSettings();
	void saveSettings(wstring uname, wstring pass);
	void parseString(wstring str);
	const std::wstring& GetAccount(){return tw_uname;}
	const std::wstring& GetPass(){return tw_pass;}
	const std::wstring& GetAPI() {return tw_api_url;}
	bool IsSavePass(){return m_save_pass;}
private:
	std::wstring  tw_uname;
	std::wstring  tw_pass;
	bool		m_save_pass;
	std::wstring  tw_api_url;
	std::wstring  rcFilePath;

};

#endif	/* _SETTINGS_H */


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
//#define _UNICODE

using namespace std;

class Setting
{
public:
	Setting();
	void applySettings(string uname, string pass,string api="http://li2z.cn/t",bool is=true);
	void loadSettings();
	void saveSettings();
	void parseString(string str);
	const std::string& GetAccount(){return tw_uname;}
	const std::string& GetPass(){return tw_pass;}
	const std::string& GetAPI() {return tw_api_url;}
	bool IsSavePass(){return m_save_pass;}
private:
	std::string  tw_uname;
	std::string  tw_pass;
	bool		m_save_pass;
	std::string  tw_api_url;
	std::string  rcFilePath;

};

#endif	/* _SETTINGS_H */


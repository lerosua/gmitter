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

#include "settings.h"

using namespace std;

Setting::Setting()
{
	//rcFilePath="/program files/gmitter/gmitter.ini";
	rcFilePath="\\Disk\\Program Files\\gmitter\\gmitter.ini";
	
}
void Setting::applySettings(string uname, std::string pass,std::string api,bool is) {
    tw_uname = uname;
    tw_pass = pass;
}

void Setting::parseString(string str) {
    size_t pos;
    pos = str.find(' ');
    pos = str.find(' ', pos + 1);
    if (str.find("Username") == 0)
        tw_uname = base64_decode(str.substr(pos + 1, str.length() - pos));
    if (str.find("Password") == 0)
        tw_pass = base64_decode(str.substr(pos + 1, str.length() - pos));
    if (str.find("SavePass") == 0)
	    m_save_pass ;
    if (str.find("ApiUrl") == 0)
	    tw_api_url = str.substr(pos+1,str.length()-pos);
}

void Setting::loadSettings() {
    ifstream rcFile;
    rcFile.open(rcFilePath.c_str(), ifstream::in);
    if (rcFile.is_open()) {
        while (!rcFile.eof()) {
            string str;
            getline(rcFile, str);
            if (!str.empty())
                parseString(str);
        }
        rcFile.close();
    } else
        cout << "Unable to open twinyrc";
}

void Setting::saveSettings() {
    ofstream rcFile;
    rcFile.open(rcFilePath.c_str(), ifstream::out);
    if (rcFile.is_open()) {
        rcFile << "Username = " << base64_encode(tw_uname) << endl;
	if(m_save_pass){
		rcFile << "Password = " << base64_encode(tw_pass) << endl;
		rcFile << "SavePass = " << string("1")<<endl;
	}
	else
		rcFile << "SavePass = " << string("0")<<endl;
	rcFile<<"ApiUrl = "<<tw_api_url<<endl;

        rcFile.close();
    } else
        cout << "Error: Unable to open .twinyrc" << endl;
}



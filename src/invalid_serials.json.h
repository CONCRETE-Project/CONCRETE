// Copyright (c) 2018 The PIVX Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.



#ifndef CONCRETE_INVALID_SERIALS_JSON_H
#define CONCRETE_INVALID_SERIALS_JSON_H

#include <string>

/*
            "  {\n"
            "    \"s\": \"c9c868bb56eacfc4f3d829528a0ae812dff26619cd38e6c9a0eea1eacddc84\"\n"
            "  },\n"
            "  {\n"
            "    \"s\": \"17ab90c682a42d7a3b8bd1da019f6e788e82f25220a1cdaca242f15873ee553\"\n"
            "  }\n"
*/

std::string LoadInvalidSerials()
{
    std::string str = "[\n"
            "]";
    return str;
}

#endif //CONCRETE_INVALID_SERIALS_JSON_H

// Copyright (c) 2018 The PIVX Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CONCRETE_INVALID_OUTPOINTS_JSON_H
#define CONCRETE_INVALID_OUTPOINTS_JSON_H
#include <string>

/*
    Example
            "  {\n"
            "    \"txid\": \"00405ad8cc4ec7b6be27dedc6bf19f2febf8e338031fe552d7bf5c0dfd6e67de\",\n"
            "    \"n\": 0\n"
            "  },\n"
*/

std::string LoadInvalidOutPoints()
{
    std::string str = "[\n"
            "]";
    return str;
}

#endif //CONCRETE_INVALID_OUTPOINTS_JSON_H

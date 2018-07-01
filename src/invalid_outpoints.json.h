// Copyright (c) 2018 The PIVX developers
// Copyright (c) 2018 The SLATE developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_INVALID_OUTPOINTS_JSON_H
#define PIVX_INVALID_OUTPOINTS_JSON_H
#include <string>

std::string LoadInvalidOutPoints()
{
    std::string str = "[\n"
            "  {\n"
            "    \"txid\": \"00405ad8cc4ec7b6be27dedc6bf19f2febf8e338031fe552d7bf5c0dfd6e67de\",\n"
            "    \"n\": 0\n"
            "  },\n"
            "  {\n"
            "    \"txid\": \"fff7164737e3437fd27b3787edeb2650eddd07966c492ffb7e0eb537c0a5b850\",\n"
            "    \"n\": 1\n"
            "  }\n"
            "]";
    return str;
}

#endif //PIVX_INVALID_OUTPOINTS_JSON_H

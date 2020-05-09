// Copyright (c) 2019 The PIVX Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CONCRETE_PAIRRESULT_H
#define CONCRETE_PAIRRESULT_H


class PairResult {

public:
    PairResult(bool res):result(res){}
    PairResult(bool res, std::string* statusStr):result(res), status(statusStr){}

    bool result;
    std::string* status = nullptr;
};


#endif //CONCRETE_PAIRRESULT_H

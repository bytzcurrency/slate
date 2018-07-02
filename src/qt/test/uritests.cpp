// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2017 The PIVX developers
// Copyright (c) 2018 The SLATE developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("slate:sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("slate:sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("slate:sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3?label=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3"));
    QVERIFY(rv.label == QString("Some Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("slate:sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("slate:sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("slate:sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3?amount=100&label=Some Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));

    uri.setUrl(QString("slate:sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3?message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("slate://sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3?message=Some Example Address", &rv));
    QVERIFY(rv.address == QString("sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("slate:sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3?req-message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("slate:sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3?amount=1,000&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("slate:sNuuvtcBAppygz4SyVN6schFdR6XHsmuW3?amount=1,000.0&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}

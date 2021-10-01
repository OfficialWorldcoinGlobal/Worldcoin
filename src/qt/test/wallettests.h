#ifndef WORLDCOIN_QT_TEST_WALLETTESTS_H
#define WORLDCOIN_QT_TEST_WALLETTESTS_H

#include <QObject>
#include <QTest>

class WalletTests : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void walletTests();
};

#endif // WORLDCOIN_QT_TEST_WALLETTESTS_H

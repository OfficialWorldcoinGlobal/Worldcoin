// Copyright (c) 2011-2014 The Worldcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef WORLDCOIN_QT_WORLDCOINADDRESSVALIDATOR_H
#define WORLDCOIN_QT_WORLDCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class WorldcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit WorldcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Worldcoin address widget validator, checks for a valid worldcoin address.
 */
class WorldcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit WorldcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // WORLDCOIN_QT_WORLDCOINADDRESSVALIDATOR_H

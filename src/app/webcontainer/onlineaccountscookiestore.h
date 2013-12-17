/*
 * Copyright 2013 Canonical Ltd.
 *
 * This file is part of webbrowser-app.
 *
 * webbrowser-app is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * webbrowser-app is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ONLINEACCOUNTSCOOKIESTORE_H
#define ONLINEACCOUNTSCOOKIESTORE_H

#include "cookiestore.h"

class OnlineAccountsCookieStorePrivate;

class OnlineAccountsCookieStore : public CookieStore
{
    Q_OBJECT
    Q_PROPERTY(quint32 accountId READ accountId WRITE setAccountId NOTIFY accountIdChanged)


public:
    OnlineAccountsCookieStore(QObject *parent = 0);
    ~OnlineAccountsCookieStore();

    quint32 accountId () const;
    void setAccountId (quint32);


Q_SIGNALS:

    void accountIdChanged();


private:

    virtual Cookies doGetCookies() const;
    virtual void doSetCookies(Cookies);


private:

    OnlineAccountsCookieStorePrivate * d_ptr;
    Q_DECLARE_PRIVATE(OnlineAccountsCookieStore)
};

#endif // ONLINEACCOUNTSCOOKIESTORE_H

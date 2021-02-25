#ifndef SCADAWINDOW_H
#define SCADAWINDOW_H

#include <windows.h>
#include <conio.h>
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsDef.h"
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsAPI.h"
#include <string>

#include <iostream>
#include <QWidget>
#include <QPushButton>

struct AdsHdl {
    ULONG in;
    ULONG out;
};

struct AdsData {
    bool    in;
    bool    out;
};

struct AdsName {
    char    in[100];
    char    out[100];
};

struct AdsInfos {
    long        error;
    long        port;
    AmsAddr     addr;
    PAmsAddr    ptr_addr;
    AdsName     names;
    AdsHdl      handlers;
    AdsData     data;
};

class SCADAWindow : public QWidget
{
    Q_OBJECT

    bool        m_state;
    QPushButton *m_in;
    QPushButton *m_out;
    AdsInfos    m_ads;
public:
    explicit SCADAWindow();
    ~SCADAWindow();

    int     initAdsConnection();
    int     getAdsDataHandlers();
    int     getAdsData();

public slots:
    void stateChanged();

};

#endif // SCADAWINDOW_H

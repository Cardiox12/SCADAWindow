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
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

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
    AdsInfos    m_ads;

    QPushButton *m_in_button;
    QPushButton *m_out_button;

    QLabel      *m_in_label;
    QLabel      *m_out_label;

    QHBoxLayout *m_main_layout;
    QVBoxLayout *m_left_layout;
    QVBoxLayout *m_right_layout;
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

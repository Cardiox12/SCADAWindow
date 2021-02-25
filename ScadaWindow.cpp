#include <ScadaWindow.h>

SCADAWindow::SCADAWindow() : QWidget()
{
    m_ads.data.in = false;
    m_ads.data.out = false;

    m_state = false;

    m_main_layout = new QHBoxLayout;
    m_left_layout = new QVBoxLayout;
    m_right_layout = new QVBoxLayout;

    m_in_label = new QLabel("In : ");
    m_out_label = new QLabel("Out : ", this);

    m_in_button = new QPushButton("In", this);
    m_out_button = new QPushButton("Out", this);

    connect(m_in_button, SIGNAL(clicked()), this, SLOT(stateChanged()));
    connect(m_out_button, SIGNAL(clicked()), this, SLOT(stateChanged()));

    // Setting Left Layout
    m_left_layout->addWidget(m_in_button);
    m_left_layout->addWidget(m_out_button);

    // Setting right Layout
    m_right_layout->addWidget(m_in_label);
    m_right_layout->addWidget(m_out_label);

    // Setting main Layout
    m_main_layout->addLayout(m_left_layout);
    m_main_layout->addLayout(m_right_layout);
    setLayout(m_main_layout);


    if ( initAdsConnection() )
        std::cout << "Error connecting to PLC" << std::endl;

    if ( getAdsDataHandlers() )
        std::cout << "Error retrieving handlers from PLC" << std::endl;

    if ( getAdsData() )
        std::cout << "Error retrieving data from PLC" << std::endl;
}

SCADAWindow::~SCADAWindow()
{
    delete m_in_label;
    delete m_out_label;
    m_ads.error = AdsPortClose();
}

int SCADAWindow::initAdsConnection()
{
    m_ads.error = 0;
    m_ads.ptr_addr = &m_ads.addr;
    m_ads.port = AdsPortOpen();
    m_ads.error = AdsGetLocalAddress(m_ads.ptr_addr);

    if ( m_ads.error )
        std::cerr << "Error: AdsGetLocalAddress: " << m_ads.error << std::endl;

    m_ads.ptr_addr->port = AMSPORT_R0_PLC_TC3;

    return ( m_ads.error );
}

int SCADAWindow::getAdsDataHandlers()
{
    strcpy(m_ads.names.in, "MAIN.In");
    strcpy(m_ads.names.out, "MAIN.Out");

    std::cout << "In : " << m_ads.names.in << std::endl;
    std::cout << "Out : " << m_ads.names.out << std::endl;

    // Get handle to the PLC program
    m_ads.error = AdsSyncReadWriteReq(
                m_ads.ptr_addr,
                ADSIGRP_SYM_HNDBYNAME,
                0x0,
                sizeof(m_ads.handlers.in),
                &m_ads.handlers.in,
                strlen(m_ads.names.in),
                m_ads.names.in
    );

    if ( m_ads.error )
        std::cout << "Handling by name failed : " << m_ads.error << std::endl;

    m_ads.error = AdsSyncReadWriteReq(
                m_ads.ptr_addr,
                ADSIGRP_SYM_HNDBYNAME,
                0x0,
                sizeof (m_ads.handlers.out),
                &m_ads.handlers.out,
                strlen(m_ads.names.out),
                m_ads.names.out
    );

    if ( m_ads.error )
        std::cout << "Handling by name failed : " << m_ads.error << std::endl;

    return ( m_ads.error );
}

int  SCADAWindow::getAdsData()
{
    m_ads.error = AdsSyncReadReq(
                m_ads.ptr_addr,
                ADSIGRP_SYM_VALBYHND,
                m_ads.handlers.in,
                sizeof(m_ads.data.in),
                &m_ads.data.in
    );

    if ( m_ads.error )
        std::cout << "Error retrieving data : " << m_ads.error << std::endl;

    m_ads.error = AdsSyncReadReq(
                m_ads.ptr_addr,
                ADSIGRP_SYM_VALBYHND,
                m_ads.handlers.out,
                sizeof(m_ads.data.out),
                &m_ads.data.out
    );

    if ( m_ads.error )
        std::cout << "Error retrieving data : " << m_ads.error << std::endl;

    std::cout << "In data : " << m_ads.data.in << std::endl;
    std::cout << "Out data : " << m_ads.data.out << std::endl;

    return ( m_ads.error );
}

void SCADAWindow::stateChanged()
{
    QObject *object = sender();

    if ( object == m_in_button ){
        std::cout << "State in changed " << std::endl;
        m_ads.data.in = !m_ads.data.in;
        m_ads.error = AdsSyncWriteReq(
                    m_ads.ptr_addr,
                    ADSIGRP_SYM_VALBYHND,
                    m_ads.handlers.in,
                    sizeof (m_ads.data.in),
                    &m_ads.data.in
        );

        if ( m_ads.error )
            std::cout << "Error writing data to PLC" << std::endl;
    } else if ( object == m_out_button ) {
        m_ads.data.out = !m_ads.data.out;
        m_ads.error = AdsSyncWriteReq(
                    m_ads.ptr_addr,
                    ADSIGRP_SYM_VALBYHND,
                    m_ads.handlers.out,
                    sizeof (m_ads.data.out),
                    &m_ads.data.out
        );
        std::cout << "State out changed" << std::endl;
    }
}




















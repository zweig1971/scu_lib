// GSI Gesellschaft für 
// Schwerionenforschung mbH, 
// Darmstadt, Germany 
//
// scumil.h
//
// Autor           : Zweig,Marcus
// Version         : 0.1
// letzte Änderung : 31.08.15
//------------------------------


#include <iostream>
#include <stdio.h>
#include <etherbone.h>
//#include "scumil_def.h"
#include <string.h>
#include <cstring>

using namespace std;

// mil information zur bestimmung der baseadress auf der scu
// --------------
#define vendor  0x0000000000000651
#define product 0x35aa6b96

// DatenTypen
//-----------------
typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

// Timer
// --------------
#define WaitMilBusReadTimeOut   10      
#define WaitMilBusWriteTimeOut  50

// Functionscodes
// --------------
#define Fct_Rd_Stat0            0xC0

// sonstiges
// --------------
#define Fct_Rd_Stat0_AdrMask    0x00FF
#define b_pulse1_frame          0x400
#define b_pulse2_frame          0x800

// Fehlermeldungen 
//----------------
#define status_ok               0x0
#define socketopen_error        0x1
#define deviceopen_error        0x2
#define deviceclose_error       0x4
#define socketclose_error       0x8
#define baseadress_error        0x10
#define device_allrdyopen       0x20
#define device_not_open         0x40
#define timer_error             0x80
#define timeout_write           0x100
#define timeout_read            0x200
#define mil_write_cmd_error     0x400
#define mil_read_error          0x800
#define mil_write_error         0x1000
#define mil_ifknr_error         0x2000
#define device_error            0x4000

// Bitmasken Status 
//----------------
#define interlock               0x1
#define data_rdy                0x2             
#define data_req                0x4
#define ev_fifo_ne              0x8
#define ev_fifo_full            0x10
#define mil_rcv_rdy             0x20
#define mil_cmd_rcv             0x40
#define mil_trm_rdy             0x80
#define mil_rcv_err             0x100
#define ev_reset_on             0x200
#define puls1_frame             0x400
#define puls2_frame             0x800
#define debounce_on             0x1000
#define ev_filt_on              0x2000
#define ev_filt_12_8b           0x4000
#define sel_fpga_n6408          0x8000

// Register Interface Mil-Macro 
//----------------
#define mil_rd_wr_data          0x0
#define mil_wr_cmd              0x4
#define mil_wr_rd_status        0x8
#define rd_clr_no_vw_cnt        0xc
#define rd_wr_not_eq_cnt        0x10
#define rd_wr_ev_fifo           0x14
#define rd_clr_ev_timer         0x18
#define rd_clr_dly_timer        0x1c
#define rd_clr_wait_timer       0x20
#define mil_wr_rd_lemo_conf     0x24
#define mil_wr_rd_lemo_dat      0x28
#define mil_rd_lemo_inp         0x2c


class scu_mil
{
private :

	struct data_scu
	{
		char scu_adress[30];
		eb_socket_t socket;
		eb_device_t device;
		eb_address_t mil_base;
		bool scu_connected;
	};


	data_scu scu_info;

	DWORD mil_status_read(WORD &mil_status);
	DWORD mil_timer_wait(WORD time);
	bool mil_write_wait(void);
	bool mil_read_wait(void);
	bool mil_test_status(WORD statusbit, DWORD &errorstatus);

	DWORD open_scu();
	DWORD close_scu();
	DWORD find_mil();

	DWORD milbus_write(WORD mildata);
	DWORD milbus_write_cmd(int cmd);
	DWORD milbus_read(WORD &mildata);
	
	DWORD event_fifo_read(); 			// not implemented
	DWORD event_timer_read();			// not implemented
	DWORD event_filter_read();			// not implemented
	DWORD event_filter_set();			// not implemented
	
	DWORD irq_mask_read();				// not implemented
	DWORD irq_mask_write();				// not implemented

	DWORD irq_enable();				// not implemented
	DWORD irq_disable();				// not implemented

	DWORD pulse1_en_dis(bool onoff);		// not implemented
	DWORD pulse2_en_dis(bool onoff);		// not implemented
	DWORD puls_set(WORD lemo_nr, WORD vale);	// not implemented
	

public:

	scu_mil(void);
	~scu_mil(void);

	string scu_milerror(DWORD status);

	DWORD scu_milbusopen(const char adress[], DWORD &errorstatus);
	DWORD scu_milbusclose(DWORD &errorstatus);
	bool scu_milstatustest(WORD statusbit, DWORD &errorstatus);
	DWORD scu_timer_wait(DWORD time, DWORD &errorstatus);
	DWORD scu_milbus_write_cmd(BYTE funktionscode, BYTE ifkadresse, DWORD &errorstatus);
	DWORD scu_milbus_write_data(WORD data, DWORD &errorstatus);
	DWORD scu_milbus_read_data(WORD &data, DWORD &errorstatus);
	DWORD scu_milbus_ifk_rd (BYTE ifkadress, BYTE ifkfunktioncode, WORD &data, DWORD &errorstatus);
	DWORD scu_milbus_ifk_wr (BYTE ifkadress, BYTE ifkfunktioncode, WORD data, DWORD &errorstatus);
	bool scu_milbus_ifk_on (BYTE ifkadress, WORD &returnifkad, DWORD &errorstatus);
	
	DWORD scu_milbus_puls1_start(DWORD &errorstatus);	// not implemented
        DWORD scu_milbus_puls1_stop(DWORD &errorstatus);	// not implemented
	DWORD scu_milbus_puls2_start(DWORD &errorstatus);	// not implemented
	DWORD scu_milbus_puls2_stop(DWORD &errorstatus);	// not implemented
};

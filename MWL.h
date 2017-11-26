#ifndef MWL_h
#define MWL_h

#include <Arduino.h>

class MWL
{
	public:
		MWL(int pin_a, int pin_clk_master, int pin_clk_slave);
		void Init_Master();
		void Init_Slave();
		String AwaitMessage(int length);
		void SendMessage(String message);
		
	private:
		int PIN_A;
		int PIN_CLK_MASTER;
		int PIN_CLK_SLAVE;
	
};

#endif

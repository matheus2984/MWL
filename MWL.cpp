#include "Arduino.h"
#include "MWL.h"

MWL::MWL(int pin_a, int pin_clk_master, int pin_clk_slave)
{
	PIN_A = pin_a;
	PIN_CLK_MASTER = pin_clk_master;
	PIN_CLK_SLAVE = pin_clk_slave;
}

void MWL::Init_Master()
{
	pinMode(PIN_A, INPUT);
	pinMode(PIN_CLK_MASTER, OUTPUT);
	pinMode(PIN_CLK_SLAVE, INPUT);
	
	digitalWrite(PIN_CLK_MASTER, LOW);
}

void MWL::Init_Slave()
{
	pinMode(PIN_A, OUTPUT);
	pinMode(PIN_CLK_MASTER, INPUT);
	pinMode(PIN_CLK_SLAVE, OUTPUT);
	
	digitalWrite(PIN_CLK_SLAVE, LOW);
}

String MWL::AwaitMessage(int count)
{
	byte value[count];
	String out = "";
	
	for(int i = 0; i < count; i++)
	{
		for(int j = 7; j >= 0; j--)
		{	
		    digitalWrite(PIN_CLK_MASTER, HIGH);
			while(digitalRead(PIN_CLK_SLAVE) == LOW){} // clockin
			
			if(digitalRead(PIN_A) == HIGH){
				bitWrite(value[i], j, 1);
			}
			else{
				bitWrite(value[i], j, 0);
			}
			digitalWrite(PIN_CLK_MASTER, LOW);
			while(digitalRead(PIN_CLK_SLAVE) == HIGH){} // clockout
		}
		char vchar = value[i];
		out += vchar;
							
	}
	
	return out;
}

void MWL::SendMessage(String message)
{
	for(int i = 0; i< message.length(); i++)
	{
		char toSend = message[i];
		for(int j = 7; j>=0; j--)
		{	
			byte b = bitRead(toSend, j);
			if(b == 1)
				digitalWrite(PIN_A, HIGH);
			else 
				digitalWrite(PIN_A, LOW);
			
			while(digitalRead(PIN_CLK_MASTER) == LOW){}
			digitalWrite(PIN_CLK_SLAVE, HIGH); // clockin
			while(digitalRead(PIN_CLK_MASTER) == HIGH){}
			digitalWrite(PIN_CLK_SLAVE, LOW); // clockout
		}
	}
}






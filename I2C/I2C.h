///////////////////////////////////////////////////////////////////
//
// I2C.h
//
///////////////////////////////////////////////////////////////////

#ifndef I2C_h
	#define I2C_h


#include <inttypes.h>
#include <Wire.h>

class I2C {
	public:
						I2C(const int iDevice, const int iReg, const int iID) ;	
		bool            IsConnected(void) ;
	protected:
		uint8_t			Write(const int iAddress, uint8_t iData);
		uint8_t			Write(const int iAddress, const int iLength, const uint8_t *pData);
		uint8_t			Write(const int iAddress, const int iLength, const int *piData);
		bool			Read(const int iAddress, uint8_t &ucData);
		bool			ReadWORD(int iAddress, uint16_t &uiData);
		bool			Read(const int iAddress, const int iLength, uint8_t *buffer);
		bool			Request(const int iAddress, const int iLength);
		int				m_iDevice;
		int				m_iIdRegister;
		int				m_iID ;
	private:
};


#endif
///////////////////// End of I2C.H ////////////////////////////////
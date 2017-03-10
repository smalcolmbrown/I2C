///////////////////////////////////////////////////////////////////
//
// I2C.cpp
//
///////////////////////////////////////////////////////////////////

#include <I2C.h>
#include <Arduino.h>


///////////////////////////////////////////////////////////////////
//
// public functions
//
///////////////////////////////////////////////////////////////////
I2C::I2C( const int iDevice, const int iReg, const int iID) {
	m_iDevice		= iDevice ;
	m_iIdRegister	= iReg ;
	m_iID			= iID;
}

///////////////////////////////////////////////////////////////////
//
// IsConnected(void)
//
// NOTE not compatible with error codes
//
// returns: true if I2C device is connected otherwise false if not
//
///////////////////////////////////////////////////////////////////

bool I2C::IsConnected(void) {
	uint8_t ucData;
	if( Read( m_iIdRegister, ucData) ){
		return ( m_iID == ucData ) ? true : false;
	} else {
		return false;
	}
}

///////////////////////////////////////////////////////////////////
//
// protected functions
//
///////////////////////////////////////////////////////////////////
//
// Write(const int iAddress, const int iData)
//
// sends data iData to I2C device iAddress over I2C buss
//
// returns: nothing
//
///////////////////////////////////////////////////////////////////

uint8_t I2C::Write(const int iAddress, const uint8_t ucData) {
	Wire.beginTransmission(m_iDevice);
	Wire.write(iAddress);
	Wire.write(ucData);
	return (Wire.endTransmission()) ? false : true ;
}

///////////////////////////////////////////////////////////////////
//
// Write(const int iAddress, const int iLength, const uint8_t *piData)
//
// sends data iData to I2C device iAddress over I2C buss
//
// returns: nothing
//
///////////////////////////////////////////////////////////////////

uint8_t I2C::Write(const int iAddress, const int iLength, const uint8_t *pucData) {
	Wire.beginTransmission(m_iDevice);
	Wire.write(iAddress);
	for( int i=0; i<iLength; i++ ) {
		Wire.write(*(pucData++) );
	}
	return (Wire.endTransmission()) ? false : true ;
}

///////////////////////////////////////////////////////////////////
//
// Write(const int iAddress, const int iLength, const int *piData)
//
// sends data iData to I2C device iAddress over I2C buss
//
// returns: nothing
//
///////////////////////////////////////////////////////////////////

uint8_t I2C::Write(const int iAddress, const int iLength, const int *piData) {
	Wire.beginTransmission(m_iDevice);
	Wire.write(iAddress);
	for(int i=0; i<iLength; i++) {
		Wire.write(*(piData++));
	}
	return (Wire.endTransmission()) ? false : true ;
}

///////////////////////////////////////////////////////////////////
//
// Read(const int iAddress, const int iLength, uint8_t *pucBuffer)
//
// reads piData from I2C device iAddress and length sucessive 
// addresses over I2C buss into the address pointed to by buffer
//
// returns: true if read is successful, false if not 
//
///////////////////////////////////////////////////////////////////

bool I2C::Read(const int iAddress, const int iLength, uint8_t *pucBuffer) {
	if(Request(iAddress, iLength)) {
		for(int i = 0; i < iLength; i++) {		// read data
			*(pucBuffer++) = Wire.read();			// and save in pointer location
		}											// then inc pointer
		return true;
	} else {
		return false;
	}
}

///////////////////////////////////////////////////////////////////
//
// Read(const int iAddress, uint8_t &ucData)
//
// reads a uint8_t from I2C device iAddress over I2C bus
//
// returns: true if read is successful, false if not  
//
///////////////////////////////////////////////////////////////////

bool I2C::Read(const int iAddress, uint8_t &ucData) {
	if(Request(iAddress, 1)) {
		ucData = Wire.read();			// read data and save in pointer location then inc pointer
		return true;
	} else {
		return false;
	}
}

///////////////////////////////////////////////////////////////////
//
// ReadWORD(const int iAddress, uint16_t &uiData)
//
// reads uint16_t from I2C device iAddress and sucessive address 
// over I2C bus
//
// returns: true if read is successful, false if not 
//
///////////////////////////////////////////////////////////////////

bool I2C::ReadWORD(const int iAddress, uint16_t &uiData) {
	uint8_t ucData[2];
	if(Request(iAddress, 2)) {
		ucData[0] = Wire.read();			// read Hi Byte of data
		ucData[1] = Wire.read();			// read Lo Byte of data
		uiData = (ucData[0] << 8) | ucData[1];
		return true;
	} else {
		return false;
	}
}

///////////////////////////////////////////////////////////////////
//
// Request(const int iAddress, const uint8_t ucLength)
//
// requests iLength bytes from I2C device iAddress in sucessive 
// addresses over I2C buss
//
// returns: true if requested data is available, false if not 
//
///////////////////////////////////////////////////////////////////

bool I2C::Request(const int iAddress, const int iLength) {
	Wire.beginTransmission(m_iDevice);
	Wire.write(iAddress);
	Wire.endTransmission();
	Wire.requestFrom(m_iDevice, iLength);

	if(Wire.available() == iLength) {
		return true;
	} else {
		return false;
	}
}

///////////////////////////////////////////////////////////////////
//
// private functions
//
///////////////////////////////////////////////////////////////////

///////////////////////// end of I2C.cpp ////////////////////
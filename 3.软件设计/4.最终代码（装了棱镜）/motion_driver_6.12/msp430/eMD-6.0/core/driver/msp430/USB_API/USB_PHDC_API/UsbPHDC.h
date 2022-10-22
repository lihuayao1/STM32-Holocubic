//(c)2009 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------+
 |                                                                             |
 |                              Texas Instruments                              |
 |                                                                             |
 |                          MSP430 USB-Example (PHDC Driver)                    |
 |                                                                             |
 +-----------------------------------------------------------------------------+
 |  Source: UsbPHDC.h, File Version 1.00 2009/12/03                             |
 |  Author: RSTO                                                               |
 |                                                                             |
 |  WHO          WHEN         WHAT                                             |
 |  ---          ----------   ------------------------------------------------ |
 |  RSTO         2008/09/03   born                                             |
 |                                                                             |
 +----------------------------------------------------------------------------*/
#ifndef _UsbPHDC_H_
#define _UsbPHDC_H_

#ifdef __cplusplus
extern "C"
{
#endif


#define kUSBPHDC_sendStarted         0x01
#define kUSBPHDC_sendComplete        0x02
#define kUSBPHDC_intfBusyError       0x03
#define kUSBPHDC_receiveStarted      0x04
#define kUSBPHDC_receiveCompleted    0x05
#define kUSBPHDC_receiveInProgress   0x06
#define kUSBPHDC_generalError        0x07
#define kUSBPHDC_busNotAvailable     0x08



/*----------------------------------------------------------------------------
 * These functions can be used in application
 +----------------------------------------------------------------------------*/

/*
 * Sends data over interface intfNum, of size size and starting at address data.
 * Returns:  kUSBPHDC_sendStarted
 *          kUSBPHDC_sendComplete
 *          kUSBPHDC_intfBusyError
 */
BYTE USBPHDC_sendData (const BYTE* data, WORD size, BYTE intfNum);

/*
 * Receives data over interface intfNum, of size size, into memory starting at address data.
 */
BYTE USBPHDC_receiveData (BYTE* data, WORD size, BYTE intfNum);

/*
 * Aborts an active receive operation on interface intfNum.
 * size: the number of bytes that were received and transferred
 * to the data location established for this receive operation.
 */
BYTE USBPHDC_abortReceive (WORD* size, BYTE intfNum);


#define kUSBPHDC_noDataWaiting 1    //returned by USBPHDC_rejectData() if no data pending

/*
 * This function rejects payload data that has been received from the host.
 */
BYTE USBPHDC_rejectData (BYTE intfNum);

/*
 * Aborts an active send operation on interface intfNum.  Returns the number of bytes that were sent prior to the abort, in size.
 */
BYTE USBPHDC_abortSend (WORD* size, BYTE intfNum);


#define kUSBPHDC_waitingForSend      0x01
#define kUSBPHDC_waitingForReceive   0x02
#define kUSBPHDC_dataWaiting         0x04
#define kUSBPHDC_busNotAvailable     0x08
#define kUSB_allPHDCEvents           0xFF

/*
 * This function indicates the status of the interface intfNum.
 * If a send operation is active for this interface,
 * the function also returns the number of bytes that have been transmitted to the host.
 * If a receiver operation is active for this interface, the function also returns
 * the number of bytes that have been received from the host and are waiting at the assigned address.
 *
 * returns kUSBPHDC_waitingForSend (indicates that a call to USBPHDC_SendData()
 * has been made, for which data transfer has not been completed)
 *
 * returns kUSBPHDC_waitingForReceive (indicates that a receive operation
 * has been initiated, but not all data has yet been received)
 *
 * returns kUSBPHDC_dataWaiting (indicates that data has been received
 * from the host, waiting in the USB receive buffers)
 */
BYTE USBPHDC_intfStatus (BYTE intfNum, WORD* bytesSent, WORD* bytesReceived);

/*
 * This function is called when the device receives a Get_Status request
 */
BYTE USBPHDC_GetDataStatusReq(VOID);


/*
 * Returns how many bytes are in the buffer are received and ready to be read.
 */
BYTE USBPHDC_bytesInUSBBuffer (BYTE intfNum);


/*----------------------------------------------------------------------------
 * Event-Handling routines
 +----------------------------------------------------------------------------*/

/*
 * This event indicates that data has been received for interface intfNum, but no data receive operation is underway.
 * returns TRUE to keep CPU awake
 */
BYTE USBPHDC_handleDataReceived (BYTE intfNum);

/*
 * This event indicates that a send operation on interface intfNum has just been completed.
 * returns TRUE to keep CPU awake
 */
BYTE USBPHDC_handleSendCompleted (BYTE intfNum);

/*
 * This event indicates that a receive operation on interface intfNum has just been completed.
 * returns TRUE to keep CPU awake
 */
BYTE USBPHDC_handleReceiveCompleted (BYTE intfNum);


#ifdef __cplusplus
}
#endif
#endif  //_UsbPHDC_H_

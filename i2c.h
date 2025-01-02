/**
  * @brief  Initializes the GPIO pins PB6 and PB7 according to the specified parameters
  * @param  None
  * @retval None
  */
void KM_I2C1_Init(void);


/**
  * @brief  Initializes and configure I2C1 according to the specified parameters
  * @param  None
  * @retval None
  */
void KM_I2C1_Config(void);


/**
  * @brief  Checks if target device is ready for communication.
  * @note   This function is used with Memory devices
  * @param  DevAddress - Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface.
  * @param  Timeout - Timeout duration
  * @retval Status - success(1) or failure(0)
  * @example  KM_I2C_IsDeviceReady((address<<1),200)
  */
int KM_I2C_IsDeviceReady(int DevAddress, int Timeout);


/**
  * @brief  Write an amount of data in blocking mode to a specific memory address
  * @param  DevAddress - Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  MemAddress - Internal memory address
  * @param  MemAddSize - Size of internal memory address
  * @param  pData - Pointer to data buffer
  * @param  len - Amount of data to be sent
  * @retval Status - success(1) or failure(0)
  * @example   ret = KM_I2C_Mem_Write(0x68, 0x00, 0x01, T_Date, 7);
  */
int KM_I2C_Mem_Write(short int DevAddress, short int MemAddress, short int MemAddSize, unsigned char *pData, short int len);


/**
  * @brief  Read an amount of data in blocking mode from a specific memory address
  * @param  DevAddress - Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  MemAddress - Internal memory address
  * @param  MemAddSize - Size of internal memory address
  * @param  Data - Pointer to data buffer
  * @param  Size - Amount of data to be sent
	
	
	
  * @retval Status - success(1) or failure(0)
  * @example   ret = KM_I2C_Mem_Read( 0x68, 0x00, 0x01, rtc_data, 7); 
  */
int KM_I2C_Mem_Read(short int DevAddress, short int MemAddress,short int MemAddSize, unsigned char *Data, short int Size);
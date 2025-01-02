/**
 * @brief Delays for given milliseconds
 * @param n number of milliseconds
 */
void KM_Delay_ms(int n);

/**
 * @brief Initializes SysTick timer
 */

void SYSTICK_INIT();

/**
 * @brief Initializes GPIOB
 */
void GPIOB_INIT();

/**
 * @brief Delays for given milliseconds using polling
 * @param n number of milliseconds
 */
void km_mdelay(int n);

/**
 * @brief Delays for given microseconds using polling
 * @param n number of microseconds
 */
void km_udelay(int n);

/**
 * @brief Delays for given microseconds using interrupt
 * @param n number of microseconds
 */
void km_udelay_it(int n);

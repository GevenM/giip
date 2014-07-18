#include "Flash.h"

#define FLASH_UNLOCK    FCTL3 = FWKEY; FCTL1 = FWKEY + WRT;
#define FLASH_LOCK      FCTL1 = FWKEY; FCTL3 = FWKEY +  LOCK;


/**********************************************************************//**
 * @brief  Erases a single segment of memory containing the address FarPtr.
 *
 * @param  FarPtr The address location within the segment of memory to be
 *                erased.
 *
 * @return none
 **************************************************************************/
void flashEraseSegment(unsigned long FarPtr)
{
  unsigned long *Flash_ptr;                         // local Flash pointer

  Flash_ptr = (unsigned long *) FarPtr;             // Initialize Flash pointer

  FCTL3 = FWKEY;
  FCTL1 = FWKEY + ERASE;

  *Flash_ptr = 0;                         // dummy write to start erase

  while (FCTL3 & BUSY );
  FCTL1 = FWKEY;
  FCTL3 = FWKEY +  LOCK;
}


void LockFlash(){
	FLASH_LOCK;
}

void UnlockFlash(){
	FLASH_UNLOCK;
}

/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"
#include "diskio.h"		/* FatFs lower layer API */
#include "sdio_sd.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
	//int result;

	switch (pdrv) {
	case DEV_RAM :
		//result = RAM_disk_status();
		// translate the reslut code here
		//return stat;
        break;
    
	case DEV_MMC :
		//result = MMC_disk_status();
		// translate the reslut code here
		//return stat;
        stat &= ~STA_NOINIT;
        break;

	case DEV_USB :
		//result = USB_disk_status();
		// translate the reslut code here
		//return stat;
        break;
    
    default:
        break;
	}
    
	return stat;
}

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
	//int result;

	switch (pdrv) {
	case DEV_RAM :
		//result = RAM_disk_initialize();
		// translate the reslut code here
		//return stat;
        break;

	case DEV_MMC :
		//result = MMC_disk_initialize();
		// translate the reslut code here
		//return stat;
    	if(SD_Init()==SD_OK)
        {
            stat &= ~STA_NOINIT;
		}
        break;

	case DEV_USB :
		//result = USB_disk_initialize();
		// translate the reslut code here
		//return stat;
        break;

    default:
        break;    
	}
    
	return stat;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res = RES_PARERR;
	SD_Error result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here
		//result = RAM_disk_read(buff, sector, count);
		// translate the reslut code here
		//return res;
        break;
    
	case DEV_MMC :
		// translate the arguments here
		//result = MMC_disk_read(buff, sector, count);
		// translate the reslut code here
		//return res;
        result = SD_ReadDisk((uint8_t *)buff, sector, count);
    	if (result == SD_OK)
		{
            res = RES_OK;
		} 
		break;

	case DEV_USB :
		// translate the arguments here
		//result = USB_disk_read(buff, sector, count);
		// translate the reslut code here
		//return res;
        break;

    default:
        break;   
	}

	return res;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res =  RES_PARERR;
	SD_Error result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here
		//result = RAM_disk_write(buff, sector, count);
		// translate the reslut code here
		//return res;
        break;
    
	case DEV_MMC :
		// translate the arguments here
		//result = MMC_disk_write(buff, sector, count);
		// translate the reslut code here
		//return res;
        result = SD_WriteDisk((uint8_t *)buff, sector, count);
        if (result == SD_OK)
        {
            res = RES_OK;
        } 
        break;

	case DEV_USB :
		// translate the arguments here
		//result = USB_disk_write(buff, sector, count);
		// translate the reslut code here
		//return res;
        break;

    default:
        break;      
	}

	return res;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res =  RES_PARERR;
	//int result;

	switch (pdrv) 
    {
	    case DEV_RAM :
	    	// Process of the command for the RAM drive
	    	//return res;
            break;
        
	    case DEV_MMC :
	    	// Process of the command for the MMC/SD card
	    	//return res;
        	switch(cmd)
	    	{
	    		case CTRL_SYNC: 
                    res = RES_OK; //刷新磁盘
	    			break;
                
	    		case GET_SECTOR_SIZE: 
	    			 *(DWORD*)buff = 512; //得到媒体大小
                     res = RES_OK;
                     break;
                
	    		case GET_BLOCK_SIZE:
	    			 *(DWORD*)buff = SDCardInfo.CardBlockSize;  //块大小
                     res = RES_OK;
	    		     break;
                
                case GET_SECTOR_COUNT:
	    			 *(DWORD*)buff = SDCardInfo.CardCapacity/512;  ///扇区数量
	    		     res = RES_OK;
	    			 break;
                
	    		default: 
                    break;
	    	}
            break;
                
	    case DEV_USB :
	    	// Process of the command the USB drive
	    	//return res;
            break;
        
        default:
            break;   
	}

	return res;
}

/*------------------------------------------------------------------
*  文件时间标签获取函数
*-------------------------------------------------------------------*/
DWORD get_fattime(void)
{
	#if  USE_RTC == 1
		
	#else 	
	     return 0;	
	#endif
}


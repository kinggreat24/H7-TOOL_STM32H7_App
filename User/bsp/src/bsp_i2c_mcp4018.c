/*
*********************************************************************************************************
*
*    模块名称 : 数字电位器MCP4018驱动模块
*    文件名称 : bsp_i2c_mcp4018.c
*    版    本 : V1.0
*    说    明 : 实现数字电位器MCP4018读写操作。
*
*    修改记录 :
*        版本号  日期        作者     说明
*        V1.0    2018-12-08  armfly  正式发布
*
*    Copyright (C), 2018-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"

static void MCP4018_SoftReset(void);

/*
*********************************************************************************************************
*    函 数 名: bsp_InitMCP4018
*    功能说明: 初始化MCP4018
*    形    参: 无
*    返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitMCP4018(void)
{
    MCP4018_SoftReset();
}

/*
*********************************************************************************************************
*    函 数 名: MCP4018_SoftReset
*    功能说明: 软件复位
*    形    参: 无
*    返 回 值: 无
*********************************************************************************************************
*/
static void MCP4018_SoftReset(void)
{
    i2c_Start();
    i2c_SendByte(0xFF);
    i2c_Start();
    i2c_Stop();
}

/*
*********************************************************************************************************
*    函 数 名: MCP4018_WriteCmd
*    功能说明: 向芯片发送1字节长度的操作码. 0-127
*    形    参: _ucOpecode : 0-127档位
*    返 回 值: 无
*********************************************************************************************************
*/
void MCP4018_WriteData(uint8_t _ucOpecode)
{
    i2c_Start(); /* 总线开始信号 */

    i2c_SendByte(MCP4018_SLAVE_ADDRESS); /* 发送设备地址+写信号 */
    i2c_WaitAck();

    i2c_SendByte(_ucOpecode); /* 1字节操作码 */
    i2c_WaitAck();

    i2c_Stop(); /* 总线停止信号 */
}

/*
*********************************************************************************************************
*    函 数 名: MCP4018_ReadData
*    功能说明: 读取MCP4018当前档位
*    形    参: 无
*    返 回 值: 原始的测量数据 ,结果未转换
*********************************************************************************************************
*/
uint8_t MCP4018_ReadData(void)
{
    uint8_t ucData1;

    i2c_Start();                                                         /* 总线开始信号 */
    i2c_SendByte(MCP4018_SLAVE_ADDRESS + 1); /* 发送设备地址+读信号 */
    i2c_WaitAck();

    ucData1 = i2c_ReadByte(); /* 读出高字节数据 */
    i2c_NAck();
    i2c_Stop(); /* 总线停止信号 */

    return ucData1;
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
#ifndef SIF_H
#define SIF_H
#include "main.h"
#include "gd32f10x_gpio.h"
#include "gd32f10x.h"
#include "systick.h"
#include "gd32f10x_libopt.h"

void Sif_off(void);
void Sif_on(void);
void Sif_Init(void);
void sif_send_data_handle(uint8_t state);
void Sum_Handle(void);
void displayReverse(void);
void displayParking(void);
void EcuandElectricalandHandle(void);
void checkGearlevel(void);
void displayReady(void);
void displaySpeed(void);
void displaySoc(void);
void displayVolts(void);
void displayInit(void);
void SetDashBoardData(uint8_t data, uint8_t state);
void timer1_config(void);

enum
{
    LIST_check,
    LIST_handle,
    LIST_Ecu,
    LIST_electrical,
    LIST_speed,
    LIST_parking,
    LIST_reverse,
    LIST_gearlevel,
    LIST_soc,
    LIST_volts,
};

typedef struct Dashboard_parameters
{
    uint8_t check;      // 刹车
    uint8_t handle;     // 转把故障
    uint8_t Ecu;        // Ecu故障
    uint8_t electrical; // 电机故障
    uint8_t speed;      // 速度
    uint8_t parking;    // P挡
    uint8_t reverse;    // R挡
    uint8_t gearlevel;  // 挡位
    uint8_t soc;        // soc
    uint8_t volts;      // 电压

} Da;

enum
{
    SYNC_SIGNAL,
    SEND_DATA,
    SEND_DATA_COMPLET
};
#endif
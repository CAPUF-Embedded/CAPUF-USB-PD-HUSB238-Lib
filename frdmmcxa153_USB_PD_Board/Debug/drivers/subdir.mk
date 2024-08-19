################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Capuf_HUSB238.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpi2c.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_reset.c \
../drivers/fsl_spc.c \
../drivers/i2c_common.c 

C_DEPS += \
./drivers/Capuf_HUSB238.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpi2c.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_reset.d \
./drivers/fsl_spc.d \
./drivers/i2c_common.d 

OBJS += \
./drivers/Capuf_HUSB238.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpi2c.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_reset.o \
./drivers/fsl_spc.o \
./drivers/i2c_common.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MCXA153VLH -DCPU_MCXA153VLH_cm33_nodsp -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\mcuxpressoIDE\workspace\frdmmcxa153_USB_PD_Board\source" -I"D:\mcuxpressoIDE\workspace\frdmmcxa153_USB_PD_Board\drivers" -I"D:\mcuxpressoIDE\workspace\frdmmcxa153_USB_PD_Board\device" -I"D:\mcuxpressoIDE\workspace\frdmmcxa153_USB_PD_Board\utilities" -I"D:\mcuxpressoIDE\workspace\frdmmcxa153_USB_PD_Board\component\uart" -I"D:\mcuxpressoIDE\workspace\frdmmcxa153_USB_PD_Board\component\lists" -I"D:\mcuxpressoIDE\workspace\frdmmcxa153_USB_PD_Board\CMSIS" -I"D:\mcuxpressoIDE\workspace\frdmmcxa153_USB_PD_Board\board" -I"D:\mcuxpressoIDE\workspace\frdmmcxa153_USB_PD_Board\frdmmcxa153\driver_examples\lpi2c\polling_b2b\master" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33+nodsp -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/Capuf_HUSB238.d ./drivers/Capuf_HUSB238.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpi2c.d ./drivers/fsl_lpi2c.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_reset.d ./drivers/fsl_reset.o ./drivers/fsl_spc.d ./drivers/fsl_spc.o ./drivers/i2c_common.d ./drivers/i2c_common.o

.PHONY: clean-drivers


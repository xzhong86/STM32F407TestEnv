#ifndef  __INIT_GPIO_H__
#define  __INIT_GPIO_H__

#define Init_GPIO_a6(P,N,MODE,PULL,SPEED,ALT) do {              \
                GPIO_InitStruct.Pin = GPIO_PIN_ ## N;           \
                GPIO_InitStruct.Mode = GPIO_MODE_ ## MODE;      \
                GPIO_InitStruct.Pull = GPIO_ ## PULL;           \
                GPIO_InitStruct.Speed = GPIO_SPEED_ ## SPEED;   \
                GPIO_InitStruct.Alternate = GPIO_ ## ALT;       \
                HAL_GPIO_Init(GPIO ## P, &GPIO_InitStruct);     \
        } while (0)
        
#define Init_GPIO_a4(P,N,MODE,PULL) Init_GPIO_a5(P, N, MODE, PULL, 0, 0) 

#endif

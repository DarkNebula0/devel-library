#pragma once
#define SIZEOF_ARRAY(x)                (sizeof(x) / sizeof(x[0]))

#define CLEAR_MEMORY(x)                memset(x, 0, sizeof(x))

#define SECONDS(x)                    (x * 1000)
#define MINUTES(x)                    SECONDS(x * 60)
#define HOURS(x)                    MINUTES(x * 60)
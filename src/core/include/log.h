//
// Created by 東口拓也 on 2022/06/25.
//

#ifndef ROLL_SHOOTING_LOG_H
#define ROLL_SHOOTING_LOG_H

#ifdef ENABLE_LOG
#define LOG(...) _pd->system->logToConsole(__VA_ARGS__);
#else
#define LOG(...) ;
#endif

#endif //ROLL_SHOOTING_LOG_H

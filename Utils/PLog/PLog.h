#ifndef __ITEM_LOG_DEBUG__
#define __ITEM_LOG_DEBUG__

typedef struct item_log_s          item_log_t; 

//日志级别，由低到高，1-4
#define ITEM_LOG_ERR               1
#define ITEM_LOG_WARN              2
#define ITEM_LOG_INFO              4
#define ITEM_LOG_DEBUG             8


#define    ITEM_LOG_TYPE_OUTPUT    1    // 日志输出在屏幕
#define    ITEM_LOG_TYPE_FILE      2    // 日志输出在文件


/*
 * @brief 		读取打印输出配置文件
 * @details		读取打印输出配置文件
 * @param[in]	cfgfile		需要读取配置文件的文件名
 * @param[out]	level		打印输出的输出级别
 * @param[out]	model		打印出书的输出模式
 * @param[in]	file		当输出模式有以文件输出，该参数生效
 * @param[in]	len			file提供的最大长度
 * @return		成功返回0，失败返回-1
 */
int Read_Log_File(char *cfgfile, int *level, int *model, char *file, size_t len);

/*
 * @brief 		初始化
 * @details		初始化
 * @param[in]	level		打印输出的输出级别
 * @param[in]	type		打印出书的输出模式
 * @param[in]	name		打印输出名字标识
 * @param[in]	file		当输出模式有以文件输出，该参数生效
 * @return		成功返回item_log_t结构的结构体句柄，失败返回NULL
 */
item_log_t *PLog_init(int level, int type, const char *name, const char *file);

/*
 * @brief 		按照不同级别 不同模式打印输出
 * @details		按照不同级别 不同模式打印输出
 * @param[in]	level		打印输出的输出级别
 * @param[in]	log_info	初始化时得到的item_log_t结构的结构体句柄
 * @return		无
 */
void _PLog(int level, const item_log_t *log_info, const char *fmt, ...);
#define PLog_Info(level, log_info, fmt, ...)        																\
    _PLog(level, log_info, "[%s | %s() %d] "fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define PLog(level, log_info, fmt, ...)																				\
	if (level & ITEM_LOG_ERR) { PLog_Info(level, log_info, "[ITEM_LOG_ERR]"fmt, ##__VA_ARGS__); }					\
	else if (level & ITEM_LOG_WARN) { PLog_Info(level, log_info, "[ITEM_LOG_WARN]"fmt, ##__VA_ARGS__); }			\
	else if (level & ITEM_LOG_INFO) { PLog_Info(level, log_info, "[ITEM_LOG_INFO]"fmt, ##__VA_ARGS__); }			\
	else if (level & ITEM_LOG_DEBUG) { PLog_Info(level, log_info, "[ITEM_LOG_DEBUG]"fmt, ##__VA_ARGS__); }			\
	else { PLog_Info(level, log_info, "[NONE]"fmt, ##__VA_ARGS__); }

/*
 * @brief 		关闭打印输出句柄
 * @details		关闭打印输出句柄
 * @param[in]	level		打印输出的输出级别
 * @param[in]	log_info	初始化时得到的item_log_t结构的结构体指针
 * @return		无
 */
void PLog_close(item_log_t *log_info);

#endif

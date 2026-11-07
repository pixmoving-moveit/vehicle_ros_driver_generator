#ifndef PIX_DRIVER_VERSION__HPP_
#define PIX_DRIVER_VERSION__HPP_

// 定义版本号
#define VERSION_MAJOR %(version_major)s 
#define VERSION_MINOR %(version_minor)s  

// 使用组合版本号
#define PIX_CHASSIS_VERSION (VERSION_MAJOR * 10 + VERSION_MINOR)

#endif // PIX_DRIVER_VERSION__HPP_


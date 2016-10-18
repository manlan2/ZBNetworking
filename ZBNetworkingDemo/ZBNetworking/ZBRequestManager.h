//
//  ZBRequestManager.h
//  ZBURLSessionManager
//
//  Created by NQ UEC on 16/5/13.
//  Copyright © 2016年 Suzhibin. All rights reserved.
//  ( https://github.com/Suzhibin )
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//




#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class ZBURLSessionManager;

#define DEBUG_LOG 0

#if(DEBUG_LOG == 1)
# define ZBLog(fmt, ...) NSLog((@"[函数名:%s]" " [第 %d 行]\n" fmt),  __FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
# define ZBLog(...);
#endif

//请求管理类： 需要将request对象的生命周期通过ZBRequestManager来维护
@interface ZBRequestManager : NSObject


@property ( nonatomic, strong) ZBURLSessionManager *manager;

/**
 *  用于维护多个request对象
 */
@property ( nonatomic, strong) NSMutableDictionary *requestDic;

/**
 *  用于维护多个webRequest对象
 */
@property ( nonatomic, strong) NSMutableDictionary *webRequestDic;

/**
 *  离线下载栏目url容器
 */
@property (nonatomic,strong) NSMutableArray *channelUrlArray;

/**
 *  离线下载栏目名字容器
 */
@property (nonatomic,strong) NSMutableArray *channelNameArray;

/**
 *  用于维护 请求头的request对象
 */
@property ( nonatomic, strong) NSMutableDictionary *mutableHTTPRequestHeaders;

/**
 *  用于判断是否有请求头
 */
@property (nonatomic,copy) NSString *value;

/**
    返回单例对象
 */
+(ZBRequestManager *)shareManager;

/**
 *  添加请求头
 *
 *  @param value
 *  @param field
 */
- (void)setValue:(NSString *)value forHeaderField:(NSString *)field;

/**
 *  
 *  @param key request 对象
 *
 *  @return
 */
- (NSString *)objectHeaderForKey:(NSString *)key;

/**
 *  删除请求头的key
 *
 *  @param key
 */
- (void)removeHeaderForkey:(NSString *)key;

/**
 离线下载 判断栏目url 或 其他参数 是否已添加到请求容器

 @param key   请求地址 或 其他参数
 @param isUrl 是否是url

 @return 1:0
 */
- (BOOL)isAddForKey:(NSString *)key isUrl:(BOOL)isUrl;

/**
 离线下载 将url 或 其他参数 添加到请求列队

 @param key   请求地址 或 其他参数
 @param isUrl 是否是url
 */
- (void)addObjectWithForKey:(NSString *)key isUrl:(BOOL)isUrl;

/**
 离线下载 将url 或 其他参数 从请求列队删除

 @param key   请求地址 或 其他参数
 @param isUrl 是否是url
 */
- (void)removeObjectWithForkey:(NSString *)key isUrl:(BOOL)isUrl;

/**
 *
 *  @param obj request 对象
 *  @param key
 */
- (void)setRequestObject:(id)obj forkey:(NSString *)key;

/**
 *
 *  @param key 
 */
- (void)removeRequestForkey:(NSString *)key;

/**
 *
 *  根据key 将request的delegate置空
 *
 *  @return  请求的协议地址
 */
//- (void)clearDelegateForKey:(NSString *)key;

- (void)setWebRequestObject:(id)obj forkey:(NSString *)key;

- (void)removeWebRequestForkey:(NSString *)key;

@end










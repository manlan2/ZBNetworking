//
//  ZBAFNetworkManager.h
//  ZBNetworkingDemo
//
//  Created by NQ UEC on 17/1/10.
//  Copyright © 2017年 Suzhibin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AFNetworking.h>
#import "ZBURLRequest.h"

typedef void (^requestConfig)(ZBURLRequest *request);

typedef void (^requestSuccess)(id responseObj,apiType type);

typedef void (^requestFailed)(NSError *error);

typedef void (^progressBlock)(NSProgress * progress);

@interface ZBAFNetworkManager : NSObject
@property (nonatomic,strong) ZBURLRequest *request;
/**
 *  用于标识不同类型的方法
 */
@property (nonatomic,assign) MethodType methodType;

+ (ZBAFNetworkManager *)sharedHelper;
/**
 *  get请求
 *
 *  @param config           请求配置  Block
 *  @param success         请求成功的 Block
 *  @param failed           请求失败的 Block
 */
+ (ZBAFNetworkManager *)requestWithConfig:(requestConfig)config  success:(requestSuccess)success failed:(requestFailed)failed;
/**
 *  get请求
 *
 *  @param config           请求配置  Block
 *  @param progressBlock    请求进度  Block
 *  @param success         请求成功的 Block
 *  @param failed           请求失败的 Block
 */
+ (ZBAFNetworkManager *)requestWithConfig:(requestConfig)config progress:(progressBlock)progressBlock  success:(requestSuccess)success failedBlock:(requestFailed)failed;

/**
 *  get请求
 *
 *  @param urlString        请求的协议地址
 *  @param parameters       请求所用的参数
 *  @param success         请求成功的 Block
 *  @param failed           请求失败的 Block
 */
- (void)GET:(NSString *)urlString parameters:(id)parameters success:(requestSuccess)success failed:(requestFailed)failed;

/**
 *  get请求
 *
 *  @param urlString        请求的协议地址
 *  @param parameters       请求所用的参数
 *  @param progressBlock    请求进度  Block
 *  @param success         请求成功的 Block
 *  @param failed           请求失败的 Block
 */
- (void)GET:(NSString *)urlString parameters:(id)parameters progress:(progressBlock)progressBlock success:(requestSuccess)success failed:(requestFailed)failed;

/**
 *  get请求
 *
 *  @param urlString        请求的协议地址
 *  @param parameters       请求所用的参数
 *  @param type             请求类型
 *  @param progressBlock    请求进度  Block
 *  @param success         请求成功的 Block
 *  @param failed           请求失败的 Block
 */
- (void)GET:(NSString *)urlString parameters:(id)parameters apiType:(apiType)type progress:(progressBlock)progressBlock success:(requestSuccess)success failed:(requestFailed)failed;

/**
 *  post 请求
 *
 *  @param urlString    请求的协议地址
 *  @param parameters   请求所用的参数
 *  @param success     请求成功的 Block
 *  @param failed       请求失败的 Block
 */
- (void)POST:(NSString *)urlString parameters:(id)parameters success:(requestSuccess)success failed:(requestFailed)failed;

/**
 *  post 请求
 *
 *  @param urlString        请求的协议地址
 *  @param parameters       请求所用的参数
 *  @param progressBlock    请求进度  Block
 *  @param success         请求成功的 Block
 *  @param failed           请求失败的 Block
 */
- (void)POST:(NSString *)urlString parameters:(id)parameters progress:(progressBlock)progressBlock success:(requestSuccess)success failed:(requestFailed)failed;

/**
 *  离线下载 请求方法
 *
 *  @param downloadArray    请求列队
 *  @param type             用于直接区分不同的request对象 离线下载 为 ZBRequestTypeOffline
 *  @param success         请求成功的 Block
 *  @param failed           请求失败的 Block
 */
- (void)offlineDownload:(NSMutableArray *)downloadArray apiType:(apiType)type success:(requestSuccess)success failed:(requestFailed)failed;

/**
 *   请求会话管理,取消请求任务
 *  Invalidates the managed session, optionally canceling pending tasks.
 *
 *  @param cancelPendingTasks Whether or not to cancel pending tasks.
 */
- (void)requestToCancel:(BOOL)cancelPendingTask;

/**
 *  网络状态监测
 */
- (NSInteger)startNetWorkMonitoring;

@end